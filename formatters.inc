<?php

/**
 * Extract text value from a form field based on language preference.
 * @param array $instance Field instance
 * @param string $langcode Currently requested language
 * @param array $item Actual object with data
 * @param string $column Property to extract from the field
 *
 * @return Value or NULL if not found
 */
function cms_text_sanitize($instance, $langcode, $item, $column) {
    // If the value uses a cacheable text format, text_field_load() precomputes the sanitized string.
    if (isset($item["safe_$column"])) {
        return $item["safe_$column"];
    } else {
        if(isset($instance['settings']['text_processing']) && $instance['settings']['text_processing'] == TRUE) {
            return check_markup($item[$column], $item['format'], $langcode);
        } else {
            return check_plain($item[$column]);
        }
    }
}


/**
 * Extract single value from fields with structure
 * $field[LANGUAGE][0][value]
 * @param array $item Actual object with data
 * @param string $langcode Currently requested language
 * @param string $property The property to extract
 *
 * @return Value or empty string if not found
 */
function cms_extract_single_value($item, $langcode, $property) {
    if(isset($item[$langcode][0][$property])) {
        return $item[$langcode][0][$property];
    }
    return '';
}

function cms_extract_list_value($item, $langcode, $property) {
    $ret = array();
    if (isset($item, $langcode) && !empty($item[$langcode])) {
        foreach ($item[$langcode] as $index => $value) {
            $ret[] = $value;
        }
    }

    return $ret;
}

function extract_term_names($term_id) {
    $term = entity_load_unchanged('taxonomy_term', $term_id);
    return $term->name;
}


/**
 * Implements hook_field_formatter_info().
 */
function cms_field_formatter_info() {
    return array(
        'cms_field_table_row_formatter' => array(
            'label' => t('Horizontal table row'),
            'field types' => array('text', 'number_integer', 'number_float', 'text_long', 'list_text', 'number_decimal'),
            'settings' => array(
                'render_tr' => TRUE, /* Render enclosing TR */
                'render_link' => '0', /* Render as anchor */
            ),
        ),
        'cms_term_reference_field_table_row_formatter' => array(
            'label' => t('Term Reference Horizontal table row'),
            'field types' => array('taxonomy_term_reference'),
            'settings' => array(
                'render_tr' => TRUE, /* Render enclosing TR */
                'render_plain_text' => '1', /* Render as anchor */
            ),
        ),
        'cms_iucn_status_formatter' => array(
            'label' => t('Species IUCN Status'),
            'field types' => array('list_text')
        ),
        'cms_link_formatter' => array(
            'label' => t('CMS Link (Horizontal table row)'),
            'field types' => array('link_field')
        ),
        'cms_region_formatter' => array(
            'label' => t('Region Horizontal table row'),
            'field types' => array('list_text'),
            'settings' => array(
                'render_tr' => TRUE,
            ),
        ),
        'cms_gallery_formatter' => array(
            'label' => t('Image Gallery'),
            'field types' => array('image')
        ),
        'cms_country_table_row_formatter' => array(
            'label' => t('Country as horizontal table row'),
            'field types' => array('entityreference')
        ),
        'cms_boolean_formatter' => array(
            'label' => t('CMS Checkbox table row'),
            'field types' => array('list_boolean'),
            'settings' => array(
                'mode' => 0, /* Yes/No default mode */
            ),
        ),
        'cms_appendix_formatter' => array(
            'label' => t('Species CMS Appendix table row'),
            'field types' => array('list_text')
        ),
        'cms_date_formatter' => array(
            'label' => t('Date in horizontal table row'),
            'field types' => array('date', 'datetime'),
            'settings' => array(
                'format' => 'month_year_date_type', /* Default */
            ),
        ),
        'cms_legal_instruments_formatter' => array(
            'label' => t('CMS instruments'),
            'field types' => array('field_collection', 'entityreference'),
        ),
        'cms_legal_instruments_signed_by_formatter' => array(
            'label' => t('CMS Instrument signed by'),
            'field types' => array('field_collection', 'entityreference'),
        ),
        'cms_species_population_instrument_formatter' => array(
            'label' => t('Species population per instrument'),
            'field types' => array('field_collection')
        ),
        'cms_species_population_size_formatter' => array(
            'label' => t('Species population size'),
            'field types' => array('field_collection')
        ),
        'cms_species_population_trend_formatter' => array(
            'label' => t('Species population trend'),
            'field types' => array('field_collection')
        ),
        'cms_range_state_formatter' => array(
            'label' => t('CMS species range states'),
            'field types' => array('field_collection')
        ),
        'cms_project_activity_formatter' => array(
            'label' => t('Project activity'),
            'field types' => array('field_collection')
        ),
        'cms_project_payments_formatter' => array(
            'label' => t('Project payments'),
            'field types' => array('field_collection')
        ),
        'cms_project_bac_formatter' => array(
            'label' => t('Project Budget line (BAC)'),
            'field types' => array('field_collection')
        ),
        'cms_project_funding_formatter' => array(
            'label' => t('Project funding (e.g. 100 EUR) table row'),
            'field types' => array('field_collection')
        ),
        'cms_country_status_formatter' => array(
            'label' => t('AEWA country status'),
            'field types' => array('field_collection')
        ),
        'cms_aewa_population_status_formatter' => array(
            'label' => t('AEWA population status'),
            'field types' => array('field_collection')
        ),
        'cms_threats_formmater' => array(
            'label' => t('Threats'),
            'field types' => array('field_collection')
        ),
    );
}


/**
 * Implements hook_field_formatter_settings_form().
 */
