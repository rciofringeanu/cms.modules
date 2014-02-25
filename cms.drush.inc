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


    $items['attach_meeting_documents_refs_1586'] = array(
        'description' => 'Attach meetings to documents (after module breakdown), see #1586'
    );


    $items['fix_decisions_publish_date_refs_1763'] = array(
        'description' => 'Fix the publish date for decisions/resolutions/recommendation, by setting it to corresponding COP/MOP date'
    );

    $items['set_resolutions_adopted_1773'] = array(
        'description' => 'Set the Resolutions status to "Adopted", if no status is set'
    );

    $items['sync_instruments_uuid'] = array(
        'description' => 'Sync uuid of instruments with CMS uuid from given file refs #1730',
        'arguments' => array(
            'source_file' => 'Required',
        ),
        'examples' => array(
            'drush sync_instruments_uuid cms/cms.initial_data/sync_instruments.json' => 'Updates the UUID and title of a instrument as in file'
        ),
    );

    $items['sync_countries_uuid'] = array(
        'description' => 'Sync countries uuid with CMS countries uuid form given file refs #1731',
        'arguments' => array(
            'source_file' => 'Required',
        ),
        'examples' => array(
            'drush sync_countries_uuid cms/cms.initial_data/cms/countries.json' => 'Updates the UUID of country as in file'
        ),

    );

    $items['set_national_reports_country_1776'] = array(
        'description' => 'Set the country field from "Submitted by" field'
    );

    $items['move_pub_date_to_partial_date_refs_1821'] = array(
        'description' => 'Move publication date to partial date field refs #1821. SET THE FIELD FIRST!'
    );

    $items['add_basic_page'] = array(
        'description' => 'Basic Page'
    );

    $items['fix_species_instruments_1730'] = array(
        'description' => 'Restore from json the species instruments relations #1730.',
        'examples' => array(
            'drush fix_species_instruments_1730 /path/to/species.json /path/to/instrument_species_mapped.json ' => 'Restore species instrument relations')
    );
    $items['fix_paths_sef'] = array(
        'description' => 'Fix paths of existing content to use SEF config from pathauto module',
        'options' => array ('type' => 'content type'),
        'examples' => array(
            'drush fix_paths_sef' => 'Restore species instrument relations',
            'drush fix_paths_sef --type=species,country' => 'Restore species instrument relations')
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


/**
 * This drush command reads the cms_initial_data/cms/document/meeting_documents.json
 * and attaches the missing resolutions and other documents to the meettings. For CMS
 */
function drush_cms_attach_meeting_documents_refs_1586() {
    $f = drupal_get_path('module', 'cms_initial_data') . '/' . CMSUtils::get_current_profile() . '/document/meeting_documents.json';
    $string = file_get_contents($f);
    $rows = json_decode($string);
    $count = 0;
    echo "Please wait, Windows is loading for the first time ... \n";
    foreach($rows as $row) {
        $ob = entity_uuid_load('node', array($row->uuid), array(), TRUE);
        $ob = current($ob);
        $ob = node_load($ob->nid);
        if(empty($ob)) {
            echo "MISSING: {$row->uuid}:{$row->title}\n";
        } else {
            $save = FALSE;
            $docs = CMSUtils::get_node_list_value($ob, 'field_meeting_document', 'target_id');
            foreach($row->docs as $doc) {
                if(!in_array($doc->uuid, $docs)) {
                    $docOb = entity_uuid_load('node', array($doc->uuid), array(), TRUE);
                    $docOb = current($docOb);
                    $docOb = node_load($docOb->nid);
                    if(!empty($docOb)) {
                        $nids = CMSUtils::get_node_list_value($ob, 'field_meeting_document', 'target_id');
                        if(!in_array($docOb->nid, $nids)) {
                            echo "Missing relation\n";
                            echo "{$ob->uuid} - {$ob->title}\n";
                            echo "{$docOb->nid}: {$docOb->title}\n";
                            $ob->field_meeting_document['und'][] = array('target_id' => $docOb->nid);
                            $count++;
                            $save = TRUE;
                            echo "-------------------------------------------------\n";
                        }
                    } else {
                        echo sprintf("MISSING DOCUMENT");
                    }
                }
            }
            if($save) {
                node_save($ob);
            }
        }
    }
    echo "Updated: $count\n";
}

/**
 * This drush task gets all the decisions without the published date field
 * and sets it do the end/start date of the first related COP/MOP meeting
 */
function drush_cms_fix_decisions_publish_date_refs_1763() {
    $types = array('resolution', 'recommendation', 'decision');
    $c = 0;
    $q = new EntityFieldQuery();
    $docs = $q->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'document')
        ->execute();
    if ($docs) {
        $docs = node_load_multiple(array_keys($docs['node']));
        foreach($docs as $nid => $doc) {
            if(!empty($doc->field_document_type['und'][0]['tid'])) {
                $tid = $doc->field_document_type['und'][0]['tid'];
                $type = taxonomy_term_load($tid);
                $type = strtolower($type->name);
                if(in_array($type, $types)) {
                    $publish_date = $doc->field_document_publish_date['und'][0];
                    if(empty($publish_date['value'])) {
                        $c++;
                        echo "Fixing publish date for {$doc->title}\n";
                        $d = CMSUtils::get_document_publish_date_from_meeting($doc, 'field_document_meeting');
                        if(!empty($d)) {
                            $doc->field_document_publish_date['und'] = array($d);
                            node_save($doc);
                        } else {
                            drupal_set_message("Failed to set publish date for {$nid}", 'warning');
                        }
                    }
                }
            } else {
                drupal_set_message("Empty field_document_type for nid: {$nid}", 'warning');
            }
        }

        echo "Document(s) fixed: $c\n";
    }else {
        echo "No documents found\n";
    }
}

