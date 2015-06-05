<?php

/**
 *  Fichiers submit & DB
 * 
 */
require_once 'models/dgf_administration_user_account_db.inc';
require_once 'dgf_administration_user_account_submit.inc';

// Chargement des fonctions utilisés dans validation
module_load_include('inc', 'dgf_administration', 'inc/Validation_utilisateurs/dgf_administration_users_verify_form');

/**
*   Rajout du JS 
* 
* 
*/
function _dgf_administration_user_account_add_js(){
  $path  = drupal_get_path('module', 'dgf_administration'); // Module PATH   
  drupal_add_js($path . '/assets/js/admin_user_details.js'); // ADMIN JS
  // drupal_add_css($path . '/assets/css/admin.css');  // CSS  
}

/*  Formulaire de gestion du compte Utilisateurs
 *  OPCAIM
 * 
 */
function dgf_administration_user_account_form($form, &$form_state) {
  _dgf_administration_user_account_add_js();
  
  global $user;
  
   $form['user']['moncompte'] = array(
    '#type' => 'markup', 
    '#markup' => '<h4>MON COMPTE</h4>',
  );
  // Raison sociale obligatoire
  $form['user']['gender'] = array(
    '#type'     => 'select',
    '#title'    => t('Titre'),
    '#options'    =>array(
    '0' => 'Mr',  '1' => 'Mme', '2' => 'Melle'
    ),
    '#required' =>  TRUE,
  );	
  // Raison sociale obligatoire
  $form['user']['nom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Nom'),
    '#required' =>  TRUE,
  );

  // Adresse obligatoire
  $form['user']['prenom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Prénom'),
    '#required' =>  TRUE,
  );

  // Adresse obligatoire
  $form['user']['email'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Email'),
    '#required' =>  TRUE,
  );	
  
  // Téléphone
  $form['user']['phone'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Téléphone'),
    '#default_value' =>  '',
    '#required' =>  TRUE,
  );
  $form['user']['passlabel'] = array(
    '#type' => 'markup', 
    '#markup' => '<h4>MODIFIER MON DE PASSE</h4>',
  );
  
  $form['user']['passconfirm'] = array(
    '#type' => 'password_confirm',
    '#title' => t('<b>Laisser vide pour ne pas moidifer</b>'),
    '#size' => 25,
  );
   
// $Roles = user_roles(); // Charges la Liste des rôles
//     
  // // Fonctionnalités de l'utilisateur
  // $Habilitations = array(        
   // '0' => t('Toutes les fonctionnalités'),
   // '1' => t('Suivre / consulter les actions (CP / toutes autres actions)') ,
   // '2' => t('Suivre / consulter les paiements (CP / toutes actions)'),
   // '3' => t('Saisir une demande « Action de formation et toutes actions FPC'),
   // '4' => t('Saisir une demande « Contrat de professionnalisation »'),
   // '5' => t('Gérer les contributions FPC (formation professionnelle continue)'),
   // '6' => t('Gérer les contributions TA (taxe apprentissage)'),
   // '7' => t('Accéder aux reporting'),
  // );
//   
  // // Habilitations
  // $form['user']['habilitations'] = array(
    // '#type'     => 'checkboxes',
    // '#title'    => t('Fonctionnalités'),
    // '#options'  => $Habilitations,
	  // '#required' =>  TRUE,
  // );
   
 $id_user_entreprise = dgf_administration_get_user_id_entreprise($user->uid);
  
 $mes_etablissements = dgf_administration_users_get_users_companies($id_user_entreprise);
  
 $form['user']['etablissement'] = array(
    '#type'    => 'markup',
    '#markup' => $mes_etablissements,
  );
  
 $form['my_companies'] = array(
    '#type' =>  'markup', 
    '#markup' => "<div id='companies-results' class='row'></div>",
  );
  
 $cancel_button = "<button type='reset' class='btn btn-danger'>Annuler</button>";
  
 $form['supprimer'] = array(
    '#type'    => 'markup',
    '#markup' => $cancel_button,
    '#prefix' => "<div class='col-lg-7'>",
    '#suffix' => "</div>",
  );
  $form['update'] = array(
    '#type'    => 'submit',
    '#value'   => t('Modifier'),
    '#submit' => array('dgf_administration_user_account_form_submit'),
    '#attributes' => array( 
	  'class' => array('btn btn-success'),
	  '#prefix' => "<div class='col-lg-offset-5'>",
    '#suffix' => "</div>",
	),
  );

  return $form;
}



