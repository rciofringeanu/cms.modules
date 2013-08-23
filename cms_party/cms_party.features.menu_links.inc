<?php
/**
 * @file
 * cms_party.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cms_party_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_view-cms-countries:parties/listing
  $menu_links['main-menu_view-cms-countries:parties/listing'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'parties/listing',
    'router_path' => 'parties/listing',
    'link_title' => 'View CMS Countries',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_view-cms-countries:parties/listing',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_identifier' => 'main-menu_countries:<front>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('View CMS Countries');


  return $menu_links;
}
