<?php

/**
 *   Enregistrement des données utilisateurs Bouton Valider
 *
 */
function dgf_administration_users_verify_submit($form, &$form_state) {
  global $user;

  $data  = $form_state['values'];  // Données à insérer en base
  $email = $form_state['values']['user_email']; //Email de l'utilisateur
  $nb_siret = $form_state['values']['nb_siret'];
  $id_drupal_user = arg(3);

  dgf_administration_users_verify_save_infos($data, $id_drupal_user);  // Insertion en base
  for ($i = 0; $i < $nb_siret; $i++) {
    $status_rattachement = $form_state['values']['rattachement_'.$i];
    $id_etablissement = $form_state['values']['id_establishment_'.$i];
    // status 0 : en attent / status 1 : valide / status 2 : refuse
    if ($status_rattachement == 1) {
      dgf_validation_utilisateur_db_update_lien_rattachement($id_drupal_user, $id_etablissement);
    } else if ($status_rattachement == 2) {
      dgf_validation_utilisateur_db_update_lien_rattachement($id_drupal_user, $id_etablissement, false);
    }
  }

  // Envoie du mail
  $to = $email;
  $from = 'no-reply@opcaim.com';

  $params = array(
    'body' => t("Vous venez de recevoir un mail d'activation de compte"),
    'subject' =>t("Création d'un compte entreprise"),
  );

  if (drupal_mail('dgf_administration', 'envoi_email', $to, language_default(), $params, $from, TRUE)) {
    drupal_set_message("Un email à été envoyé à " . $email);
    drupal_set_message(t("Validation de l'utilisateur avec succès"));
    drupal_goto("gestion/utilisateurs");
  }
  else {
    drupal_set_message("Une erreur s'est produite lors de l'envoi de votre email");
  }
}

/**
 *   Action Bouton Refuser
 *
 */
function dgf_administration_users_verify_refuse_submit($form, &$form_state) {

  $id_drupal_user = arg(3);
  $id_user_entreprise = shared_get_user_id_entreprise($id_drupal_user);

  $email = $_SESSION['email']; // Email de l'utilisateur
  $from = 'no-reply@opcaim.com';
  dgf_administration_delete_user($id_drupal_user); // Suppression de l'utilisateur

  // Envoie email
  $params = array(
    'body' => t("Demande de suppréssion de compte"),
    'subject' =>t("Suppréssion de compte entreprise"),
  );

  if (drupal_mail('dgf_administration', 'envoi_email', $email, language_default(), $params, $from, TRUE)) {
    drupal_set_message("Un email à été envoyé à " . $email);
    drupal_goto("gestion/utilisateurs");
  }
  // $form_state['redirect'] = "<front>"; // Redirection
}