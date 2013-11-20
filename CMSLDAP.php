<?php



/**
 * PHP Class for CMS LDAP functionalities
 * Basic sequence of LDAP is connect, bind, search, interpret search result
 * and close connection
 *
 * @author kempiseth
 */
class CMSLDAP {

    //Private properties:
    private $password;
    private $connect;

    //Walk through result:
    private $entry_identifier; // current pointer to resultset
    private $attributes; // attributes for current entry
    private $attr; // current attribute

    //Whole resultset:
    private $search_result = array(); // last search result
    private $count_entries = 0; // last entries count
    private $entries = array();       // last entries array

    //Public properties:
    public $bind_rdn;
    public $base_dn;
    public $people_dn;
    public $organization_dn;
    public $address;
    public $port;
    public $connected = FALSE;

    public function __construct() {
        $this->base_dn = variable_get(LDAP_BASE_DN);
        $this->bind_rdn = variable_get(LDAP_BIND_RDN);
        $this->people_dn = variable_get(LDAP_PEOPLE_DN);
        $this->organization_dn = variable_get(LDAP_ORGANIZATION_DN);
        $this->department_dn = variable_get(LDAP_DEPARTMENT_DN);

        $hash = substr(drupal_get_hash_salt(), 0, 24);
        $cipher = mcrypt_module_open(MCRYPT_BLOWFISH,'','cbc','');
        mcrypt_generic_init($cipher, $hash, IV);
        $decrypted = mdecrypt_generic($cipher, variable_get(LDAP_PASSWORD));
        mcrypt_generic_deinit($cipher);
        $this->password = $decrypted;

        $this->address = variable_get(LDAP_ADDRESS);
        $this->port = variable_get(LDAP_PORT);

        $this->connect = ldap_connect($this->address, $this->port);
        if ($this->connect) {
            ldap_set_option($this->connect, LDAP_OPT_PROTOCOL_VERSION, 3);
            $bind_result = @ldap_bind($this->connect, $this->bind_rdn, $this->password);

            if (!$bind_result) {
                drupal_set_message('Unable to bind the LDAP server! Please contact site administrator.', 'error');
            }

            $this->connected = TRUE;
        } else {
            drupal_set_message('Unable to connect to the LDAP server! Please contact site administrator.', 'error');
        }
    }

    public function __destruct() {
        $this->close();
    }

    function check_for_errors() {
        $error = ldap_error($this->connect);
        $errno = ldap_errno($this->connect);

        if ($error) {
            return array(
                'error' => t($error),
                'errno' => $errno,
            );
        }

        return array();
    }

    /**
     * Sort LDAP result entries
     *
     * @param string $sortfilter The attribute to use as a key in the sort.
     * @return bool
     */
    public function sort($sort_filter) {
        return ldap_sort($this->connect, $this->search_result, $sort_filter);
    }

    /**
     * Search LDAP entries based on a specific filter
     *
     * @param   string   $base_dn
     * @param   string   $filter
     * @param   array    $attributes
     * @param   array    $attrsonly
     * @return  array
     */
    public function search($base_dn, $filter, $attributes = array(), $attrsonly = null) {
        $this->search_result = ldap_search($this->connect, $base_dn, $filter, $attributes, $attrsonly);
        return $this->search_result;
    }

    /**
     * Search LDAP entries with pagination, based on a specific filter
     *
     * @param   string   $base_dn
     * @param   string   $filter
     * @param   int      $page
     * @param   array    $attributes
     * @param   array    $attrsonly
     * @param   int      $page_size
     * @return  array
     */
    public function paged_search($base_dn, $filter, $page = 1, $attributes = array(), $attrsonly = null, $page_size = 10) {
        $results = array();
        $cookie = '';
        do {
            ldap_control_paged_result($this->connect, $page_size, TRUE, $cookie);
            $this->search_result = ldap_search($this->connect, $base_dn, $filter, $attributes, $attrsonly);
            $entries = $this->get_entries();
            $results[] = $entries;
            ldap_control_paged_result_response($this->connect, $this->search_result, $cookie);
        } while($cookie !== NULL && $cookie != '');

        if (!empty($results)) {
            return $results[$page];
        }

        return $results;
    }

    public function group_paged_search($base_dn, $filter, $attribute = 'uniquemember', $page = 1, $per_page = 15) {
        $this->search_result = $this->search($base_dn, $filter);
        $total_entries = 0;
        $total_pages = 1;
        $page_results = array();

        if ($this->search_result) {
            $results = $this->get_entries();
            if ($results['count']) {
                $entries = $results[0][$attribute];
                $total_entries = $entries['count'];
                sort($entries);
                $paged_entries = array_chunk($entries, $per_page);
                $page_results = $paged_entries[$page - 1];
                $total_pages = ceil($total_entries / $per_page);
            }
        }

        return array(
            'entries' => $page_results,
            'total_pages' => $total_pages,
            'total_entries' => $total_entries,
        );
    }

    public function read($base_dn, $filter, $attributes = array(), $attrsonly = null) {
        $this->search_result = ldap_read($this->connect, $base_dn, $filter, $attributes, $attrsonly);
        return $this->search_result;
    }

    /**
     * Return first entry from an LDAP search result
     */
    public function first_entry() {
        $this->entry_identifier = ldap_first_entry($this->connect, $this->search_result);
        return $this->entry_identifier;
    }

    /**
     * Get the next entry from an LDAP search results
     */
    public function next_entry() {
        $this->entry_identifier = ldap_next_entry($this->connect, $this->entry_identifier);
        return $this->entry_identifier;
    }

    public function list_onelevel($base_dn, $filter, $attributes = array(), $attrsonly = null) {
        $this->search_result = ldap_list($this->connect, $base_dn, $filter, $attributes, $attrsonly);
        return $this->search_result;
    }