function cms_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
    $display = $instance['display'][$view_mode];
    $settings = $display['settings'];
    $type = $display['type'];

    $element = array();
    switch($type) {
        case 'cms_field_table_row_formatter':
            $element['render_tr'] = array(
                '#type'           => 'checkbox',
                '#title'          => t('Render enclosing &lt;tr&gt;&lt;/tr&gt; table row'),
                '#default_value'  => $settings['render_tr'],
            );
            $element['render_link'] = array(
                '#type'           => 'select',
                '#title'          => t('URI link'),
                '#default_value'  => $settings['render_link'],
                '#options' => array(
                    '0' => '-- None --',
                    '1' => 'Internal link',
                    '2' => 'External link'
                )
            );
            break;
        case 'cms_term_reference_field_table_row_formatter':
            $element['render_tr'] = array(
                '#type'           => 'checkbox',
                '#title'          => t('Render enclosing &lt;tr&gt;&lt;/tr&gt; table row'),
                '#default_value'  => $settings['render_tr'],
            );
            $element['render_plain_text'] = array(
                '#type'           => 'checkbox',
                '#title'          => t('Render as plain text'),
                '#default_value'  => $settings['render_plain_text']
            );
            break;
        case 'cms_region_formatter':
            $element['render_tr'] = array(
                '#type'           => 'checkbox',
                '#title'          => t('Render enclosing &lt;tr&gt;&lt;/tr&gt; table row'),
                '#default_value'  => $settings['render_tr'],
            );
        case 'cms_iucn_status_formatter':
            break;
        case 'cms_link_formatter':
            break;
        case 'cms_gallery_formatter':
            break;
        case 'cms_country_table_row_formatter':
            break;
        case 'cms_appendix_formatter':
            break;
        case 'cms_boolean_formatter':
            $element['mode'] = array(
                '#type'           => 'select',
                '#title'          => t('Render mode'),
                '#default_value'  => $settings['mode'],
                '#options' => array(
                    '0' => 'Yes/No (default)',
                )
            );
            break;
        case 'cms_date_formatter':
            $choices = array();
            $types = system_get_date_types();
            foreach ($types as $type => $type_info) {
                $format = key(system_get_date_formats($type));
                $choices[$type] = format_date(REQUEST_TIME, $type, $format);
            }

            $element['format'] = array(
                '#type'           => 'select',
                '#title'          => t('Date format'),
                '#default_value'  => 'cms_date',
                '#options' => $choices,
            );
            break;
    }
    return $element;
}


/**
 * Implements hook_field_formatter_settings_summary().
 */
function cms_field_formatter_settings_summary($field, $instance, $view_mode) {
    $display = $instance['display'][$view_mode];
    $settings = $display['settings'];
    $type = $display['type'];
    switch($type) {
        case 'cms_field_table_row_formatter':
            return t('Render the data as horizontal table row. Handles URLs');
        case 'cms_term_reference_field_table_row_formatter':
            return t('Render Term references as horizontal table row. Handles URLs');
        case 'cms_region_formatter':
            return t('Renderer Region as horizontal table row.');
        case 'cms_iucn_status_formatter':
            return t('Renderer for IUCN status field');
            break;
        case 'cms_link_formatter':
            return t('Renderer link field');
            break;
        case 'cms_gallery_formatter':
            return t('Render multiple images field as gallery');
        case 'cms_country_table_row_formatter':
            return t('Render Country reference as horizontal table row');
        case 'cms_boolean_formatter':
            return t('Render the boolean field as Yes/No text');
        case 'cms_appendix_formatter':
            return t('Renderer for CMS Appendix field');
        case 'cms_date_formatter':
            return t('Render date field');
        default:
            break;
    }
}


/**
 * Implements hook_field_formatter_view().
 *
 * @param string $entity_type The type of $entity, i.e. node
 * @param object $entity The entity being displayed, i.e. StdClass
 * @param array $field The field structure
 * @param array $instance The field instance
 * @param string $langcode The language associated with $items, i.e. "und"
 * @param array $items Array of values for this field
 * @param array $display The display settings to use, as found in the
 * 'display' entry of instance definitions. The array notably contains
 * the following keys and values: 'type', 'settings'
 *
 * @return A renderable array for the $items, as an array of child
 * elements keyed by numeric indexes starting from 0.
 */
