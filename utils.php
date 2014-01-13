<?php

# DIRECTORY_SEPARATOR is a name too long for a constant :D
define('_DS_', DIRECTORY_SEPARATOR);

module_load_include('module', 'contacts', 'contacts');

final class CMSUtils {
    public static $regions = array(
        "EU" => "Europe",
        "AF" => "Africa",
        "AS" => "Asia",
        "OC" => "Oceania",
        "SCA" => "South & Central America & the Caribbean",
        "NA" => "North America",
    );

    public static function use_pretty_print() {
        $version = explode('.', phpversion());
        $php_version = ($version[0] * 10000 + $version[1] * 100 + $version[2]);
        if ($php_version > 50400) {
            return TRUE;
        }

        return FALSE;
    }


    /**
     * Calculate a slug with a maximum length for a string.
     *
     * @param $string
     *   The string you want to calculate a slug for.
     * @param $length
     *   The maximum length the slug can have.
     * @return
     *   A string representing the slug
     */
    public static function slug($string, $length = -1, $separator = '-') {
        // transliterate
        $string = CMSUtils::transliterate($string);

        // lowercase
        $string = strtolower($string);

        // replace non alphanumeric and non underscore charachters by separator
        $string = preg_replace('/[^a-z0-9]/i', $separator, $string);

        // replace multiple occurences of separator by one instance
        $string = preg_replace('/'. preg_quote($separator) .'['. preg_quote($separator) .']*/', $separator, $string);

        // cut off to maximum length
        if ($length > -1 && strlen($string) > $length) {
            $string = substr($string, 0, $length);
        }

        // remove separator from start and end of string
        $string = preg_replace('/'. preg_quote($separator) .'$/', '', $string);
        $string = preg_replace('/^'. preg_quote($separator) .'/', '', $string);

        return $string;
    }

    /**
     * Unslugify a fiven string
     *
     * @param   string   $slug
    */
    public static function unslugify($slug) {
        return str_replace('-', ' ', $slug);
    }

    public static function starts_with($haystack, $needle) {
        return !strncmp($haystack, $needle, strlen($needle));
    }

    public static function ends_with($haystack, $needle) {
        $length = strlen($needle);
        if ($length == 0) {
            return true;
        }

        return (substr($haystack, -$length) === $needle);
    }

    /**
     * Regular Expression snippet to validate Google Analytics tracking code
     * see http://code.google.com/apis/analytics/docs/concepts/gaConceptsAccounts.html#webProperty
     *
     * @author  Faisalman <movedpixel@gmail.com>
     * @license http://www.opensource.org/licenses/mit-license.php
     * @link    http://gist.github.com/faisalman
     * @param   $str     string to be validated
     * @return  Boolean
     */
    function is_analytics($string){
        return preg_match("/^UA-\d{4,9}-\d{1,4}$/i", strval($string)) ? true : false;
    }

    /**
     * Echo a formatted string with newline
     * @param string format See sprintf() for a description of format
     * @param mixed args Variable arguments
     */
    static function println($message) {
        $params = array($message) + func_get_args();
        call_user_func_array('printf', $params);
        echo "\n";
    }


    /**
     * Replace non alphanumeric characters from a specified string
     *
     * @param   string   $string
     * @return  string
    */
    public static function alphanumeric($string) {
        return preg_replace("/[^A-Za-z0-9]/i", "", $string);
    }

