<?php

/**
 * Function used in Services views to get some text/date field array of values
 *
 * @param   string  $field_name
 * @param   node    $node
 *
 * @author Dragos Dumitrescu
 */

function api_field_values($field_name, $node) {
    return API_CMS::get_api_field_values($field_name, $node);
}



/**
 * Function used in Services views to get some text/date field one value
 *
 * @param   string  $field_name
 * @param   node    $node
 *
 * @author Dragos Dumitrescu
 */

function api_field_single_value($field_name, $node) {
    return current(API_CMS::get_api_field_values($field_name, $node));
}

/**
 * Function used in Services (Views PHP) to return URL
 * @param $node
 * @param bool $absolute
 *
 * @return string
 */

function cms_api_get_url($node, $absolute = TRUE) {
    return url(
            drupal_lookup_path('alias',"node/" . $node->nid),
            array(
                'absolute'=> $absolute,
            )
        );
}

/**
 * Function to return taxonomy terms
 * @param $node
 * @param $field_name
 * @param int $cardinality
 *
 * @return array of multiple terms | string - one term
 */
function cms_api_get_term($node, $field_name, $cardinality = 0) {
    return API_CMS::api_get_taxonomy_term($field_name, $node, $cardinality);
}

function cms_api_entity_get_term_($nid, $field_name, $bundle, $cardinality = 0) {
    return API_CMS::api_entity_get_taxonomy_term($nid, $field_name, $bundle, $cardinality);
}

/**
 * Class API_CMS
 */
class API_CMS {

    /**
     * Function that returns field language used by a node
     *
     * @param $node - node
     * @param $field - field name
     * @param string $type - type of node
     *
     * @return string - language code
     */
    static function get_field_language($node, $field){
        if (!empty($GLOBALS['api_content_types_langcodes'][$node->type])) {
            $langcodes = $GLOBALS['api_content_types_langcodes'];
            if(!empty($langcodes[$node->type][$field])) {
                return $langcodes[$node->type][$field];
            } else {
                return LANGUAGE_NONE;
            }
        } else {
            if(empty($GLOBALS['api_content_types_langcodes'])) {
                $GLOBALS['api_content_types_langcodes'] = array();
            }
            $GLOBALS['api_content_types_langcodes'][$node->type] = field_language('node', $node);
            return $GLOBALS['api_content_types_langcodes'][$node->type][$field];
        }
    }


    /**
     * Function to get an array with collection-field's fields values
     *
     * @param   array   $field_names - array of field names for which return the value (to set just the necessary fields (not like revision_id etc.)
     * @param   string  $field_Collection - field collection
     * @param   string  $lang   - node language
     *
     * @return  array   array of single values of fields
     *
     * @author Dragos Dumitrescu
     */

    static function set_api_fields_coll_field($field_names, $field_collection, $lang = 'und'){
        $result = array();
        foreach ($field_names as $field_key => $field_name) {
            if (isset($field_collection->{$field_key}[$lang])) {
                $field_info = field_info_field($field_key);
                switch($field_info['type']) {
                    case 'taxonomy_term_reference':
                        if ($field_info['cardinality'] > 1) {
                            foreach ($field_collection->{$field_key}[$lang] as $term) {
                                $result[$field_name] []= taxonomy_term_load($term['tid'])->name;
                            }
                        } else {
                            $result[$field_name] = taxonomy_term_load($field_collection->{$field_key}[$lang][0]['tid'])->name;
                        }
                        break;
                    case 'entityreference':
                        $target_type = current($field_info['settings']['handler_settings']['target_bundles']);
                        $result[$field_name] = call_user_func_array('API_CMS::api_get_ref_'.$target_type,
                                array($field_collection->{$field_key}[$lang][0]['target_id']));
                        break;
                    default:
                        if ($field_info['cardinality'] > 1) {
                            foreach ($field_collection->{$field_key}[$lang] as $field) {
                                $result[$field_name] []= $field['value'];
                            }
                        } else {
                            $result[$field_name] = $field_collection->{$field_key}[$lang][0]['value'];
                        }
                        break;
                }
            }
        }
        return $result;
    }

    /**
     * @param $node
     * @param $field_coll_name
     * @param $fields_map
     *
     * @return array
     */
    static function api_get_field_collection_values($node, $field_coll_name, $fields_map) {
        $langcode = API_CMS::get_field_language($node, $field_coll_name);
        foreach ($node->{$field_coll_name}[$langcode] as $field) {
            $ids []= $field['value'];
        }
        $results = array();
        $fields = entity_load('field_collection_item', array($ids));
        foreach ($fields as $field_coll) {
            $result = API_CMS::set_api_fields_coll_field($fields_map, $field_coll, $langcode);
            $results []= $result;
        }
        return $results;
    }

    static function api_get_entity_field_collection_values($nid, $bundle, $field_coll_name, $fields_map) {
        $entity = (object) array(
            'nid' => $nid,
            'vid' => $nid,
            'type' => $bundle,
        );
        $entities = array(
            $nid => $entity,
        );
        $langcode = field_language('node', $entity, $field_coll_name);
        $field_info = field_info_field($field_coll_name);
        field_attach_load('node', $entities,  FIELD_LOAD_CURRENT, array('field_id' => $field_info['id']));
        $ids = array();
        if (!empty($entities[$nid]->{$field_coll_name}[$langcode])) {
            foreach ($entities[$nid]->{$field_coll_name}[$langcode] as $field) {
                $ids []= $field['value'];
            }
        }
        $results = array();
        if (!empty($ids)) {
            $fields = entity_load('field_collection_item', $ids);
            foreach ($fields as $field_coll) {
                $result = API_CMS::set_api_fields_coll_field($fields_map, $field_coll, $langcode);
                $results []= $result;
            }
        }
        return $results;
    }


