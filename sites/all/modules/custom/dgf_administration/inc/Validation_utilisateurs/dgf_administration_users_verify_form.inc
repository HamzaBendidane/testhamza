<?php

// Require files
require_once 'models/dgf_administration_users_verify_db.inc';   // Requêtes
require_once 'dgf_administration_users_verify_validate.inc'; // Validation
require_once 'dgf_administration_users_verify_submit.inc'; // Validation

/**
 *   ADD JS & CSS
 *
 *
 */
function _dgf_administration_users_verify_add_css_js() {
  $path  = drupal_get_path('module', 'dgf_administration'); // Module PATH
  drupal_add_js($path . '/assets/js/admin_validate_users.js'); // ADMIN JS
}

 /**
 *
 *  Formulaire de validation d'un utilisateurs.
 *  @param: $form , &$form_state
 *
 *
 */
function dgf_administration_users_verify_form($form, &$form_state) {
  _dgf_administration_users_verify_add_css_js();  // Load JS & CSS

  global $user;  // $user_roles = $user->roles; // Roles utilisateurs
  $id_drupal_user  = arg(3);  // Id user
  $user_extranet_infos = dgf_administration_users_verify_get_infos($id_drupal_user);

  // Get  user infos
  if (isset($id_drupal_user)) {
      foreach ($user_extranet_infos as $value) {
        $civilite = $value->civilite;
        $first_name = $value->first_name;
        $last_name = $value->last_name;
        $user_mail = $value->mail;
        $user_fonction = $value->fonction;
        $user_phone = $value->telephone;
    }
  }

  $_SESSION['email'] = $user_mail; // Email utilisateur

  $form['infos'] = array(
    '#type' => 'fieldset',
    '#title' => t('INFORMATIONS PERSONNELLES'),
  );

  $form['infos']['user_gender'] = array(
    '#type'     => 'select',
    '#title'    => t('Titre:'),
    '#options' => shared_db_get_title(true),
    '#default_value'  => empty($civilite) ? null : trim($civilite),
    //'#required' =>  TRUE,
  );
  $form['infos']['user_name'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Nom:'),
    //'#required' =>  TRUE,
    '#default_value' => empty($last_name) ? '' : $last_name,
  );
  $form['infos']['user_surname'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Prénom:'),
    '#default_value' => empty($first_name) ? '' : $first_name,
     //'#required' =>  TRUE,
  );
  $form['infos']['user_email'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Adresse email'),
    '#default_value' => empty($user_mail) ? '' : $user_mail,
    //'#required' =>  TRUE,
  );
  $form['infos']['user_fonction'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Fonction'),
    '#default_value' => empty($user_fonction) ? '' : $user_fonction,
    //'#required' =>  TRUE,
  );
  $form['infos']['user_phone'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Téléphone'),
    '#default_value' => empty($user_phone) ? '' : $user_phone,
    //'#required' =>  TRUE,
  );

  // Charges la Liste des rôles
  $Roles = user_roles();

  // On enlève les rôles indésirés.
  unset($Roles[0], $Roles[1], $Roles[2] , $Roles[3]);

  $spec_roles = array(
   'Administrateur adhérent',
   'Collaborateur adhérent',
   'Organisme de formation',
   'Cabinet comptable');

  // Inputs des roles
  $form['infos']['roles'] = array(
    '#type'     => 'select',
    '#title'    => t('Profil:'),
    //'#options'  => empty($user_roles) ? $Roles : $user_roles,
    '#options'  => $spec_roles,
      '#default_value' => array(1),
    //'#required' =>  TRUE,
  );

  // Fonctionnalités.
  $form['Actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('FONCTIONNALITES'),
  );

  $habilitations = shared_db_get_habilitation($id_drupal_user);
  $default_value = array();
  foreach ($habilitations as $habilitation) {
    $default_value[] = $habilitation->cle;
  }
  // Fonctionnalités de l'utilisateur
  // Habilitations
  $form['Actions']['habilitations'] = array(
      '#type'     => 'checkboxes',
      '#options'  => shared_get_habilitation(),
      '#default_value' => $default_value,
    //'#title'    => t('Fonctionnalités'),
    //'#required' =>  TRUE,
  );

  // MES ETABLISSEMENTS
  // Get user entreprise from Drupal USER ID
  $lien_user_entreprise_ref_esclave_entreprise = dgf_administration_db_get_lien_user_entreprise_ref_esclave_entreprise($id_drupal_user);

  $compt = 0;
  $form['establishment_title'] = array(
      '#type' =>  'markup',
      '#markup' => "<div id='my-companies' class='row'><h4>MES ETABLISSEMENTS</h4>",
  );

  // On parcourt les entreprises de l'utilisateur
  foreach ($lien_user_entreprise_ref_esclave_entreprise as $lien) {
    $entreprise = shared_db_get_entreprise_data($lien->id_ref_esclave_entreprise);

    // PARTIE ENTREPRISE
    $html_entreprise = "<div class='col-lg-4'><ul>";
    $html_entreprise .= "<li>Raison sociale: " . $entreprise->raison_sociale . "</li>";
    $html_entreprise .= "<li>Siret: " . $entreprise->siret . "</li>";
    $html_entreprise .= "<li>N° Adhérent:</li>";
    $html_entreprise .= "<li>Adresse: " . $entreprise->rue . ' '
        . $entreprise->complement_de_rue . ' '
            . $entreprise->code_postal . ' '
                . $entreprise->ville .  "</li>";
    $html_entreprise .= "</ul></div>";

    $form['establishment_'.$compt] = array(
        '#type' =>  'markup',
        '#markup' => $html_entreprise,
        '#prefix' => '<div class="row company-'.$compt.'">'
    );
    $form['id_establishment_'.$compt] = array(
        '#type' =>  'hidden',
        '#value' => $entreprise->id,
    );

    $company_adefim_id = dgf_administration_users_get_adefim_id($lien->id_ref_esclave_entreprise);
    $company_adefim_infos = dgf_administration_users_get_infos_adefim($company_adefim_id);
//     $company_adefim_contact = dgf_administration_users_get_contact_adefim($company_adefim_id);

    // PARTIE ADEFIM
    $html_adefim = "<div class='col-lg-4'><ul>";
    $html_adefim .= "<li>ADEFIM: " . $company_adefim_infos->raison_sociale . "</li>";
    $html_adefim .= "<li>Téléphone: " . $company_adefim_infos->telephone_principal . "</li>"; // number_format($number, 2, '.', '');
    $html_adefim .= "<li>Email: " . $company_adefim_infos->email . "</li>";
    $html_adefim .= "</ul></div>";

    $form['adefim_'.$compt] = array(
        '#type' =>  'markup',
        '#markup' => $html_adefim,
    );

    // PARTIE VALIDATION
    $company_statut = $entreprise->est_valide;
    if($company_statut == 0){
      $company_statut_msg =  "En attente";
    }
    else{
      $company_statut_msg = "Validé";
    }
    // Gestion des droits au rattachement
    if ($lien->est_valide == 0) {
      if (user_access('GES_VAL_ETA')){
        $select_values = array('En attente', 'Validé', 'Refusé');
        $form['rattachement_'.$compt] = array(
            '#type' =>  'select',
            '#options'  => $select_values,
            '#prefix' => "<div class='col-lg-4'><b>Statut de  rattachement </b>",
            '#suffix' => "Statut établissement : ".$company_statut_msg."</div></div>",
        );
      } else {
        $rattachement_msg = "Rattachement en attente de validation";
        $form['rattachement_'.$compt] = array(
            '#type' =>  'markup',
            '#markup'  => $rattachement_msg,
            '#suffix' => 'Statut établissement : '.$company_statut_msg.'</div>'
        );
      }
    } else {
      $rattachement_msg = "Rattachement validé";
      $form['rattachement_'.$compt] = array(
          '#type' =>  'markup',
          '#markup'  => $rattachement_msg,
          '#suffix' => 'Statut établissement : '.$company_statut_msg.'</div>'
      );
    }
    $compt++;
  }

//   $user_id_entreprise = dgf_administration_get_user_id_entreprise($id_drupal_user);
//   $mes_etablissements = dgf_administration_users_get_users_companies($user_id_entreprise);

//   $form['establishment'] = array(
//     '#type' =>  'markup',
//     '#markup' => $mes_etablissements,
//   );
//   $form['my_companies'] = array(
//     '#type' =>  'markup',
//     '#markup' => "<div class='clearfix'></div><div id='companies-results' class='row'></div>",
//   );
//   $form['reaffect'] = array(
//     '#type'    => 'submit',
//     '#value'   => t('Réaffecter'),
//     '#submit' => array('reaffect_establishment'),
//     '#prefix' => '<div class="row"><div class="col-lg-1">',
//     '#suffix'  => '</div>',
//     '#attributes' => array(
//     'class' => array('btn btn-danger'),
//     ),
//   );
  $form['nb_siret'] = array(
      '#type'    => 'hidden',
      '#value'   => $compt,
  );
  $form['clear'] = array(
    '#type'    => 'markup',
    '#markup'   => "<div class='clearfix'>&nbsp;</div>",
  );
  $form['cancel'] = array(
    '#type'    => 'button',
    '#value'   => t('Annuler'),
    '#submit' => array('dgf_administration_users_verify_cancel'),
    '#execute_submit_callback' => TRUE,
    '#prefix' => '<div class="row"><div class="col-lg-1">',
    '#suffix'  => '</div>',
    '#attributes' => array(
    'class' => array('btn btn-danger'),
    ),
  );
  $form['refuse'] = array(
    '#type'    => 'submit',
    '#value'   => t('Refuser'),
    '#submit' => array('dgf_administration_users_verify_refuse_submit'),
    '#prefix' => '<div class="col-lg-offset-9">',
    '#attributes' => array(
    'class' => array('btn btn-primary'),
    ),
    '#limit_validation_errors' => array(),
  );
  $form['save'] = array(
    '#type'    => 'submit',
    '#value'   => t('Valider'),
    '#submit'  => array('dgf_administration_users_verify_submit'),
    '#validate' => array('dgf_administration_users_verify_form_validate'
    ),
    '#suffix'  => '</div></div>',
    '#attributes' => array(
    'class' => array('btn btn-success'),
  ),
  );

  return $form;
}