    /**
     * Transliterate a given string.
     *
     * @param $string
     *   The string you want to transliterate.
     * @return
     *   A string representing the transliterated version of the input string.
     */
    public static function transliterate($string) {
        static $charmap;
        if (!$charmap) {
            $charmap = array(
                // Decompositions for Latin-1 Supplement
                chr(195) . chr(128) => 'A', chr(195) . chr(129) => 'A',
                chr(195) . chr(130) => 'A', chr(195) . chr(131) => 'A',
                chr(195) . chr(132) => 'A', chr(195) . chr(133) => 'A',
                chr(195) . chr(135) => 'C', chr(195) . chr(136) => 'E',
                chr(195) . chr(137) => 'E', chr(195) . chr(138) => 'E',
                chr(195) . chr(139) => 'E', chr(195) . chr(140) => 'I',
                chr(195) . chr(141) => 'I', chr(195) . chr(142) => 'I',
                chr(195) . chr(143) => 'I', chr(195) . chr(145) => 'N',
                chr(195) . chr(146) => 'O', chr(195) . chr(147) => 'O',
                chr(195) . chr(148) => 'O', chr(195) . chr(149) => 'O',
                chr(195) . chr(150) => 'O', chr(195) . chr(153) => 'U',
                chr(195) . chr(154) => 'U', chr(195) . chr(155) => 'U',
                chr(195) . chr(156) => 'U', chr(195) . chr(157) => 'Y',
                chr(195) . chr(159) => 's', chr(195) . chr(160) => 'a',
                chr(195) . chr(161) => 'a', chr(195) . chr(162) => 'a',
                chr(195) . chr(163) => 'a', chr(195) . chr(164) => 'a',
                chr(195) . chr(165) => 'a', chr(195) . chr(167) => 'c',
                chr(195) . chr(168) => 'e', chr(195) . chr(169) => 'e',
                chr(195) . chr(170) => 'e', chr(195) . chr(171) => 'e',
                chr(195) . chr(172) => 'i', chr(195) . chr(173) => 'i',
                chr(195) . chr(174) => 'i', chr(195) . chr(175) => 'i',
                chr(195) . chr(177) => 'n', chr(195) . chr(178) => 'o',
                chr(195) . chr(179) => 'o', chr(195) . chr(180) => 'o',
                chr(195) . chr(181) => 'o', chr(195) . chr(182) => 'o',
                chr(195) . chr(182) => 'o', chr(195) . chr(185) => 'u',
                chr(195) . chr(186) => 'u', chr(195) . chr(187) => 'u',
                chr(195) . chr(188) => 'u', chr(195) . chr(189) => 'y',
                chr(195) . chr(191) => 'y',
                // Decompositions for Latin Extended-A
                chr(196) . chr(128) => 'A', chr(196) . chr(129) => 'a',
                chr(196) . chr(130) => 'A', chr(196) . chr(131) => 'a',
                chr(196) . chr(132) => 'A', chr(196) . chr(133) => 'a',
                chr(196) . chr(134) => 'C', chr(196) . chr(135) => 'c',
                chr(196) . chr(136) => 'C', chr(196) . chr(137) => 'c',
                chr(196) . chr(138) => 'C', chr(196) . chr(139) => 'c',
                chr(196) . chr(140) => 'C', chr(196) . chr(141) => 'c',
                chr(196) . chr(142) => 'D', chr(196) . chr(143) => 'd',
                chr(196) . chr(144) => 'D', chr(196) . chr(145) => 'd',
                chr(196) . chr(146) => 'E', chr(196) . chr(147) => 'e',
                chr(196) . chr(148) => 'E', chr(196) . chr(149) => 'e',
                chr(196) . chr(150) => 'E', chr(196) . chr(151) => 'e',
                chr(196) . chr(152) => 'E', chr(196) . chr(153) => 'e',
                chr(196) . chr(154) => 'E', chr(196) . chr(155) => 'e',
                chr(196) . chr(156) => 'G', chr(196) . chr(157) => 'g',
                chr(196) . chr(158) => 'G', chr(196) . chr(159) => 'g',
                chr(196) . chr(160) => 'G', chr(196) . chr(161) => 'g',
                chr(196) . chr(162) => 'G', chr(196) . chr(163) => 'g',
                chr(196) . chr(164) => 'H', chr(196) . chr(165) => 'h',
                chr(196) . chr(166) => 'H', chr(196) . chr(167) => 'h',
                chr(196) . chr(168) => 'I', chr(196) . chr(169) => 'i',
                chr(196) . chr(170) => 'I', chr(196) . chr(171) => 'i',
                chr(196) . chr(172) => 'I', chr(196) . chr(173) => 'i',
                chr(196) . chr(174) => 'I', chr(196) . chr(175) => 'i',
                chr(196) . chr(176) => 'I', chr(196) . chr(177) => 'i',
                chr(196) . chr(178) => 'IJ', chr(196) . chr(179) => 'ij',
                chr(196) . chr(180) => 'J', chr(196) . chr(181) => 'j',
                chr(196) . chr(182) => 'K', chr(196) . chr(183) => 'k',
                chr(196) . chr(184) => 'k', chr(196) . chr(185) => 'L',
                chr(196) . chr(186) => 'l', chr(196) . chr(187) => 'L',
                chr(196) . chr(188) => 'l', chr(196) . chr(189) => 'L',
                chr(196) . chr(190) => 'l', chr(196) . chr(191) => 'L',
                chr(197) . chr(128) => 'l', chr(197) . chr(129) => 'L',
                chr(197) . chr(130) => 'l', chr(197) . chr(131) => 'N',
                chr(197) . chr(132) => 'n', chr(197) . chr(133) => 'N',
                chr(197) . chr(134) => 'n', chr(197) . chr(135) => 'N',
                chr(197) . chr(136) => 'n', chr(197) . chr(137) => 'N',
                chr(197) . chr(138) => 'n', chr(197) . chr(139) => 'N',
                chr(197) . chr(140) => 'O', chr(197) . chr(141) => 'o',
                chr(197) . chr(142) => 'O', chr(197) . chr(143) => 'o',
                chr(197) . chr(144) => 'O', chr(197) . chr(145) => 'o',
                chr(197) . chr(146) => 'OE', chr(197) . chr(147) => 'oe',
                chr(197) . chr(148) => 'R', chr(197) . chr(149) => 'r',
                chr(197) . chr(150) => 'R', chr(197) . chr(151) => 'r',
                chr(197) . chr(152) => 'R', chr(197) . chr(153) => 'r',
                chr(197) . chr(154) => 'S', chr(197) . chr(155) => 's',
                chr(197) . chr(156) => 'S', chr(197) . chr(157) => 's',
                chr(197) . chr(158) => 'S', chr(197) . chr(159) => 's',
                chr(197) . chr(160) => 'S', chr(197) . chr(161) => 's',
                chr(197) . chr(162) => 'T', chr(197) . chr(163) => 't',
                chr(197) . chr(164) => 'T', chr(197) . chr(165) => 't',
                chr(197) . chr(166) => 'T', chr(197) . chr(167) => 't',
                chr(197) . chr(168) => 'U', chr(197) . chr(169) => 'u',
                chr(197) . chr(170) => 'U', chr(197) . chr(171) => 'u',
                chr(197) . chr(172) => 'U', chr(197) . chr(173) => 'u',
                chr(197) . chr(174) => 'U', chr(197) . chr(175) => 'u',
                chr(197) . chr(176) => 'U', chr(197) . chr(177) => 'u',
                chr(197) . chr(178) => 'U', chr(197) . chr(179) => 'u',
                chr(197) . chr(180) => 'W', chr(197) . chr(181) => 'w',
                chr(197) . chr(182) => 'Y', chr(197) . chr(183) => 'y',
                chr(197) . chr(184) => 'Y', chr(197) . chr(185) => 'Z',
                chr(197) . chr(186) => 'z', chr(197) . chr(187) => 'Z',
                chr(197) . chr(188) => 'z', chr(197) . chr(189) => 'Z',
                chr(197) . chr(190) => 'z', chr(197) . chr(191) => 's',
                // Euro Sign
                chr(226) . chr(130) . chr(172) => 'E'
            );
        }

        // transliterate
        return strtr($string, $charmap);
    }