/**
 * Set the Resolutions status to "Adopted", if no status is set
 */
function drush_cms_set_resolutions_adopted_1773() {
    $q = new EntityFieldQuery();
    $docs = $q->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'document')
        ->execute();
    $docs = node_load_multiple(array_keys($docs['node']));
    $t = taxonomy_get_term_by_name('Adopted', 'document_status');
    $c = 0;
    if(!empty($t)) {
        $t = current($t);
        $tid = $t->tid;
        $field_info = field_info_field('field_document_status');
        foreach($docs as $nid => $doc) {
            $type = taxonomy_term_load($doc->field_document_type['und'][0]['tid']);
            $type = strtolower($type->name);
            if("resolution" == $type) {
                $lang = $field_info['translatable'] ? $doc->language : LANGUAGE_NONE;
                $status = field_get_items('node', $doc, 'field_document_status', $lang);
                if(!$status) {
                    $doc->field_document_status[$lang][] = array('tid' => $tid);
                    node_save($doc);
                    echo "Setting document to Adopted: $nid\n";
                    $c++;
                }
            }
        }
    } else {
        drupal_set_message("Cannot find term 'Adopted' in taxonomy 'document_status'", 'error');
    }
    echo "Done. Resolutions affected: $c\n";
}

/**
 * Updates legal instrument UUID as in cms_uuid from json file
 * Used for sync uuid between profiles
 *
 * @param $file_path json file with instrument (uuid and titles from each profile)
 *                        searches the instrument by 'profile'_title (aewa_title) key in json
 */


