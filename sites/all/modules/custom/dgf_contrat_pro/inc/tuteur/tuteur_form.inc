<?php

function _dgf_contrat_pro_tuteur_require_once_files() {
  require_once 'tuteur_db.inc';
  require_once 'tuteur_langs.inc';
  require_once 'tuteur_submit.inc';
  require_once 'tuteur_validate.inc';
  require_once drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/stagiaire/stagiaire_db.inc';
}

function _dgf_contrat_pro_tuteur_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/tuteur/js/tuteur.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/tuteur/css/tuteur.css' );
}

function dgf_contrat_pro_tuteur_form($form, &$form_state) {
  _dgf_contrat_pro_tuteur_require_once_files();
  _dgf_contrat_pro_tuteur_include_js_css();

  $temp_dgf_form_tuteur = array();
  $salarie = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(4) !== null) {
    $id_dgf = arg(4);
    $temp_dgf_form_tuteur = tuteur_db_get_temp_dgf_form_tuteur($id_dgf);
    $salarie = tuteur_db_get_v_salarie($temp_dgf_form_tuteur['id_ref_esclave_salarie']);
    $temp_dgf_form_salarie = salarie_db_get_temp_dgf_form_salarie($id_dgf);
  } else {
    return;
  }

  shared_get_referentiel_data(array('ref_diplome'));
  $entreprises = shared_db_functions_get_ref_esclave_entreprise();

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa-6.png',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => $id_dgf,
      '#title' => t('Id demande' )
  );

  $form['id_dgf_tuteur'] = array(
      '#type' => 'hidden',
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['id'] : null,
      '#title' => t('Id demande' )
  );

  $default_value_etablishment = null;
  if ($temp_dgf_form_tuteur) {
    $default_value_etablishment = trim($temp_dgf_form_tuteur['id_ref_esclave_entreprise']);
  } else if ($temp_dgf_form_salarie) {
    $default_value_etablishment = trim($temp_dgf_form_salarie['id_ref_esclave_entreprise']);
  }

  if (empty($entreprises)) {
    drupal_set_message('Attention, il n\'y a aucun établissement pour votre compte utilisateur. Vous ne pouvez faire
      une demande.', 'error');
  } else {
    $form['etablishment'] = array(
        '#type' => 'select',
        '#title' => t('Etablissement' ),
        '#prefix' => '<div class="required">',
        '#suffix' => '</div>',
        '#default_value' => $default_value_etablishment,
        '#options' => $entreprises,
    );
  }

  $form['id_salarie'] = array(
      '#type' => 'hidden',
      '#default_value' => ($temp_dgf_form_tuteur) ? trim($temp_dgf_form_tuteur['id_ref_esclave_salarie']) : null,
      '#title' => t('Id salarie' )
  );

  $form['modal'] = array(
      '#type' => 'hidden',
      '#default_value' => isset($_GET['modal']) ? $_GET['modal'] : '',
      '#title' => t('Modal à afficher' )
  );

  $form['lastname'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Nom' ),
      '#default_value' => $salarie ? trim($salarie['nom']) : null,
      '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
  );

  $form['firstname'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => $salarie ? trim($salarie['prenom']) : null,
      '#title' => t('Prénom' ),
  );

  $form['telephone'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone' ),
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['telephone'] : null,
  );
  $form['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email' ),
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['email'] : null,
  );

  $form['birthday'] = array(
      '#title' => t('Date de naissance' ),
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => $salarie ? date_format(date_create($salarie['date_de_naissance']), 'd/m/Y') : null,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" )
  );

  $form['nb_salarie'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Nombre de salariés encadrés par ce tuteur' ),
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['nb_salarie_encadre'] : null,
  );

  $form['emploi_occupe'] = array(
      '#type' => 'textfield',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#title' => t('Emploi occupé' ),
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['emploi'] : null,
  );

  $form['dernier_diplome'] = array(
      '#type' => 'select',
      '#title' => t('Dernier diplome obtenu' ),
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_diplome'],
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['id_ref_diplome'] : null,
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
      'dgf_contrat_pro_tuteur_specific_form_validate',
      'dgf_contrat_pro_tuteur_standard_form_validate',
  );
  $submitsBoutonNext = array('dgf_contrat_pro_tuteur_form_submit');
  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_contrat_pro_tuteur_form_validate');
  $validatorsSave = array(
      'dgf_contrat_pro_tuteur_standard_form_validate',
      'dgf_contrat_pro_tuteur_specific_form_validate'
  );
  $submitsSave = array('dgf_contrat_pro_tuteur_form_submit');
  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);

  _dgf_contrat_pro_tuteur_attestation_form($form, $temp_dgf_form_tuteur);

  _dgf_contrat_pro_tuteur_message_info_finale_form($form, $temp_dgf_form_tuteur);

  return $form;
}