function cms_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
    $element = array();
    $settings = $display['settings'];
    $type = $display['type'];
    $element['#theme'] = $type;
    switch ($type) {
        case 'cms_field_table_row_formatter':
            foreach ($items as $delta => $item) {
                $element[$delta]['#settings'] = $settings;
                $allowed_values = array();
                if ($field['type'] == 'list_text') {
                    $allowed_values = $field['settings']['allowed_values'];
                }

                $output = cms_text_sanitize($instance, $langcode, $item, 'value');
                if (!empty($allowed_values) && array_key_exists($output, $allowed_values)) {
                    $output = $allowed_values[$output];
                }

                $element[$delta]['text'] = array('#markup' => $output);
            }
            break;
        case 'cms_term_reference_field_table_row_formatter':
            foreach ($items as $delta => $item) {
                $term = entity_load_unchanged('taxonomy_term', $item['tid']);
                $uri = entity_uri('taxonomy_term', $term);
                $element[$delta] = array(
                  '#type' => 'link',
                  '#title' => $term->name,
                  '#href' => $uri['path'],
                  '#options' => $uri['options'],
                  '#settings' => $settings,
                );
            }
            break;
        case 'cms_iucn_status_formatter':
            foreach ($items as $delta => $value) {
                $element[$delta]['#settings'] = array('allowed_values' => $field['settings']['allowed_values']);
                $element[$delta]['text'] = array('#markup' => $value);
            }
            break;
        case 'cms_link_formatter':
            foreach ($items as $delta => $value) {
                $element[$delta]['link'] = array('#markup' => $value);
            }
            break;
        case 'cms_region_formatter':
            foreach ($items as $delta => $item) {
                $element[$delta]['#settings'] = $settings;
                $output = cms_text_sanitize($instance, $langcode, $item, 'value');
                if (in_array($output , array_keys(CMSUtils::$regions))) {
                    $output = CMSUtils::$regions[$output];
                }
                $element[$delta]['text'] = array('#markup' => $output);
            }
            break;
        case 'cms_gallery_formatter':
            foreach ($items as $delta => $item) {
                $item['path'] = file_create_url($item['uri']);
                $item['attributes'] = array();
                $image = theme_image($item);
                $element[$delta] = array(
                    '#markup' => $image,
                );
            }
            break;
        case 'cms_country_table_row_formatter':
            foreach ($items as $delta => $item) {
                if (isset($item['target_id']) && (!empty($item['target_id']))) {
                    $country = node_load($item['target_id']);
                    $element[$delta]['text'] = (!empty($country)) ? $country->title : '';
                }else {
                    $element[$delta]['text'] = '';
                }
            }
            break;
        case 'cms_boolean_formatter':
            foreach ($items as $delta => $value) {
                $element[$delta]['text'] = array('#markup' => $value);
            }
            break;
        case 'cms_date_formatter':
            foreach ($items as $delta => $value) {
                $element[$delta]['#settings'] = $settings;
                $element[$delta]['text'] = $value;
            }
            break;
        case 'cms_appendix_formatter':
            foreach ($items as $delta => $value) {
                $element[$delta]['text'] = $value;
            }
            break;
        case 'cms_legal_instruments_formatter':
            foreach ($items as $delta => $value) {
                if (array_key_exists('target_id', $value)) {
                    $ob = @entity_load_single('node', $value['target_id']);
                    $element[$delta]['#instance'] = $ob;
                    $element[$delta]['text'] = $value;
                }else {
                    $ob = field_collection_item_load($value['value']);
                    $instrument_id = cms_extract_single_value($ob->field_species_instrument, $langcode, 'target_id');
                    $instrument = CMSLegalInstrument::cms_instrument_title_by_id($instrument_id);
                    $element[$delta]['instrument'] = $instrument;
                    $date = strtotime(cms_extract_single_value($ob->field_species_instrument_date, $langcode, 'value'));
                    if ($date) {
                        $element[$delta]['date'] = date("Y", $date);
                    }
                }
            }
            break;
        case 'cms_legal_instruments_signed_by_formatter':
            foreach ($items as $delta => $value) {
                foreach ($items as $delta => $value) {
                    if (array_key_exists('value', $value)) {
                        $ob = field_collection_item_load($value['value']);
                        $country_iso2 = cms_extract_single_value($ob->field_country, $langcode, 'iso2');
                        $country = Country::get_by_iso2($country_iso2);
                        $element[$delta]['country'] = ($country) ? $country->title : '';

                        $date = strtotime(cms_extract_single_value($ob->field_date, $langcode, 'value'));
                        $element[$delta]['date'] = ($date) ? date("d F Y", $date) : '';
                        $status = (property_exists($ob, 'field_status')) ? taxonomy_term_load($ob->field_status[$langcode][0]['tid']) : '';
                        $element[$delta]['status'] = (property_exists($status, 'name')) ? $status->name : '';
                        $element[$delta]['ob'] = $ob;
                    }else {
                        $ob = $value;
                        $element[$delta]['country'] = $ob['field_country'];
                        $element[$delta]['date'] = $ob['field_date'];
                        $element[$delta]['status'] = $ob['field_status'];
                        $element[$delta]['ob'] = $ob;
                    }
                }
            }
            break;
        case 'cms_species_population_instrument_formatter':
            foreach ($items as $delta => $value) {
                if (array_key_exists('value', $value)) {
                    $ob = field_collection_item_load($value['value']);
                    $instrument_id = cms_extract_single_value($ob->field_species_pop_li, $langcode, 'target_id');
                    $instrument = @entity_load('node', array($instrument_id));
                    $element[$delta]['instrument'] = $instrument[$instrument_id];
                    $element[$delta]['value'] = cms_extract_single_value($ob->field_species_pop_v, $langcode, 'value');
                    $element[$delta]['ob'] = $ob;
                }else {
                    $ob = $value;
                    $element[$delta]['instrument'] = $ob['field_species_pop_li'];
                    $element[$delta]['value'] = $ob['field_species_pop_v'];
                    $element[$delta]['ob'] = $ob;
                }
            }
            break;
        case 'cms_species_population_size_formatter':
            foreach ($items as $delta => $value) {
                if (array_key_exists('value', $value)) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $population_name = (property_exists($ob, 'field_species_pop_size_r')) ? taxonomy_term_load($ob->field_species_pop_size_r[$langcode][0]['tid']) : '';
                        $element[$delta]['region'] = (property_exists($population_name, 'name')) ? $population_name->name : '';
                        $element[$delta]['size_years'] = (property_exists($ob, 'field_species_pop_size_i')) ? cms_extract_single_value($ob->field_species_pop_size_i, $langcode, 'value') : '';
                        $element[$delta]['size_quality'] = (property_exists($ob, 'field_species_pop_size_q')) ? cms_extract_single_value($ob->field_species_pop_size_q, $langcode, 'value') : '';
                        $element[$delta]['estimate'] = (property_exists($ob, 'field_species_pop_size_e')) ? cms_extract_single_value($ob->field_species_pop_size_e, $langcode, 'value') : '';
                        $element[$delta]['size_reference'] = (property_exists($ob, 'field_species_pop_size_ref')) ? cms_extract_single_value($ob->field_species_pop_size_ref, $langcode, 'value') : '';
                        $element[$delta]['size_notes'] = (property_exists($ob, 'field_species_pop_size_n')) ? cms_extract_single_value($ob->field_species_pop_size_n, $langcode, 'value') : '';
                        $element[$delta]['trend_years'] = (property_exists($ob, 'field_species_pop_trend_i')) ? cms_extract_single_value($ob->field_species_pop_trend_i, $langcode, 'value') : '';
                        $element[$delta]['trend_quality'] = (property_exists($ob, 'field_species_pop_trend_q')) ? cms_extract_single_value($ob->field_species_pop_trend_q, $langcode, 'value') : '';
                        $element[$delta]['trend'] = (property_exists($ob, 'field_species_pop_trend_t')) ? cms_extract_single_value($ob->field_species_pop_trend_t, $langcode, 'value') : '';
                        $element[$delta]['trend_reference'] = (property_exists($ob, 'field_species_pop_trend_ref')) ? cms_extract_single_value($ob->field_species_pop_trend_ref, $langcode, 'value') : '';
                        $element[$delta]['trend_notes'] = (property_exists($ob, 'field_species_pop_trend_n')) ? cms_extract_single_value($ob->field_species_pop_trend_n, $langcode, 'value') : '';
                    }
                }else {
                    $ob = $value;
                    $element[$delta]['region'] = $ob['field_species_pop_size_r'];
                    $element[$delta]['size_years'] = $ob['field_species_pop_size_i'];
                    $element[$delta]['size_quality'] = $ob['field_species_pop_size_q'];
                    $element[$delta]['estimate'] = $ob['field_species_pop_size_e'];
                    $element[$delta]['size_reference'] = $ob['field_species_pop_size_ref'];
                    $element[$delta]['size_notes'] = $ob['field_species_pop_size_n'];
                    $element[$delta]['trend_years'] = $ob['field_species_pop_trend_i'];
                    $element[$delta]['trend_quality'] = $ob['field_species_pop_trend_q'];
                    $element[$delta]['trend'] = $ob['field_species_pop_trend_t'];
                    $element[$delta]['trend_reference'] = $ob['field_species_pop_trend_ref'];
                    $element[$delta]['trend_notes'] = $ob['field_species_pop_trend_n'];
                }
            }
            break;
        case 'cms_species_population_trend_formatter':
            foreach ($items as $delta => $value) {
                if (array_key_exists('value', $value)) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $element[$delta]['region'] = (property_exists($ob, 'field_species_pop_trend_r')) ? cms_extract_single_value($ob->field_species_pop_trend_r, $langcode, 'value') : '';
                        $element[$delta]['years'] = (property_exists($ob, 'field_species_pop_trend_i')) ? cms_extract_single_value($ob->field_species_pop_trend_i, $langcode, 'value') : '';
                        $element[$delta]['quality'] = (property_exists($ob, 'field_species_pop_trend_q')) ? cms_extract_single_value($ob->field_species_pop_trend_q, $langcode, 'value') : '';
                        $element[$delta]['trend'] = (property_exists($ob, 'field_species_pop_trend_t')) ? cms_extract_single_value($ob->field_species_pop_trend_t, $langcode, 'value') : '';
                        $element[$delta]['reference'] = (property_exists($ob, 'field_species_pop_trend_ref')) ? cms_extract_single_value($ob->field_species_pop_trend_ref, $langcode, 'value') : '';
                        $element[$delta]['notes'] = (property_exists($ob, 'field_species_pop_trend_n')) ? cms_extract_single_value($ob->field_species_pop_trend_n, $langcode, 'value') : '';
                    }
                }else {
                    $ob = $value;
                    $element[$delta]['region'] = $ob['field_species_pop_trend_r'];
                    $element[$delta]['years'] = $ob['field_species_pop_trend_i'];
                    $element[$delta]['quality'] = $ob['field_species_pop_trend_q'];
                    $element[$delta]['trend'] = $ob['field_species_pop_trend_t'];
                    $element[$delta]['reference'] = $ob['field_species_pop_trend_ref'];
                    $element[$delta]['notes'] = $ob['field_species_pop_trend_n'];
                }
            }
            break;
        case 'cms_range_state_formatter':
            foreach ($items as $delta => $value) {
                if (array_key_exists('value', $value)) {
                    $ob = field_collection_item_load($value['value']);
                    $country_nid = cms_extract_single_value($ob->field_species_range_state, $langcode, 'target_id');
                    $country = node_load($country_nid);
                    $element[$delta]['country'] = ($country) ? $country->title : '';
                    $element[$delta]['territories'] = cms_extract_single_value($ob->field_species_territories, $langcode, 'value');


                    $field_name = 'field_species_range_state_status';
                    $status_field = field_info_field($field_name);
                    $allowed_values = $status_field['settings']['allowed_values'];
                    $status = cms_extract_single_value($ob->field_species_range_state_status, $langcode, 'value');
                    if (!empty($allowed_values) && array_key_exists($status, $allowed_values)) {
                        $status = $allowed_values[$status];
                    }
                    $element[$delta]['status'] = $status;
                }else {
                    $element[$delta]['country'] = $ob['field_species_range_state'];
                    $element[$delta]['territories'] = $ob['field_species_territories'];
                    $element[$delta]['status'] = $ob['field_species_range_state_status'];
                }
            }
            break;

        case 'cms_project_activity_formatter':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $element[$delta]['description'] = (property_exists($ob, 'field_project_activity_desc')) ? cms_extract_single_value($ob->field_project_activity_desc, $langcode, 'value') : '';
                        $start_date = strtotime(cms_extract_single_value($ob->field_project_activity_start, $langcode, 'value'));
                        $element[$delta]['start_date'] = ($start_date) ? date("d F Y", $start_date) : '';
                        $end_date = strtotime(cms_extract_single_value($ob->field_project_activity_end, $langcode, 'value'));
                        $element[$delta]['end_date'] = ($end_date) ? date("d F Y", $end_date) : '';
                        $element[$delta]['responsibility'] = (property_exists($ob, 'field_project_activity_resp')) ? cms_extract_single_value($ob->field_project_activity_resp, $langcode, 'value') : '';
                        $element[$delta]['output'] = (property_exists($ob, 'field_project_activity_output')) ? cms_extract_single_value($ob->field_project_activity_output, $langcode, 'value') : '';
                    }
                }else {
                    $ob = $value;
                    $element[$delta]['description'] = $ob['field_project_activity_desc'];
                    $element[$delta]['start_date'] = $ob['field_project_activity_start'];
                    $element[$delta]['end_date'] = $ob['ffield_project_activity_end'];
                    $element[$delta]['responsibility'] = $ob['field_project_activity_resp'];
                    $element[$delta]['output'] = $ob['field_project_activity_output'];
                }
            }
            break;
        case 'cms_project_payments_formatter':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $element[$delta]['amount'] = (property_exists($ob, 'field_project_payment_amount')) ? cms_extract_single_value($ob->field_project_payment_amount, $langcode, 'value') : '';
                        $date = strtotime(cms_extract_single_value($ob->field_project_payment_date, $langcode, 'value'));
                        $element[$delta]['date'] = ($date) ? date("d F Y", $date) : '';
                        $element[$delta]['comments'] = (property_exists($ob, 'field_project_payment_comments')) ? cms_extract_single_value($ob->field_project_payment_comments, $langcode, 'value') : '';
                        $element[$delta]['pyin'] = (property_exists($ob, 'field_project_payment_pyin')) ? cms_extract_single_value($ob->field_project_payment_pyin, $langcode, 'value') : '';
                    }
                }else {
                    $ob = $value;
                    $element[$delta]['amount'] = $ob['field_project_payment_amount'];
                    $element[$delta]['date'] = $ob['field_project_payment_date'];
                    $element[$delta]['comments'] = $ob['field_project_payment_comments'];
                    $element[$delta]['pyin'] = $ob['field_project_payment_pyin'];
                }
            }
            break;
        case 'cms_project_bac_formatter':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $year = strtotime(cms_extract_single_value($ob->field_project_bac_year, $langcode, 'value'));
                        $element[$delta]['year'] = ($year) ? date("Y", $year) : '';

                        $element[$delta]['fund'] = (property_exists($ob, 'field_project_bac_fund')) ? cms_extract_single_value($ob->field_project_bac_fund, $langcode, 'value') : '';
                        $element[$delta]['ou'] = (property_exists($ob, 'field_project_bac_ou')) ? cms_extract_single_value($ob->field_project_bac_ou, $langcode, 'value') : '';
                        $element[$delta]['project_number'] = (property_exists($ob, 'field_project_bac_project_number')) ? cms_extract_single_value($ob->field_project_bac_project_number, $langcode, 'value') : '';
                        $element[$delta]['programme'] = (property_exists($ob, 'field_project_bac_programme')) ? cms_extract_single_value($ob->field_project_bac_programme, $langcode, 'value') : '';
                        $element[$delta]['object_code'] = (property_exists($ob, 'field_project_bac_object_code')) ? cms_extract_single_value($ob->field_project_bac_object_code, $langcode, 'value') : '';
                    }
                }else {
                    $ob = $value;
                    $element[$delta]['year'] = $ob['field_project_bac_year'];
                    $element[$delta]['fund'] = $ob['field_project_bac_fund'];
                    $element[$delta]['ou'] = $ob['field_project_bac_ou'];
                    $element[$delta]['project_number'] = $ob['field_project_bac_project_number'];
                    $element[$delta]['programme'] = $ob['field_project_bac_programme'];
                    $element[$delta]['object_code'] = $ob['field_project_object_code'];
                }
            }
            break;
        case 'cms_project_funding_formatter':
            foreach ($items as $delta => $value) {
                $ob = field_collection_item_load($value['value']);
                $element[$delta]['amount'] = cms_extract_single_value($ob->field_project_funds_req_amount, $langcode, 'value');
                $element[$delta]['currency'] = (property_exists($ob, 'field_project_funds_req_amount_c') && (!empty($ob->field_project_funds_req_amount_c))) ? taxonomy_term_load($ob->field_project_funds_req_amount_c[$langcode][0]['tid']) : '';
            }
            break;
        case 'cms_country_status_formatter':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $ob = field_collection_item_load($value['value']);
                        $country_nid = cms_extract_single_value($ob->field_species_status_country, $langcode, 'target_id');
                        $country = node_load($country_nid);
                        $element[$delta]['country'] = (!empty($country)) ? $country : '';
                        $status = (property_exists($ob, 'field_species_aewa_status')) ? taxonomy_term_load($ob->field_species_aewa_status[$langcode][0]['tid']) : '';
                        $element[$delta]['status'] = (is_object($status) && property_exists($status, 'name')) ? $status->name : '';
                    }
                }else {
                    $element[$delta]['country'] = $value['field_species_status_country'];
                    $element[$delta]['status'] = $value['field_species_aewa_status'];
                }
            }
            break;
        case 'cms_aewa_population_status_formatter':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    $population_name = (property_exists($ob, 'field_aewa_pop_status_name') && (!empty($ob->field_aewa_pop_status_name))) ? taxonomy_term_load($ob->field_aewa_pop_status_name[$langcode][0]['tid']) : '';
                    $element[$delta]['field_aewa_pop_status_name'] = (property_exists($population_name, 'name')) ? $population_name->name : '';

                    $element[$delta]['field_aewa_pop_status_col_a'] = array();
                    if (property_exists($ob, 'field_aewa_pop_status_col_a')) {
                        foreach ($ob->field_aewa_pop_status_col_a[$langcode] as $index => $col_a_fc) {
                            $col_a = field_collection_item_load($col_a_fc['value']);
                            $status = @taxonomy_term_load($col_a->field_pop_status_col_a_status[$langcode][0]['tid']);
                            $element[$delta]['field_aewa_pop_status_col_a'][$index]['field_pop_status_col_a_status'] = ($status) ? $status->name : '';
                            $element[$delta]['field_aewa_pop_status_col_a'][$index]['field_pop_status_col_a_unknown'] = ($col_a->field_pop_status_col_a_unknown[$langcode][0]['value']);
                            $element[$delta]['field_aewa_pop_status_col_a'][$index]['field_pop_status_col_a_hunting'] = ($col_a->field_pop_status_col_a_hunting[$langcode][0]['value']);
                        }
                    }

                    $element[$delta]['field_aewa_pop_status_col_b'] = array();
                    if (property_exists($ob, 'field_aewa_pop_status_col_b')) {
                        foreach ($ob->field_aewa_pop_status_col_b[$langcode] as $index => $col_b_fc) {
                            $col_b = field_collection_item_load($col_b_fc['value']);
                            $status = @taxonomy_term_load($col_b->field_pop_status_col_b_status[$langcode][0]['tid']);
                            $element[$delta]['field_aewa_pop_status_col_b'][$index]['field_pop_status_col_b_status'] = ($status) ? $status->name : '';
                            $element[$delta]['field_aewa_pop_status_col_b'][$index]['field_pop_status_col_b_unknown'] = ($col_b->field_pop_status_col_b_unknown[$langcode][0]['value']);
                            $element[$delta]['field_aewa_pop_status_col_b'][$index]['field_pop_status_col_b_hunting'] = ($col_b->field_pop_status_col_b_hunting[$langcode][0]['value']);
                        }
                    }

                    $element[$delta]['field_aewa_pop_status_col_c'] = array();
                    if (property_exists($ob, 'field_aewa_pop_status_col_c')) {
                        foreach ($ob->field_aewa_pop_status_col_c[$langcode] as $index => $col_c_fc) {
                            $col_c = field_collection_item_load($col_c_fc['value']);
                            $status = @taxonomy_term_load($col_c->field_pop_status_col_c_status[$langcode][0]['tid']);
                            $element[$delta]['field_aewa_pop_status_col_c'][$index]['field_pop_status_col_c_status'] = ($status) ? $status->name : '';
                            $element[$delta]['field_aewa_pop_status_col_c'][$index]['field_pop_status_col_c_unknown'] = ($col_c->field_pop_status_col_c_unknown[$langcode][0]['value']);
                            $element[$delta]['field_aewa_pop_status_col_c'][$index]['field_pop_status_col_c_hunting'] = ($col_c->field_pop_status_col_c_hunting[$langcode][0]['value']);
                        }
                    }
                }else {
                    $element[$delta] = $value;
                }
            }
            break;
        case 'cms_threats_formmater':
            foreach ($items as $delta => $value) {
                if (in_array('value', array_keys($value))) {
                    $ob = field_collection_item_load($value['value']);
                    if ($ob) {
                        $ob = field_collection_item_load($value['value']);
                        $threat = NULL;
                        if (!empty($ob->field_species_threat)) {
                            $threat = taxonomy_term_load($ob->field_species_threat[$langcode][0]['tid']);
                        }

                        $element[$delta]['threat'] = '';
                        $element[$delta]['notes'] = '';
                        if ($threat) {
                            $element[$delta]['threat'] = $threat->name;
                        }

                        if (property_exists($ob, 'field_species_threat_notes') && (!empty($ob->field_species_threat_notes))) {
                            $element[$delta]['notes'] = $ob->field_species_threat_notes[$langcode][0]['value'];
                        }
                    }
                }else {
                    $element[$delta]['threat'] = $value['field_species_threat'];
                    $element[$delta]['notes'] = $value['field_species_threat_notes'];
                }
            }
            break;
    }
    return $element;
}