function drush_cms_sync_instruments_uuid($file_path) {
    $JSON = CMSUtils::read_json($file_path, TRUE);
    $total_instruments = count($JSON);
    CMSUtils::println('Found %s instruments', $total_instruments);

    $current_profile = CMSUtils::get_current_profile();
    $count_saves = 0;
    foreach ($JSON as $row) {
        $modified = FALSE;
        $curr_instrument_title = $row[$current_profile.'_title'];
        $nodes = entity_uuid_load('node',array($row['cms_uuid']));
        //if uuid already synced
        if (!empty($nodes)) {
            $node = current($nodes);
            if ($node->title != $row['title']) {
                CMSUtils::println('Instrument %s has different title than it\'s correspondent in CMS %s',$node->title, $row['cms_title']);
                $node->title = $row['title'];
                $modified = TRUE;
            }
            if ($modified == TRUE) {
                $count_saves ++;
                node_save($node);
                CMSUtils::println('Instrument %s was updated',$node->title);
            }
        } else if(!empty($curr_instrument_title)) {
            //if not synced
            $query = new EntityFieldQuery();
            $entities = $query->entityCondition('entity_type', 'node')
                ->propertyCondition('type', 'legal_instrument')
                ->propertyCondition('title', $curr_instrument_title)
                ->propertyCondition('status', 1)
                ->range(0,1)
                ->execute();
            if (!empty($entities['node'])) {
                $node = node_load(array_shift(array_keys($entities['node'])));
                if ($node->uuid != $row['cms_uuid']) {
                    CMSUtils::println('Instrument %s has different uuid than it\'s correspondent in CMS %s',$node->title, $row['cms_title']);
                    $node->uuid = $row['cms_uuid'];
                    $modified = TRUE;
                }
                if ($node->title != $row['title']) {
                    CMSUtils::println('Instrument %s has different title than it\'s correspondent in CMS %s',$node->title, $row['cms_title']);
                    $node->title = $row['title'];
                    $modified = TRUE;
                }
                if ($modified == TRUE) {
                    $count_saves ++;
                    node_save($node);
                    CMSUtils::println('Instrument %s was updated',$node->title);
                }
            } else {
                CMSUtils::println('Instrument %s was not found by title or UUID in the JSON file',$row['title']);
            }
        } else if(empty($curr_instrument_title)) {
            CMSUtils::println('Instrument %s has no title set for this instrument in the JSON file',$row['title']);
        }
    }
    CMSUtils::println('%s instruments updated',$count_saves);
}


/**
 * Updates countries' UUID as it's iso2 match in json file
 * Used for sync countries' UUID between profiles
 *
 * @param $file_path    json file with countries (uuid and iso2)
 *                           searches the Country by field_country_iso2 key in json
 */
function drush_cms_sync_countries_uuid($file_path) {
    $JSON = CMSUtils::read_json($file_path, TRUE);
    $total_instruments = count($JSON);

    CMSUtils::println('Found %s countries', $total_instruments);
    $count_saves = 0;
    foreach ($JSON as $country) {
        $nodes = entity_uuid_load('node',array($country['uuid']));
        //if uuid sync or in cms profile
        if (!empty($nodes)) {
            CMSUtils::println('Country %s already has the UUID as in JSON file', $country['title']);
        } else {
            //if not synced
            $query = new EntityFieldQuery();
            $entities = $query->entityCondition('entity_type', 'node')
                ->propertyCondition('type', 'country')
                ->propertyCondition('status', 1)
                ->fieldCondition('field_country_iso2', 'value', $country['field_country_iso2'], '=')
                ->range(0,1)
                ->execute();
            if (!empty($entities['node'])) {
                $node = node_load(array_shift(array_keys($entities['node'])));
                CMSUtils::println('Country %s has different UUID than it\'s correspondent in CMS. Updating...',$country['title']);
                $node->uuid = $country['uuid'];
                node_save($node);
                $count_saves ++;
            } else {
                CMSUtils::println('Country %s couldn\'t be found by UUID or ISO2', $country->title);
            }
        }
    }
    CMSUtils::println('%s Countries updated',$count_saves);
}




/**
 * Get the 'Country Report' field from 'Submitted by' and unset the
 * 'Submitted by' in case of a match
 */
function drush_cms_set_national_reports_country_1776() {
    $q = new EntityFieldQuery();
    $res = $q->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'country')
        ->execute();
    $res = node_load_multiple(array_keys($res['node']));
    $countries = array();
    foreach($res as $nid => $ob) {
        $countries[strtolower($ob->title)] = $nid;
    }

    $nr = taxonomy_get_term_by_name('National Report', 'document_type');
    if(empty($nr)) {
        drupal_set_message("Failed to get tid for National Report document type", 'error');
        return;
    }
    $nr = current($nr);
    $nr = $nr->tid;

    // Fetch all the national reports
    $q = new EntityFieldQuery();
    $q->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'document')
        ->fieldCondition('field_document_type', 'tid', $nr);
    $res = $q->execute();
    $docs = node_load_multiple(array_keys($res['node']));
    $i = 0;
    $m = 0;
    foreach($docs as $dnid => $doc) {
        // Get a hold on the submitted by field tid
        $sb = CMSUtils::get_node_simple_value($doc, 'field_document_submitted_by', 'tid');
        if(!empty($sb)) {
            $sb = taxonomy_term_load($sb);
            $sb_name = strtolower($sb->name);
            if(array_key_exists($sb_name, $countries)) {
                $cid = $countries[$sb_name];
                // Assign country to the report
                $doc->field_document_country[$doc->language][] = array('target_id' => $cid);
                // Unset the 'Submitted by' field
                $doc->field_document_submitted_by[$doc->language] = array();
                echo "Saving node {$doc->nid}\n";
                node_save($doc);
                $m++;
            } else {
                CMSUtils::println("Cannot match '%s' to country for document #: %s", $sb->name, $dnid);
                $i++;
            }
        }
    }
    echo "Documents NOT matched: $i\n";
    echo "Documents matched: $m\n";
}