    public static function is_slug($str) {
        return $str == CMSUtils::slug($str);
    }

    /**
     * Generate a random string with a specified length
     *
     * @param   int      $length
     * @return  string   $string
    */
    public static function random_string($length = 8) {
        $string = '';

        for ($i = 0; $i < $length; $i++) {
            $string .= chr(mt_rand(97, 122));
        }

        return $string;
    }

    /**
     * Check whether or not an AJAX request has been made
     *
     * @return   boolean
    */
    public static function request_is_ajax() {
        return (isset($_SERVER['HTTP_X_REQUESTED_WITH']) && ($_SERVER['HTTP_X_REQUESTED_WITH'] == 'XMLHttpRequest'));
    }

    /**
     * Tests wheter a directory is valid, exists and is readable
     * @param string $dir Path to the file (Preffered absolute path)
     * @param boolean $writable Additionally check if the directory is writable. Default FALSE.
     * @return boolean TRUE if valid
     */
    public static function is_valid_dir($dir, $writable = FALSE) {
        if($writable) {
            return is_dir($dir) && is_readable($dir) && is_writable($dir);
        } else {
            return is_dir($dir) && is_readable($dir);
        }
    }

    /**
    * Character Limiter
    *
    * Limits the string based on the character count.  Preserves complete words
    * so the character count may not be exactly as specified.
    *
    * @param   string
    * @param   int
    * @param   string   the end character. Usually an ellipsis
    * @return   string
    */
   public static function character_limiter($str, $n = 500, $end_char = '&#8230;') {
        if (strlen($str) < $n) {
            return $str;
        }

        // a bit complicated, but faster than preg_replace with \s+
        $str = preg_replace('/ {2,}/', ' ', str_replace(array("\r", "\n", "\t", "\x0B", "\x0C"), ' ', $str));

        if (strlen($str) <= $n) {
             return $str;
        }

        $out = '';
        foreach (explode(' ', trim($str)) as $val) {
            $out .= $val.' ';

            if (strlen($out) >= $n) {
                 $out = trim($out);
                 return (strlen($out) === strlen($str)) ? $out : $out . $end_char;
            }
       }
   }

    /**
     * Create a new array without elements that has $key
     * @param array $array Given array
     * @param mix $key A key that need to be removed
     * @return array A new array
     */
    public static function remove_element_from_array($array, $key) {
        $return = array();
        foreach ($array as $k => $v) {
            if ($k !== $key) {
                if (is_array($v)) {
                    $v = remove_element_from_array($v, $key);
                }
                $return[$k] = $v;
            }
        }
        return $return;
    }

    public static function valid_phone($string) {
        if(preg_match('/^[+]?([0-9]?)[(|s|-|.]?([0-9]{3})[)|s|-|.]*([0-9]{3})[s|-|.]*([0-9]{4})$/', $string)) {
            return TRUE;
        }else {
            return FALSE;
        }
    }

    public static function not_null($value, $is_array = FALSE, $is_int = FALSE) {
        if ($value == NULL) {
            if ($is_array) {
                return array();
            }elseif($is_int) {
                return 0;
            }else {
                return '';
            }
        }

        return $value;
    }

    public static function get_default_language($node = NULL) {
        return LANGUAGE_NONE;

        if (($node !== NULL) && (is_object($node))) {
            if (property_exists($node, 'language')) {
                return $node->language;
            }else {
                return language_default('language');
            }
        }
    }

