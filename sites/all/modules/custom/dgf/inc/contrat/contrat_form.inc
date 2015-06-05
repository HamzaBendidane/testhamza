<?php

function _dgf_contrat_require_once_files() {
  require_once 'contrat_db.inc';
require_once 'contrat_langs.inc';
require_once 'contrat_submit.inc';
require_once 'contrat_validate.inc';
}

function _dgf_contrat_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf' ) . '/inc/contrat/js/contrat.js' );
  drupal_add_css(drupal_get_path('module', 'dgf' ) . '/inc/contrat/css/contrat.css' );
}

// --------------------------------------------------
// Création du formulaire
// --------------------------------------------------
function dgf_contrat_form($form, &$form_state) {
  _dgf_contrat_require_once_files();
  _dgf_contrat_include_js_css();

  // on regarde le 3eme argument de l'url pour retrouver s'il y a des données
  $temp_dgf_form_contrat = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(3) !== null) {
    $id_dgf = arg(3);
    $temp_dgf_form_contrat = contrat_db_get_temp_dgf_form_salarie($id_dgf);
  } else {
    return;
  }

  shared_get_referentiel_data(array('ref_groupe'));

  $age = contrat_db_get_age_salarie($id_dgf);

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa-3.png',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => $id_dgf,
      '#title' => t('Id demande' )
  );

  $form['id_dgf_contrat'] = array(
      '#type' => 'hidden',
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['id'] : null,
      '#title' => t('Id demande' )
  );

  if ($age >= 26) {
    $form['plus_26_ans'] = array(
        '#type' => 'item',
        '#field_suffix' => '<div class="messageInfo center">Contrat de professionnalisation plus de 26 ans </div>',
        '#title' => t(''),
    );
  } else {
    $form['moins_26_ans'] = array(
        '#type' => 'item',
        '#field_suffix' => '<div class="messageInfo center">Contrat de professionnalisation moins de 26 ans </div>',
        '#title' => t(''),
    );
  }

  $form['nature'] = array(
      '#type' => 'radios',
      '#title' => 'Nature du contrat',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['id_ref_type_contrat'] : NULL,
      '#options' => array(t('CDI'), t('CDD')),
  );

  $form['type'] = array(
      '#type' => 'select',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['id_ref_esclave_type_contrat'] : NULL,
      '#title' => t('Type de contrat'),
      '#options' => contrat_db_get_type_de_contrat(),
  );

  $form['date_begin'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Date de début'),
      '#default_value' => $temp_dgf_form_contrat ? shared_parse_mssql_date($temp_dgf_form_contrat['date_debut'])->format('d/m/Y') : NULL,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['date_end'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Date de fin'),
      '#default_value' => $temp_dgf_form_contrat ? shared_parse_mssql_date($temp_dgf_form_contrat['date_fin'])->format('d/m/Y') : NULL,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['training_duration'] =array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Durée du contrat'),
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['duree_contrat_mois'] : NULL,
      '#field_suffix' => t('en mois'),
      '#attributes' => array('disabled' => true)
  );

  $form['test_period'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Durée de la période d’essai'),
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['duree_essai_jour'] : NULL,
      '#field_suffix' => t('en jours')

  );

  $form['weekly_hour'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required"><div class = "left">',
      '#suffix' => '</div>',
	  '#size' => '20',
      '#title' => t('Durée hebdomadaire'),
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['duree_hebdo_travail_heure'] : NULL,
      '#field_suffix' => t('en heures')
  );

  $form['weekly_minute'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class = "right">',
      '#suffix' => '</div></div>',
	  '#size' => '20',
      '#title' => t(''),
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['duree_hebdo_travail_minute'] : NULL,
      '#field_suffix' => t('en minutes')
  );

  $form['niveau'] = array(
      '#type' => 'textfield',
	  '#prefix' => '<div class="clearfix"></div>',
      '#title' => t('Niveau'),
      '#default_value' => isset($temp_dgf_form_contrat['niveau']) ? $temp_dgf_form_contrat['niveau'] : NULL,
      '#field_suffix' => '<a id="niveau_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message niveau" style="float: none;"></a>',
  );

  $form['coefficient'] = array(
      '#type' => 'textfield',
      '#title' => t('Coefficient'),
      '#default_value' => isset($temp_dgf_form_contrat['coefficient']) ? $temp_dgf_form_contrat['coefficient'] : NULL,
      '#field_suffix' => '<a id="coef_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message coef" style="float: none;"></a>',
  );

  $form['group'] = array(
      '#type' => 'select',
      '#title' => t('Groupe'),
      '#field_suffix' => '<a id="group_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message group" style="float: none;"></a>',
      '#default_value' => isset($temp_dgf_form_contrat['id_ref_groupe']) ? $temp_dgf_form_contrat['id_ref_groupe'] : NULL,
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_groupe'],
  );

   $form['position_held'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Emploi occupé'),
      '#default_value' => $temp_dgf_form_contrat ? $temp_dgf_form_contrat['emploi_occupe'] : NULL,
  );

  $form['collective_convention'] = array(
      '#type' => 'select',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Convention collective'),
      '#default_value' => isset($temp_dgf_form_contrat['id_ref_esclave_convention_collective']) ?
        trim($temp_dgf_form_contrat['id_ref_esclave_convention_collective']) : NULL,
      '#options' => contrat_db_get_convention_collective(),
  );

  $form['monthly_gross_pay'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Salaires brut mensuel'),
      // soit la valeur saisie pas l'user en cas de retour, soit la valeur calculée en cas de poursuite
      '#default_value' => isset($temp_dgf_form_contrat['salaire_brut_mensuel']) ?
        $temp_dgf_form_contrat['salaire_brut_mensuel'] : '',
      '#field_suffix' => '<a id="pay_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message pay" style="float: none;"></a>',
  );

  $form['min_monthly_gross_pay'] = array(
      '#type' => 'hidden',
      '#title' => t('Minimum salaires brut mensuel'),
      '#default_value' => contrat_db_get_minimum_salaire_salarie($id_dgf, $age),
  );

  $form['clearfix'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div></div>',
  );

  // Ajout des boutons d'actions
  $validatorsBoutonNext = array(
        'dgf_cp_contract_standard_validate',
        'dgf_cp_contract_specific_validate',
  );
  $submitsBoutonNext = array('dgf_contrat_form_submit');
  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_contrat_form_validate');
  $validatorsSave = array('dgf_cp_contract_specific_validate');
  $submitsSave = array('dgf_contrat_form_submit');
  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);

  return $form;
}
