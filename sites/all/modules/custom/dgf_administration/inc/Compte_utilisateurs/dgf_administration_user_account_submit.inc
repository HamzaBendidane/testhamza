<?php

/**
 *  Submit du formulaire
 *  @param: $form - &$form_state.
 * 
 * 
 */
function dgf_administration_user_account_form_submit($form, &$form_state) {
  global $user; 
  
  // Nouvelles données
  $gender  = $form_state['values']['gender'];
  $name    = $form_state['values']['nom'];
  $surname = $form_state['values']['prenom'];
  $mail    = $form_state['values']['email'];
  $phone   = $form_state['values']['phone'];
  $pass    = $form_state['values']['passconfirm'];
  
  if(!empty($pass)){
    // Sauvegarde en base - Mapping des données 
    $data = array(
              'civilite' => $gender,
              'name' => $name,
              'password' => $pass, 
              'mail' => $mail,
              'telephone' =>$phone,
              'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
              'id_user_creation' => $user->uid,
              'is_delete' => 0,
              'id_user_drupal' => $user->uid,
    );
  }
  else{
     $data = array(
              'civilite' => $gender,
              'name' => $name,
              'mail' => $mail,
              'telephone' =>$phone,
              'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
              'id_user_creation' => $user->uid,
              'is_delete' => 0,
              'id_user_drupal' => $user->uid,
    );
  }
  
  $id_drupal_user = shared_get_drupal_user_id($user->uid);
  
  // Met à jour les données en base 
  dgf_administration_update_user_infos($data, $id_drupal_user);
  
  // Sauvegarde les habilitations
  // shared_save_user_habilitations($habilitations, $id_drupal_user);
  
  drupal_set_message("Mise à jour des infos avec succès");
}

