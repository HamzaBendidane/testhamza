<?php

function _dgf_organisme_formation_require_once_files() {
  require_once 'organisme_formation_langs.inc';
  require_once 'organisme_formation_submit.inc';
  require_once 'organisme_formation_validate.inc';
  require_once 'organisme_formation_db.inc';
  require_once 'organisme_formation_auto_complete.inc';
}

function _dgf_organisme_formation_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf' ) . '/inc/organisme_formation/js/organisme_formation.js' );
  drupal_add_css(drupal_get_path('module', 'dgf' ) . '/inc/organisme_formation/css/organisme_formation.css' );
}

function dgf_organisme_formation_form($form, &$form_state) {


  _dgf_organisme_formation_require_once_files();
  _dgf_organisme_formation_include_js_css();

  $fonctions = organisme_formation_db_get_function_contact();
  $civilites = shared_db_get_title();
  // On récupère les informations précédemment saisies
  $temp_dgf_form_organisme_formation = array();
  $organisme_formation = array();
  $contact_organisme_formation = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(3) !== null) {
    $id_dgf = arg(3);
    $temp_dgf_form_organisme_formation = organisme_formation_db_get_temp_dgf_form_organisme_formation($id_dgf);
    $organisme_formation = organisme_formation_db_get_v_organisme_formation(
        $temp_dgf_form_organisme_formation['id_ref_esclave_organisme_formation']);
    $adresse_organisme_formation = organisme_formation_db_get_v_adresse_organisme_formation(
        $temp_dgf_form_organisme_formation['id_ref_esclave_organisme_formation']);
    $contact_organisme_formation = organisme_formation_db_get_v_contact_organisme_formation(
        $temp_dgf_form_organisme_formation['id_ref_esclave_contacts_organisme_formation']);
  } else {
    return;
  }

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa-5.png',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => $id_dgf,
      '#title' => t('Id demande' )
  );

  $form['id_dgf_organisme_formation'] = array(
      '#type' => 'hidden',
      '#default_value' => $temp_dgf_form_organisme_formation ? $temp_dgf_form_organisme_formation['id'] : null,
      '#title' => t('Id demande' )
  );

  $form['title_markup'] = array(
      '#type' => 'markup',
      '#markup' => '<legend><span class="container-legend">' . t('Rechercher un organisme de formation') .'</span></legend>',
  );

  $form['siret_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de SIRET'),
      '#default_value' => $organisme_formation ? trim($organisme_formation['siret']) : NULL,
      '#attributes' =>array('placeholder' => t('Min. 3 premiers chiffres')),
      '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  $form['activity_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de déclaration d’activité'),
      '#attributes' =>array('placeholder' => t('Min. 3 premiers chiffres')),
      '#default_value' => $organisme_formation ? trim($organisme_formation['numero_de_declaration_existence']) : NULL,
      '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  $html_orga_infos = '';
  if ($adresse_organisme_formation) {
    $html_orga_infos = trim($adresse_organisme_formation['numero_de_rue']) . ' '
            .trim($adresse_organisme_formation['rue']) . ' ' . trim($adresse_organisme_formation['complement_de_rue'])
            . ' ' . trim($adresse_organisme_formation['complement_de_rue_2']) . ' '
            . trim($adresse_organisme_formation['code_postal']) . ' ' . trim($adresse_organisme_formation['ville'])
            . '<br />';
    $html_orga_infos .= 'Téléphone : ' . trim($organisme_formation['telephone_principal']) . '<br />';
    $html_orga_infos .= 'Courriel : ' . trim($organisme_formation['email']) . '<br />';
    $html_orga_infos .= 'Numéro de TVA intracommunautaire : ' . trim($organisme_formation['tva_intracommunautaire'])
        . '<br />';
  }

  $form['corporate_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Raison sociale'),
      '#attributes' =>array('placeholder' => t('Min. 3 premieres lettres')),
      '#default_value' => $organisme_formation ? trim($organisme_formation['raison_sociale']) : NULL,
      '#field_suffix' => '<img src='.base_path() . path_to_theme() . '/' . 'images/search.png'.' />',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>
          <div class="form-wrapper" id="print-info-generale" style="display:none">
            <legend><span class="container-legend">Organisme de formation ou prestataire</span></legend>
            <div class="form-item form-type-textfield form-item-street-number" id="orga-info">' . $html_orga_infos . '</div>
          </div>',
  );

  $form['id_ref_organisme_formation'] = array(
      '#type' => 'hidden',
      '#default_value' => $temp_dgf_form_organisme_formation ?
        $temp_dgf_form_organisme_formation['id_ref_esclave_organisme_formation'] : null,
      '#title' => t('Id demande' ),
      '#attributes' => array("id" => "id-ref-formation")
  );

