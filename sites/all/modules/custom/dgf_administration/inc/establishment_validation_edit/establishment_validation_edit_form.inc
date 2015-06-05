<?php

// require_once 'establishment_validation_edit_db.inc';

function opcaim_require_once() {
  require_once 'establishment_validation_edit_const.inc';
  require_once 'establishment_validation_edit_validate.inc';
  require_once 'establishment_validation_edit_db.inc';
//   require_once 'establishment_validation_edit_submit.inc';
}




function opcaim_establishment_validation_edit_populate_select($table) {
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

function _opcaim_establishment_validation_edit_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_validation_edit/js/establishment_validation_edit.js' );
  drupal_add_css(drupal_get_path('module', 'dgf_administration' ) . '/inc/establishment_validation_edit/css/establishment_validation_edit.css' );
}

function opcaim_establishment_validation_edit_form($form, &$form_state) {
  opcaim_require_once();
  $id = arg(3);
  $datas = get_data_for_establishment_validation($id);
//   $infos = get_info_for_establishment_validation($datas[0]->siret);
  // On sauve ces données pour les utiliser lors de la procédure stockée
//   var_dump($datas); die;
  $form_state['storage']['id'] = $id;
//   $form_state['storage']['id_contact'] = $datas[0]->c_id;
  $form_state['storage']['id_address'] = $datas[0]->a_id;

  _opcaim_establishment_validation_edit_include_js_css();

  $form['is_modif'] = array(
      '#type' => 'hidden',
      '#default_value' => (@$infos[0]->siret) ? $infos[0]->siret : NULL,
      '#title' => t('Id demande' )
  );

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

//   $options = get_all_adefim();
//   $default = get_entreprise_adefim($id);
//   $form['top_content']['adefim'] = array(
//       '#type' => 'select',
//       '#title' => t('ADEFIM de gestion'),
//       '#default_value' => $default,
//       '#options' => ($options) ? $options : 'Veuillez choisir une ADEFIM',
// //       '#options' => get_all_adefim(),
//       '#attributes' => array(
//           'class' => array('col-md-4')
//       ),
//   );

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
//       '#description' => (@$infos[0]->siret) ? rtrim($infos[0]->siret) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['street_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Numéro de rue'),
      '#default_value' => rtrim($datas[0]->numero_de_rue),
//       '#description' => (@$infos[0]->numero_de_rue) ? rtrim($infos[0]->numero_de_rue) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['adress_complement'] = array(
      '#type' => 'textfield',
      '#title' => t('Complément d\'adresse'),
      '#default_value' => rtrim($datas[0]->complement_de_rue),
//       '#description' => (@$infos[0]->complement_de_rue) ? rtrim($infos[0]->complement_de_rue) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['left']['city'] = array(
      '#type' => 'textfield',
      '#title' => t('Ville'),
      '#default_value' => rtrim($datas[0]->ville),
//       '#description' => (@$infos[0]->ville) ? rtrim($infos[0]->ville) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  if (!isset($_SESSION['referentiel_extranet_datas']['nafs']) || empty($_SESSION['referentiel_extranet_datas']['nafs'])) {
    $_SESSION['referentiel_extranet_datas']['nafs'] = opcaim_establishment_validation_edit_populate_select('nafs');
  }

  $form['establishement_content']['left']['code_naf'] = array(
      '#type' => 'select',
      '#title' => t('Code NAF'),
      '#default_value' => rtrim($datas[0]->id_naf),
//       '#description' => (@$infos[0]->id_naf) ? rtrim($infos[0]->id_naf) : NULL,
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
//       '#description' => (@$infos[0]->raison_sociale) ? rtrim($infos[0]->raison_sociale) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['street_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom de rue'),
      '#default_value' => rtrim($datas[0]->rue),
//       '#description' => (@$infos[0]->rue) ? rtrim($infos[0]->rue) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['zip_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Code postal'),
      '#default_value' => rtrim($datas[0]->code_postal),
//       '#description' => (@$infos[0]->code_postal) ? rtrim($infos[0]->code_postal) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['establishement_content']['right']['phone_number'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#default_value' => rtrim($datas[0]->telephone_principal),
//       '#description' => (@$infos[0]->telephone_principal) ? rtrim($infos[0]->telephone_principal) : NULL,
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  //--------------------
  // Partie responsable
  //--------------------
//   $form['responsible_content'] = array(
//       '#type' => 'fieldset',
//       '#title' => t('Responsable'),
//       '#attributes' => array(
//           'class' => array('col-md-12')
//       ),
//   );

  //----------------------------
  // Partie responsable gauche
  //----------------------------
//   $form['responsible_content']['left'] = array(
//       '#type' => 'container',
//       '#attributes' => array(
//           'class' => array('col-md-6')
//       ),
//   );

//   $form['responsible_content']['left']['title'] = array(
//       '#type' => 'select',
//       '#title' => t('Titre'),
//       '#default_value' => rtrim($datas[0]->id_civilite),
// //       '#description' => (@$infos[0]->id_civilite) ? rtrim($infos[0]->id_civilite) : NULL,
//       '#options' => array('0'=>'Veuillez choisir un titre','Mr.'=>'Mr.','Mme'=>'Mme'), // TODO
//       '#attributes' => array(
//           'class' => array('col-md-10')
//       ),
//   );

//   $form['responsible_content']['left']['firstname'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Prénom'),
//       '#default_value' => rtrim($datas[0]->prenom),
// //       '#description' => (@$infos[0]->prenom) ? rtrim($infos[0]->prenom) : NULL,
//       '#attributes' => array(
//           'class' => array('col-md-10')
//       ),
//   );

//   $form['responsible_content']['left']['email'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Courriel'),
//       '#default_value' => rtrim($datas[0]->email),
// //       '#description' => (@$infos[0]->email) ? rtrim($infos[0]->email) : NULL,
//       '#attributes' => array(
//           'class' => array('col-md-10')
//       ),
//   );
  //----------------------------
  // Partie responsable droite
  //----------------------------
//   $form['responsible_content']['right'] = array(
//       '#type' => 'container',
//       '#attributes' => array(
//           'class' => array('col-md-6')
//       ),
//   );

//   $form['responsible_content']['right']['lastname'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Nom'),
//       '#default_value' => rtrim($datas[0]->nom),
// //       '#description' => (@$infos[0]->nom) ? rtrim($infos[0]->nom) : NULL,
//       '#attributes' => array(
//           'class' => array('col-md-10')
//       ),
//   );

//   $form['responsible_content']['right']['function'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Fonction'),
//       '#default_value' => rtrim($datas[0]->libelle),
// //       '#description' => (@$infos[0]->libelle) ? rtrim($infos[0]->libelle) : NULL,
//       '#attributes' => array(
//           'class' => array('col-md-10')
//       ),
//   );

//   $form['button_content'] = array(
//       '#type' => 'container',
//       '#attributes' => array(
//           'class' => array('col-md-10 col-md-offset-2')
//       ),
//   );

  //----------------------------
  // Partie boutons
  //----------------------------
  $form['button_content']['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<input class="col-md-3 form-submit" type="button" id="edit-cancel" name="op" value="Annuler">',
  );

  $form['button_content']['refuse'] = array(
      '#type' => 'submit',
      '#value' => t('Refuser la création'),
      '#attributes' => array(
          'class' => array('col-md-3'),
      ),
      '#validate' => array(
          'opcaim_establishment_validation_edit_standard_validate',
          'opcaim_establishment_validation_edit_specific_validate',
      ),
      '#submit' => array('get_stored_proc_refuse_establishment_submit'),
  );

  $form['button_content']['valid'] = array(
      '#type' => 'submit',
      '#value' => t('Valider la création'),
      '#attributes' => array(
          'class' => array('col-md-3'),
      ),
      '#validate' => array(
          'opcaim_establishment_validation_edit_standard_validate',
          'opcaim_establishment_validation_edit_specific_validate',
      ),
      '#submit' => array('get_stored_proc_valid_establishment_submit'),
  );

  return $form;
}