    /**
     * Get all websites and their URLs for current state
     * e.g.
     *   state = local
     *   websites = {
                     'cms': 'http://cms.localhost',
                     'aewa': 'http://aewa.localhost'
                    }
    */
    public static function get_all_websites() {
        $websites = array();
        $current_url = variable_get('current_url');

        $stored_websites = variable_get('websites', $websites);
        $state = variable_get('state');

        if (array_key_exists($state, $stored_websites) && is_array($stored_websites[$state])) {
            $websites = $stored_websites[$state];
            foreach ($websites as $index => $website) {
                $websites[$index]['current'] = ($website['url'] == $current_url) ? true : false;
            }
        }

        return $websites;
    }

    public static function get_mapped_websites() {
        $data = &drupal_static(__FUNCTION__);
        if (!isset($data)) {
            $websites = variable_get('websites');
            $state = variable_get('state');

            if (in_array($state, array_keys($websites)) && is_array($websites[$state])) {
                foreach($websites[$state] as $index => $website) {
                    $data[$index] = $website['title'];
                }
            }
        }

        return $data;
    }

    /**
     * Get current website profile
    */
    public static function get_current_profile() {
        return variable_get('current_profile');
    }

    public static function is_CMS() {
        return (CMSUtils::get_current_profile() == 'cms') ? TRUE : FALSE;
    }

    /**
     * Using cURL login user to a specified Drupal website
     *
     * @param       string      $website
     */
    public static function remote_login($website, $cron_job = FALSE) {
        global $user;
        $cookie_file = tempnam('/tmp', $website);

        /**
         * First, check if user is logged in on the current website
         *
         * IMPORTANT: Be careful that Drupal cron job are not running under an authenticated user
        */
        if (!$user->uid && !$cron_job) {
            drupal_access_denied();
            drupal_exit();
        }

        /**
         * Initialize and set cURL options
        */
        $ch = curl_init();
        $url = $website . '/user/login';
        $curl_options = array(
            CURLOPT_URL => $url,
            CURLOPT_COOKIEFILE => $cookie_file,
            CURLOPT_COOKIEJAR => $cookie_file,
            CURLOPT_FOLLOWLOCATION => 1,
            CURLOPT_RETURNTRANSFER => 1,
            CURLOPT_POST => 1,
        );
        curl_setopt_array($ch, $curl_options);

        /**
         * Set data to post in the remote login form
        */
        $POST = array(
            'name' => 'AP1US3R',
            'pass' => 'LM5XLIq_wmEhHC4Q0fFic7zc',
            'form_id' => 'user_login',
            'op' => 'Log in',
        );

        /**
         * Set cURL post fields options with our POST data
        */
        curl_setopt($ch, CURLOPT_POSTFIELDS, $POST);

        /**
         * Log in to remote website
        */
        $response = curl_exec($ch);

        /**
         * Check if logged in succeeded.
         * If the URL from the headers is the same as /user/login, authentication has failed.
        */
        $headers = curl_getinfo($ch);
        curl_close($ch);
        unset($ch);
        if ($headers['url'] == $url) {
            unlink($cookie_file);
            return false;
        }else {
            return $cookie_file;
        }
    }

    /**
     * Extract a simple value from Drupal node field
     * @param object $node Drupal node
     * @param array $field_name Drupal field name
     * @param string $property_name Property to extract. Default 'value'
     *
     * @return Returns Actual value or NULL
     */
    public static function get_node_simple_value($node, $field_name, $property = 'value', $langcode = '') {
        if (empty($langcode)) {
            $langcode = CMSUtils::get_default_language($node);
        }

        if(!empty($node->{$field_name}[$langcode][0][$property])) {
            return $node->{$field_name}[$langcode][0][$property];
        }
        return NULL;
    }

    /**
     * Set a simple value to a Drupal node, with multilanguage
     *
     * $node->$field[$langcode][0][$property] = $v;
     *
     * @param object $node Drupal node
     * @param string $field_name Node property/field
     * @param mixed $value The value or array with values (key must be non-null)
     * @param string $key The key to extract from $value, if it's an array
     * @param string $property Property to set to the nodes' value. Default 'value'
     */
    public static function set_node_simple_value(&$node, $field_name, $value, $key = NULL, $property = 'value') {
        $langcode = CMSUtils::get_default_language($node);
        if(!empty($value)) {
            $v = $value;
            if($key != NULL) {
                $v = $value[$key];
            }

            $node->$field_name = array($langcode => array(0 => array($property => $v)));
        }
    }

    /**
     * Set a boolean value to a Drupal node, with multilanguage
     *
     * $node->$field[$langcode] = $v;
     *
     * @param object $node Drupal node
     * @param string $field_name Node property/field
     * @param mixed $value The value or array with values (key must be non-null)
     * @param string $key The key to extract from $value, if it's an array
     * @param string $property Property to set to the nodes' value. Default 'value'
     */
    public static function set_node_boolean_value(&$node, $field_name, $value, $key = NULL, $property = 'value') {
        $langcode = CMSUtils::get_default_language($node);

        $v = 0;
        if(!empty($value)) {
            $v = $value;
            if($key != NULL) {
                $v = $value[$key];
            }
        }
        $node->$field_name = array($langcode => array(0 => array($property => $v)));
    }


