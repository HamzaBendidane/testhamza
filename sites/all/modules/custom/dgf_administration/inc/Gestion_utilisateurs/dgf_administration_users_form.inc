<?php

// Fichiers submit et models DB
require_once 'models/dgf_administration_users_form_models.inc';
require_once 'dgf_administration_users_form_submit.inc';

/**
 * Form Submit Inc
 * @param $form, &$form_state
 *
 *
 */
function _dgf_administration_users_add_css_js() {
  $path  = drupal_get_path('module', 'dgf_administration'); // Module PATH
  drupal_add_js($path . '/assets/js/admin_user_account.js'); // ADMIN JS
  drupal_add_css($path . '/assets/css/admin.css');  // CSS
}

/**
 * Formulaire de gestion du compte Utilisateurs OPCAIM
 *
 * @param $form , &$form_state
 *
 * @return $form
 *
 */
function dgf_administration_users_form($form, &$form_state) {

  _dgf_administration_users_add_css_js(); // LOAD JS & CSS

  $form['rechercher'] = array(
    '#type' => 'fieldset',
    '#title' => ('Rechercher'),
  );

  // Numéro de demande
  $form['rechercher']['num_demande'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Numéro de demande de création de compte: '),
  );

  // Nom
  $form['rechercher']['nom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Nom'),
  );

  // Prénom
  $form['rechercher']['prenom'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Prénom'),
  );

  // Email
  $form['rechercher']['email'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Adresse email'),
  );

  // Numéro de siret
  $form['rechercher']['siret'] = array(
    '#type'     => 'textfield',
    '#title'    => t('N° siret'),
  );

  // OPtions pour les entreprises validés.
  $opts = array('Tous', 'Non', 'Oui');

  // Numéro de siret
  $form['rechercher']['valide'] = array(
    '#type'     => 'select',
    '#title'    => t('validé ?'),
    '#options'  => $opts,
  );

  $form['rechercher']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Rechercher'),
    '#submit' => array('dgf_administration_users_search_result'),
    '#attributes' => array(
	    'class' => array('btn btn-success'),
	   ),
  );

  $form['rechercher']['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<button type="reset" class="btn btn-danger">Réinitialiser</button>',
  );

  // Chargement AJAX Spinner
  $form['loading'] = array(
   '#type' => 'markup',
     // Données à afficher
   '#prefix' => '<div id="loading">',
   '#suffix' => '</div>',
  );
  // Espace d'affichage des résultats
  $form['resultats'] = array(
   '#type' => 'markup',
     // Données à afficher
   '#prefix' => '<div id="resultats">',
   '#suffix' => '</div>',
  );
 dgf_administration_users_get_ids();
 return $form; // or return system_settings_form($form);
}

/**
 * Redirection vers la création d'un utilisateur
 * 
 */
function dgf_administration_users_form_create_submit($form, &$form_state) {
  $form_state['redirect'] = "/creer/utilisateur";    
}

/**
 *  SERVICE AJAX DE RECHERCHE
 *  @param:
 *  $num_demande : Numéro de demande
 *  $name :  nom ...
 *
 *
 */
function ajax_gestion_search() {
  // On récuppère les données de la base
  $db_response_data  = dgf_administration_users_query();
  
  dgf_administration_users_display_data($db_response_data); // Affiche les résultats de la recherche
   
  //dgf_administration_users_tabler($db_response_data); TODO Tester la version tableau
}

/**
 *  SERVICE AJAX AFFICHAGE DE TOUS LES UTILISATEURS
 *
 */
function ajax_gestion_users(){
  // On récuppère les données de la base
  $data  = dgf_administration_users_query_all();

  // Affiche les résultats de la recherche
  dgf_administration_users_display_data($data);
}

/**
 * Implementation du Hook _theme()
 *
 *
 */
function dgf_administration_users_theme($existing, $type, $theme, $path){
  $render = array(
        'display' => array(
            'template' => 'dgf_administration_users',
            'path' => $path . '/theme',
            'type' => 'theme',
            'variables' => array(
                'title' => 'lol',
            ),
        ),
    );
    return  $render;
}