/**
 *  Permet de réaffecter un établissement à un ADEEFIM
 *
 */
function dgf_administration_users_reaffect_submit(&$form_state){
  $id_drupal_user = arg(3);
  // TODO REAFFECTER UN ETABLISSEMENT
}

/**
 *   Redirection vers la page de recherche d'un utilisateur, bouton Cancel
 *
 */
function dgf_administration_users_verify_cancel() {
  drupal_goto("gestion/utilisateurs");
}

/**
 *  Infos sur les établissements et les Adefims, liés à une entreprise.
 *
 *  @param: Id user entreprise.
 *
 */
function  dgf_administration_users_get_users_companies($id_user_entreprise){

  $id_entreprise = dgf_administration_users_etablissement($id_user_entreprise); // Id de l'entreprise dans le référentiel Esclave
  $company_adefim_id = dgf_administration_users_get_adefim_id($id_entreprise);

  // INFOS ETABLISSEMENTS
  $user_companies_infos = dgf_administration_users_get_etablissement_infos($id_entreprise);
  $user_companies_adress = dgf_administration_users_get_etablissement_adresses($id_entreprise);

   // INFOS ADEFIM
  $company_adefim_infos = dgf_administration_users_get_infos_adefim($company_adefim_id);
  $company_adefim_contact = dgf_administration_users_get_contact_adefim($company_adefim_id);

  // Si résultats vides on arrête le traitement.
  if (empty($user_companies_infos) || empty($user_companies_adress) || empty($company_adefim_infos) || empty($company_adefim_contact)) {
    return false;
  }

  // ENTREPRISES
  $company = new stdClass;
  $company_adress = new stdClass;

  // ADEFIMS
  $adefim  = new stdClass;
  $adefim_contact  = new stdClass;

  if (!empty($user_companies_infos) || !empty($user_companies_adress)){
    foreach ($user_companies_infos as $c_infos) {
      $company->id = trim($c_infos->id);
      $company->raison_sociale = trim($c_infos->raison_sociale);
      $company->siret = trim($c_infos->siret);
      $company->valide = $c_infos->est_valide;
      $company->actif = $c_infos->est_actif;
    }
    foreach ($user_companies_adress as $c_infos_adress) {
      $company_adress->rue = trim($c_infos_adress->rue);
      $company_adress->complement_de_rue = trim($c_infos_adress->complement_de_rue);
      $company_adress->complement_de_rue_plus = trim($c_infos_adress->complement_de_rue_2);
      $company_adress->cp = $c_infos_adress->code_postal;
      $company_adress->ville = trim($c_infos_adress->ville);
    }
  }

  if(!empty($company_adefim_infos) || !empty($company_adefim_contact)){
    foreach ($company_adefim_infos as $a_infos) {
      $adefim->raison_sociale_adefim = trim($a_infos->raison_sociale);
      $adefim->siret_adefim = trim($a_infos->siret);
      $adefim->telephone_adefim = trim($a_infos->telephone_principal);
      $adefim->email_adefim = trim($a_infos->email);
    }
    foreach ($company_adefim_contact as $a_infos_contact) {
      $adefim_contact->civilite = trim($a_infos_contact->id_civilite);
      $adefim_contact->prenom = trim($a_infos_contact->prenom);
      $adefim_contact->nom = trim($a_infos_contact->nom);
      $adefim_contact->email = trim($a_infos_contact->email);
    }
  }

  // Données à afficher
  $html  = "<div id='my-companies' class='row'><h4>MES ETABLISSEMENTS</h4>";

  // PARTIE ENTREPRISE
  $html .= "<div class='col-lg-4'><ul>";
  $html .= "<li>Raison sociale: " . $company->raison_sociale . "</li>";
  $html .= "<li>Siret: " . $company->siret . "</li>";
  $html .= "<li>N° Adhérent:</li>";
  $html .= "<li>Adresse: " . $company_adress->rue . ' ' . $company_adress->complement_de_rue . ' '  . $company_adress->cp . ' ' . $company_adress->ville .  "</li>";
  $html .= "</ul></div>";

  // PARTIE ADEFIM
  $html .= "<div class='col-lg-4'><ul>";
  $html .= "<li>ADEFIM: " . $adefim->raison_sociale_adefim . "</li>";
  $html .= "<li>Contact: " . $adefim_contact->civilite .' ' .  $adefim_contact->prenom . ' ' . $adefim_contact->nom . "</li>";
  $html .= "<li>Téléphone: " . $adefim->telephone_adefim . "</li>"; // number_format($number, 2, '.', '');
  $html .= "<li>Email: " . $adefim->email_adefim . "</li>";
  $html .= "</ul></div>";

  // PARTIE VALIDATION
  $company_statut = $company->valide;
  if($company_statut == 0){
    $company_statut_msg =  "En attente";
  }
  else{
    $company_statut_msg = "Validé";
  }
  // Gestion des droits au rattachement
  if (user_access('GES_VAL_ETA')){
    $rattachement_msg = "Rattachement validé";
    $select_values = array('En attente', 'Validé', 'Refusé');
    $select  = theme('select', array('element' => array(
        '#id' => 'status_rattachement',
        '#name' => 'status_rattachement',
        '#title' => 'status_rattachement',
        '#options' => $select_values,
    )));
    $html .= "<div class='col-lg-4'><b>Statut de  rattachement </b>: " . $select . "</div><div class='clear'></div>";
  }
  else{
    $rattachement_msg = "Rattachement en attente de validation";
  }

  $html .= "<div class='col-lg-4'><b>Statut établissement: " . $company_statut_msg . "</b></div>";
  $html .= "<div class='col-lg-4'><b>" . $rattachement_msg . "</b></div>";
  $html .= "</div>";

  print $html;
}

/**
 * Implements Hook_theme()
 */
function dgf_administration_users_get_users_companies_theme() {
  $theme = array(
    'validation_utilisateurs' => array(
      'template' => 'dgf_administration_users_verify',
    )
  );
  //  return theme('validation_utilisateurs');
  return $theme;
}
