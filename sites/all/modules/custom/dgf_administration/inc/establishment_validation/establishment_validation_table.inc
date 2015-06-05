<?php

require_once 'establishment_validation_const.inc';
require_once 'establishment_validation_form.inc';
require_once 'establishment_validation_query.inc';
require_once 'establishment_validation_auto_complete.inc';

function _opcaim_validation_establishment_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_validation/js/establishment_validation.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_validation/css/establishment_validation.css' );
}

function opcaim_validation_establishment_init_page() {
  _opcaim_validation_establishment_include_js_css();
  drupal_add_js('refreshTable();', 'inline');
  return ('<div id="table-container"></div>');
}

function opcaim_validation_establishment_data() {
  $form = drupal_get_form('opcaim_establishment_validation_form');
  $output = drupal_render($form);

  // Table header
  $header = array(
      array('data' => 'SIRET', 'field' => 'siret'),
      array('data' => 'Modification', 'field' => 'ya_pas'),
      array('data' => 'Raison sociale', 'field' => 'raison_sociale'),
      array('data' => 'Téléphone', 'field' => 'telephone_principal_entreprise'),
      array('data' => 'Responsable', 'field' => 'corporate_name'),
      array('data' => 'Action', 'field' => 'action'),
  );

  // Setting the sort conditions
  if(isset($_GET['sort']) && isset($_GET['order'])) {
    // Sort it Ascending or Descending?
    if($_GET['sort'] == 'asc')
      $sort = 'ASC';
    else
      $sort = 'DESC';
  
    // Which column will be sorted
    switch($_GET['order']) {
    	case 'SIRET':
    	  $order = 'siret';
    	  break;
    	case 'Raison sociale':
    	  $order = 'raison_sociale';
    	  break;
//     	case 'Responsable':
//     	  $order = 'nom_contact';
//     	  break;
    	default:
    	  $order = 'siret';
    }
  }
  else {
    $sort = 'ASC';
    $order = 'raison_sociale';
  }

  $siret = $_GET['siret'];
  $corporateName = $_GET['corporateName'];
  $responsibleName = $_GET['responsibleName'];

  $rows = get_data_for_establishment_validation($order, $sort, $siret, $corporateName, $responsibleName);
//   $output .= '<input type="button" id="edit-add-top" name="op" value="Ajouter" class="col-md-2 col-md-offset-10 edit-add btn btn-default" href="">';
  // Setting the output of the field
  $output .= theme_table(
      array(
          'header' => $header,
          'rows' => $rows,
          'attributes' => array(),
          'sticky' => true,
          'caption' => '',
          'colgroups' => array(),
          'empty' => t("Il n'y a pas de données à afficher...")
      )
  );
//   $output .= '<input type="button" id="edit-add-bottom" name="op" value="Ajouter" class="col-md-2 col-md-offset-10 edit-add btn btn-default" href="">';

  $output .= theme('pager',
      array(
          'tags' => array()
      )
  );
  // On choisit laméthode die() pour éviter l'affichage en double du template
  die($output);
}

// TODO : ajouter le bouton pour les exports excel 
// ici ou dans la vue ?