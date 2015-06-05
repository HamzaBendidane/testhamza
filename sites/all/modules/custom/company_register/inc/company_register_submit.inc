<?php

function company_register_information_form_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-suivant') {
    $form_state['storage']['display_confirmation'] = TRUE;
    $form_state['storage']['information_data'] = $form_state['values'];
    $form_state["rebuild"] = TRUE;   // Added
  }
}

/**
 *  Page suivante formulaire de création
 *  Passage page suivante
 *  @see company_register_chart_submit()
 *
 *  @param  $form
 *  @param  &$form_state
 *  @return $form
 *
 */
function company_register_charte_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-accepte') {
    if (isset($_SESSION['id_user_entreprise'])) {
      company_register_db_update_user_entreprise();
      unset($_SESSION['id_user_entreprise']);
    }
  }
  drupal_goto('/login');
}

/**
 * Formulaires d'enregistrement des entreprises
 *
 */
function company_register_confirmation_form_submit($form, &$form_state){
  $data_information = $form_state['storage']['information_data'];
  $data_confirmation = $form_state['values'];

  $numero_demande  = company_register_get_numero_demande() + 1;
  $signature   = $data_confirmation['utilisateur_signature'];
  $nb_siret    = $data_information['nb_siret'];

  //___________________ Sauvegardde des entreprises et utilisateurs ________________________ //
  // On sauvegarde le user dans la table users de drupal en bloqué
  $new_user = array(
      'name' => $data_information['utilisateur_email'],
      'pass' => $data_information['utilisateur_password'],
      'mail' => $data_information['utilisateur_email'],
      'init' => $data_information['utilisateur_email'],
      'status' => 0,
      'access' => REQUEST_TIME,
      'roles' => array('7' => 'COLLABORATEUR ENTREPRISE'),
  );
  // $account returns user object
  $account = user_save(null, $new_user);
  $id_drupal_user = $account->uid;

  // On sauvegarde le ou les établissements
  $id_entreprises = company_register_db_save_company_infos($data_information, $data_confirmation, $nb_siret);
  // On sauvegarde le ou les adresses des établissements
  company_register_db_save_company_adresses($data_information, $nb_siret);
  // On sauvegarde le responsable entreprise
  $id_user_responsable = company_register_db_save_user_responsable($data_information);
  // On sauvegarde le drupal_user de la BDD extranet avec $id_drupal_user
  $id_extranet_drupal_user = company_register_db_save_extranet_drupal_user($data_information, $id_drupal_user); // company_register_save_user_entreprise($data);
  // On sauvegarde le user_entreprise avec $id_extranet_drupal_user
  $id_user_entreprise = company_register_db_save_user_entreprise($numero_demande, $signature, $id_extranet_drupal_user, $id_user_responsable);
  // save habilitation et entreprises liés aux utilisateurs
  company_register_db_save_user_habilitations($data_information, $id_extranet_drupal_user, $id_user_entreprise, $nb_siret);

  $_SESSION['id_user_entreprise'] = $id_user_entreprise;

  // ____________________________  Envoie du mail à l'utilisateur _________________________ //

  $user_email = $data_information['utilisateur_email'];  // Utilisateur Mail
  $to = $user_email;
  $from = 'no-reply@opcaim.com';

  // Données à envoyer par mail
  $Civilité_Utilisateur = $data_information['utilisateur_titre'];
  $Prenom_utilisateur = $data_information['utilisateur_prenom'];
  $Nom_utilisateur = $data_information['utilisateur_nom'];
  //$Droits_utilisateur = $data['UtilisateurNom']; TODO : Prendre les bonnes valeurs

  // Message pour l'utilisateur
  $message_utilisateur =  $Civilité_Utilisateur.' '.$Prenom_utilisateur.'  '.$Nom_utilisateur.' '.",
                          Nous avons bien reçu votre demande d’ouverture de compte pour accéder à votre espace Extranet OPCAIM.
                          Votre demande sera étudiée dans les plus brefs délais, après validation par l’ADEFIM ou les ADEFIM, vous serez informé de la validation de votre compte par mail. Vous pourrez alors vous connecter avec votre adresse mail (identifiant) et le mot de passe saisi dans cette demande.
                          Votre demande porte le numéro :" .$numero_demande. "
                          Titulaire :".$Civilité_Utilisateur.' '.$Prenom_utilisateur.'  '.$Nom_utilisateur.' '."
                          Cordialement";

  // Message pour Responsable entreprise
  $civilite_resp = $data_information['responsable_titre'];
  $prenom_resp =   $data_information['responsable_prenom'];
  $nom_resp =      $data_information['responsable_nom'];

  $message_responsable = $civilite_resp .'  '. $prenom_resp .' '.$nom_resp. ",Nous avons reçu une demande d’ouverture de compte pour accéder à l’espace Extranet OPCAIM, formulée par votre collaborateur".
                         $Civilité_Utilisateur . ' '. $Prenom_utilisateur . ' '.$Nom_utilisateur. "et permettant d’accéder aux fonctionnalités suvantes :
                         Saisir une demande « Action de formation et toutes actions FPC
                         Saisir une demande « Contrat de professionnalisation »".
                         $Civilité_Utilisateur . ' '. $Prenom_utilisateur . ' '.$Nom_utilisateur." recevra très prochainement ses identifiants de connexion.
                         Considérant le caractère confidentiel des informations auxquelles il accédera, nous lui demanderons de prendre les précautions d’usage
                         en ne communiquant à quiconque son mot de passe et en conservant ce courrier en lieu sûr. En cas de départ ou de changement de fonction au sein de la société,
                         merci de nous tenir informés afin que nous modifions ou supprimions les droits d’accès.
                         Cordialement.
                         ";
  // INFOS ADEFIM TODO
  $Civilité_adefim_ref ='';
  $Prenom_adefim_ref ='';
  $Nom_adefim_ref = '';
  $Liste_etablissements ='';

  // Message ADEFIM
  $message_adefim = $Civilité_adefim_ref. '  '. $Prenom_adefim_ref.'  '.$Nom_adefim_ref."La demande de création de compte vous a été adressée ".$numero_demande."
                    concernant la création du compte de".
                    $civilite_resp .'  '. $prenom_resp .' '.$nom_resp."
                    pour l’établissement ". $Liste_etablissements." Cordialement";


  $param_utilisateur = array(
    'body' => t($message_utilisateur),
    'subject' =>t("Création d'un compte entreprise"),
  );

  $param_responsable = array(
    'body' => t($message_responsable),
    'subject' =>t("Demande de création d'un compte entreprise"),
  );

  $param_adefim = array(
    'body' => t($message_adefim),
    'subject' =>t("Demande de création d'un compte entreprise"),
  );


  if (drupal_mail('dgf_administration', 'envoi_email', $to, language_default(), $param_utilisateur, $from, TRUE)) {
    drupal_set_message("Un email à été envoyé à " . $user_email);
    drupal_set_message(t("Validation de l'utilisateur avec succès"));

    $to_resp =  $data_information['responsable_email']; // Envoie du mail pour le responsable entreprise
    drupal_mail('dgf_administration', 'envoi_email', $to_resp, language_default(), $param_responsable, $from, TRUE);

    // TODO : mail à l'ADEFIM
//     $to_adefim = $data_information['responsable_email']; // Envoie du mail ADEFIM TODO EMAIL ADEFIM
//     drupal_mail('dgf_administration', 'envoi_email', $to_adefim, language_default(), $param_adefim, $from, TRUE);

    drupal_goto("nouvelle/entreprise/charte"); // REDIRECTION CHARTE
  }
  else {
    drupal_set_message("Une erreur s'est produite lors de l'envoi de votre email");
  }

  // REDIRIGE VERS LA PAGE Charte
  $form_state['redirect'] = 'nouvelle/entreprise/charte';
}


function dgf_administration_company_send_mail($module, $type, $to, $lang, $params, $from, $true){

  drupal_mail();

}