/**
 * Hook theme_hook().
 *
 * Override in theme with THEME_theme()
 */
function cms_theme() {
    return array(
        // Override in theme with themename_cms_field_table_row_formatter()
        'cms_field_table_row_formatter' => array('render element' => 'item'),
        'cms_term_reference_field_table_row_formatter' => array('render element' => 'item'),
        'cms_region_formatter' => array('render element' => 'item'),
        'cms_iucn_status_formatter' => array('render element' => 'item'),
        'cms_link_formatter' => array('render element' => 'item'),
        'cms_gallery_formatter' => array('render element' => 'item'),
        'cms_country_table_row_formatter' => array('render element' => 'item'),
        'cms_boolean_formatter' => array('render element' => 'item'),
        'cms_appendix_formatter' => array('render element' => 'item'),
        'cms_date_formatter' => array('render element' => 'item'),
        'cms_legal_instruments_formatter' => array('render element' => 'item'),
        'cms_legal_instruments_signed_by_formatter' => array('render element' => 'item'),
        'cms_species_population_instrument_formatter' => array('render element' => 'item'),
        'cms_species_population_size_formatter' => array('render element' => 'item'),
        'cms_species_population_trend_formatter' => array('render element' => 'item'),
        'cms_range_state_formatter' => array('render element' => 'item'),
        'cms_project_activity_formatter' => array('render element' => 'item'),
        'cms_project_payments_formatter' => array('render element' => 'item'),
        'cms_project_bac_formatter' => array('render element' => 'item'),
        'cms_project_funding_formatter' => array('render element' => 'item'),
        'cms_country_status_formatter' => array('render element' => 'item'),
        'cms_aewa_population_status_formatter' => array('render element' => 'item'),
        'cms_threats_formmater' => array('render element' => 'item'),
    );
}


