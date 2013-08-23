<?php
/**
 * @file
 * cms.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cms_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_administration:admin
  $menu_links['user-menu_administration:admin'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin',
    'router_path' => 'admin',
    'link_title' => 'Administration',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_administration:admin',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Administration');


  return $menu_links;
}
