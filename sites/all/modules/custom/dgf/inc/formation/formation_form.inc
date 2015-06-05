<?php


function _dgf_formation_include_js_css() {
  drupal_add_js ( drupal_get_path ( 'module', 'dgf' ) . '/inc/formation/js/formation.js' );
  drupal_add_css ( drupal_get_path ( 'module', 'dgf' ) . '/inc/formation/css/formation.css' );
}

function _dgf_formation_require_once_files() {
  require_once drupal_get_path('module', 'dgf' ) . '/inc/contrat/contrat_db.inc';
  require_once drupal_get_path('module', 'dgf' ) . '/inc/contrat/contrat_validate.inc';
  require_once 'formation_db.inc';
  require_once 'formation_langs.inc';
  require_once 'formation_submit.inc';
  require_once 'formation_validate.inc';
}

/**
 * Form for the training step.
 *
 * @see dgf_cp_form().
 *
 * @param type $form
 * @param type $form_state
 * @return type
 */
function dgf_formation_form($form, &$form_state) {
  _dgf_formation_require_once_files();
  _dgf_formation_include_js_css ();

  // on regarde le 3eme argument de l'url
  $temp_dgf_form_formation = array();
  $temp_dgf_form_formation_repartition = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(3) !== null) {
    $id_dgf = arg(3);
    $temp_dgf_form_formation = formation_db_get_temp_dgf_form_formation($id_dgf);
    $temp_dgf_form_contrat = contrat_db_get_temp_dgf_form_salarie($id_dgf);
    // on récupère les répartitions si on a un id
    if ($temp_dgf_form_formation) {
      $temp_dgf_form_formation_repartition = formation_db_get_temp_dgf_form_formation_repartition(
          $temp_dgf_form_formation['id']);
    }
  } else {
    return;
  }

  shared_get_referentiel_data('ref_finalite_formation', false);
  $data_referentiel_esclave = formation_db_get_referentiel_esclave_data();

  $date_jour = new DateTime();
  $annee_formation = (int)($date_jour->format('Y'));

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa-4.png',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => $id_dgf,
      '#title' => t('Id demande' )
  );

  $form['id_dgf_formation'] = array(
      '#type' => 'hidden',
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['id'] : null,
      '#title' => t('Id demande formation' )
  );

  $form['formations_recurrentes'] = array(
      '#type' => 'item',
      '#title' => t(''),
      '#markup' => dgf_formation_formations_recurrentes(),
  );

  $form['type_qualification'] = array(
      '#type' => 'radios',
      '#title' => 'Type de qualification',
      '#required' => TRUE,
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_finalite_formation'],
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['id_ref_finalite_formation']
        : null,
  );

  // TODO : Lié le numéro de CQPI avec l'intitulé de formation
  $form['num_CQPI_CQPM'] = array(
      '#type' => 'textfield',
      '#title' => 'N° CQPI/CQPM',
      '#default_value' => $temp_dgf_form_formation['num_cqpi'] ? $temp_dgf_form_formation['num_cqpi'] : null,
//       '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['libelle'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'Intitulé de la formation' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['intitule_formation']
        : null,
      '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
  	  '#attributes' =>array('placeholder' => t('Min. 3 premiers caractères'))
  );

  $form['id_libelle'] = array(
      '#type' => 'hidden',
      '#title' => 'N° CQPI/CQPM',
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['id_ref_esclave_intitule_formation']
        : null
  );

  $form['date_begin'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Date de début de contrat'),
      '#default_value' => $temp_dgf_form_contrat ? shared_parse_mssql_date($temp_dgf_form_contrat['date_debut'])->format('d/m/Y') : NULL,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['date_end'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Date de fin de contrat'),
      '#default_value' => $temp_dgf_form_contrat ? shared_parse_mssql_date($temp_dgf_form_contrat['date_fin'])->format('d/m/Y') : NULL,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['training_start'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'Date de début de la formation' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? shared_parse_mssql_date($temp_dgf_form_formation['date_debut'])->format('d/m/Y') : null,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['date_exam'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'Date de l\'examen' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? shared_parse_mssql_date($temp_dgf_form_formation['date_examen'])->format('d/m/Y') : null,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['total_duration'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'Durée totale' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['duree_totale_heure'] : null,
      '#element_validate' => array(
          'element_validate_integer_positive'
      ),
      '#field_suffix' => ' en heures <a id="total_duration_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip"
        data-original-title="'. @MSG_INFO_FORMATION_DUREES .'" style ="float:none;"></a>',
  );

  $form['duration_main_learning'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'dont enseignements généraux' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['duree_ens_gen_heure'] : null,
      '#element_validate' => array(
          'element_validate_integer_positive'
      ),
   	  '#prefix' => '<div class="paddingduree">',
      '#field_suffix' => ' en heures <a id="duration_main_learning_info" class="glyphicon glyphicon-question-sign"
        data-toggle="tooltip" data-original-title="'. @MSG_INFO_FORMATION_DUREES .'" style ="float:none;"></a>',
  );

  $form['accompanying_actions'] = array(
      '#type' => 'textfield',
      '#title' => t ( 'dont actions d’accompagnement et évaluations' ),
      '#required' => TRUE,
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['duree_acc_heure'] : null,
      '#element_validate' => array(
          'element_validate_integer_positive'
      ),
 	  '#suffix' => '</div>',
      '#field_suffix' => ' en heures <a id="accompanying_actions_info" class="glyphicon glyphicon-question-sign"
        data-toggle="tooltip" data-original-title="'. @MSG_INFO_FORMATION_DUREES .'" style ="float:none;"></a>',
  );

  $form['specialty_training'] = array(
      '#type' => 'select',
      '#title' => t ( 'Spécialité formation' ),
      '#options' => $data_referentiel_esclave['specialites_formation'],
      '#default_value' => $temp_dgf_form_formation ? $temp_dgf_form_formation['id_ref_esclave_specialite'] : null,
  );

  // TODO : n'afficher que si effectif entreprise > 10
  $form['internal_training'] = array(
      '#type' => 'checkbox',
      '#title' => t('Formation interne'),
      '#default_value' =>($temp_dgf_form_formation) ? $temp_dgf_form_formation['formation_interne'] : false,
  );

  $form['internal_training_value'] = array(
      '#type' => 'hidden',
      '#title' => t('Formation interne value'),
      '#value' => ($temp_dgf_form_formation) ? $temp_dgf_form_formation['formation_interne'] : false
  );

  $form['annual_distribution'] = array(
      '#type' => 'fieldset',
      '#title' => t ( 'Répartition annuelle : ' )
  );

  $form['annual_distribution']['year1'] = array(
      '#type' => 'textfield',
      '#title' => (!empty($temp_dgf_form_formation_repartition[0]->annee)) ?
          $temp_dgf_form_formation_repartition[0]->annee : (string)($annee_formation),
      '#default_value' => (!empty($temp_dgf_form_formation_repartition[0]) ?
          $temp_dgf_form_formation_repartition[0]->repartition_heure : null),
  	  '#field_suffix' => 'en heures',
  );

  $form['annual_distribution']['year2'] = array(
      '#type' => 'textfield',
      '#title' => (!empty($temp_dgf_form_formation_repartition[1]->annee)) ?
          $temp_dgf_form_formation_repartition[1]->annee : (string)($annee_formation+1),
      '#default_value' => (!empty($temp_dgf_form_formation_repartition[1]) ?
          $temp_dgf_form_formation_repartition[1]->repartition_heure : null),
  	  '#field_suffix' => 'en heures',
  );

  $form['annual_distribution']['year3'] = array(
      '#type' => 'textfield',
      '#title' => (!empty($temp_dgf_form_formation_repartition[2]->annee)) ?
          $temp_dgf_form_formation_repartition[2]->annee : (string)($annee_formation+2),
      '#default_value' => (!empty($temp_dgf_form_formation_repartition[2]) ?
          $temp_dgf_form_formation_repartition[2]->repartition_heure : null),
  	  '#field_suffix' => 'en heures',
  );

  $form['clearfix'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div></div>',
  );

  $modal_internal_training_content = '<div id="modalinternaltraining" class="modal" tabindex="-1" role="dialog" aria-hidden="true" aria-labelledby="mySmallModalLabel">
      <div class="modal-dialog modal-md">
          <div class="modal-content">
              <div class="modal-header">
                  <h4 class="modal-title">Formation interne</h4>
              </div>
              <div class="modal-body">
                <p>
                    L\'employeur atteste que le service de formation interne dispose
                    des moyens nécessaires à la réalisation de la formation du salarié.
                </p>
              </div>
              <div class="modal-footer">
              <input class="btn btn-submit form-submit" data-dismiss="modal" type="button" id="internal_training_quit_modal" value="Oui">
              </div>
          </div><!-- /.modal-content -->
      </div><!-- /.modal-dialog -->
    </div><!-- /.modal -->';

  $form['modal_internal_training'] = array(
      '#type' => 'markup',
      '#markup' => $modal_internal_training_content,
  );

  // Ajout des boutons d'actions
  $validatorsBoutonNext = array(
      'dgf_formation_form_validate_standard',
      'dgf_formation_form_validate',
  );
  $submitsBoutonNext = array('dgf_formation_form_submit');
  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_formation_form_validate_standard');
  $validatorsSave = array('dgf_formation_form_validate_standard');
  $submitsSave = array('dgf_formation_form_submit');
  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);

  return $form;
}

function dgf_formation_formations_recurrentes() {
  // Recherche des formations récurrentes
  //  max(count(libellé de formations)) pour l'utilisateur
  $formations_recurrentes = array();
  $formations_recurrentes =  formation_db_get_formations_recurrentes();
  $listgroupitem_formations_recurrentes = null;
  $page = '';
  $i = 0;
  foreach ($formations_recurrentes as $formation) {
  	$i++;
  	if(($i % 2) == 0) {
  		$paire = 'even';
  	}
  	else {
  		$paire = 'odd';
  	}
  	$listgroupitem_formations_recurrentes = $listgroupitem_formations_recurrentes . '<li class="list-group-item '. $paire .'" data-id="'. $formation['id'] .'">' . $formation['libelle'] . '</li>';
  }

  if (isset($listgroupitem_formations_recurrentes)) {
    $page = '
        <div class="panel panel-info">
          <div class="panel-heading">
            <h3 class="panel-title">Formations récurrentes</h3>
    		<div class="panel-arrow-header"></div>
          </div>
          <div class="panel-body">
            <ul class="list-group">'.$listgroupitem_formations_recurrentes.'</ul>
          </div>
          <div class="panel-footer">
            <div class="panel-arrow-footer"></div>
          </div>
        </div>
    ';
  }

  return $page;
}