<?php

/**
 *  Envoie des données à modifier
 *  @param: $form , &$form_state
 *  @
 * 
 */
function dgf_administration_update_users_form_submit($form, &$form_state) {
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
  $id_user = $user->uid; 

  // Sauvegarde le rôle
  // user_role_save($r);
  $r = new stdClass;
  $r->rid = $roles;
  
  save_user_infos($gender, $name, $email, $phone, $fonction, $id_user); // On met à jour les infos de l'utilisateur 
   
  // save_user_habilitations($habilitations, $id_user);        
  shared_save_user_habilitations($habilitations, $id_user); // Puis on sauvegarde les habilitations 
       
  // Message de confirmation
  drupal_set_message(t("La modification de compte à bien été pris en compte"));
}

/**
 *  Supprime un utilisateur de la base
 * 
 *  SPECS: Cet écran permet de supprimer un utilisateur de manière logique. 
 *  Son compte est bloqué et il ne pourra plus se connecter à l’extranet.
 *  
 */
function dgf_administration_delete_user($form, &$form_state) {
    
  db_set_active(@DB_EXTRANET);
  
  $mail = $form_state['values']['email'];
  
  $sql_del = db_delete('drupal_user')
            ->condition('mail', $mail, '=')
            ->execute();
                  
  db_set_active();
  
  // On bloque son compte
  $id = $_GET['user_id'];
  
  $upd_users = db_update('users')
               ->fields(array('status' => 0))
               ->condition('uid', $id , '=')
               ->execute();
   
  $form_state['redirect'] = "<front>";       
                  
 }