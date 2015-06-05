<?php

require_once 'demande_langs.inc';
require_once 'demande_form.inc';
require_once 'demande_filter.inc';

function _dgf_contrat_pro_stagiaire_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_suivi' ) . '/inc/demande/js/suivi_demande.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_suivi' ) . '/inc/demande/css/suivi_demande.css' );
}

function dgf_suivi_demande_init_page() {
  _dgf_contrat_pro_stagiaire_include_js_css();
  drupal_add_js('refreshTable();', 'inline');
  return ('<div id="table-container" class="row"></div>');
}

function dgf_suivi_demande_data() {
//   shared_get_referentiel_data(array('ref_diplome', 'ref_derniere_situation','ref_beneficiaire_minimas_sociaux'));
  $form = drupal_get_form('dgf_suivi_demande_form');
  $output = drupal_render($form);

  // Table header
  // TODO : mettre les chamsp correspondants à la SPEC
  // voir par rapport au commentaire à chaque $order
  $header = array(
      array('data' => 'Date d\'enregistrement', 'field' => 'date_creation'),
      array('data' => 'N° action', 'field' => 'numero_demande'),
      array('data' => 'Etablissement', 'field' => 'etablishment'),
      array('data' => 'Nature de l’action', 'field' => 'id_nature_demande'),
      array('data' => 'Intitulé de l’action', 'field' => 'id_ref_intitule_formation'),
      array('data' => 'Durée totale', 'field' => 'duree_totale_heure'),
      array('data' => 'Dates de formation', 'field' => 'date_debut'),
      array('data' => 'Raison sociale du prestataire <br />ou de l’organisme de formation', 'field' => 'raison_sociale'),
      array('data' => 'Nombre de participants<br/>Nom prénom stagiaire', 'field' => 'trainees_count'),
      array('data' => 'Coût pédagogique', 'field' => 'training_cost'),
      array('data' => 'Paiement direct O/N', 'field' => 'paiement_direct'),
      array('data' => 'Etat', 'field' => 'status'),
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
    	case 'Date d\'enregistrement':
    	  $order = 'date_creation'; 
    	  break;
    	case 'N° action':
    	  $order = 'numero_demande'; // numero_myopca
    	  break;
//     	case 'Etablissement':
//     	  $order = 'id_ref_esclave_entreprise'; // Lien_dgf_ref_esclave_entreprise.id_ref_esclave_entreprise
//     	  break;
//     	case 'Nature de l’action':
//     	  $order = 'id_nature_demande'; // Dgf.id_nature_demande Dgf_form_formation.id_ref_intitule_formation ou intitule_formation Dgf_form_formation.duree_totale_heure
//     	  break;
//     	case 'Intitulé de l’action':
//     	  $order = 'id_ref_intitule_formation'; // Dgf.id_nature_demande Dgf_form_formation.id_ref_intitule_formation ou intitule_formation Dgf_form_formation.duree_totale_heure
//     	  break;
//     	case 'Durée totale':
//     	  $order = 'duree_totale_heure'; // Dgf.id_nature_demande Dgf_form_formation.id_ref_intitule_formation ou intitule_formation Dgf_form_formation.duree_totale_heure
//     	  break;
//     	case 'Dates de la formation':
//     	  $order = 'date_debut'; //Dgf_form_formation.date_debut Dgf_form_formation.date_fin
//     	  break;
//     	case 'Raison sociale du prestataire <br />ou de l’organisme de formation':
//     	  $order = 'raison_sociale'; // Organisme_de_formation.raison_sociale
//     	  break;
//     	case 'Nombre de participants':
//     	  $order = 'trainees_count'; // Dgf_form_formation.nb_participant
//     	  break;
//     	case 'Nom prénom stagiaire':
//     	  $order = 'trainee_infos'; // Salarie.nom Salarie.prenom
//     	  break;
//     	case 'Coût pédagogique':
//     	  $order = 'cout_pedagogique'; // Dgf_form_formation.cout_pedagogique Dgf_form_formation.paiement_direct
//     	  break;
//     	case 'Paiement direct O/N':
//     	  $order = 'paiement_direct'; // Dgf_form_formation.cout_pedagogique Dgf_form_formation.paiement_direct
//     	  break;
//     	case 'Etat':
//     	  $order = 'statut'; // Dgf_form_formation.cout_pedagogique Dgf_form_formation.paiement_direct
//     	  break;
    	default:
    	  $order = 'raison_sociale'; // date_creation
    }
  }
  else {
    $sort = 'ASC';
    $order = 'date_creation'; //date_creation
  }

  $actionNumber = $_GET['actionNumber'];
  $actionNature = $_GET['actionNature'];
  $actionState = $_GET['actionState'];
  $yearExercise = $_GET['yearExercise'];
  $workerName = $_GET['workerName'];
  $etablishment = $_GET['etablishment'];
  
  $rows = get_data_for_demande($order, $sort, $actionNumber, $actionNature, $actionState, $yearExercise, $workerName, $etablishment);

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