//   // OF possède un compte
//   $form['extranet_count'] = array(
//       '#type' => 'checkbox',
//       '#title' => t('OF possède un compte extranet.'),
//       '#attributes' =>array(
//           'checked' => t('checked'),
//           'disabled' => true,
//       ),
//   );

  _dgf_organisme_formation_info_generale_form($form, null);

  _dgf_organisme_formation_contact_form($form, $temp_dgf_form_organisme_formation, $organisme_formation, $form_state,
    $fonctions, $civilites);

  _dgf_organisme_formation_new_contact_form($form, null, $fonctions, $civilites);

  _dgf_organisme_formation_cout_form($form, $temp_dgf_form_organisme_formation);


  $form['direct_payment'] = array(
      '#type' => 'radios',
      '#title' => t('Le tuteur : ' ),
      '#options' => array(
          t('Ne souhaite pas que l\'OPCAIM règle directement l’organisme de formation, demande le remboursement.' ) ,
          t('Souhaite que l\'OPCAIM règle directement l’organisme de formation.' )),
      '#default_value' => $temp_dgf_form_organisme_formation ? $temp_dgf_form_organisme_formation['paiement_direct'] : null,
      '#title' => t(''),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  // Début Modal Quitter
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
      'dgf_organisme_formation_standard_validate',
      'dgf_organisme_formation_specific_validate',
  );
  $submitsBoutonNext = array('dgf_organisme_formation_form_submit');
  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_organisme_formation_form_validate');
  $validatorsSave = array('dgf_organisme_formation_form_standard_validate', 'dgf_organisme_formation_specific_validate');
  $submitsSave = array('dgf_organisme_formation_form_submit');
  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);


  return $form;
}

function _dgf_organisme_formation_info_generale_form(&$form, $values_default) {
  $form['info_generale'] = array(
      '#type' => 'container',
      '#title' => t(''),
      '#attributes' => array('style' => 'display: none;'),
  );

  $form['info_generale']['title_markup'] = array(
      '#type' => 'markup',
      '#markup' => '<legend><span class="container-legend">' . t('Nouvel organisme de formation ou prestataire') .'</span></legend>',
  );

  $form['info_generale']['street_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de rue'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => (!empty($values_default['t_numero_adresse'])) ? $values_default['t_numero_adresse'] : NULL,
  );

  $form['info_generale']['street_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom de rue'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => isset($values['address']) ? $values['address'] : NULL,
  );

  $form['info_generale']['address_complement'] = array(
      '#type' => 'textfield',
      '#title' => t('Complement d\'adresse'),
      '#default_value' => (!empty($values_default['t_complement_rue'])) ? $values_default['t_complement_rue'] : NULL,
  );

  $form['info_generale']['zip_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code postal'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => (!empty($values_default['t_code_postal'])) ? $values_default['t_code_postal'] : NULL,
  );

  $form['info_generale']['city'] = array(
      '#type' => 'textfield',
      '#title' => t('Ville'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
      '#default_value' => (!empty($values_default['t_ville'])) ? $values_default['t_ville'] : NULL,
  );

  $form['info_generale']['country'] = array(
      '#type' => 'textfield',
      '#title' => t('Pays'),
      '#default_value' => 'France',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  $form['info_generale']['phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_telephone'])) ? $values_default['t_telephone'] : NULL,
  );

  $form['info_generale']['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Courriel'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_email'])) ? $values_default['t_email'] : NULL,
  );

  $form['info_generale']['tva_bool'] = array(
      '#type' => 'checkbox',
      '#title' => t('Assujetti à la TVA'),
//       '#default_value' => (!empty($values_default['t_assujetti_tva'])) ? $values_default['t_assujetti_tva'] : NULL,
  );

  $form['info_generale']['tva_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de TVA intracommunautaire'),
