<?php

// MODIFICATION D'UN UTILISATEUR
/**
 * Require functions
 *
 */
function _dgf_administration_require() {
  require_once 'dgf_administration_update_form_submit.inc';
  require_once 'models/dgf_administration_user_update_db.inc';
}

/**
 *   ADD JS & CSS
 */
function _dgf_administration_users_details_add_css_js() {
  $path  = drupal_get_path('module', 'dgf_administration'); // Module PATH
  drupal_add_js($path . '/assets/js/admin_user_details.js'); // ADMIN JS
  // drupal_add_css($path . '/assets/css/admin.css');  // CSS
}

/*  Formulaire de gestion des
 *  utilisateurs OPCAIM
 *
 *
 */
function dgf_administration_update_users_form($form, &$form_state) {
	// Include
	_dgf_administration_require();
  _dgf_administration_users_details_add_css_js();

  $TitreOptions = array( 'Mr'  => t('Mr'), 'Mme' => t('Mme'),  'Melle' => t('Melle'));

    // $user_roles = $user->roles; // Roles utilisateurs
  $user_id  = $_GET['user_id']; // Id user à modifier

  $infos = shared_users_verify_get_infos($user_id);

  // Get  user infos
  if (isset($infos)) {
      foreach ($infos as $user_infos) {
        $civilite = $user_infos->civilite;
        $name = $user_infos->name;
        $user_mail = $user_infos->mail;
        $user_fonction = $user_infos->fonction;
        $user_phone = $user_infos->telephone;
    }
  }

  // Titre
  $form['user']['gender'] = array(
    '#type' => 'select',
    '#title' => t('Titre: '),
    '#options' => $TitreOptions,
    '#required' => true,
    '#default_value'  => empty($civilite) ? 'Mr' : $civilite,
  );


  // Raison sociale obligatoire
  $form['user']['nom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Nom: '),
    '#required' =>  TRUE,
    '#default_value'  => empty($name) ? '' : $name,
  );

  // Adresse obligatoire
  $form['user']['prenom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Prénom: '),
    '#required' =>  TRUE,
    //'#default_value'  => empty($surname) ? '' : $surname,
  );

  // Adresse obligatoire
  $form['user']['email'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Email'),
    '#required' =>  TRUE,
    '#default_value'  => empty($user_mail) ? '' : $user_mail,
  );

  // Adresse obligatoire
  $form['user']['fonction'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Fonction'),
    '#required' =>  TRUE,
    '#default_value'  => empty($user_fonction) ? '' : $user_fonction,
  );


  // Téléphone
  $form['user']['phone'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Téléphone'),
    '#required' =>  TRUE,
    '#default_value'  => empty($user_phone) ? '' : $user_phone,
  );

  // Charges la Liste des rôles
  $Roles = user_roles();

  // On enlève les rôles indésirés.
  unset($Roles[1], $Roles[2], $Roles[3] , $Roles[4], $Roles[5]);

  // Inputs des roles
  $form['user']['roles'] = array(
    '#type'     => 'select',
    '#title'    => t('Profil:'),
    '#options'  => $Roles,
	  '#required' =>  TRUE,
  );

  // Fonctionnalités de l'utilisateur
  // Habilitations
  $form['user']['habilitations'] = array(
    '#type'     => 'checkboxes',
    '#title'    => t('Fonctionnalités'),
    '#options'  => shared_get_habilitation(),
	  '#required' =>  TRUE,
  );

  $cancel_button = "<button type='reset' class='btn btn-danger'>ANNULER</button>";

  // Annuler
  $form['supprimer'] = array(
    '#type'    => 'markup',
    '#markup' => $cancel_button,
  );

 //  Supprimer
 $form['delete'] = array(
    '#type'    => 'submit',
    '#value'   => t('SUPPRIMER'),
    '#submit'  => array('dgf_administration_delete_user'),
    '#attributes' => array(
    'class' => array('btn btn-success'),
  ),
  );

 //  Modifier
 $form['update'] = array(
    '#type'    => 'submit',
    '#value'   => t('MODIFIER'),
    '#submit'  => array('dgf_administration_update_users_form_submit'),
    '#attributes' => array(
    'class' => array('btn btn-success'),
  ),
  );

  return $form;
}
