<?php

require_once 'establishement_management_validate.inc';
require_once 'establishment_management_langs.inc';
require_once 'establishment_management_submit.inc';
require_once 'establishment_management_query.inc';


function _opcaim_establishment_management_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_management/js/establishment_management.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_management/css/establishment_management.css' );
}

function opcaim_establishment_management_populate_select($table) {
  $results = array();
  db_set_active('opcaim_referentiel_esclave');
  $results = db_select($table, 't')
    ->fields('t', array('id'))
//     ->condition('est_actif', 1, '=')
//     ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAllAssoc('id', PDO::FETCH_ASSOC);

  $datas = array();
  // On donne la valeur de l'item à la clef 
  // pour pouvoir définir la default value dans les select 
  foreach ($results as $key => $items) {
    $key = rtrim($items['id']);
    $datas[$key] = rtrim($items['id']);
  }
  // ajout de la valeur (nulle) par défaut
  array_unshift($datas, 'Veuillez choisir dans la liste');

  db_set_active();

  return $datas;
}

function opcaim_establishment_management_form($form, &$form_state) {
  $id = arg(4);
  $datas = get_data_for_establishment_management($id);

  _opcaim_establishment_management_include_js_css();
//   shared_get_referentiel_data(array('ref_convention_collective', 'ref_groupe'));
  //----------------------
  // Partie en tête
  //----------------------
  $form['top_content'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-md-12')
      ),
  );

  $type = 'établissement';
  $form['top_content']['type'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="form-item form-type-markup form-item-type col-md-5">
          <label id="label-type">Type d\'établissement</label>
          <span id="text-type">'. $type . '</span>
        </div>',
  );

  // TODO : if type = établissement on affiche adefim
  $form['top_content']['adefim'] = array(
      '#type' => 'select',
      '#title' => t('ADEFIM de gestion'),
      '#options' => array(
          0 => t('Veuillez choisir votre ADEFIM' ),
          1 => t('default' )
      ),
      '#attributes' => array(
          'class' => array('col-md-4')
      ),
  );

  //----------------------
  // Partie établissement
  //----------------------
  $form['establishement_content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Etablissement'),
    '#attributes' => array(
        'class' => array('col-md-12')
    ),
  );

  //----------------------------
  // Partie établissement gauche
  //----------------------------
  $form['establishement_content']['left'] = array(
    '#type' => 'container',
    '#attributes' => array(
        'class' => array('col-md-6')
    ),
  );

  $form['establishement_content']['left']['siret'] = array(
      '#type' => 'textfield',
      '#title' => t('SIRET'),
      '#default_value' => rtrim($datas[0]->siret),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['street_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Numéro de rue'),
      '#default_value' => rtrim($datas[0]->numero_de_rue),
    '#attributes' => array(
        'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['adress_complement'] = array(
      '#type' => 'textfield',
      '#title' => t('Complément d\'adresse'),
      '#default_value' => rtrim($datas[0]->complement_de_rue),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('Ville'),
    '#default_value' => rtrim($datas[0]->ville),
    '#attributes' => array(
        'class' => array('col-md-10')
      ),
  );

  if (!isset($_SESSION['referentiel_extranet_datas']['nafs']) || empty($_SESSION['referentiel_extranet_datas']['nafs'])) {
    $_SESSION['referentiel_extranet_datas']['nafs'] = opcaim_establishment_management_populate_select('nafs');
  }

  $form['establishement_content']['left']['code_naf'] = array(
      '#type' => 'select',
      '#title' => t('Code NAF'),
      '#default_value' => rtrim($datas[0]->id_nace),
      '#options' => $_SESSION['referentiel_extranet_datas']['nafs'],
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  //----------------------------
  // Partie établissement droite
  //----------------------------
  $form['establishement_content']['right'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-md-6')
      ),
  );
  

  $form['establishement_content']['right']['corporate_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Raison sociale'),
      '#default_value' => rtrim($datas[0]->raison_sociale),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['street_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom de rue'),
      '#default_value' => rtrim($datas[0]->rue),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['zip_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code postal'),
      '#default_value' => rtrim($datas[0]->code_postal),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#default_value' => rtrim($datas[0]->telephone_principal),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  if (!isset($_SESSION['referentiel_extranet_datas']['naces']) || empty($_SESSION['referentiel_extranet_datas']['naces'])) {
    $_SESSION['referentiel_extranet_datas']['naces'] = opcaim_establishment_management_populate_select('naces');
  }

  $form['establishement_content']['right']['code_nace'] = array(
      '#type' => 'select',
      '#title' => t('Code NACE'),
      '#default_value' => rtrim($datas[0]->id_nace),
      '#options' => $_SESSION['referentiel_extranet_datas']['naces'],
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  //--------------------
  // Partie responsable 
  //--------------------
  $form['responsible_content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Responsable'),
    '#attributes' => array(
        'class' => array('col-md-12')
    ),
  );

  //----------------------------
  // Partie responsable gauche
  //----------------------------
  $form['responsible_content']['left'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-md-6')
      ),
  );

  $form['responsible_content']['left']['title'] = array(
      '#type' => 'select',
      '#title' => t('Titre'),
//       '#default_value' => rtrim($datas[0]->id_civilite),
      '#options' => array('0'=>'Veuillez choisir un titre','Mr.'=>'Mr.','Mme'=>'Mme'),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['responsible_content']['left']['firstname'] = array(
      '#type' => 'textfield',
      '#title' => t('Prénom'),
//       '#default_value' => rtrim($datas[0]->prenom),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['responsible_content']['left']['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Courriel'),
//       '#default_value' => rtrim($datas[0]->email),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );
  //----------------------------
  // Partie responsable droite
  //----------------------------
  $form['responsible_content']['right'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-md-6')
      ),
  );

  $form['responsible_content']['right']['lastname'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom'),
//       '#default_value' => rtrim($datas[0]->nom),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['responsible_content']['right']['function'] = array(
      '#type' => 'textfield',
      '#title' => t('Fonction'),
//       '#default_value' => rtrim($datas[0]->id_fonction),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['button_content'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-md-10 col-md-offset-2')
      ),
  );

  $form['button_content']['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<input class="col-md-3 form-submit" type="button" id="edit-cancel" name="op" value="Annuler">
          <input class="col-md-3 form-submit" type="button" id="edit-refuse" name="op" value="Refuser la création" data-id="'.$id.'">',
  );

  $form['button_content']['valid'] = array(
      '#type' => 'submit',
      '#value' => t('Valider la création'),
      '#attributes' => array(
          'class' => array('col-md-3'),
          'data-id' => array($id),
      ),
      '#validate' => array(
      	'opcaim_establishment_management_standard_validate',
      	'opcaim_establishment_management_specific_validate',
      ),
//       '#submit' => array(drupal_goto('/gestion/etablissement/list/')),
      '#submit' => 'dgf_contrat_form_submit',
  );

  return $form;
}