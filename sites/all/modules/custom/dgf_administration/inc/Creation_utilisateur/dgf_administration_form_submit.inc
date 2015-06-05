<?php

/**
 *  Envoie des données à modifier
 *  @param: $form , &$form_state
 * 
 */
function dgf_administration_form_submit($form, &$form_state) {
  global $user;
  
  // USER INFOS
  $gender   = $form_state['values']['gender'];
  $name     = $form_state['values']['nom'];
  $surname  = $form_state['values']['prenom'];
  $email    = $form_state['values']['email'];
  $phone    = $form_state['values']['phone'];
  $fonction = $form_state['values']['fonction'];
  $roles    = $form_state['values']['roles'];
  $habilitations =  $form_state['values']['habilitations']; 

  // ETABLISSEMENT
  $siret           = $form_state['values']['siret'];
  $raison_sociale  = $form_state['values']['raison_sociale'];
  $num_rue         = $form_state['values']['num_rue'];
  $rue             = $form_state['values']['rue'];
  $complt_rue      = $form_state['values']['complt_rue'];
  $ville           = $form_state['values']['ville'];
  $code_postal     = $form_state['values']['code_postal'];
  $tel             = $form_state['values']['tel'];
  $code_naf        = $form_state['values']['code_naf'];
 
  $id_user =  $user->uid; // Drupal User
  $id_entreprise = shared_get_user_id_entreprise($id_user);
  
  if($id_entreprise != NULL) {
    $id_tbl_entreprise = "'" . $id_entreprise . "'"; // Si l'entreprise existe
  }
  else{
    $id_tbl_entreprise = 'null';  // Cas d'une nouvelle entreprise
  }
  if (empty($tel) || $tel == NULL) {
    $tel = 'NULL';
  }

  if (!empty($siret)) {
   save_company_infos($id_user, $id_tbl_entreprise, $raison_sociale, $siret, $code_naf, $tel);
   save_company_adress_infos($id_user, $num_rue, $rue, $complt_rue, $code_postal, $ville, $id_tbl_entreprise);
  }
  save_user_infos($gender, $name, $email, $phone, $fonction, $id_user); // On met à jour les infos de l'utilisateur 
  save_user_habilitations($habilitations, $id_user);  // Puis on sauvegarde les habilitations  
     
  drupal_set_message(t("La création de compte à bien été pris en compte"));
};

  // $r = new stdClass;
  // $r->rid = $roles;
  //   
  // // Sauvegarde le rôle
  // // user_role_save($r);
  //   
  // // Message de confirmation
  // 