/**
 * Generic field formatter for two-column values
 * <tr>
 *     <th>Label</th>
 *     <td>Value</td>
 * </tr>
 * @param array $variables Render data
 */
function theme_cms_field_table_row_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $values = $item['#items'];
        $ret = '';
        foreach ($values as $index => $item_value) {
            $value = $item[$index];
            if($value['#settings']['render_link'] != 0) {
                $v = render($value);
                if($value['#settings']['render_link'] = 2) {
                    $v = sprintf('<a target="_blank" href="%s" title="%s">%s</a>', $v, t('Click to open this link in new window'), $v);
                } else {
                    $v = sprintf('<a href="%s">%s</a>', $v, $v);
                }
            } else {
                $v = render($value);
            }

            $ret .= $v;
            if (($index + 1) < count($values)) {
                $ret .= ", ";
            }
        }

        return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $ret);
    }
}

function theme_cms_term_reference_field_table_row_formatter($variables) {
    extract($variables);

    if (!empty($item['#items'])) {
        $output = sprintf("<tr><th>%s</th><td>", $item['#title']);

        foreach ($item['#items'] as $index => $term_data) {
            $value = $item[$index];
            $title = $value['#title'];
            $href = $value['#href'];
            if ($index + 1 == count($item['#items'])) {
                $output .= ($value['#settings']['render_plain_text'] == 0) ? l($title, $href) : $title;
            }else {
                $output .= ($value['#settings']['render_plain_text'] == 0) ? l($title, $href) : $title;
                $output .= '<br />';
            }
        }

        $output .= "</td></tr>";
        return $output;
    }
}