function _dgf_contrat_pro_tuteur_attestation_form(&$form, $temp_dgf_form_tuteur) {
  //modal attestation
  $prefix = '<div id="modal-certification-tuteur" class="modal" tabindex="-1" role="dialog" aria-hidden="true">
            <div class="modal-dialog">
                <div class="modal-content attestation">
                    <div class="modal-header">
                        <button type="button" class="close modalNext" data-dismiss="modal" aria-hidden="true">&times;</button>
                        <h4 class="modal-title">Attestation </h4>
                    </div>
                    <div class="modal-body">';

  $suffix =
  '</div>
                </div><!-- /.modal-content -->
            </div><!-- /.modal-dialog -->
          </div><!-- /.modal -->';


  $form['modal_attestation']['header'] = array(
      '#type' => 'markup',
      '#markup' => $prefix,
  );

  $form ['modal_attestation']['beneficier'] = array(
      '#type' => 'radios',
      '#title' => t('Le tuteur : ' ),
      '#options' => array(
          0 => t('va bénéficier d’une formation' ),
          1 => t('a déjà bénéficié d’une formation' )
      ),
      '#default_value' => $temp_dgf_form_tuteur && $temp_dgf_form_tuteur['certif_role_tuteur'] && $temp_dgf_form_tuteur['certif_deux_ans_exp'] ? $temp_dgf_form_tuteur['formation_tuteur'] : NULL,

  );

  $form ['modal_attestation']['date_formation'] = array(
      '#title' => t('Date de formation' ),
      '#type' => 'textfield',
      '#default_value' => $temp_dgf_form_tuteur ?
        date_format(date_create($temp_dgf_form_tuteur['date_formation']), 'd/m/Y') : null,
      '#attributes' => array('class' => array('datePicker'),"autocomplete"=>"off" ),
      '#prefix' => '<div id="vaBeneficierFormation">',
  );

  $form ['modal_attestation']['duree_formation'] = array(
      '#title' => t('Durée de formation' ),
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['duree_formation'] : null,
      '#type' => 'textfield',
  );

  $form ['modal_attestation']['nom_organisme'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom de l\'organisme ' ),
      '#suffix' => '</div>',
      '#default_value' => $temp_dgf_form_tuteur ? $temp_dgf_form_tuteur['nom_organisme'] : null,
  );

  $checkbox_default_value = array();
  if ($temp_dgf_form_tuteur) {
    if ($temp_dgf_form_tuteur['certif_role_tuteur'] && $temp_dgf_form_tuteur['certif_deux_ans_exp']) {
      $checkbox_default_value = array('A été informé sur son rôle de tuteur', 'Bénéficie de plus de 2 ans d\'ancienneté');
    } else if ($temp_dgf_form_tuteur['certif_role_tuteur']) {
      $checkbox_default_value = array('A été informé sur son rôle de tuteur');
    } else if ($temp_dgf_form_tuteur['certif_deux_ans_exp']) {
      $checkbox_default_value = array('Bénéficie de plus de 2 ans d\'ancienneté');
    }
  }

  $form ['modal_attestation']['certifier'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Vous certifiez que le tuteur: ' ),
      '#suffix' =>'</div>
                <div class="modal-footer">',
      '#options' => drupal_map_assoc(array(
          t('A été informé sur son rôle de tuteur' ),
          t('Bénéficie de plus de 2 ans d\'ancienneté' ),
      )),
      '#default_value' => $checkbox_default_value,
  );

  $form ['modal_attestation']['certifier']['#field_suffix'] = '<a id="va_beneficier_info" class="glyphicon glyphicon-question-sign" data-toggle="tooltip" data-original-title="Vous devez certifier avoir respecté vos obligations liées au tutorat.
