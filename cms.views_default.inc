<?php
/**
 * @file
 * cms.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cms_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'available_decisions';
  $view->description = 'List of decisions with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Decisions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'decision' => 'decision',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_decisions'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Entity Reference'),
  );
  $export['available_decisions'] = $view;

  $view = new view;
  $view->name = 'available_documents';
  $view->description = 'List of documents with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Documents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_document_number']['id'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['table'] = 'field_data_field_document_number';
  $handler->display->display_options['fields']['field_document_number']['field'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['label'] = '';
  $handler->display->display_options['fields']['field_document_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_number']['field_api_classes'] = 0;
  /* Field: Content: CMS Instrument */
  $handler->display->display_options['fields']['field_document_instrument']['id'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['table'] = 'field_data_field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['field'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['label'] = '';
  $handler->display->display_options['fields']['field_document_instrument']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_instrument']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_document_instrument']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_document_instrument] - [field_document_number] - [title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'document' => 'document',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_documents'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('[field_document_instrument] - [field_document_number] - [title]'),
    t('Entity Reference'),
  );
  $export['available_documents'] = $view;

  $view = new view;
  $view->name = 'available_national_reports';
  $view->description = 'List of documents with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available National Reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Type (field_document_type) */
  $handler->display->display_options['relationships']['field_document_type_tid']['id'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['table'] = 'field_data_field_document_type';
  $handler->display->display_options['relationships']['field_document_type_tid']['field'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['required'] = 1;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_document_number']['id'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['table'] = 'field_data_field_document_number';
  $handler->display->display_options['fields']['field_document_number']['field'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['label'] = '';
  $handler->display->display_options['fields']['field_document_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_number']['field_api_classes'] = 0;
  /* Field: Content: CMS Instrument */
  $handler->display->display_options['fields']['field_document_instrument']['id'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['table'] = 'field_data_field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['field'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['label'] = '';
  $handler->display->display_options['fields']['field_document_instrument']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_instrument']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_document_instrument']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_document_instrument] - [field_document_number] - [title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'document' => 'document',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '414',
  );
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Has taxonomy term';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['required'] = 1;
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'document_type';
  $handler->display->display_options['filters']['tid']['error_message'] = 0;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_national_reports'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('term from field_document_type'),
    t('[field_document_instrument] - [field_document_number] - [title]'),
    t('Has taxonomy term'),
    t('Entity Reference'),
  );
  $export['available_national_reports'] = $view;

  $view = new view;
  $view->name = 'available_other_documents';
  $view->description = 'List of documents with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Other Documents';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Type (field_document_type) */
  $handler->display->display_options['relationships']['field_document_type_tid']['id'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['table'] = 'field_data_field_document_type';
  $handler->display->display_options['relationships']['field_document_type_tid']['field'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['required'] = 1;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_document_number']['id'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['table'] = 'field_data_field_document_number';
  $handler->display->display_options['fields']['field_document_number']['field'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['label'] = '';
  $handler->display->display_options['fields']['field_document_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_number']['field_api_classes'] = 0;
  /* Field: Content: CMS Instrument */
  $handler->display->display_options['fields']['field_document_instrument']['id'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['table'] = 'field_data_field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['field'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['label'] = '';
  $handler->display->display_options['fields']['field_document_instrument']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_instrument']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_document_instrument']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_document_instrument] - [field_document_number] - [title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'document' => 'document',
  );
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['operator'] = 'not';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '414',
    1 => '447',
  );
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Has taxonomy term';
  $handler->display->display_options['filters']['tid']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['tid']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['tid']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'document_type';

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_other_documents'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('term from field_document_type'),
    t('[field_document_instrument] - [field_document_number] - [title]'),
    t('Has taxonomy term'),
    t('Entity Reference'),
  );
  $export['available_other_documents'] = $view;

  $view = new view;
  $view->name = 'available_plans';
  $view->description = 'List of documents with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Plans';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Type (field_document_type) */
  $handler->display->display_options['relationships']['field_document_type_tid']['id'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['table'] = 'field_data_field_document_type';
  $handler->display->display_options['relationships']['field_document_type_tid']['field'] = 'field_document_type_tid';
  $handler->display->display_options['relationships']['field_document_type_tid']['required'] = 1;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_document_number']['id'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['table'] = 'field_data_field_document_number';
  $handler->display->display_options['fields']['field_document_number']['field'] = 'field_document_number';
  $handler->display->display_options['fields']['field_document_number']['label'] = '';
  $handler->display->display_options['fields']['field_document_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_number']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_number']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_number']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_number']['field_api_classes'] = 0;
  /* Field: Content: CMS Instrument */
  $handler->display->display_options['fields']['field_document_instrument']['id'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['table'] = 'field_data_field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['field'] = 'field_document_instrument';
  $handler->display->display_options['fields']['field_document_instrument']['label'] = '';
  $handler->display->display_options['fields']['field_document_instrument']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_instrument']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_document_instrument']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_document_instrument']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_document_instrument']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_document_instrument] - [field_document_number] - [title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'document' => 'document',
  );
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '447',
  );
  $handler->display->display_options['filters']['tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Has taxonomy term';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['required'] = 1;
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = 1;
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'document_type';
  $handler->display->display_options['filters']['tid']['error_message'] = 0;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_plans'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('term from field_document_type'),
    t('[field_document_instrument] - [field_document_number] - [title]'),
    t('Has taxonomy term'),
    t('Entity Reference'),
  );
  $export['available_plans'] = $view;

  $view = new view;
  $view->name = 'available_projects';
  $view->description = 'List of projects with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Projects';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_projects'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Entity Reference'),
  );
  $export['available_projects'] = $view;

  $view = new view;
  $view->name = 'available_publications';
  $view->description = 'List of publications with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Publications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'publication' => 'publication',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_publications'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Entity Reference'),
  );
  $export['available_publications'] = $view;

  $view = new view;
  $view->name = 'available_species';
  $view->description = 'List of species with status published';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Available Species';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'species' => 'species',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['available_species'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Title'),
    t('Entity Reference'),
  );
  $export['available_species'] = $view;

    $view = new view();
    $view->name = 'published_meetings';
    $view->description = 'List of meetings with status published';
    $view->tag = 'default';
    $view->base_table = 'node';
    $view->human_name = 'Available Meetings';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Instrument */
    $handler->display->display_options['fields']['field_meeting_instrument']['id'] = 'field_meeting_instrument';
    $handler->display->display_options['fields']['field_meeting_instrument']['table'] = 'field_data_field_meeting_instrument';
    $handler->display->display_options['fields']['field_meeting_instrument']['field'] = 'field_meeting_instrument';
    $handler->display->display_options['fields']['field_meeting_instrument']['label'] = '';
    $handler->display->display_options['fields']['field_meeting_instrument']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['field_meeting_instrument']['settings'] = array(
        'link' => 0,
    );
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
    /* Sort criterion: Content: Title */
    $handler->display->display_options['sorts']['title']['id'] = 'title';
    $handler->display->display_options['sorts']['title']['table'] = 'node';
    $handler->display->display_options['sorts']['title']['field'] = 'title';
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 1;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Content: Type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'node';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
        'meeting' => 'meeting',
    );

    /* Display: Entity Reference */
    $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'entityreference_style';
    $handler->display->display_options['style_options']['search_fields'] = array(
        'title' => 'title',
    );
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'entityreference_fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $translatables['published_meetings'] = array(
        t('Master'),
        t('more'),
        t('Apply'),
        t('Reset'),
        t('Sort by'),
        t('Asc'),
        t('Desc'),
        t('Items per page'),
        t('- All -'),
        t('Offset'),
        t('« first'),
        t('‹ previous'),
        t('next ›'),
        t('last »'),
        t('Entity Reference'),
    );
  $export['published_meetings'] = $view;

  return $export;
}