function theme_cms_country_table_row_formatter($variables) {
    extract($variables);

    if (!empty($item['#items'])) {
        foreach ($item['#items'] as $index => $data) {
            return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $item[$index]['text']);
        }
    }
}

function theme_cms_gallery_formatter($variables) {
    extract($variables);

    if (!empty($item['#items'])) {
        $output = '
        <div class="carousel-inner">
            <div class="active item">
                ' . $item[0]['#markup'] . '
            </div>';
        unset($item['#items'][0]);

        foreach ($item['#items'] as $index => $image) {
            $output .= '<div class="item">' . $item[$index]['#markup'] . '</div>';
        }

        $output .= '</div>';
        return $output;
    }
}

function theme_cms_region_formatter($variables) {
    extract($variables);

    if (!empty($item['#items'])) {
        foreach ($item['#items'] as $index => $data) {
            return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $item[$index]['text']['#markup']);
        }
    }
}

/**
 * Formatter for the IUCN status (from pre-defined values)
 * @param array $variables Render data
 */
function theme_cms_iucn_status_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $value = $item['#items'][0]['value'];
        $allowed = $item[0]['#settings']['allowed_values'];
        if(isset($allowed[$value])) {
            $value = $allowed[$value];
            return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $value);
        }
    }
}


/**
 * Formatter for link (Horizontal table row)
 * @param array $variables Render data
 */