    /**
     * Set a list of values to a Drupal node, with multilanguage
     *
     * $node->$field[$langcode] = array(array($property => $values[0]) ...);
     *
     * @param object $node Drupal node
     * @param string $field_name Node property/field
     * @param array $values Array with values
     * @param string $property Property to set to the nodes' value. Default 'value'
     */
    public static function set_node_list_value(&$node, $field_name, $values, $property = 'value') {
        $langcode = CMSUtils::get_default_language($node);

        if(!empty($values)) {
            $v = array();
            foreach($values as $value) {
                $v[] = array($property => $value);
            }
            $node->$field_name = array($langcode => $v);
        }
    }


    /**
     * Retrieve the list of values for a node with multiple values per field
     * @param stdClass $node Node object
     * @param string $field_name Name of the field to get data from
     * @param type $property_name (Optional) Name of the property to get, default is 'value'
     * @param type $langcode (Optional) Language code
     * @return array Array of values
     */
    public static function get_node_list_value($node, $field_name, $property = 'value') {
        $langcode = CMSUtils::get_default_language($node);

        $ret = array();
        if(!empty($node->{$field_name}[$langcode]) && is_array($node->{$field_name}[$langcode])) {
            foreach($node->{$field_name}[$langcode] as $value) {
                $ret[] = $value[$property];
            }
        }
        return $ret;
    }

    /**
     * Add attachments such as PDF, DOC, JPG files to a publication. Does
     * not alter existing values.
     *
     * @param object $node Reference to the node to update
     * @param string $property Property of the node to attach the file in
     * @param array $data Data to get information from (ex. JSON). Must contain key "$property" defined above
     * @param string $path_prefix Prefix that is added to the file path. Default empty.
     */
    public static function node_import_file(&$node, $property, $data, $path_prefix = '', $destination_dir = '') {
        if(!empty($data[$property])) {
            $langcode = CMSUtils::get_default_language($node);
            if ((!property_exists($node, $property)) || ($node->$property === NULL)) {
                $node->$property = array($langcode => array());
            }

            if((!is_array($node->$property)) || (!array_key_exists($langcode, $node->$property))) {
                $node->$property[$langcode] = array();
            }

            foreach($data[$property] as $attachment) {
                $path = $path_prefix . $attachment['path'];
                if(!is_file($path)) {
                    CMSUtils::println("CMSUtils::node_import_file(): Not a valid file: %s", $path);
                    continue;
                }
                if(!is_readable($path)) {
                    CMSUtils::println("CMSUtils::node_import_file(): Not a readable file: %s", $path);
                    continue;
                }
                $file_obj = (object)array(
                    'uid' => 1,
                    'uri' => $path,
                    'filemime' => file_get_mimetype($path),
                    'status' => 1,
                );
                $file = file_copy($file_obj, 'public://' . $destination_dir);
                if($file !== FALSE) {
                    $file->display = 1;
                    $file = (array)$file;
                    $node->{$property}[$langcode][] = $file;
                } else {
                    CMSUtils::println("CMSUtils::node_import_file(): Could not add attachment: %s", $path);
                }
            }
        }
    }


    /**
     * Export node attachment files such as documents or images. It creates one directory
     * inside the $base_dir with slug from $node->title and subdirectory with property name.
     * <code>
     * $base_dir/slug($node->title)/$field_name/
     * </code>
     * @param stdClass $node Node
     * @param string $field_name Which node field to export. Possible values: 'field_publication_attachment' or 'field_publication_image'.
     * @param string $base_dir Base directory to export the files
     */
    public static function node_export_files($node, $field_name, $base_dir) {
        $ret = array();

        $slug = CMSUtils::slug($node->title);
        $rel_path = $slug . DIRECTORY_SEPARATOR . $field_name;
        $pub_dir = $base_dir . DIRECTORY_SEPARATOR . $rel_path;
        CMSUtils::mkdir($pub_dir);
        if(is_dir($pub_dir) && is_writable($pub_dir)) {
            if(!empty($node->{$field_name}[$node->language])) {
                foreach($node->{$field_name}[$node->language] as $file) {
                    $filename = $file['filename'];
                    $dest = $pub_dir . DIRECTORY_SEPARATOR . $filename;
                    $f = file_stream_wrapper_get_instance_by_uri($file['uri']);
                    copy($f->realpath(), $dest);
                    $ret[] = array('path' => $rel_path . DIRECTORY_SEPARATOR . $filename);
                }
            }
        } else {
            CMSUtils::println("CMSPublication::export_files(): Invalid export directory %s", $pub_dir);
        }
        return $ret;
    }


    /**
     * Read the content of a CSV file and return it as array with rows.
     * First row may be the header.
     *
     * @param string $file_path Path to a valid CSV file
     * @return array Array of items. Each item is an array with columns
     * @throws Exception if cannot read the CSV file
     */
    public static function read_csv($file_path) {
        $ret = array();
        if($file_path == null) {
            throw new Exception("read_csv(): NULL file passed. Aborting");
        }
        if(!is_file($file_path)) {
            throw new Exception(sprintf("read_csv(): File %s does not exists", $file_path));
        }
        if(!is_readable($file_path)) {
            throw new Exception(sprintf("read_csv(): File %s is not readable", $file_path));
        }
        $handle = fopen($file_path, 'r');
        while (($row = fgetcsv($handle)) !== FALSE) {
            $ret[] = $row;
        }
        return $ret;
    }


