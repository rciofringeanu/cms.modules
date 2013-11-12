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

    return $items;
}

/**
 * Callback function for set_encrypted_variable drush command.
 *
 * Using Drupal hash salt set an encrypted value for a specified variable
 *
 * @param   string   $variable_name
 * @param   string   $value_to_encrypt
 *
 *
 */
function drush_cms_set_encrypted_variable($variable_name, $value_to_encrypt) {
    variable_del($variable_name);

    // PHP mcrypt_ecb is not accepting strings longer the 25 chars
    $hash = substr(drupal_get_hash_salt(), 0, 24);

    variable_set($variable_name, mcrypt_ecb(MCRYPT_3DES, $hash,
        $value_to_encrypt, MCRYPT_ENCRYPT));
}