/**
 * Function refs #1821
 * Move the published date from field_publication_published (date) to field_publication_published_date (partial_date)
 *
 * Author Dragos Dumitrescu
 */

function drush_cms_move_pub_date_to_partial_date_refs_1821() {
    $field_info = field_info_instance('node', 'field_publication_published_date', 'publication');
    if ($field_info == NULL) {
        echo "Cannot find field_publication_published_date. Canceling...";
        return;
    }

    $field_info = field_info_instance('node', 'field_publication_published', 'publication');
    if ($field_info == NULL) {
        echo "Cannot find field_publication_published. You might have already done this update. Canceling...";
        return;
    }

    $publications = node_load_multiple( array(),
        array(
            'type' => 'publication',
        )
    );
    CMSUtils::println("%s publications found", count($publications));
    $saves_counter = 0;
    foreach ($publications as $node) {
        if (!empty($node->field_publication_published[$node->language][0]['value'])) {
            $date = $node->field_publication_published[$node->language][0]['value'];
            if (empty($node->field_publication_published_date[$node->language][0]['from']['year'])) {
                $node->field_publication_published_date[$node->language][0]['from']['year'] = date('Y', strtotime($date));
                $node->field_publication_published_date[$node->language][0]['from']['month'] = date('m', strtotime($date));
                node_save($node);
                $saves_counter++;
            } else {
                CMSUtils::println("%s has already year set in published_date field", $node->title);
            }
        } else {
            CMSUtils::println("--> %s has empty published date", $node->title);
        }
    }
    CMSUtils::println('-------------------------------------------');
    CMSUtils::println("%s Publications were updated", $saves_counter);
    CMSUtils::println("Check if the update is ok and you can delete the field_publication_published.");

}

/**
 * Function used for creating basic pages from json
 * for each existing domains except default
 *
 * @param $file_path
 */
function drush_cms_add_basic_page($file_path) {

    $JSON = CMSUtils::read_json($file_path, TRUE);
    $total_pages = count($JSON);
    CMSUtils::println('%s pages found', $total_pages);
    $language = language_default()->language;
    //Get domains
    $domain_ids = domain_id_list();
    //Remove primary domain
    array_shift($domain_ids);

    foreach ($domain_ids as $domain_id ) {
        $count_saves = 0;
        foreach ($JSON as $page) {
            //Check if page for domain already exists
            $items = entity_load('node', FALSE, array(
                'type' => 'page',
                'title' => $page['title'],
            ));
            if (count($items)) {
                foreach ($items as $item) {
                    if($item->domain_source == $domain_id) {
                        CMSUtils::println("%s already exists for domain %s", $page['title'], $domain_id);
                        continue 2;
                    }
                }
            }
            //Creating new page for domain
            $node = new stdClass();
            $node->type = "page";
            $node->title = $page['title'];
            $node->language = $language;
            $node->domain_site = FALSE;
            $node->domain_source = $domain_id;
            $node->domains = array($domain_id => $domain_id);
            $node->domain_path = array($domain_id => $page['alias']);
            node_object_prepare($node);
            node_save($node);
            if ($node->nid) {
                $count_saves ++;
            }
        }
        CMSUtils::println('%s pages SAVED and %s FAILED for domain %s', $count_saves, $total_pages - $count_saves, $domain_id);
    }
    CMSUtils::println("Done.");
}