function theme_cms_link_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $value = $item['#items'][0];
        return sprintf('<tr><th>%s</th><td><a href="%s">%s</a></td></tr>', $item['#title'], $value['uri'], $value['title']);
    }
}

/**
 * Generic boolean field formatter
 * @param array $variables Render data
 */
function theme_cms_boolean_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $value = $item['#items'][0]['value'] == 1 ? t('Yes') : t('No');
        return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $value);
    }
}


/**
 * Formatter for the species appendix
 * @param array $variables Render data
 */
function theme_cms_appendix_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $value .= $st['value'];
            if($idx < count($item['#items']) - 1) {
                $value .= ', ';
            }
        }
        return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $value);
    }
}


/**
 * Generic date formatter
 * @param array $variables Render data
 */
function theme_cms_date_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $title = $item['#title'];
        $item = $item[0];
        $type = $item['#settings']['format'];
        $value = '';
        if(!empty($item['text']['value'])) {
            $value = format_date(strtotime($item['text']['value']), $type);
        }
        return sprintf('<tr><th>%s</th><td>%s</td></tr>', $title, $value);
    }
}


/**
 * Formatter for the legal instruments of a species
 * @param array $variables Render data
 */
function theme_cms_legal_instruments_formatter($variables) {
    extract($variables); // $item
    if(!empty($item['#items'])) {
        $title = $item['#title'];
        $is_fieldcollection = ($item['#field_type'] == 'field_collection') ? TRUE : FALSE;
        $ret = ($item['#field_type'] == 'field_collection') ? array() : '';

        foreach($item['#items'] as $idx => $st) {
            if (array_key_exists('#instance', $item[$idx])) {
                $is_fieldcollection = FALSE;
                $ret .= '<a href="/node/' . $item[$idx]['#instance']->nid . '">' . $item[$idx]['#instance']->title . '</a>';
                if($idx < count($item['#items']) - 1) {
                    $ret .= ', ';
                }
            }else {
                if (in_array('value', array_keys($st))) {
                    $ob = $item[$idx];
                }else {
                    $ob = $st;
                }

                if (is_object($ob['instrument'])) {
                    $v = $ob['instrument']->title;
                }else {
                    $v = $ob['instrument'];
                }

                if(!empty($ob['date'])) {
                    $v = sprintf('%s (%s)', $v, $ob['date']);
                } else {
                    $v = sprintf('%s', $v);
                }
                $ret[] = $v;
            }
        }

        if ($is_fieldcollection) {
            return sprintf('<tr><th>%s</th><td>%s</td></tr>', $title, implode(', ', $ret));
        }else {
            return sprintf('<tr><th>%s</th><td>%s</td></tr>', $item['#title'], $ret);
        }
    }
}

function theme_cms_legal_instruments_signed_by_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $row = $item[$idx];
            if (is_object($row['country']) && property_exists($row['country'], 'title')) {
                $country_label = $row['country']->title;
            }else {
                $country_label = $row['country'];
            }

            $date = $row['date'];
            $status = $row['status'];
            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td></tr>', $country_label, $date, $status);
        }

        return $ret;
    }
}


/**
 * Formatter for the species population per instrument
 * @param array $variables Render data
 */
function theme_cms_species_population_instrument_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $row = $item[$idx];
            if (is_object($row['instrument']) && property_exists($row['instrument'], 'title')) {
                $instrument_label = $row['instrument']->title;
            }else {
                $instrument_label = $row['instrument'];
            }

            $value = $row['value'];
            $ret .= sprintf('<tr><td>%s</td><td>%s</td></tr>', $instrument_label, $value);
        }
        return $ret;
    }
}


/**
 * Formatter for the species range states
 * @param array $variables Render data
 */
function theme_cms_range_state_formatter($variables) {
    extract($variables); // $item
    $ret = array();
    if(!empty($item['#items'])) {
        foreach($item['#items'] as $idx => $st) {
            $v = '';
            if (in_array('value', array_keys($st))) {
                $ob = $item[$idx];
            }else {
                $ob = $st;
            }

            $country = '';
            if (array_key_exists('country', $ob)) {
                $country = $ob['country'];
            }elseif (array_key_exists('field_species_range_state', $ob)) {
                $country = $ob['field_species_range_state'];
            }

            if ($country) {
                $v = $country;
            }

            $territories = '';
            if (array_key_exists('field_species_territories', $ob)) {
                $territories = $ob['field_species_territories'];
            }elseif (!empty($ob['territories'])) {
                $territories = $ob['territories'];
            }

            if($territories) {
                $v = sprintf('%s (%s)', $v, $territories);
            } else {
                $v = sprintf('%s', $v);
            }

            $status = '';
            if (array_key_exists('status', $ob)) {
                $status = $ob['status'];
            }elseif (!empty($ob['status'])) {
                $status = $ob['status'];
            }

            if($status) {
                $v = sprintf('%s (Status: %s)', $v, $status);
            } else {
                $v = sprintf('%s', $v);
            }

            $ret[] = $v;
        }
        return implode(', ', $ret);
    }
}

/**
 * Formatter for the species population size
 * @param array $variables Render data
 */
function theme_cms_species_population_size_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $region = $ob['region'];
            $size_years = $ob['size_years'];
            $size_quality = $ob['size_quality'];
            $estimate = $ob['estimate'];
            $size_notes = $ob['size_notes'];
            $size_reference_title = $size_reference = $ob['size_reference'];
            $trend_years = $ob['trend_years'];
            $trend_quality = $ob['trend_quality'];
            $trend = $ob['trend'];
            $trend_notes = $ob['trend_notes'];
            $trend_reference_title = $trend_reference = $ob['trend_reference'];

            $ret .= sprintf('<tr><td rowspan="2">%s</td><td>%s</td><td>%s</td><td>%s</td>',
                            $region, $size_years, $size_quality, $estimate);

            if (strlen($size_reference_title) > 50) {
                $size_reference_title = substr($size_reference_title, 0, 50);
                $ret .= sprintf('<td>
                                %s
                                <a href="javascript:void(0);"
                                   class="ref-popover"
                                   rel="popover"
                                   data-original-title="Reference"
                                   data-trigger="hover"
                                   data-placement="left"
                                   data-content="%s">[' . t('more') . ']</a>
                                </td>', $size_reference_title, $size_reference);
            }else {
                $ret .= sprintf('<td>%s</td>', $size_reference);
            }

            $ret .= sprintf('<td>%s</td></tr>', $size_notes);

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td>',
                           $trend_years, $trend_quality, $trend);

            if (strlen($trend_reference_title) > 50) {
                $trend_reference_title = substr($trend_reference_title, 0, 50);
                $ret .= sprintf('<td>
                                %s
                                <a href="javascript:void(0);"
                                   class="ref-popover"
                                   rel="popover"
                                   data-original-title="Reference"
                                   data-trigger="hover"
                                   data-placement="left"
                                   data-content="%s">[' . t('more') . ']</a>
                                </td>', $trend_reference_title, $trend_reference);
            }else {
                $ret .= sprintf('<td>%s</td>', $trend_reference);
            }

            $ret .= sprintf('<td>%s</td></tr>', $trend_notes);
        }
        return $ret;
    }
}


