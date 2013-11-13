<?php

/**
 * Implements hook_drush_command();
 *
 * Generic drush commands for CMS websites
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

    return $items;
}

/**
 * Callback function for set_encrypted_variable drush command.
 *
 * Using Drupal hash salt set an encrypted value for a specified variable
 *
 * @param   string   $variable_name
 * @param   string   $value_to_encrypt
 */
function drush_cms_set_encrypted_variable($variable_name, $value_to_encrypt) {
    variable_del($variable_name);

    // PHP mcrypt_ecb is not accepting strings longer the 25 chars
    $hash = substr(drupal_get_hash_salt(), 0, 24);

    variable_set($variable_name, mcrypt_ecb(MCRYPT_3DES, $hash,
        $value_to_encrypt, MCRYPT_ENCRYPT));
}

/**
 * Callback function for set_logo drush command
 *
 * Upload and set website logo
*/
function drush_cms_set_log() {
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
