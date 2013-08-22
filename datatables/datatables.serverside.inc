<?php
/**
*  Serverside processing of datatables
*/
function datatables_serverside($name, $display_id, $base64_args = NULL){
        $view_name = check_plain($name);
        $view_display_id = check_plain($display_id);
        if($base64_args != NULL){
            $args = explode('|',base64_decode($base64_args));
        }

        $sortable_columns = isset($_GET['sortable']) ? $_GET['sortable'] : array();
        $sort_by = $_GET['iSortCol_0'];
        $sort_type = $_GET['sSortDir_0'];

        $_GET['order'] = (!empty($sortable_columns)) ? $sortable_columns[$sort_by] : '';
        $_GET['sort'] = $sort_type;

        $iColumns = $_GET['iColumns'];
        $iDisplayLength = is_numeric($_GET['iDisplayLength']) ? $_GET['iDisplayLength'] : 10;
        $iDisplayStart = is_numeric($_GET['iDisplayStart']) ? $_GET['iDisplayStart'] : 0;
        $iSortingCols = is_numeric($_GET['iSortingCols']) ? $_GET['iSortingCols'] : 0;

        $view = views_get_view($view_name);
        $view->set_display($view_display_id);

        if(!empty($args)){
            $view->set_arguments($args);
        }

        $view->set_use_pager = TRUE;
        $view->set_items_per_page($iDisplayLength);
        $view->set_current_page(0);
        $view->set_offset($iDisplayStart);
        $view->get_total_rows = TRUE;

        $view->pager['items_per_page'] = $iDisplayLength;
        $view->execute();

        $total_rows = ($view->total_rows) ? $view->total_rows : count($view->result);
        $iTotalRecords = $total_rows + $iDisplayStart;
        $iTotalDisplayRecords = $total_rows + $iDisplayStart;

        $options  = $view->style_plugin->options;
        $handler  = $view->style_plugin;

        $fields   = &$view->field;
        $columns  = $handler->sanitize_columns($options['columns'], $fields);

        $renders = array();
        $keys = array_keys($view->field);

        /*
         * Output
         */
        $output = array(
            "sEcho" => intval($_GET['sEcho']),
            "iTotalRecords" => $iTotalRecords,
            "iTotalDisplayRecords" => $iTotalDisplayRecords,
            "aaData" => array()
        );

        foreach ($view->result as $count => $row) {
            foreach ($keys as $id) {
                $renders[$count][$id] = $view->field[$id]->theme($row);
            }
        }

        $vars['rows'] = array();
        foreach ($columns as $field => $column) {
            if ($field == $column && empty($fields[$field]->options['exclude'])) {
                $vars['header'][$field] = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
            }

            foreach ($view->result as $num => $row) {
                if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
                    $field_output = $renders[$num][$field];

                    if (empty($field_output) && !empty($vars['rows'][$num][$column])) {
                        continue;
                    }

                    $vars['rows'][$num][] = $field_output;
                }
            }
        }

        $output['aaData'] = $vars['rows'];

        drupal_json_output($output); 
        drupal_exit();
}
