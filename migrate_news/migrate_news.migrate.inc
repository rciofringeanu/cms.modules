<?php
/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201404040008
 */


class CustomCSV extends MigrateSourceCSV {
    public function __construct($path, array $csvcolumns = array(), array $options = array(), array $fields = array()) {
        parent::__construct($path, $csvcolumns, $options, $fields);
        $this->fgetcsv['delimiter'] = ';';
    }
}

class AEWANewsMigration extends Migration {

    protected $columns = array(
        0 => array('id_csv', 'Id'),
        1 => array('created_csv', 'created'),
        2 => array('title_csv', 'title'),
        3 => array('title_fr_csv', 'title_fr'),
        4 => array('body_url_csv', 'body'),
        5 => array('body_url_fr_csv', 'body_fr'),
    );


    public function __construct() {
        parent::__construct();
        ini_set('auto_detect_line_endings', TRUE);
        //The defintion of the collumns. Keys are integers. values are array(field name, description).

        //The Description of the import. This desription is shown on the Migrate GUI
        $this->description = t('Import of news content.');

        //The Source of the import
        $this->source = new CustomCSV(
            drupal_get_path('module', 'migrate_news') . DIRECTORY_SEPARATOR . 'data' . DIRECTORY_SEPARATOR . 'test.csv',
            $this->columns, array('delimiter' => ',', 'header_rows' => 1));

        //The destination CCK (boundle)
        $this->destination = new MigrateDestinationNode('news');

        //Source and destination relation for rollbacks
        $this->map = new MigrateSQLMap(
            $this->machineName,
            array(
                'id_csv' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE,
                    'alias' => 'import'
                )
            ),
            MigrateDestinationNode::getKeySchema()
        );

        //Field ampping
        $this->addFieldMapping('title', 'title_csv');
        $this->addFieldMapping('created', 'created_csv');
        $this->addFieldMapping('changed', 'created_csv');
        $this->addFieldMapping('status')->defaultValue(0);
        $this->addFieldMapping('sticky')->defaultValue(0);
        $this->addFieldMapping('promote')->defaultValue(0);
        $this->addFieldMapping('language')->defaultValue('en');
        $this->addFieldMapping('domain_site')->defaultValue(1);
        $this->addFieldMapping('comment')->defaultValue(1);
        $this->addFieldMapping('body', 'body_url_csv');
        $this->addFieldMapping('body:format')->defaultValue('full_html');
        $this->addFieldMapping('uid')->defaultValue(4); // NEpler
    }

    public function prepareRow($row) {
        parent::prepareRow($row);
        $this->processBody($row);
        return TRUE;
    }

    public function processBody(&$row) {
        $url = $row->body_url_csv;
        $html = file_get_contents($url);
        $qp = @htmlqp($html, NULL, array('convert_to_encoding' => 'utf-8'));

        $body = '<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"></head><body>' .
            $qp->top()->find("td[@class='body']")->innerXHTML() . '</body></html>';

        $qp = @htmlqp($body, NULL, array('convert_to_encoding' => 'utf-8'));
        // Process IMG tags
        $imgs = $qp->top()->find('img');
        foreach ($imgs as $img) {
            $src = $img->attr('src');

            if(is_string($url)) {
                $result = parse_url($url);
            } else {
                $result = $url;
            }
            $base = $result['scheme']."://".$result['host'];
            if($src[0] == '/') { // Absolute
                $furl = $base . $src;
            } else { // Relative
                $furl = $result['scheme']."://".$result['host'] .$result['path'] . '/../' . $src;
            }
            try {
                // Open the file using.
                if (($handle = fopen($furl, 'r')) &&
                    // Parse the url.
                    ($url = parse_url($furl)) &&
                    // Get the url path.
                    !empty($url['path']) &&
                    // Get the filename.
                    ($filename = basename($url['path']))) {
                    // Construct a uri.
                    $uri = 'public://imported/' . $filename;
                    // Save the item as a managed file directly from the stream wrapper.
                    $file = file_save_data($handle, $uri, TRUE);
                    if ($file) {
                        // Now we update the markup with the new url.
                        $new_url = file_create_url($uri);
                        // Use QueryPath to update the url.
                        $img->attr('src', $new_url);
                        // Record this file as used by this node/our module.
                        //file_usage_add($file, 'cms', 'node', $entity->nid);
                        $row->files[] = $file; // Attach files, so we can later mark them as used by item file_usage_add($file, 'MYMODULE', 'node', $entity->nid)
                    }
                    fclose($handle);
                }
            }
            catch(Exception $e) {
                drupal_set_message($e->getMessage(), 'error');
            }
        }
        return $qp->top()->find('body')->innerXHTML();
    }

    public function complete($entity, $source_row) {
        if(!empty($source_row->files)) {
            foreach($source_row->files as $file) {
                file_usage_add($file, 'cms_news', 'node', $entity->nid); // Mark the file as in use
            }
        }
    }
}


class CMSNewsMigration extends AEWANewsMigration {

    public function __construct() {
        parent::__construct();
        //The Description of the import. This desription is shown on the Migrate GUI
        $this->description = t('Import CMS news content.');

        //The Source of the import
        $this->source = new CustomCSV(
            drupal_get_path('module', 'migrate_news') . DIRECTORY_SEPARATOR . 'data' . DIRECTORY_SEPARATOR . 'cms.csv',
            $this->columns, array('delimiter' => ',', 'header_rows' => 1));

        $this->removeFieldMapping("uid");
        $this->addFieldMapping('uid')->defaultValue(5); // NEpler
    }
}