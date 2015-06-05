<?php

// TODO : mettre les libellés dans un fichier séparé

function _dgf_contrat_pro_stagiaire_require_once_files() {
  require_once 'stagiaire_langs.inc';
  require_once 'stagiaire_submit.inc';
  require_once 'stagiaire_validate.inc';
  require_once 'stagiaire_db.inc';
}

function _dgf_contrat_pro_stagiaire_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/stagiaire/js/stagiaire.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/stagiaire/css/stagiaire.css' );
}

function dgf_contrat_pro_stagiaire_form($form, &$form_state) {
  _dgf_contrat_pro_stagiaire_require_once_files();
  _dgf_contrat_pro_stagiaire_include_js_css();

  // on regarde le 4eme argument de l'url
  $temp_dgf_form_salarie = array();
  $stagiaire = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(4) !== null) {
    $id_dgf = arg(4);
    $temp_dgf_form_salarie = salarie_db_get_temp_dgf_form_salarie($id_dgf);
    $stagiaire = salarie_db_get_v_salarie($temp_dgf_form_salarie['id_ref_esclave_salarie']);
  }

  shared_get_referentiel_data(array('ref_diplome', 'ref_derniere_situation','ref_beneficiaire_minimas_sociaux'));
  $entreprises = shared_db_functions_get_ref_esclave_entreprise();

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa-2.png',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => ($temp_dgf_form_salarie) ? $id_dgf : null,
      '#title' => t('Id demande' ));

  if (empty($entreprises)) {
    drupal_set_message('Attention, il n\'y a aucun établissement pour votre compte utilisateur. Vous ne pouvez faire
      une demande.', 'error');
  } else {
    $form['etablishment'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="required">',
        '#suffix' => '</div>',
        '#title' => t('Etablissement'),
        '#options' => $entreprises,
        '#default_value' => ($temp_dgf_form_salarie) ? trim($temp_dgf_form_salarie['id_ref_esclave_entreprise']) : null,
    );
  }

  $form['id_salarie'] = array(
      '#type' => 'hidden',
      '#default_value' => ($temp_dgf_form_salarie) ? trim($temp_dgf_form_salarie['id_ref_esclave_salarie']) : null,
      '#title' => t('Id salarie' ));

  $form['lastname'] = array(
    '#type' => 'textfield',
    '#prefix' => '<div class="required">',
    '#suffix' => '</div>',
    '#default_value' => ($stagiaire) ? trim($stagiaire['nom']) : null,
    '#title' => t('Nom' ),
    '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
  );

  $form['firstname'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#default_value' => ($stagiaire) ? trim($stagiaire['prenom']) : null,
      '#suffix' => '</div>',
      '#title' => t('Prénom' ));

  $form['birthday'] = array(
    '#title' => t('Date de naissance'),
    '#type' => 'textfield',
    '#prefix' => '<div class="required">',
    '#suffix' => '</div>',
    '#default_value' => ($stagiaire) ? date_format(date_create($stagiaire['date_de_naissance']), 'd/m/Y')  : null,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['age'] = array(
    '#type' => 'textfield',
    '#title' => t('Âge'),
    '#attributes' => array('readonly' => 'readonly'),
  );

  $civilites = shared_db_get_title(false);
  $form['man_woman'] = array(
      '#type' => 'radios',
      '#title' => t('Civilité'),
      '#default_value' => $stagiaire ? trim($stagiaire['id_civilite']) : null,
      '#options' => $civilites,
  );

  $form['handicapped_worker'] = array(
      '#type' => 'radios',
      '#title' => t('Reconnu travailleur handicapé'),
      '#default_value' => ($stagiaire) ? $stagiaire['est_travailleur_handicape'] : null,
      '#options' => array(
          0 => t('Non'),
          1 => t('Oui' )
      )
  );

  $form['num_rue'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de rue'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['numero_rue'] : null,
      '#attributes' =>array('placeholder' => t('N°'))
  );
  $form['nom_rue'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom de rue'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['nom_rue'] : null,
      '#attributes' =>array('placeholder' => t('Voie'))
  );
  $form['complement_adresse'] = array(
      '#type' => 'textfield',
      '#title' => t('Complement d\'adresse'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['complement_adresse'] : null,
  );

  $form['zip_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code postal / Ville'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['code_postal'] : null,
  );

  $form['city'] = array(
      '#type' => 'textfield',
      '#title' => t('Ville'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['ville'] : null,
  );

  $form['phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['telephone'] : null,
  );

  $form['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Courriel'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['email'] : null,
  );

  $form['highest_level'] = array(
      '#type' => 'select',
      '#title' => t('Diplôme le plus élevé'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_diplome'],
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['id_ref_diplome'] : null,
      '#field_suffix' => '<a id="highest_level_tooltip" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message à definir" style ="float:none;"></a>',
  );

  $form['social_beneficiary'] = array(
      '#type' => 'select',
      '#title' => t('Bénéficiaire des minimas sociaux'),
      '#options' =>  $_SESSION['referentiel_extranet_datas']['ref_beneficiaire_minimas_sociaux'],
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['id_ref_beneficiaire_minimas_sociaux'] : null,
  );

  $form['last_status'] = array(
      '#type' => 'select',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Dernière situation'),
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_derniere_situation'],
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['id_ref_derniere_situation'] : null,
  );

  $form['pole_emploi_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro d\'inscrit au pôle emploi'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['numero_inscrit_pole_emploi'] : null,
  );

  $form['since_month'] = array(
      '#type' => 'textfield',
      '#title' => t('Depuis combien de mois'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['nombre_mois_inscrit_pole_emploi'] : null,
  );

  $form['pension_fund'] = array(
      '#type' => 'textfield',
      '#title' => t('Caisse de retraite'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['caisse_retraite'] : null,
  );

  $form['contingency_fund'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Caisse de prévoyance'),
      '#default_value' => ($temp_dgf_form_salarie) ? $temp_dgf_form_salarie['caisse_prevoyance'] : null,
  );

  $form['info_juridique'] = array(
      '#type' => 'item',
      '#field_suffix' => '<a id="juridique_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="le message à definir" style ="float:none;"></a>',
      '#title' => t('Informations juridique')
  );
  $form['plus_26_ans'] = array(
      '#type' => 'item',
      '#field_suffix' => '<div class="messageInfo">Attention : Pour être éligible au contrat de professionnalisation, le stagiaire de plus de 26 ans doit posséder un numéro d’identification « demandeur d’emploi », pour ce faire, il suffit de s\'inscrire au pôle emploi.</div>',
      '#title' => t(''),
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
      'dgf_contrat_pro_stagiaire_standard_form_validate',
      'dgf_contrat_pro_stagiaire_specific_form_validate',
   );
  $submitsBoutonNext = array('dgf_contrat_pro_stagiaire_form_submit');
  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_contrat_pro_stagiaire_form_validate');
  $validatorsSave = array(
      'dgf_contrat_pro_stagiaire_standard_form_validate',
      'dgf_contrat_pro_stagiaire_specific_form_validate',
  );
  $submitsSave = array('dgf_contrat_pro_stagiaire_form_submit');
  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);

  return $form;
}

