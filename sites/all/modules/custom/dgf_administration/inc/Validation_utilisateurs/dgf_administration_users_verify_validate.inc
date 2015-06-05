<?php

/**
 *   Validation des champs utilisateurs
 *   @param: $form , &$form_state
 *
 */
function dgf_administration_users_verify_form_validate($form , &$form_state) {

  // Validation des champs
  $civilite = $form_state['values']['user_gender'];
  $user_name = $form_state['values']['user_name'];
  $user_surname = $form_state['values']['user_surname'];
  $user_email = $form_state['values']['user_email'];
  $user_fonction = $form_state['values']['user_fonction'];
  $user_phone = $form_state['values']['user_phone'];
  $user_habilitations = $form_state['values']['habilitations'];


//   $mail_to_check = user_load_by_mail($user_email);

  if(empty($civilite)){
    form_set_error('user_gender', t('Le champ civilité est obligatoire'));
  }
  if(empty($user_name)){
    form_set_error('user_name', t('Le champ nom est obligatoire'));
  }
  if(empty($user_surname)){
    form_set_error('user_surname', t('Le champ prénom est obligatoire'));
  }
  if(empty($user_email)){
    form_set_error('user_email', t('Le champ email est obligatoire'));
  }
//   if($mail_to_check){
//     form_set_error('user_email', t('Un compte existe déjà pour cette adresse mail, il n’est pas possible d’en créer un autre.'));
//   }
  if(empty($user_fonction)){
    form_set_error('user_fonction', t('Le champ fonction  est obligatoire'));
  }
  if(empty($user_phone)){
    form_set_error('user_phone', t('Le champ téléphone est obligatoire'));
  }
  if(empty($user_habilitations)){
    form_set_error('habilitations', t('Un droit au moins doit être sélectionné.'));
  }
}