    /**
     * Read JSON file and make it an object
     * @param string $file_path Path to a valid JSON file
     * @param bool $assoc When TRUE, returned objects will be converted into associative arrays.
     * @return object Object (array, stdClass etc.) resembling JSON structure
     */
    public static function read_json($file_path, $assoc = false) {
        $ret = NULL;
        if($file_path == null) {
            throw new Exception("read_json(): NULL file passed. Aborting.");
        }
        if(!is_file($file_path)) {
            throw new Exception(sprintf("read_json(): File %s does not exists", $file_path));
            return $ret;
        }
        if(!is_readable($file_path)) {
            throw new Exception(sprintf("read_json(): File %s is not readable", $file_path));
            return $ret;
        }
        $content = file_get_contents($file_path);
        if($content !== FALSE) {
            $ret = json_decode($content, $assoc);
            if($ret === NULL) {
                throw new Exception(sprintf("read_json(): Unable to decode JSON data from %s", $file_path));
            }
        } else {
            throw new Exception(sprintf("read_json(): Generic error reading %s", $file_path));
        }
        return $ret;
    }

    /**
     * @param string $term_name Term name
     * @param string $vocabulary_name Name of the vocabulary to add the term if doesn't exist
     * @param boolean $create Create the term if it doesn't exist
     * @param string $description Term description
     * @param array $parent Term parents tids
     * @return stdClass|FALSE The actual term object or FALSE if invalid term name or term doesn't exist
     */
    public static function vocabulary_get_or_create_term($term_name, $vocabulary_name, $create = TRUE, $description = '', $parent = array()) {
        $term_name = trim($term_name);
        if(empty($term_name)) {
            return FALSE;
        }
        $ret = taxonomy_get_term_by_name($term_name, $vocabulary_name);
        if(empty($ret)) {
            $ret = NULL;
            if($create) {
                // Create the term into vocabulary
                $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
                if(!empty($vocabulary)) {
                    $term = array('vid' => $vocabulary->vid, 'name' => $term_name, 'description' => $description);
                    if (!empty($parent)) {
                        $term['parent'] = $parent;
                    }
                    $term = (object)$term;
                    if (taxonomy_term_save($term)) {
                        $ret = $term;
                    }
                } else {
                    CMSUtils::println('CMSUtils::vocabulary_get_or_create_term(): Cannot find term %s inside vocabulary %s', $term_name, $vocabulary_name);
                }
            }
        } else {
            $ret = current($ret);
        }
        return $ret;
    }

    /**
     * Get a specified vocabulary and if it doesn't exists, create it.
     *
     * @param   string   $name   Vocabulary name
     * @param   string   $machine_name   Vocabulary machine name
     * @param   string   $description   Vocabulary description
     * @param   string   $module   Content types that use the new created vocabulary
     * @return  stdClass|FALSE   The identified/created vocabulary or FALSE if the vocabulary could not be created
    */
    public static function vocabulary_get_or_create($name, $machine_name, $description = '', $module = array()) {
        $ret = taxonomy_vocabulary_machine_name_load($machine_name);
        if(empty($ret)) {
            $vocabulary = array(
                'name' => $name,
                'machine_name' => $machine_name,
                'description' => $description,
            );
            if (!empty($module)) {
                $vocabulary['module'] = $module;
            }
            $vocabulary = (object) $vocabulary;
            taxonomy_vocabulary_save($vocabulary);
            $ret = taxonomy_vocabulary_machine_name_load($machine_name);
        }

        return $ret;
    }


    /**
     * Create directory if it doesn't exist
     *
     * @param string $path Path to the directory
     * @param int $mode Directory permisssions - defaults to mkdir's 0777
     * @return boolean TRUE if exists and is writeable
     */
    public static function mkdir($path, $mode = 0775) {
        @mkdir($path, $mode, TRUE);
        return is_dir($path) && is_writable($path);
    }

    public static function truncate_file($filepath) {
        if (file_exists($filepath)) {
            $fp = fopen($filepath, "r+");
            ftruncate($fp, 0);
            fclose($fp);
        }
    }


    /**
     * Create a new CMS Publication node instance. Name is taken from publication module.
     * @param bool $save If TRUE, object is saved into database
     *
     * @return object The node object initialized
     */
    static function node_create_article($title, $save = TRUE) {
        global $user;
        $node = new stdClass();
        $node->type = 'article';
        node_object_prepare($node);
        $node->title = $title;
        $node->language = CMSUtils::get_default_language();
        $node->status = 1;
        $node->uid = $user->uid;
        $node->changed = $_SERVER['REQUEST_TIME'];
        $node->created = $_SERVER['REQUEST_TIME'];

        $node = node_submit($node);
        if($save) {
            node_save($node);
        }
        return $node;
    }


    /**
     * Get or create a specified role
     *
     * @param   string   $role_name
     * @return  object   Drupal role
    */
    static function get_or_create_role($role_name) {
        $role = user_role_load_by_name($role_name);

        if (!$role) {
            $role = new stdClass();
            $role->name = $role_name;
            user_role_save($role);
            $role = user_role_load_by_name($role_name);
        }

        return $role;
    }