function drush_cms_fix_species_instruments_1730($data_file_path, $instruments_map_file_path) {
    $species_data = CMSUtils::read_json($data_file_path, TRUE);
    $instruments_map = CMSUtils::read_json($instruments_map_file_path, TRUE);
    $total_species = count($species_data);
    CMSUtils::println('%s species found', $total_species);
    $total_saves = 0;
    foreach ($species_data as $species) {
        $query = new EntityFieldQuery();
        $entities = $query->entityCondition('entity_type', 'node')
            ->propertyCondition('type', 'species')
            ->propertyCondition('title', $species['title'])
            ->propertyCondition('status', 1)
            ->range(0,1)
            ->execute();
        if(!empty($entities)) {
            $node = node_load(array_shift(array_keys($entities['node'])));
        }

        $imported_instruments = array();
        $imported_instruments_ids = array();
        if (isset($species['field_species_instruments'])) {
            foreach ($species['field_species_instruments'] as $instrument_collection) {
                $query = new EntityFieldQuery();
                if (isset($instruments_map[$instrument_collection['field_species_instrument']])) {
                    $current_instrument_title = $instruments_map[$instrument_collection['field_species_instrument']];
                } else {
                    CMSUtils::println('%s doesn\'t have a mapped title', $instrument_collection['field_species_instrument']);
                    continue;
                }
                $entities = $query->entityCondition('entity_type', 'node')
                    ->propertyCondition('type', 'legal_instrument')
                    ->propertyCondition('title', $current_instrument_title)
                    ->propertyCondition('status', 1)
                    ->range(0,1)
                    ->execute();
                if (!empty($entities['node'])) {
                    $instrument_id = array_shift(array_keys($entities['node']));
                    $imported_instruments_ids []= $instrument_id;
                    $imported_instruments[$instrument_id] = $instrument_collection;
                } else {
                    CMSUtils::println('%s can\'t load by title', $current_instrument_title);
                    continue;
                }

            }
        }
        if (count($imported_instruments) > 0) {
            $existing_instruments = array();
            if (isset($node->field_species_instruments[LANGUAGE_NONE])) {
                foreach ($node->field_species_instruments[LANGUAGE_NONE] as $field_collection) {
                    $field_collection = field_collection_item_load($field_collection['value']);
                    $existing_instruments[]= $field_collection->field_species_instrument[LANGUAGE_NONE][0]['target_id'];
                }
            }
            $new_instruments_ids = array_unique(array_diff($imported_instruments_ids, $existing_instruments));
            $save = false;
            foreach ($new_instruments_ids as $nid) {
                $new_fc = array();
                $new_fc['field_name'] = 'field_species_instruments';
                $new_fc['field_species_instrument'][LANGUAGE_NONE][0]['target_id'] = $nid;
                if (isset($imported_instruments[$nid]['field_species_instrument_date']) && (!empty($imported_instruments[$nid]['field_species_instrument_date']))) {
                    $new_fc['field_species_instrument_date'][LANGUAGE_NONE][0]['value'] = $imported_instruments[$nid]['field_species_instrument_date'];
                }
                $entity = entity_create('field_collection_item', $new_fc);
                $entity->setHostEntity('node', $node);
                $save = true;
                $total_saves ++;
            }
            if ($save) {
                CMSUtils::println('%s has new instruments with ids %s', $node->title, implode(', ', $new_instruments_ids));
                node_save($node);
            }
        }
    }
    CMSUtils::println('%s species saved', $total_saves);
}

function drush_cms_fix_paths_sef() {
    $types = drush_get_option('type');
    if (empty($types)) {
        $types = array(
            'species', 'meeting', 'legal_instrument', 'project', 'country', 'document', 'publication',
            'award', 'page', 'campaign', 'news', 'working_group', 'event_calendar'
        );
    } else {
        $types = explode(',', $types);
    }
    foreach ($types as $type) {
        $query = new EntityFieldQuery();
        $entities = $query->entityCondition('entity_type', 'node')
            ->propertyCondition('type', $type)
            ->execute();
        if (!empty($entities['node'])) {
            CMSUtils::println('Updating for %s ...', $type);
            $total_saves = 0;
            foreach ($entities['node'] as $nid => $entity) {
                $node = node_load($nid);
                $node->path['pathauto'] = TRUE;
                node_save($node);
                $total_saves ++;
                echo $nid .', ';
            }
            CMSUtils::println('');
            CMSUtils::println('-------------------');
            CMSUtils::println('%s  %s saved', $total_saves, $type);
        } else {
            CMSUtils::println('No %s found', $type);
        }
    }
    CMSUtils::println('Done!');
}


