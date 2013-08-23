<?php
/**
 * @file
 * cms_party.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cms_party_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'parties_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Convention Parties List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CMS Countries';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Clear filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'datatables';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_cms_party_country' => 'field_cms_party_country',
    'field_cms_party_instrument' => 'field_cms_party_instrument',
    'field_cms_party_status' => 'field_cms_party_status',
  );
  $handler->display->display_options['style_options']['default'] = 'field_cms_party_country';
  $handler->display->display_options['style_options']['info'] = array(
    'field_cms_party_country' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cms_party_instrument' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cms_party_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = 1;
  $handler->display->display_options['style_options']['elements'] = array(
    'search_box' => 1,
    'table_info' => 1,
    'save_state' => 0,
  );
  $handler->display->display_options['style_options']['layout'] = array(
    'autowidth' => 1,
    'themeroller' => 0,
    'sdom' => '',
  );
  $handler->display->display_options['style_options']['pages'] = array(
    'pagination_style' => 'full_numbers',
    'length_change' => 1,
    'display_length' => '10',
    'processing' => 0,
    'server_side' => 0,
    'items_per_page_options' => '10, 25, 50, All',
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No parties found';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_cms_party_country']['id'] = 'field_cms_party_country';
  $handler->display->display_options['fields']['field_cms_party_country']['table'] = 'field_data_field_cms_party_country';
  $handler->display->display_options['fields']['field_cms_party_country']['field'] = 'field_cms_party_country';
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['path'] = '[view_node]';
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_cms_party_country']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_cms_party_country']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_cms_party_country']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_cms_party_country']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_cms_party_country']['field_api_classes'] = 0;
  /* Field: Content: Legal Instrument */
  $handler->display->display_options['fields']['field_cms_party_instrument']['id'] = 'field_cms_party_instrument';
  $handler->display->display_options['fields']['field_cms_party_instrument']['table'] = 'field_data_field_cms_party_instrument';
  $handler->display->display_options['fields']['field_cms_party_instrument']['field'] = 'field_cms_party_instrument';
  $handler->display->display_options['fields']['field_cms_party_instrument']['label'] = 'CMS Instrument';
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_cms_party_instrument']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_cms_party_instrument']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_cms_party_instrument']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_cms_party_instrument']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_cms_party_instrument']['field_api_classes'] = 0;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_cms_party_status']['id'] = 'field_cms_party_status';
  $handler->display->display_options['fields']['field_cms_party_status']['table'] = 'field_data_field_cms_party_status';
  $handler->display->display_options['fields']['field_cms_party_status']['field'] = 'field_cms_party_status';
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_cms_party_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_cms_party_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_cms_party_status']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_cms_party_status']['field_api_classes'] = 0;
  /* Field: Node: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Links';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = 'View';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['view_node']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['view_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['view_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['view_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['view_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['view_node']['hide_alter_empty'] = 1;
  /* Sort criterion: Content: Country (field_cms_party_country) */
  $handler->display->display_options['sorts']['field_cms_party_country_target_id']['id'] = 'field_cms_party_country_target_id';
  $handler->display->display_options['sorts']['field_cms_party_country_target_id']['table'] = 'field_data_field_cms_party_country';
  $handler->display->display_options['sorts']['field_cms_party_country_target_id']['field'] = 'field_cms_party_country_target_id';
  $handler->display->display_options['sorts']['field_cms_party_country_target_id']['expose']['label'] = 'Country';
  /* Sort criterion: Content: Legal Instrument (field_cms_party_instrument) */
  $handler->display->display_options['sorts']['field_cms_party_instrument_target_id']['id'] = 'field_cms_party_instrument_target_id';
  $handler->display->display_options['sorts']['field_cms_party_instrument_target_id']['table'] = 'field_data_field_cms_party_instrument';
  $handler->display->display_options['sorts']['field_cms_party_instrument_target_id']['field'] = 'field_cms_party_instrument_target_id';
  $handler->display->display_options['sorts']['field_cms_party_instrument_target_id']['expose']['label'] = 'Legal Instrument';
  /* Sort criterion: Content: Status (field_cms_party_status) */
  $handler->display->display_options['sorts']['field_cms_party_status_tid']['id'] = 'field_cms_party_status_tid';
  $handler->display->display_options['sorts']['field_cms_party_status_tid']['table'] = 'field_data_field_cms_party_status';
  $handler->display->display_options['sorts']['field_cms_party_status_tid']['field'] = 'field_cms_party_status_tid';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cms_party' => 'cms_party',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Country (field_cms_party_country) */
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['id'] = 'field_cms_party_country_target_id';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['table'] = 'field_data_field_cms_party_country';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['field'] = 'field_cms_party_country_target_id';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['expose']['operator_id'] = 'field_cms_party_country_target_id_op';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['expose']['label'] = 'Country';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['expose']['operator'] = 'field_cms_party_country_target_id_op';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['expose']['identifier'] = 'field_cms_party_country_target_id';
  $handler->display->display_options['filters']['field_cms_party_country_target_id']['expose']['multiple'] = FALSE;
  /* Filter criterion: Content: Legal Instrument (field_cms_party_instrument) */
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['id'] = 'field_cms_party_instrument_target_id';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['table'] = 'field_data_field_cms_party_instrument';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['field'] = 'field_cms_party_instrument_target_id';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['expose']['operator_id'] = 'field_cms_party_instrument_target_id_op';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['expose']['label'] = 'CMS Instrument';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['expose']['operator'] = 'field_cms_party_instrument_target_id_op';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['expose']['identifier'] = 'field_cms_party_instrument_target_id';
  $handler->display->display_options['filters']['field_cms_party_instrument_target_id']['expose']['multiple'] = FALSE;
  /* Filter criterion: Content: Status (field_cms_party_status) */
  $handler->display->display_options['filters']['field_cms_party_status_tid']['id'] = 'field_cms_party_status_tid';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['table'] = 'field_data_field_cms_party_status';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['field'] = 'field_cms_party_status_tid';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cms_party_status_tid']['expose']['operator_id'] = 'field_cms_party_status_tid_op';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['expose']['operator'] = 'field_cms_party_status_tid_op';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['expose']['identifier'] = 'field_cms_party_status_tid';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['expose']['reduce'] = 0;
  $handler->display->display_options['filters']['field_cms_party_status_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['field_cms_party_status_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['vocabulary'] = 'party_status';
  $handler->display->display_options['filters']['field_cms_party_status_tid']['error_message'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'parties_listing');
  $handler->display->display_options['path'] = 'parties/listing';
  $handler->display->display_options['menu']['title'] = 'Parties';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['parties_list'] = array(
    t('Master'),
    t('CMS Countries'),
    t('more'),
    t('Search'),
    t('Clear filters'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('No parties found'),
    t('Country'),
    t('[view_node]'),
    t('CMS Instrument'),
    t('Status'),
    t('Links'),
    t('View'),
    t('Legal Instrument'),
    t('Page'),
  );
  $export['parties_list'] = $view;

  return $export;
}