//       '#default_value' => (!empty($values_default['t_numero_tva'])) ? $values_default['t_numero_tva'] : NULL,
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );
}

function _dgf_organisme_formation_contact_form(&$form, $temp_dgf_form_organisme_formation, $organisme_formation,
    $form_state, $fonctions, $civilites) {
  $form['contact'] = array(
      '#type' => 'container',
      '#title' => t(''),
      '#attributes' => array('style' => 'display: none;'),
  );

  $form['contact']['title_markup'] = array(
      '#type' => 'markup',
      '#markup' => '<legend><span class="container-legend">' . t('Personne à contacter') .'</span></legend>',
  );

  // récupérer les contacts si on est en modif ou une erreur dans le form
  if (isset($form_state['input']['siret_number'])) {
    $contact = organisme_formation_db_get_contact_select($form_state['input']['siret_number']);
  } else if ($organisme_formation) {
    $contact = organisme_formation_db_get_contact_select($organisme_formation['siret']);
  } else {
    $contact = array();
  }

  $form['contact']['select_contact'] = array(
      '#type' => 'select',
      '#title' => t('Contact'),
      '#default_value' => $temp_dgf_form_organisme_formation ? trim($temp_dgf_form_organisme_formation['id_ref_esclave_contacts_organisme_formation']) : NULL,
      '#validated' => TRUE,
      '#options' => $contact,
      '#prefix' => '<div class="required">',
  );

  $form['contact']['add'] = array(
      '#type' => 'button',
      '#value' => t('Ajouter' ),
      '#attributes' => array(
          'class' => array('btn btn-primary add-button'),
          'type' => array('button'),
      ),
      '#suffix' => '</div>',
  );


  $prefix = '<div id="complete-contact-modal" class="modal" tabindex="-1" role="dialog" aria-hidden="true">
      <div class="modal-dialog modal-md">
          <div class="modal-content">
              <div class="modal-header">
                  <button type="button" class="close modalQuit" data-dismiss="modal" aria-hidden="true">&times;</button>
                  <h4 class="modal-title">Données manquantes</h4>
              </div>
              <div class="modal-body">
                <p>Veuillez indiquer la fonction et le courriel du contact sélectionné
                  afin que l\'OPCAIM puisse régler directement l\'organisme de formation</p>';
  $suffix = '</div>
              <div class="modal-footer">
              <input class="btn btn-cancel modalQuit" data-dismiss="modal" type="button" id="edit-modal-quit" value="Annuler">
              <input class="btn btn-submit form-submit modalValid" data-dismiss="modal" type="button" id="edit-complete-modal-save" value="Valider">
              </div>
          </div><!-- /.modal-content -->
      </div><!-- /.modal-dialog -->
    </div><!-- /.modal -->';

  $form['contact']['complete_contact_fonction'] = array(
      '#type' => 'select',
      '#title' => t('Fonction'),
      '#options' => $fonctions,
      '#prefix' => $prefix,
  );

  $form['contact']['complete_contact_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#suffix' => $suffix,
  );

  $prefix = '<div id="new-contact-modal" class="modal" tabindex="-1" role="dialog" aria-hidden="true">
      <div class="modal-dialog modal-md">
          <div class="modal-content">
              <div class="modal-header">
                  <button type="button" class="close modalQuit" data-dismiss="modal" aria-hidden="true">&times;</button>
                  <h4 class="modal-title">Ajouter un contact</h4>
              </div>
              <div class="modal-body">';

  $suffix = '</div>
              <div class="modal-footer">
              <input class="btn btn-cancel modalQuit" data-dismiss="modal" type="button" id="edit-modal-quit" value="Annuler">
              <input class="btn btn-submit form-submit modalValid" type="button" id="edit-modal-save" value="Valider">
              </div>
          </div><!-- /.modal-content -->
      </div><!-- /.modal-dialog -->
    </div><!-- /.modal -->';

  $form['contact']['modal'] = array(
      '#type' => 'container',
      '#title' => t(''),
      '#prefix' => $prefix,
      '#suffix' => $suffix,
  );

  $form['contact']['modal']['modal_contact_title'] = array(
      '#type' => 'select',
      '#title' => t('Civilité'),
//       '#default_value' => (!empty($values_default['t_contact_prenom'])) ? $values_default['t_contact_prenom'] : NULL,
      '#options' => $civilites,
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  $form['contact']['modal']['modal_contact_lastname'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_contact_nom'])) ? $values_default['t_contact_nom'] : NULL,
  );

  $form['contact']['modal']['modal_contact_firstname'] = array(
      '#type' => 'textfield',
      '#title' => t('Prénom'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_contact_prenom'])) ? $values_default['t_contact_prenom'] : NULL,
  );

  $form['contact']['modal']['modal_contact_fonction'] = array(
      '#type' => 'select',
      '#title' => t('Fonction'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_contact_fonction'])) ? $values_default['t_contact_fonction'] : NULL,
      '#options' => $fonctions,
  );

  $form['contact']['modal']['modal_contact_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_contact_email'])) ? $values_default['t_contact_email'] : NULL,
  );

  $form['contact']['modal']['modal_contact_phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
//       '#default_value' => (!empty($values_default['t_contact_telephone'])) ? $values_default['t_contact_telephone'] : NULL,
  );
}