    /**
     * Assign permissions to a role
     * @param string $role_name
     * @param array $permissions
     * @return boolean
     */
    static function role_add_permissions($role_name, $permissions) {
        $role = user_role_load_by_name($role_name);
        if(!empty($role)) {
            user_role_change_permissions($role->rid, $permissions);
            return TRUE;
        } else {
            // CMSUtils::println('CMSUtils::role_add_permissions(): Roles %s does not exists', $role_name);
        }
        return FALSE;
    }


    static function set_vocabulary_permissions(&$permissions, $vocabulary_name, $content_type, $role) {
        $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
        if(!empty($vocabulary)) {
            $permissions += array(
                "add terms in {$vocabulary->vid}" => TRUE,
                "edit terms in {$vocabulary->vid}" => TRUE,
                "delete terms in {$vocabulary->vid}" => TRUE
            );
        } else {
            CMSUtils::println('CMSUtils::set_vocabulary_permissions(): Cannot find vocabulary %s. Cannot assign vocabulary permission to role %s', $vocabulary_name, $role);
        }

        return $permissions;
    }


    /**
     * Create new root vocabulary (no parent)
     * @param string $name
     * @param string $machine_name
     * @return integer Same as taxonomy_vocabulary_save, or 0 if already exists
     */
    static function vocabulary_create($name, $machine_name) {
        $existing = taxonomy_vocabulary_machine_name_load($machine_name);
        if($existing === FALSE) {
            $voc = new stdClass();
            $voc->name = $name;
            $voc->machine_name = $machine_name;
            $voc->hierarchy = 0;
            return taxonomy_vocabulary_save($voc);
        }
        return 0;
    }

    static function vocabulary_delete($name) {
        $vocabulary = taxonomy_vocabulary_machine_name_load($name);
        if(!empty($vocabulary)) {
            taxonomy_vocabulary_delete($vocabulary->vid);
            return TRUE;
        }
    }


    /**
     * Retrieve a term filtered by its name and/or vocabulary and/or parent id.
     *
     * @param string $name Term name
     * @param string $vid Vocabulary ID. Default is ignored unless you set to a valid ID
     * @param integer $parent_id Optional parent. Default to -1, which means no filter on parent. If you want to retrieve a root term, pass 0.
     * @return StdClass|boolean FALSE if not found or term as stdClass
     */
    public static function vocabulary_get_term($name, $vid=-1, $parent=-1) {
        $query = db_select('taxonomy_term_data', 't')->fields('t');
        $query->join('taxonomy_term_hierarchy', 'h', 'h.tid = t.tid');
        $query->condition('t.name', $name);
        if($vid != -1) {
            $query->condition('t.vid', $vid);
        }
        if($parent != -1) {
            $query->condition('h.parent', $parent);
        }
        $result = $query->execute()->fetchAssoc();
        if($result !== FALSE) {
            return (object)$result;
        }
        return FALSE;
    }


    public static function vocabulary_get_terms($vocabulary_name, $name_as_key = FALSE, $name_key_value = FALSE) {
        $terms = array();
        $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
        if ($vocabulary) {
            $vocabulary_terms = taxonomy_get_tree($vocabulary->vid);
            if ($vocabulary_terms) {
                foreach ($vocabulary_terms as $key => $term) {
                    if ($name_key_value) {
                        $terms[$term->name] = $term->name;
                    }elseif ($name_as_key) {
                        $terms[$term->name] = $term->tid;
                    }else {
                        $terms[$term->tid] = $term->name;
                    }
                }
            }
        }

        return $terms;
    }
    /**
     * Assign to a node property the ID of a taxonomic vocabulary term
     *
     * @param object $node stdClass $node Reference to the node to update
     * @param string $field_name Name of the field (also must exist inside $data array, as key)
     * @param string $vocabulary_name Name of the vocabulary to create this field
     * @param array $data Data to get information from (ex. JSON). Must contain key $field_name
     */
    public static function set_node_field_vocabulary_term(&$node, $field_name, $vocabulary_name, $data) {
        if(!empty($data[$field_name])) {
            $voc_term = $data[$field_name];
            $term = self::vocabulary_get_or_create_term($voc_term, $vocabulary_name);
            if(!empty($term)) {
                $node->{$field_name}[$node->language][0]['tid'] = $term->tid;
            }
        }
    }


    /**
     * Retrieve the UUID for a node (and assign one if doesn't already have).
     * @param stdClass $node Drupal node
     * @return string Node UUID or NULL if $node is NULL
     */
    static function get_node_uuid($node) {
        $ret = NULL;
        if(empty($node->uuid)) {
            CMSUtils::println('Assigning new UUID for node %s (%s)', $node->type, $node->title);
            module_load_include('inc', 'uuid', 'uuid');
            $node->uuid = uuid_generate();
            node_save($node);
        } else {
            $ret = $node->uuid;
        }
        return $ret;
    }

