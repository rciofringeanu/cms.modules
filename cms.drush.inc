<?php

/**
 * Implements hook_drush_command();
 *
 * Generic drush commands for CMS websites
 *
 * @author Bogdan Tanase
 *         Dragos Dumitrescu
 *
 * @return   array   $items
 */
function cms_drush_command() {
    $items['set_encrypted_variable'] = array(
        'description' => 'Encrypt LDAP password',
        'examples' => array(
            'drush set_encrypted_variable <variable_name> <value_to_ecrypt≥' => 'Encrypt LDAP password'
        ),
        'arguments' => array(
            'variable_name' => 'Required',
            'value_to_encrypt' => 'Required',
        ),
        'required-arguments' => TRUE,
        'aliases' => array('sev')
    );

    $items['set_logo'] = array(
        'description' => 'Set website logo',
    );

    $items['update_meetings_documents_relations'] = array(
        'description' => 'Fix the lost relations between meetings and documents refs #1586',
        'arguments' => array(
            'source_file' => 'Required',
        ),
        'examples' => array(
            'drush update_meetings_documents_relations cms/meeting/meetings_documents.json' => 'Update the meeting documents relation from file'
        ),
        'aliases' => array('umdr'),
    );

    return $items;
}

/**
 * Callback function for set_encrypted_variable drush command.
 *
 * Using Drupal hash salt set an encrypted value for a specified variable
 *
 * @author  Bogdan Tanase
 *
 * @param   string   $variable_name
 * @param   string   $value_to_encrypt
 */
function drush_cms_set_encrypted_variable($variable_name, $value_to_encrypt) {
    variable_del($variable_name);

    // PHP mcrypt_ecb is not accepting strings longer the 25 chars
    $hash = substr(drupal_get_hash_salt(), 0, 24);
    $td = mcrypt_module_open('tripledes', '', 'ecb', '');
    mcrypt_generic_init($td, $hash, IV);
    $encrypted_data = mcrypt_generic($td, $value_to_encrypt);
    mcrypt_generic_deinit($td);
    mcrypt_module_close($td);

    variable_set($variable_name, $encrypted_data);

}

/**
 * Callback function for set_logo drush command
 *
 * Upload and set website logo
 *
 * @author   Bogdan Tanase
 */
function drush_cms_set_logo() {
    global $theme_key;

    $current_profile = CMSUtils::get_current_profile();
    $file_path = drupal_get_path('module', 'cms_initial_data') . _DS_ . $current_profile . _DS_ . 'files' . _DS_ . 'logo.png';

    $file_object = (object) array(
        'uid' => 1,
        'uri' => $file_path,
        'filemime' => file_get_mimetype($file_path),
        'status' => 1,
    );

    $file = file_copy($file_object, 'public://');

    if ($file) {
        $file->display = 1;
        $logo_path = file_create_url($file->uri);
        $theme_name = 'cms_theme';
        $var_name = 'theme_' . $theme_key . '_settings';
        $settings = variable_get($var_name, array());
        $settings['logo_path'] = $logo_path;
        variable_set($var_name, $settings);
    }
}

/**
 * Callback function for update_meetings_documents_relations;
 *
 * Fix relations between meetings and documents
 *
 * @author  Dragos Dumitrescu
 *
 * @param   string   $file_path
 *    Path to JSON file where are stored relations between meetings and documents
 */
function drush_cms_update_meetings_documents_relations($file_path) {
    $JSON = CMSUtils::read_json($file_path, TRUE);
    $total_meetings = count($JSON);
    CMSUtils::println('Found %s meetings', $total_meetings);

    $md_field = 'field_meeting_document';
    $dm_field = 'field_document_meeting';
    $total_docs_found = 0;
    $total_docs_added = 0;

    foreach ($JSON as $idx => $row) {
        CMSUtils::println('Checking Meeting: "%s"',$row['title']);
        if (!isset($row['uuid']) || empty($row['uuid'])) {
            CMSUtils::println('Meeting "%s" has no uuid', $row['title']);
            continue;
        }
        if (!isset($row[$md_field]) || empty($row[$md_field])) {
            CMSUtils::println('Meeting "%s" has no documents in the import file', $row['title']);
            continue;
        }
        //Get meeting node entity
        $meeting = entity_uuid_load('node', array($row['uuid']));
        reset($meeting);
        $meeting = current($meeting);
        // now we have meeting with fields target_id with uuid not nid (this is how entity_uuid_load works)

        if (!isset($meeting->nid)) {
            CMSUtils::println('Meeting "%s" failed to load by uuid',$row['title']);
            continue;
        }

        CMSUtils::println('   --> "%s" Documents found in file', count($row[$md_field]));

        //Add the documents to meeting
        if (property_exists($meeting, $md_field)) {
            $items = array();
            $uuids = array();

            if (is_array($meeting->{$md_field}) && array_key_exists($meeting->language, $meeting->{$md_field})) {
                $items = $meeting->{$md_field}[$meeting->language];
            }
            //get current docs uuids - entity_uuid_load puts target_id as uuid not nid
            if ($items) {
                foreach ($items as $item) {
                    $uuids[] = $item['target_id'];
                }
            }
            CMSUtils::println('   --> The meeting already has "%s" documents', count($uuids));

            //load meeting with node load because the one loaded entity_uuid isn't good for save
            $node = node_load($meeting->nid);

            $docs_found = count($row[$md_field]);
            $total_docs_found += $docs_found;
            $docs_added = 0;
            // check docs if linked already in meeting
            foreach ($row[$md_field] as $doc_uuid) {
                //if currently not linked
                if (!in_array($doc_uuid, $uuids)) {
                    $doc = entity_uuid_load('node', array($doc_uuid));
                    reset($doc);
                    $doc = current($doc);
                    if (empty($doc)) {
                        CMSUtils::println('   --> Document "%s" not found', $doc_uuid);
                        continue;
                    }
                    $node->{$md_field}[$node->language][count($items)+$docs_added]['target_id'] = $doc->nid;
                    $node->content_relation = TRUE;
                    $docs_added++;
                }
            }
            if ($docs_added > 0) {
                node_save($node);
            }
            CMSUtils::println('   --> "%s" Documents added to the meeting', $docs_added);
            $total_docs_added += $docs_added;
        }
        CMSUtils::println('Summary: "%s" Documents added to the meeting from %s found for %s Meetings ', $total_docs_added, $total_docs_found, $total_meetings);
    }
    return;
}
