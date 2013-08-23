<?php
/**
 * @file
 * cms_party.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cms_party_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cms_party_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cms_party_node_info() {
  $items = array(
    'cms_party' => array(
      'name' => t('Convention Party'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '0',
      'title_label' => '',
      'help' => '',
    ),
  );
  return $items;
}