    /**
     * Count entries of an LDAP search results
     *
     * @return   int
     */
    public function count_entries() {
        $this->count_entries = ldap_count_entries($this->connect, $this->search_result);
        return $this->count_entries;
    }

    /**
     * Get entries of an LDAP search result resource
     *
     * @return   array
     */
    public function get_entries() {
        if (!is_bool($this->search_result) && !is_bool($this->connect)) {
            $this->entries = ldap_get_entries($this->connect, $this->search_result);
        }

        return $this->entries;
    }

    /**
     * Get all attributes of a specified LDAP entry
     *
     * @return   array
     */
    public function get_attributes() {
        $this->attributes = ldap_get_attributes($this->connect, $this->entry_identifier);
        return $this->attributes;
    }

    /**
     * Get first attribute of a specified LDAP entry
     *
     * @return   string
     */
    public function first_attribute() {
        $this->attr = ldap_first_attribute($this->connect, $this->entry_identifier);
        return $this->attr; // string
    }

    /**
     * Get the next attribute of a specified LDAP entry
     *
     * @return   string
     */
    public function next_attribute() {
        $this->attr = ldap_next_attribute($this->connect, $this->entry_identifier);
        return $this->attr; // string
    }

    /**
     * Get values of a specified attribute from an LDAP entry
     *
     * @return   array
     */
    public function get_string_values($attribute) {
        return ldap_get_values($this->connect, $this->entry_identifier, $attribute);
    }

    public function get_binary_values($attribute) {
        return ldap_get_values_len($this->connect, $this->entry_identifier, $attribute);
    }

    public function get_dn() {
        return ldap_get_dn($this->connect, $this->entry_identifier);
    }

    /**
     * Add e new entry
     *
     * @param   string   $dn
     * @param   array    $entry
     * @return  bool
     */
    public function add($dn, $entry) {
        return ldap_add($this->connect, $dn, $entry);
    }

    /**
     * Add an entry to a specified group
     *
     * @param   string   $group_name
     * @param   array    $group_info
     * @return  bool
     */
    public function add_to_group($group_name, $group_info) {
        $group_dn = "cn=$group_name," . $this->people_dn;
        return ldap_mod_add($this->connect, $group_dn, $group_info);
    }

    public function create_group($group_name, $dn, $members = array()) {
        $group['cn'] = $group_name;
        $group['objectclass'] = 'top';
        $group['objectclass'] = 'groupOfUniqueNames';

        foreach ($members as $member) {
            $group['uniquemember'] = $member;
        }

        return $this->add($dn, $group);
    }

    /**
     * Delete a specified entry
     *
     * @param   string   $dn
     * @return  bool
     */
    public function delete($dn) {
        return ldap_delete($this->connect, $dn);
    }

    /**
     * Delete an entry from a specified group
     *
     * @param   string   $group_name
     * @param   array    $group_info
     * @return  bool
     */
    public function delete_from_group($group_name, $group_info) {
        $group_dn = "cn=$group_name," . $this->people_dn;
        return ldap_mod_del($this->connect, $group_dn, $group_info);
    }

    /**
     * Edit a specified entry
     *
     * @param   string   $dn
     * @param   array    $values
     * @return  bool
     */
    public function edit($dn, $values) {
        $attrs_to_del = array();
        $attrs_to_mod = array();
        foreach ($values as $key => $value) {
            if (empty($value)) {
                $attrs_to_del[$key] = array();
            }else {
                $attrs_to_mod[$key] = $value;
            }
        }

        if ($attrs_to_del) {
            ldap_modify($this->connect, $dn, $attrs_to_del);
        }

        return ldap_modify($this->connect, $dn, $attrs_to_mod);
    }

    /**
     * Modify the name of an entry
     * @param string $dn The distinguished name of an LDAP entity.
     * @param string $newrdn The new RDN.
     * @param string $newparent The new parent/superior entry.
     * @param bool $deleteoldrdn If TRUE the old RDN value(s) is removed, else
     * the old RDN value(s) is retained as non-distinguished values of the entry.
     * @return bool Returns TRUE on success or FALSE on failure.
     */
    public function rename($dn, $newrdn, $newparent, $deleteoldrdn) {
        return ldap_rename($this->connect, $dn, $newrdn, $newparent, $deleteoldrdn);
    }

    /**
     * Close opened LDAP connection
     */
    public function close() {
        if ($this->connect) {
            if ($this->search_result) {
                @ldap_free_result($this->search_result);
            }

            ldap_close($this->connect);
        }
    }

    /**
     * Prepare data for inetOrgPerson entry.
     * @param string $gn Given name
     * @param string $sn Surname
     * @return array Return a data array for inetorgperson entry.
     */
    public static function prepare_inetorgperson($gn, $sn) {
        $data["cn"] = "$gn $sn";
        $data["gn"] = $gn;
        $data["sn"] = $sn;
        $data["objectclass"][0] = "top";
        $data["objectclass"][1] = "cmsContact";
        return $data;
    }

    /**
     * Search for a specified user
     *
     * @param     string     $user_id
     * @return    array
     */
    public function search_user($user_id) {
        $this->search($this->people_dn, '(uid=' . $user_id . ')');
        $user_result = $this->get_entries();
        if ($user_result['count']) {
            return $user_result[0];
        }else {
            return array();
        }
    }

    /**
     * Search for a specified organization
     *
     * @param     string     $organization_id
     * @return    array
     */
    public function search_organization($organization_id) {
        $this->search($this->organization_dn, '(oid=' . $organization_id . ')');
        $organization_result = $this->get_entries();
        if ($organization_result['count']) {
            return $organization_result[0];
        }else {
            return array();
        }
    }
}

?>