    /**
     * Function to get an array of term names for a specific field
     *
     * @param   string  $field_name - field name
     * @param   node  $node   - node
     *
     * @return  array   array of term names (string)
     *
     * @author Dragos Dumitrescu
     */

    static function get_api_taxonomy_terms($field_name, $node) {
        $terms = array();
        $langcode = API_CMS::get_field_language($node, $field_name);
        if ( !empty($node->{$field_name}[$langcode]) ) {
            foreach ($node->{$field_name}[$langcode] as $term_ref) {
                $terms []= taxonomy_term_load($term_ref['tid'])->name;
            }
        }
        return $terms;
    }

    /**
     * Function to get an array of term names for a specific field
     *
     * @param   string  $field_name - field name
     * @param   node  $node   - node
     *
     * @return  array   array of term names (string)
     *
     * @author Dragos Dumitrescu
     */

    static function api_get_taxonomy_term($field_name, $node, $cardinality = 0) {
        $terms = null;
        $langcode = API_CMS::get_field_language($node, $field_name);
        $field_info = field_info_field($field_name);
        if ( !empty($node->{$field_name}[$langcode]) ) {
            if ($field_info['cardinality'] > 1 || $cardinality > 1) {
                $terms = array();
                foreach ($node->{$field_name}[$langcode] as $term_ref) {
                    $terms []= taxonomy_term_load($term_ref['tid'])->name;
                }
            } else {
                $terms = taxonomy_term_load($node->{$field_name}[$langcode][0]['tid'])->name;
            }
        }
        return $terms;
    }


    static function api_entity_get_taxonomy_term($nid, $field_name, $bundle, $cardinality = 0) {
        $terms = null;
        $entity = (object) array(
            'nid' => $nid,
            'vid' => $nid,
            'type' => $bundle,
        );
        $entities = array(
                $nid => $entity,
        );
        $langcode = field_language('node', $entity, $field_name);
        $field_info = field_info_field($field_name);
        field_attach_load('node', $entities,  FIELD_LOAD_CURRENT, array('field_id' => $field_info['id']));

        if (!empty($entities[$nid]->{$field_name}[$langcode]) ) {
            if (($field_info['cardinality'] > 1 && $cardinality > 1)
                || ($field_info['cardinality'] > 1 && $cardinality == 0 )) {
                $terms = array();
                foreach ($entities[$nid]->{$field_name}[$langcode] as $term_ref) {
                    $term = taxonomy_term_load($term_ref['tid']);
                    if (!empty($term->name)) {
                        $terms []= $term->name;
                    }
                }
            } else {
                $term = taxonomy_term_load($entities[$nid]->{$field_name}[$langcode][0]['tid']);
                if (!empty($term->name)) {
                    $terms = $term->name;
                }
            }
        }
        return $terms;
    }


    /**
     * Function to get an array of field values for a specific field
     *
     * @param   string  $field_name - field name
     * @param   node  $node   - node
     *
     * @return array    array of values
     *
     * @author Dragos Dumitrescu
     */

    static function get_api_field_values($field_name, $node) {
        $values = array();
        $langcode = API_CMS::get_field_language($node, $field_name);
        if ( !empty($node->{$field_name}[$langcode]) ) {
            foreach ($node->{$field_name}[$langcode] as $value) {
                $values []= $value['value'];
            }
        }
        return $values;
    }


    /**
     * Get an instrument array mapped as defined in documentation
     * deprecated - to be removed
     *
     * @param $nid
     *
     * @return array|bool
     */
    static function get_instrument($nid) {
        $node = node_load($nid);
        if ($node == false) {
            return FALSE;
        }
        $instrument = array();
        $instrument['instrument'] = $node->title;
        $instrument['uuid'] = $node->uuid;
        return $instrument;
    }

    /**
     * Get an instrument array mapped as defined in documentation
     * Used by set_api_fields_coll_field for type "legal_instrument"
     *
     * @param $nid
     *
     * @return array|bool
     */
    static function api_get_ref_legal_instrument($nid) {
        $node = node_load($nid);
        if ($node == false) {
            return FALSE;
        }
        $instrument = array();
        $instrument['instrument'] = $node->title;
        $instrument['uuid'] = $node->uuid;
        return $instrument;
    }

    /**
     * Get a country array mapped as defined in documentation
     * @param $nid
     *
     * @return array|bool
     */
    static function api_get_ref_country($nid) {
        $node = node_load($nid);
        if ($node == false) {
            return FALSE;
        }
        $lang_iso3 = API_CMS::get_field_language($node, 'field_country_iso3');
        $lang_iso2 = API_CMS::get_field_language($node, 'field_country_iso2');
        $country = array();
        $country['name'] = $node->title;
        $country['uuid'] = $node->uuid;
        $country['iso3l'] = $node->field_country_iso3[$lang_iso3][0]['value'];
        $country['iso2l'] = $node->field_country_iso2[$lang_iso2][0]['value'];
        return $country;
    }

    /**
     * Get a country array mapped as defined in documentation
     * @param $nid
     *
     * @return array|bool
     */
    static function get_country($nid) {
        $node = node_load($nid);
        if ($node == false) {
            return FALSE;
        }
        $lang_iso3 = API_CMS::get_field_language($node, 'field_country_iso3');
        $lang_iso2 = API_CMS::get_field_language($node, 'field_country_iso2');
        $country = array();
        $country['name'] = $node->title;
        $country['uuid'] = $node->uuid;
        $country['iso3l'] = $node->field_country_iso3[$lang_iso3][0]['value'];
        $country['iso2l'] = $node->field_country_iso2[$lang_iso2][0]['value'];
        return $country;
    }

}