    /**
     * Remove a speciefied menu item and subitems
     *
     * @param   string   $menu   Menu name
     * @param   string   $title  Menu item title
     * @param   string   $path   Menu tiem path
     *
     * @return  boolean  TRUE/FALSE
    */
    static function remove_menu_and_submenu($menu = 'main-menu', $title = '', $path = '') {
        $ret = FALSE;
        if (empty($title) || empty($path)) {
            return $ret;
        }

        /**
         * Remove specified item from menu
        */
        $mlid = db_select('menu_links' , 'ml')
                ->condition('ml.link_path' , $path)
                ->condition('ml.link_title' , $title)
                ->condition('ml.has_children' , '1')
                ->condition('ml.expanded' , '1')
                ->fields('ml' , array('mlid'))
                ->execute()
                ->fetchField();

        if(!empty($mlid)) {
            menu_link_delete($mlid);

            /**
             * Remove specified item's sublinks
            */
            $tree = menu_tree_all_data($menu);
            foreach ($tree as $branch){
                if ($branch['link']['title'] == $title){
                    $childtree = $branch['below'];
                    foreach ($childtree as $title => $menu_item) {
                        if (isset($menu_item['link']['mlid'])) {
                            menu_link_delete($menu_item['link']['mlid']);
                        }
                    }
                    $ret = TRUE;
                }
            }
        }

        return $ret;
    }


    /**
     * Make an user Drupal administrator. Useful for functional tests.
     * @param object $user Drupal user object
     * @param string $role Role name to assign
     * @return object User object updated
     */
    static function user_assign_role($user, $role = 'administrator') {
        $roles = user_roles();
        $index = array_search($role, $roles);
        $user->roles[$index] = $role;
        return user_save($user);
    }


    /**
     * Get published content
     */
    static function get_published_content($contents){
        $published_content = array();
        foreach($contents as $content) {
            if ($content['entity']->status == '1') {
                $published_content[] = $content;
            }
        }
        return $published_content;
    }

    /**
     * Get related published nodes
     *
     * @param     array      $related_array
     * @return    array      $published_content
     */
    static function get_published_nodes($related_array){
        $published_content = array();
        foreach($related_array as $related) {
            $node = node_load($related['target_id']);
            if ($node && is_object($node) && $node->status == '1') {
                $published_content[] = $related;
            }
        }

        return $published_content;
    }

    /**
     * Set HTTP headers for data export
     *
     * @param   string   $type
     *    Accepted values 'text/csv', 'application/vnd.ms-excel'
     * @param   string   $filename
     */
    public static function set_download_http_headers($type = 'text/csv', $filename = 'export.csv') {
        if (!in_array($type, array('text/csv', 'application/vnd.ms-excel'))) {
            watchdog('system', ". Unknown donload type $type. Data export aborted.", array(), WATCHDOG_ERROR);
            return FALSE;
        }

        drupal_add_http_header('Pragma', 'public');
        drupal_add_http_header('Expires', 'Mon, 26 Jul 1997 05:00:00 GMT');
        drupal_add_http_header('Last-Modified', gmdate('D, d M Y H:i:s').' GMT');
        drupal_add_http_header('Cache-Control', 'cache, must-revalidate, post-check=0, pre-check=0, max-age=0');
        drupal_add_http_header('Content-Description', 'File transfer');
        drupal_add_http_header('Content-Type', $type . '; charset=utf-8');
        drupal_add_http_header('Content-Disposition', 'attachment; filename=' . $filename);
        drupal_add_http_header('Content-Transfer-Encoding', 'binary');

        return TRUE;
    }


    /**
     * Computes the document date getting the date from associated COP/MOP meeting
     * @param stdClass $doc Drupal document node
     * @param string $meetings_field Name of the node field that keeps the related meetings
     */
    function get_document_publish_date_from_meeting($doc, $meetings_field) {
        $meetings = CMSUtils::get_node_list_value($doc, 'field_document_meeting', 'target_id');
        $types = array('mop', 'cop');
        $meetings = node_load_multiple($meetings);
        foreach($meetings as $node) {
                $tid = $node->field_meeting_type['und'][0]['tid'];
                $type = taxonomy_term_load($tid);
                $type = strtolower($type->name);
                if(in_array($type, $types)) {
                    return (!empty($node->field_meeting_end['und'][0]['value'])) ?
                        $node->field_meeting_end['und'][0]
                        : $node->field_meeting_start['und'][0];
                }
        }
        return FALSE;
    }

    /**
     * Get a specified Drupal cache or create it if it does not exists
     *
     * @param    string    $cid
     *  Drupal cache unique identifed
     * @param    string    $callback
     *  Callback function which creates the cache
    */
    public static function get_or_create_cache($cid, $callback) {
        if ($cache = cache_get($cid)) {
            $cache_data = $cache->data;
        }else {
            $callback();
            $cache_data = cache_get($cid)->data;
        }

        return $cache_data;
    }

    /**
     * LDAP results are returned with a 'count' key and most of the time we need to remove it
     *
     * @param    array    $data
    */
    public static function unset_count_key(&$data = array()) {
        if (is_array($data) && array_key_exists('count', $data)) {
            unset($data['count']);
        }
    }
}