Circulaire N°2012/15 du 19/07/2012 : « la personne désignée, pour être tuteur doit être volontaire et justifier d’une expérience professionnelle d’au moins deux ans dans une qualification en rapport avec l’objectif de professionnalisation visée »
          "></a>';

  $form ['modal_attestation']['modal_annuler'] = array(
      '#type' => 'submit',
      '#value' => t('Annuler'),
      '#attributes' => array('class' => array('btn btn-danger modalQuit'),),
      '#validate' => array('dgf_contrat_pro_tuteur_form_validate'),
  );

  $form ['modal_attestation']['modal_save_attestation'] = array(
      '#type' => 'submit',
      '#value' => t('Sauvegarder'),
      '#attributes' => array('class' => array('btn btn-primary modalSave'),),
      '#validate' => array(
          'dgf_contrat_pro_tuteur_specific_form_validate',
          'dgf_contrat_pro_tuteur_standard_form_validate',
          'dgf_contrat_pro_tuteur_attestation_form_validate',
      ),
      '#submit' => array('dgf_contrat_pro_tuteur_attestation_form_submit',),
  );

  $form['modal_attestation']['footer'] = array(
      '#type' => 'markup',
      '#markup' => $suffix,
  );
}

function _dgf_contrat_pro_tuteur_message_info_finale_form(&$form, $temp_dgf_form_tuteur) {
  // Gestion de l'afichage en modal
  $prefix = '<div id="modal-message-information-final" class="modal" tabindex="-1" role="dialog" aria-hidden="true">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close modalQuit" data-dismiss="modal" aria-hidden="true">&times;</button>
                        <h4 class="modal-title">Fin de saisie</h4>
                    </div>';

  $body_prefix    = '<div class="modal-body">';
  $body_suffix    = '</div>';


  $footer_prefix     = '<div class="modal-footer">';
  $footer_suffix     = '</div>';
  $suffix  =       '</div><!-- /.modal-content -->
            </div><!-- /.modal-dialog -->
          </div><!-- /.modal -->';

  $form['modal_info_final']['header'] = array(
      '#type' => 'markup',
      '#markup' => $prefix,
  );



  $form['modal_info_final']['text'] = array (
      '#type' => 'fieldset',
      '#title' => '',
      '#prefix' => $body_prefix,
       '#suffix' => $body_suffix,

  );


  $form['modal_info_final']['text']['lines'] = array(
      '#type' => 'markup',
      '#markup' => @MSG_MESSAGE_INFORMATION_FINAL,
  );

  $form['modal_info_final']['goto-cerfa'] = array (
      '#type' => 'submit',
      '#value' => @MSG_MESSAGE_INFORMATION_FINAL_BUTTON,
      '#submit' => array ('dgf_contrat_pro_tuteur_message_info_finale_form_submit'),
      '#attributes' => array(
          'class' => array('btn btn-primary modalSuivant'),
      ),
      '#prefix' => $footer_prefix,
      '#suffix' => $footer_suffix,
  );

  $form['modal_info_final']['footer'] = array(
      '#type' => 'markup',
      '#markup' => $suffix,
  );
}