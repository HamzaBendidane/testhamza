<?php

function _parametres_require_once() {
  // Fichiers du modules: langues, crud, model, submit, validate etc...
  require_once 'parametres_db.inc';
  require_once 'parametres_form.inc';
  require_once 'parametres_langs.inc'; // Gestion des langues
  require_once 'parametres_submit.inc'; // Envoie des données
  require_once 'parametres_validate.inc'; // Validation
}

/**
 * Form Submit Inc
 * @param $form, &$form_state
 *
 *
 */
function _parametres_add_css_js() {
  drupal_add_js(drupal_get_path('module', 'dgf_administration' ) . '/inc/parametres/js/parametres.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_administration' ) . '/inc/parametres/css/parametres.css' );
}

function parametres_init_page() {

  _parametres_require_once();
  _parametres_add_css_js();

  $form = drupal_get_form('parametres_form');
  $output = drupal_render($form);
  $output .= '<div id="table-container"></div>';

  return $output;
}

function parametres_data() {
  _parametres_require_once();

  $referentiel_selected = $_GET['referentiel_selected'];

  if ($referentiel_selected == 'ref_nature_demande' || $referentiel_selected == 'ref_nature_formation') {
    // Table header
    $header = array(
        array('data' => 'Label', 'field' => 'label', 'sort' => 'asc'),
        array('data' => 'Action', 'field' => 'action'),
    );
  } else if ($referentiel_selected == 'ref_justificatif') {
    // Table header
    $header = array(
        array('data' => 'Nature de demande', 'field' => 'rnd.id_ref_nature_demande', 'sort' => 'asc'),
        array('data' => 'Code', 'field' => 'r.code'),
        array('data' => 'Label', 'field' => 'r.label', 'sort' => 'asc'),
        array('data' => 'Obligatoire', 'field' => 'r.is_mandatory', 'sort' => 'asc'),
        array('data' => 'Action', 'field' => 'action'),
    );
  } else {
    // Table header
    $header = array(
        array('data' => 'Code', 'field' => 'code'),
        array('data' => 'Label', 'field' => 'label', 'sort' => 'asc'),
        array('data' => 'Action', 'field' => 'action'),
    );
  }

  // Setting the sort conditions
  if (isset($_GET['sort']) && $_GET['sort'] != '' && isset($_GET['order']) && $_GET['order'] != '') {
    // Sort it Ascending or Descending?
    if ($_GET['sort'] == 'asc') {
      $sort = 'ASC';
    } else {
      $sort = 'DESC';
    }

    // Which column will be sorted
    switch($_GET['order']) {
      case 'Nature de demande':
        $order = 'rnd.id';
        break;
      case 'Code':
        $order = 'r.code';
        break;
      case 'Label':
        $order = 'r.label';
        break;
      case 'Obligatoire':
        $order = 'r.is_mandatory';
        break;
      default:
        $order = 'r.label';
    }
  }

  if ($referentiel_selected == 'ref_justificatif') {
    $rows = parametres_db_get_data_list_justificatifs($order, $sort, $referentiel_selected);
  } else {
    $rows = parametres_db_get_data_list($order, $sort, $referentiel_selected);
  }


  $output .= l('Ajouter', '/opcaim-admin/parametres/add-referentiel/'.$referentiel_selected, array(
      'attributes' => array('class' => 'col-md-2 col-md-offset-10 edit-add-button btn btn-default')
  ));

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
  $output .= '<br />';
  $output .= l('Ajouter', '/opcaim-admin/parametres/add-referentiel/'.$referentiel_selected, array(
      'attributes' => array('class' => 'col-md-2 col-md-offset-10 edit-add-button btn btn-default')
  ));

  $output .= theme('pager',
      array(
          'tags' => array()
      )
  );

  // On choisit laméthode die() pour éviter l'affichage en double du template
  die($output);
//   return $output;
}