<?php

/**
 * Check l'email du Responsable en base
 *
 */
function company_register_validate_users_email($form, &$form_state) {
   // Check if user exsit on database of Drupal
  // $mail_to_check = $form_state['values']['Responsable']['Email2'];

  // Validation de l'email du responsable
  $resp_email   =  $form_state['values']['responsable_email'];
  $resp_email_two  =  $form_state['values']['responsable_email2'];

  if(strcmp($resp_email, $resp_email_two) != 0 ){
    form_set_error('responsable_email2', t(@ERROR_MAIL_NOT_EQUAL));
  }
  // Check EMAIL FORMAT
  if(!valid_email_address($resp_email)) {
    form_set_error('responsable_email', t(@ERROR_MAIL_FORMAT));
  }
  if(!valid_email_address($resp_email_two)){
    form_set_error('EmailResresponsable_email2ponsable2', t(@ERROR_MAIL_FORMAT));
  }

  $user_email   =  $form_state['values']['utilisateur_email'];
  $user_email_two  =  $form_state['values']['utilisateur_email2'];

  if(strcmp($user_email, $user_email_two) != 0 ){
    form_set_error('utilisateur_email2', t(@ERROR_MAIL_NOT_EQUAL));
  }
  // Check EMAIL FORMAT
  if(!valid_email_address($user_email)) {
    form_set_error('utilisateur_email', t(@ERROR_MAIL_FORMAT));
  }
  if(!valid_email_address($user_email_two)){
    form_set_error('utilisateur_email2', t(@ERROR_MAIL_FORMAT));
  }
  // Check if User EMAIL EXIST in BASE
  if(user_load_by_mail($user_email)) {
    form_set_error('utilisateur_email', t(@ERROR_MAIL_EXIST));
  }
}

 /**
 * Validation du formulaire d'inscription
 * @param type $form
 * @param type $form_state
 *
 */
 function company_register_form_validate($form , &$form_state) {

  // Validation des champs responsables entreprises
  if (!$form_state['values']['responsable_fonction']) {
    form_set_error('responsable_fonction', t('La fonction du responsable est obligatoire'));
  }
  if (!$form_state['values']['responsable_nom']) {
    form_set_error('responsable_nom', t('Le nom du responsable est obligatoire'));
  }
  if (!$form_state['values']['responsable_prenom']) {
    form_set_error('responsable_prenom', t('Le prénom du responsable est obligatoire'));
  }

  //Validation des champs utilisateurs
  if (!$form_state['values']['utilisateur_nom']) {
    form_set_error('utilisateur_nom', t('Le nom de l\'utilisateur est obligatoire'));
  }
  if (!$form_state['values']['utilisateur_prenom']) {
    form_set_error('utilisateur_prenom', t('Le prénom de l\'utilisateur est obligatoire'));
  }
  if (!$form_state['values']['utilisateur_fonction']) {
    form_set_error('utilisateur_fonction', t('La fonction de l\'utilisateur est obligatoire'));
  }
  if (!$form_state['values']['utilisateur_telephone']) {
    form_set_error('utilisateur_telephone', t(@ERROR_USER_PHONE));
  }
  // Fonctionnalités Utilisateur - Au moins une obligatoire
  if (!$form_state['values']['utilisateur_fonctions']) {
    form_set_error('utilisateur_fonctions', t(@ERROR_USER_RIGHTS));
  }
}

/**
 *  Effectue la validation du numéro de siret.
 *
 */
function company_register_check_siret($SiretField, $SiretNumber) {

  // TODO : fonction à changer : vérifier le SIRET avec la clé.
  // Effectue la validation du numéro du siret
  if (strlen($SiretNumber) < 3) {
    form_set_error($SiretField, t('Au moins 3 caractères doivent être saisis dans le champ N° de Siret'));
  }
}

/**
 *  Validation des champs entreprises: Adressese et raison sociale.
 *
 */
function company_register_validate_entreprise($form, &$form_state) {
  // Validation des champs entreprises
  $nb_siret = $form_state['values']['nb_siret'];

  for ($i = 0; $i < $nb_siret; $i++) {
    // Autre siret
    $siret    = $form_state['values']['company_siret_'.$i];
    // Check Siret Number
    company_register_check_siret('company_siret_'.$i, $siret );

    if (!$form_state['values']['company_siret_'.$i] ) {
      form_set_error('company_siret_'.$i, t('Le numéro de siret est obligatoire'));
    }
    if (!$form_state['values']['company_raison_sociale_'.$i]) {
      form_set_error('company_raison_sociale_'.$i, t('Vous n’avez pas sélectionné d’entreprise, le champ raison sociale est obligatoire.'));
    }
    if (!$form_state['values']['company_adresse_street_number_'.$i]) {
      form_set_error('company_adresse_street_number_'.$i, t('Le numéro de rue est obligatoire'));
    }
    if (!$form_state['values']['company_adresse_street_name_'.$i]) {
      form_set_error('company_adresse_street_name_'.$i, t('Le champ rue est obligatoire'));
    }
//     if (!$form_state['values']['company_adresse_street_name_more_'.$i]) {
//       form_set_error('company_adresse_street_name_more_'.$i, t('Le champ complément de rue est obligatoire'));
//     }
    if (!$form_state['values']['company_adresse_town_'.$i]) {
      form_set_error('company_adresse_town_'.$i, t('Le champ ville est obligatoire'));
    }
    if (!$form_state['values']['company_code_postal_'.$i]) {
      form_set_error('company_code_postal_'.$i, t('Le code postal est obligatoire'));
    }
    if (!$form_state['values']['company_telephone_'.$i]) {
      form_set_error('company_telephone_'.$i, t('Le champ téléphone est obligatoire'));
    }
    if (!$form_state['values']['code_naf_'.$i]) {
      form_set_error('code_naf_'.$i, t('Le code naf est obligatoire'));
    }
  }
}