function _dgf_organisme_formation_new_contact_form(&$form, $data, $fonctions, $civilites) {

  $form['new_contact'] = array(
      '#type' => 'container',
      '#title' => t(''),
      '#attributes' => array('style' => 'display: none;'),
  );

  $form['new_contact']['icon_for_contact'] = array(
      '#type' => 'markup',
      '#markup' => '<legend><span class="container-legend">' . t('Personne à contacter') .'</span></legend>',
  );

  $form['new_contact']['new_contact_title'] = array(
      '#type' => 'select',
      '#title' => t('Civilité'),
//       '#default_value' => (!empty($values_default['t_contact_prenom'])) ? $values_default['t_contact_prenom'] : NULL,
      '#options' => $civilites,
  );

  $form['new_contact']['new_contact_lastname'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom'),
//       '#default_value' => (!empty($values_default['t_contact_nom'])) ? $values_default['t_contact_nom'] : NULL,
  );

  $form['new_contact']['new_contact_firstname'] = array(
      '#type' => 'textfield',
      '#title' => t('Prénom'),
//       '#default_value' => (!empty($values_default['t_contact_prenom'])) ? $values_default['t_contact_prenom'] : NULL,
  );

  $form['new_contact']['new_contact_fonction'] = array(
      '#type' => 'select',
      '#title' => t('Fonction'),
//       '#default_value' => (!empty($values_default['t_contact_fonction'])) ? $values_default['t_contact_fonction'] : NULL,
      '#options' => $fonctions,
  );

  $form['new_contact']['new_contact_mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
//       '#default_value' => (!empty($values_default['t_contact_email'])) ? $values_default['t_contact_email'] : NULL,
  );

  $form['new_contact']['new_contact_phone'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
//       '#default_value' => (!empty($values_default['t_contact_telephone'])) ? $values_default['t_contact_telephone'] : NULL,
  );


}

function _dgf_organisme_formation_cout_form(&$form, $temp_dgf_form_organisme_formation) {
  $form['cost'] = array(
      '#type' => 'container',
      '#title' => t(''),
  );

  $form['cost']['title_markup'] = array(
      '#type' => 'markup',
      '#markup' => '<legend><span class="container-legend">' . t('Coûts / dépenses') .'</span></legend>',
  );

  $form['cost']['pedagogical_cost'] = array(
      '#type' => 'textfield',
      '#title' => t('Coût pédagogique'),
      '#default_value' => $temp_dgf_form_organisme_formation ? $temp_dgf_form_organisme_formation['cout_pedagogique'] : NULL,
      '#field_suffix' => '€HT',
      '#prefix' => '<div class="required">',
      '#suffix' => '</div>',
  );

  $form['cost']['eval_pre_formative'] = array(
      '#type' => 'textfield',
      '#title' => t('Evaluation pré-formative'),
      '#default_value' => $temp_dgf_form_organisme_formation ? $temp_dgf_form_organisme_formation['evaluation_preformative'] : NULL,
  );

  $form['cost']['certification_passing'] = array(
      '#type' => 'textfield',
      '#title' => t('Passage de la certification'),
      '#default_value' => $temp_dgf_form_organisme_formation ? $temp_dgf_form_organisme_formation['passage_certification'] : NULL,
  );
}