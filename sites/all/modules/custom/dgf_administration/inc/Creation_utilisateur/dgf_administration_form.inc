<?php

/**
 * Require functions
 *
 */
function _dgf_administration_require() {
  require_once 'dgf_administration_form_submit.inc';
  require_once 'dgf_administration_form_langs.inc';
  require_once 'models/dgf_administration_user_create_db.inc';
}

/**
 *   ADD JS & CSS
 */
function _dgf_administration_users_details_add_css_js() {
  $path  = drupal_get_path('module', 'dgf_administration'); // Module PATH
  drupal_add_js($path . '/assets/js/creation_utilisateur.js'); // ADMIN JS
  // drupal_add_css($path . '/assets/css/admin.css');  // CSS
}

/*  Formulaire de gestion des
 *  utilisateurs OPCAIM
 *
 *
 */
function dgf_administration_form($form, &$form_state) {
	// Include
	_dgf_administration_require();
  _dgf_administration_users_details_add_css_js();

  $TitreOptions = array( 'Mr'  => t('Mr'), 'Mme' => t('Mme'),  'Melle' => t('Melle'));

  $form['user']['title'] = array(
    '#type' => 'item',
    '#title' => t('<h4>CREER UN UTILISATEUR</h4>'),
  );

  // Titre
  $form['user']['gender'] = array(
    '#type' => 'select',
    '#title' => t('Titre: '),
    '#options' => $TitreOptions,
    '#required' => true,
  );

  // Raison sociale obligatoire
  $form['user']['nom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Nom: '),
    '#required' =>  TRUE,
  );

  // Adresse obligatoire
  $form['user']['prenom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Prénom: '),
    '#required' =>  TRUE,
  );

  // Adresse obligatoire
  $form['user']['email'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Email'),
    '#required' =>  TRUE,
  );

  // Adresse obligatoire
  $form['user']['fonction'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Fonction'),
    '#required' =>  TRUE,
  );


  // Téléphone
  $form['user']['phone'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Téléphone'),
    '#required' =>  TRUE,
  );

  // Inputs des roles
  $form['user']['roles'] = array(
    '#type'     => 'select',
    '#title'    => t('Profil:'),
    '#options'  => array('COLLABORATEUR ENTREPRISE'),
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

 //  Sauvegarde des données.
 $form['rattacher'] = array(
    '#type'    => 'button',
    '#value'   => t(@RATTACHER_SIRET),
    '#attributes' => array(
    'class' => array('btn btn-success'),
    ),
    '#prefix' => '<h4>MES ETABLISSEMENTS</h4>',
    '#suffix' => '<br><br>',
 );

 // Nouvel établissement
 $form['new']['siret'] = array(
   '#type' => 'textfield',
   '#title' => t('N° Siret'),
   '#prefix' => '<div id="add_company">',
 );
 $form['new']['raison_sociale'] = array(
   '#type' => 'textfield',
   '#title' => t('Raison sociale'),
 );
 $form['new']['num_rue'] = array(
   '#type' => 'textfield',
   '#title' => t('N° Rue'),
 );
 $form['new']['rue'] = array(
   '#type' => 'textfield',
   '#title' => t('Rue'),
 );
 $form['new']['complt_rue'] = array(
   '#type' => 'textfield',
   '#title' => t('Complément de rue'),
 );
 $form['new']['ville'] = array(
   '#type' => 'textfield',
   '#title' => t('Ville'),
 );
  $form['new']['code_postal'] = array(
   '#type' => 'textfield',
   '#title' => t('Code postal'),
 );
  $form['new']['tel'] = array(
   '#type' => 'textfield',
   '#title' => t('téléphone'),
 );
  $form['new']['code_naf'] = array(
   '#type' => 'textfield',
   '#title' => t('Code NAF'),
   '#suffix' => '</div>'
 );

 $cancel_button = "<button type='reset' class='btn btn-danger'>Annuler</button>";

 $form['supprimer'] = array(
    '#type'    => 'markup',
    '#markup' => $cancel_button,
  );

 //  Sauvegarde des données.
 $form['enregistrer'] = array(
    '#type'    => 'submit',
    '#value'   => t('CREER'),
    '#submit'  => array('dgf_administration_form_submit'),
    '#attributes' => array(
	  'class' => array('btn btn-success'),
	),
  );

  return $form;
}