/**
 * Formatter for the species population trend
 * @param array $variables Render data
 */
function theme_cms_species_population_trend_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $region = $ob['region'];
            $years = $ob['years'];
            $quality = $ob['quality'];
            $trend = $ob['trend'];
            $reference_title = $reference = $ob['reference'];
            $notes = $ob['notes'];

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td>',
                            $region, $years, $quality, $trend);

            if (strlen($reference_title) > 50) {
                $reference_title = substr($reference_title, 0, 50);
                $ret .= sprintf('<td>
                                %s
                                <a href="javascript:void(0);"
                                   class="ref-popover"
                                   rel="popover"
                                   data-original-title="Reference"
                                   data-trigger="hover"
                                   data-placement="left"
                                   data-content="%s">[' . t('more') . ']</a>
                                </td>', $reference_title, $reference);
            }else {
                $ret .= sprintf('<td>%s</td>', $reference);
            }

            $ret .= sprintf('<td>%s</td></tr>', $notes);
        }
        return $ret;
    }
}

function theme_cms_project_activity_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $description = $ob['description'];
            $start_date = $ob['start_date'];
            $end_date = $ob['end_date'];
            $responsibility = $ob['responsibility'];
            $output = $reference = $ob['output'];

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>',
                            $description, $start_date, $end_date, $responsibility, $output);
        }
        return $ret;
    }
}

function theme_cms_project_payments_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $amount = $ob['amount'];
            $date = $ob['date'];
            $comments = $ob['comments'];
            $pyin = $reference = $ob['pyin'];

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>',
                            $amount, $date, $comments, $pyin);
        }
        return $ret;
    }
}

function theme_cms_project_bac_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $year = $ob['year'];
            $fund = $ob['fund'];
            $ou = $ob['ou'];
            $project_number = $ob['project_number'];
            $programme = $ob['programme'];
            $object_code = $ob['object_code'];

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>',
                            $year, $fund, $ou, $project_number, $programme, $object_code);
        }

        return $ret;
    }
}

/**
 * Formatter for the species population trend
 * @param array $variables Render data
 */
function theme_cms_project_funding_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            $amount = $ob['amount'];
            $currency = (is_object($ob['currency'])) ? $ob['currency']->name : '';

            $ret .= sprintf('<tr><th>%s</th><td>%s %s</td></tr>',
                            $item['#title'], $amount, $currency);
        }
        return $ret;
    }
}

/**
 * Formatter for the species range states
 * @param array $variables Render data
 */
function theme_cms_country_status_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];
            if (is_object($ob['country'])) {
                $country = $ob['country']->title;
            }else {
                $country = ucfirst($ob['country']);
            }

            $status = (!empty($ob['status'])) ? $ob['status'] : '';

            $ret .= sprintf('<tr><td>%s</td><td>%s</td></tr>',
                            $country, $status);
        }

        return $ret;
    }
}

/**
 * Formatter for the species range states
 * @param array $variables Render data
 */
function theme_cms_aewa_population_status_formatter($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];

            $population_name = (!empty($ob['field_aewa_pop_status_name'])) ? $ob['field_aewa_pop_status_name'] : '';

            $column_a = '';
            foreach ($ob['field_aewa_pop_status_col_a'] as $index => $value) {
                $status = ($value['field_pop_status_col_a_unknown']) ? '(' . $value['field_pop_status_col_a_status'] . ')' : $value['field_pop_status_col_a_status'];
                $status = ($value['field_pop_status_col_a_hunting']) ? $status . '*' : $status;
                $column_a .= $status;
                if (($index + 1) < count($ob['field_aewa_pop_status_col_a'])) {
                    $column_a .= ' ';
                }
            }

            $column_b = '';
            foreach ($ob['field_aewa_pop_status_col_b'] as $index => $value) {
                $status = ($value['field_pop_status_col_b_unknown']) ? '(' . $value['field_pop_status_col_b_status'] . ')' : $value['field_pop_status_col_b_status'];
                $status = ($value['field_pop_status_col_b_hunting']) ? $status . '*' : $status;
                $column_b .= $status;
                if (($index + 1) < count($ob['field_aewa_pop_status_col_b'])) {
                    $column_b .= ' ';
                }
            }

            $column_c = '';
            foreach ($ob['field_aewa_pop_status_col_c'] as $index => $value) {
                $status = ($value['field_pop_status_col_c_unknown']) ? '(' . $value['field_pop_status_col_c_status'] . ')' : $value['field_pop_status_col_c_status'];
                $status = ($value['field_pop_status_col_c_hunting']) ? $status . '*' : $status;
                $column_c .= $status;
                if (($index + 1) < count($ob['field_aewa_pop_status_col_c'])) {
                    $column_c .= ' ';
                }
            }

            $ret .= sprintf('<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>',
                            $population_name, $column_a, $column_b, $column_c);
        }

        return $ret;
    }
}

function theme_cms_threats_formmater($variables) {
    extract($variables); // $item
    $ret = '';
    if(!empty($item['#items'])) {
        $value = '';
        foreach($item['#items'] as $idx => $st) {
            $ob = $item[$idx];

            $ret .= sprintf('<tr><td>%s</td><td>%s</td></tr>',
                            $ob['threat'], $ob['notes']);
        }

        return $ret;
    }
}
