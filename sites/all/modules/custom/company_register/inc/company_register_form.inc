<?php

/**
 * Fonction Require pour les .inc
 */
function _company_register_require(){
  require_once 'company_register_db.inc'; // Bases de données
  require_once 'company_register_langs.inc'; // Langues
  require_once 'company_register_validate.inc'; // Validate
  require_once 'company_register_submit.inc'; // Submit
}

/**
 * Fonction ajout pour les js et css
 *
 */
function _company_register_add_js_css() {
  // Add CSS and JS
  $path = drupal_get_path('module', 'company_register');
  // JS
  drupal_add_js( $path . '/assets/js/company_register.js');
  // CSS
  drupal_add_css( $path . '/assets/css/company_register.css');

}

/**
 *  FORMULAIRE 1: CHARTE CONFIDENTIALITE
 *  @param: $form , &$form_state
 *  @return: $form - Le formulaire de création de compte avec la charte
 *
 */
function company_register_charte($form, &$form_state){
  // Add JS & CSS
  _company_register_add_js_css();

  // On affiche le formulaire de la page 2 si c'est la page 2
  if (!empty($form_state['page_num']) && $form_state['page_num'] == 1) {
    return company_register_create_account($form, $form_state);
  }

  // Sinon on est à la page 1
  $form_state['page_num'] = 0;

  // Texte valider
  $form['ValidText'] = array(
      '#type' => 'markup',
      '#markup' => "<div>". t(@OPCAIM_INFOS_VALID) . "</div>",
  );

  // Rappel OPCAIM
  $form['Rappel'] = array(
      '#type' => 'markup',
      '#markup' => "<div>". t(@OPCAIM_INFOS) . "</div>",
  );

  // Charte OPCAIM
  $form['charte'] = array(
      '#type' => 'markup',
      '#markup' => "<div id='charte' class='scroller'>" . @CHARTE_CONFIDENTIALITE . "</div><div class='clearfix'></div>", // Charte de confidentialité
  );

  //   // Bouton de redirection
  //   $link = l(t(@REFUSER_CHARTE), '/login', array('attributes' => array('class' => 'charte-btn')));
  //   // Bouton d'impression
  //   $print = "<a class='charte-btn' onClick='window.print()' id='PrintBtn'>" . @IMPRIMER . "</a>";

  //   $html_button = '<div id="boutonActionCharte" class="center">';
  //   $html_button .= $link . $print;
  //   $form['Action'] = array(
  //       '#type' => 'markup',
  //       '#markup' => $html_button,
  //   );

  $form['action'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="boutonAction">',
  );

  $form['button']['refuse'] = array(
      '#type'  => 'submit',
      '#value' => t(@REFUSER_CHARTE),
  );

  $form['button']['Impression'] = array(
      '#type'  => 'submit',
      '#value' => @IMPRIMER,
  );

  $form['button']['accepte'] = array(
      '#type'  => 'submit',
      '#value' => t(@ACCEPTER_CHARTE),
      '#attributes' => array('class' => array('btn btn-primary')),
  );

  $form['action_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div>',
  );

  return $form;
}

function company_register_information_form($form, &$form_state) {
  _company_register_require();
  _company_register_add_js_css();

  if (isset($form_state['storage']['display_confirmation'])) {
    return company_register_confirmation_form($form, $form_state);
  }

  // Rappel OPCAIM
  $form['rappel'] = array(
      '#type' => 'markup',
      '#markup' => "<div class='row'>". t(@OPCAIM_INFOS) . "</div>",
  );

  // Formulaire d'enregistrement partie Entreprise
  _company_register_entreprise_form($form, $form_state);

  // Formulaire d'enregistrement partie responsable Entreprise
  _company_register_user_responsable_form($form, $form_state);

  // Formulaire d'enregistrement partie Utilisateur Entreprise
  _company_register_user_entreprise_form($form, $form_state);

  // Envoie des données pour enregistrement
  $form['suivant'] = array(
      '#type'   => 'submit',
      '#submit' => array('company_register_information_form_submit'),//array('company_register_create_account_submit'),
      '#value'  => t('Suite'),
      '#validate' => array(
          'company_register_form_validate',
          'company_register_validate_users_email',
          'company_register_validate_entreprise'
      ),
  );
  // Envoie du formulaire au formulaire 3
  return $form;
}

function company_register_confirmation_form($form, &$form_state) {
  _company_register_require();
  _company_register_add_js_css();

  /* ------------------------------
   *  Responsable de l'entreprise
  * -----------------------------*/
  $email_responsable    = $form_state['values']['responsable_email'];
  $fonction_responsable = $form_state['values']['responsable_fonction'];

  /* -------------------------------
   *  Utilisateur
  * -----------------------------*/
  $email_utilisateur    = $form_state['values']['utilisateur_email'];
  $fonctionnalites      = $form_state['values']['utilisateur_fonctions'];
  $tel_utilisateur      = $form_state['values']['utilisateur_telephone'];

  /* ------------------------------
   *  Données Entreprises
  * -----------------------------*/
  $form['confirmation'] = array(
      '#type'  => 'item',
      '#title' => '<p>' . t(@REGISTER_CONFIRM_MESSAGE) . '</p>',
      '#prefix' => '<div id="confirmation" class="col-lg-12">',
  );

  $form['entreprise'] = array(
      '#type'  => 'item',
      '#title' => t('<h4>Entreprise</h4>'),
      '#prefix' => '<div class="col-lg-6">',
      '#suffix' => '</div>',
  );

  $form['adefim_titre'] = array(
      '#type'  => 'item',
      '#title' => t('<h4>ADEFIM</h4>'),
      '#prefix' => '<div class="col-lg-6">',
      '#suffix' => '</div>',
  );

  //  AFFICHAGE ENTREPRISE & ADEFIMS
  $nb_siret = $form_state['values']['nb_siret'];

  for ($i=0; $i < $nb_siret ; $i++) {
    $raison_sociale = $form_state['values']['company_raison_sociale_'.$i];
    $siret          = $form_state['values']['company_siret_'.$i];
    $adefim_entreprises = shared_get_adefim_from_siret($siret);

    $form['raison_sociale_'.$i] = array(
        '#type'  => 'item',
        '#title' => t('<b>Raisons sociale:  ' . $raison_sociale . '</b>'),
        '#prefix' => '<div class="row"><div class="col-lg-6">',
    );
    $form['siret_'.$i] = array(
        '#type'  => 'item',
        '#title' => t('<b>Siret: '. trim($siret) . '</b>'),
        '#suffix' => '</div>'
    );

    if (count($adefim_entreprises) === 1) {
      $form['nom_adefim_'.$i]= array(
          '#type'  => 'item',
          '#title' => t('<b>Nom: '. $adefim_entreprises[0]->raison_sociale . '</b>'),
          '#prefix' => '<div class="col-lg-6">',
          '#suffix' => '</div></div>',
      );
    } else if (count($adefim_entreprises) > 1) {
      $options = array();
      foreach ($adefim_entreprises as $adefim) {
        $options[trim($adefim->id_adefim)] = trim($adefim->raison_sociale);
      }
      $form['nom_adefim_'.$i]= array(
          '#type'  => 'select',
          '#title' => t('<b>Nom: </b>'),
          '#prefix' => '<div class="col-lg-6">',
          '#suffix' => '</div></div>',
          '#options' => $options,
      );
    } else {
      $form['nom_adefim_'.$i]= array(
          '#type'  => 'select',
          '#title' => t('<b>Nom: </b>'),
          '#prefix' => '<div class="col-lg-6">',
          '#suffix' => '</div></div>',
          '#options' => shared_get_adefim(),
      );
    }
  }

  /* ---------------------------------
   *    Données Responsable Entreprise
  * -----------------------------*/
  $form['responsable_entreprise'] = array(
      '#type'  => 'item',
      '#title' => t('<h4>Le responsable de l\'entreprise</h4>'),
      '#prefix' => '<div class="col-lg-12">',
  );
  $form['responsable_email'] = array(
      '#type'  => 'item',
      '#title' => t('<span class="res_label">Email:</span>  ' . $email_responsable),
  );
  $form['responsable_fonction'] = array(
      '#type'  => 'item',
      '#title' => t('<span class="res_label">Fonction responsable:</span>' . $fonction_responsable),
      '#suffix' => '</div>',
  );

  /* -----------------------------------
   *  Données Utilisateur ENTREPRISE
  * ---------------------------------*/
  $form['utilisateur_entreprise'] = array(
      '#type'  => 'item',
      '#title' => t('<h4>Utilisateur</h4>'),
      '#prefix' => '<div class="col-lg-12">',
  );

  $form['utilisateur_email'] = array(
      '#type'  => 'item',
      '#title' => t('<span class="res_label">Email:</span>' . $email_utilisateur),
  );

  $form['utilisateur_tel'] = array(
      '#type'  => 'item',
      '#title' => t('<span class="res_label">Téléphone:</span>' . $tel_utilisateur),
  );
  $form['utilisateur_signature'] = array(
      '#type'       => 'textfield',
      '#title'      => t('Je soussigné'),
      '#attributes' => array(
          'placeholder' => array(t('Veuillez entrer votre nom')),
      ),
      '#required' => TRUE,
      '#suffix' => '</div>',
  );

  $numero_demande  = company_register_get_numero_demande() + 1;

  $form['num_demande'] = array(
      '#type'  => 'markup',
      '#markup' => '<div class="num"><h3>' .  t('Votre numéro de demande: ' . $numero_demande ) .  '</h3></div>',
      '#prefix' => '<div class="col-lg-12">',
      '#suffix' => '</div>',
  );
  // Bouton Rappel
  $form['rappel'] = array(
      '#type'  => 'item',
      '#title' => t(@Rappel),
      '#prefix' => '<div class="row col-lg-12">',
      '#suffix' => '</div>',
  );

  // Bouton Impression
  /* ----------------------------------
   *   Partie Bouton Confirmer et envoie
  * ---------------------------------*/

  $form['action'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="boutonAction">',
  );

  $form['button']['back'] = array(
      '#type'  => 'submit',
      '#value' => @MODIFIER_DEMANDE,
  );

  $form['button']['Impression'] = array(
      '#type'  => 'submit',
      '#value' => @IMPRIMER,
  );


  $form['button']['next'] = array(
      '#type'  => 'submit',
      '#value' => t('CONFIRMER VOTRE DEMANDE'),
      '#submit' => array('company_register_confirmation_form_submit'),
      '#attributes' => array('class' => array('btn btn-primary')),
  );

  $form['action_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div>',
      '#suffix' => '</div>',
  );

  return $form;
}

function _company_register_entreprise_form(&$form, $form_state) {
  // Champs Entreprises
  $form['company'] = array(
      '#type'  => 'fieldset',
      '#title' => t('<b>L\'ENTREPRISE</b>'),
  );

  $form['company']['nb_siret'] = array(
      '#type' => 'hidden',
      '#default_value' => 1,
  );

  // TODO : faire la même si ça vient de la bdd
  $nb_siret = $form_state['input'] ? $form_state['input']['nb_siret'] : 1;

  for ($i = 0; $i < $nb_siret; $i++) {
      // Numéro siret
      $form['company']['company_siret_'.$i] = array(
          '#type'  => 'textfield',
          '#title' => t('N° Siret'),
          '#prefix' => "<div class='company-infos company-infos-".$i."'><div class='left-col'>",
          '#suffix' => "</div>",
          '#attributes' => array('class' => array('autocomplete-siret')),
      );

      // Raison sociale obligatoire
      $form['company']['company_raison_sociale_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Raison sociale'),
          // '#default_value' => empty($raison_sociale) ? '' : $raison_sociale,
          '#default_value' => (!empty($_SESSION['data']['CompanyRaisonSociale'])) ? $_SESSION['data']['CompanyRaisonSociale'] : NULL,
          '#prefix' => "<div class='right-col'>",
          '#suffix' => "</div>",
      );

      $form['company']['code_naf_'.$i] = array(
          '#type'     => 'select',
          '#title'    => t('Code NAF'),
          '#required' =>  TRUE,
          '#options'  => company_register_get_code_naf(),
//           '#default_value' => (!empty($_SESSION['data']['CodeNaf'])) ? $_SESSION['data']['CodeNaf'] : NULL,
          '#prefix' => "<div class='left-col'>",
          '#suffix' => "</div>",
      );

      // Adresse obligatoire
      $form['company']['company_adresse_street_number_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Adresse'),
          //'#default_value' => empty($rue_entreprise) ? '' : $rue_entreprise,
          '#default_value' => (!empty($_SESSION['data']['CompanyAdresseStreetNumber'])) ? $_SESSION['data']['CompanyAdresseStreetNumber'] : NULL,
          '#prefix' => "<div class='left-col form-item-company-adresse-street-number'>",
          '#suffix' => "</div>",
          '#attributes' =>array('placeholder' => t('N°'))
      );

      // Adresse obligatoire
      $form['company']['company_adresse_street_name_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Rue'),
          // '#default_value' => empty($comp_rue_entreprise) ? '' : $comp_rue_entreprise,
          '#default_value' => (!empty($_SESSION['data']['CompanyAdresseStreetName'])) ? $_SESSION['data']['CompanyAdresseStreetName'] : NULL,
          '#prefix' => "<div class='left-col width-30 form-item-company-adresse-street-name'>",
          '#suffix' => "</div>",
          '#attributes' =>array('placeholder' => t('Voie'))
      );

      // Adresse obligatoire
      $form['company']['company_adresse_street_name_more_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Complément de rue'),
          // '#default_value' => empty($comp_rue_entreprise_suite) ? '' : $comp_rue_entreprise_suite,
          '#default_value' => (!empty($_SESSION['data']['CompanyAdresseStreetNameMore'])) ? $_SESSION['data']['CompanyAdresseStreetNameMore'] : NULL,
          '#prefix' => "<div class='form-item-company-adresse-street-name-more'>",
          '#suffix' => "</div>",
      );

      // Code postal obligatoire
      $form['company']['company_code_postal_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Code postal / Ville'),
          // '#default_value' => empty($code_postal) ? '' : $code_postal,
          '#default_value' => (!empty($_SESSION['data']['CompanyAdresseTown'])) ? $_SESSION['data']['CompanyAdresseTown'] : NULL,
          '#prefix' => "<div class='left-col placeholder'></div><div class='left-col form-item-company-code-postal'>",
          '#suffix' => "</div>",
      );

      // Adresse obligatoire
      $form['company']['company_adresse_town_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Ville'),
          // '#default_value' => empty($ville) ? '' : $ville,
          '#default_value' => (!empty($_SESSION['data']['CompanyAdresseTown'])) ? $_SESSION['data']['CompanyAdresseTown'] : NULL,
          '#prefix' => "<div class='left-col width-30 form-item-company-adresse-town'>",
          '#suffix' => "</div>",

          //'#required' =>  TRUE,
      );

      // Téléphone
      $form['company']['company_telephone_'.$i] = array(
          '#type'     => 'textfield',
          '#title'    => t('Téléphone'),
          // '#default_value' => empty($phone) ? '' : $phone,
          '#default_value' => (!empty($_SESSION['data']['CompanyTelephone'])) ? $_SESSION['data']['CompanyTelephone'] : NULL,
          '#prefix' => "<div class='form-item-company-telephone'>",
          '#suffix' => "</div></div>",
      );

      if ($i == 0) {
        $form['company']['demande_multi_siret'] = array(
            '#type' =>'checkbox',
            '#title' => t('Voulez-vous faire une demande d’ouverture de compte pour plusieurs établissements ?  '),
        );
      }
  }

  $form['company']['autre_siret'] = array(
      '#type' => 'markup',
      '#markup' => "<div id='autreSiret'></div>",
  );

  // Button ajoutez un siret
  $form['company']['ajout_siret'] = array(
      '#type'     => 'button',
      '#value'    => t('Ajoutez un siret'),
  );
}

function _company_register_user_responsable_form(&$form, $form_state) {
  $form['responsable'] = array(
      '#type' => 'fieldset',
      '#title' => t('<b>LE RESPONSABLE DE L\'ENTREPRISE</b>'),
  );

  // Titre
  $form['responsable']['responsable_titre'] = array(
      '#type' => 'select',
      '#title' => t('Titre'),
      '#options' => shared_db_get_title(true),
      '#required' => TRUE,
//       '#default_value' => (!empty($_SESSION['data']['responsableTitre'])) ? $_SESSION['data']['responsableTitre'] : NULL,
  );
  // Code postal obligatoire
  $form['responsable']['responsable_nom'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom'),
      '#required' => TRUE,
//       '#default_value' => (!empty($_SESSION['data']['responsableNom'])) ? $_SESSION['data']['responsableNom'] : NULL,

  );
  // Téléphone
  $form['responsable']['responsable_prenom'] = array(
      '#type' => 'textfield',
      '#title' => t('Prénom'),
      '#required' => TRUE,
//       '#default_value' => (!empty($_SESSION['data']['responsablePrenom'])) ? $_SESSION['data']['responsablePrenom'] : NULL,
  );
  // Email
  $form['responsable']['responsable_email'] = array(
      '#type' => 'textfield',
      '#title' => t('Courriel'),
      '#required' =>  TRUE,
//       '#default_value' => (!empty($_SESSION['data']['Emailresponsable'])) ? $_SESSION['data']['Emailresponsable'] : NULL,
  );
  $form['responsable']['responsable_email2'] = array(
      '#type' => 'textfield',
      '#title' => t('Confirmer courriel'),
      '#required' =>  TRUE,
      '#validate' => array('company_register_check_responsable_email_form_validate'),
      // '#default_value' => (!empty($_SESSION['data']['Emailresponsable2'])) ? $_SESSION['data']['Emailresponsable2'] : NULL,
  );

  // Fonction
  $form['responsable']['responsable_fonction'] = array(
      '#type' => 'textfield',
      '#title' => t('Fonction'),
      '#required' => TRUE,
  );
}

function _company_register_user_entreprise_form(&$form, $form_state) {
  $form['utilisateur'] = array(
      '#type' => 'fieldset',
      '#title' => t('<b>L\'UTILISATEUR</b>'),
  );

  // Titre
  $form['utilisateur']['utilisateur_titre'] = array(
      '#type' => 'select',
      '#title' => t('Titre'),
      '#options' => shared_db_get_title(true),
      '#required' => TRUE,
  );
  // Nom utilisateur
  $form['utilisateur']['utilisateur_nom'] = array(
      '#type' => 'textfield',
      '#title' => t('Nom'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurNom'])) ? $_SESSION['data']['utilisateurNom'] : NULL,
      '#required' => TRUE,
  );
  // Prenom utilisateur
  $form['utilisateur']['utilisateur_prenom'] = array(
      '#type' => 'textfield',
      '#title' => t('Prénom'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurPrenom'])) ? $_SESSION['data']['utilisateurPrenom'] : NULL,
      '#required' => TRUE,
  );
  // Email
  $form['utilisateur']['utilisateur_email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurEmail'])) ? $_SESSION['data']['utilisateurEmail'] : NULL,
      '#required' => TRUE,
  );
  $form['utilisateur']['utilisateur_email2'] = array(
      '#type' => 'textfield',
      '#title' => t('Confirmer courriel'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurEmail2'])) ? $_SESSION['data']['utilisateurEmail2'] : NULL,
      '#required' => TRUE,
  );
  // Fonction
  $form['utilisateur']['utilisateur_fonction'] = array(
      '#type' => 'textfield',
      '#title' => t('Fonction'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurFonction'])) ? $_SESSION['data']['utilisateurFonction'] : NULL,
      '#required' => TRUE,
  );
  // Téléphone
  $form['utilisateur']['utilisateur_telephone'] = array(
      '#type' => 'textfield',
      '#title' => t('Téléphone'),
      '#default_value' => (!empty($_SESSION['data']['utilisateurTelephone'])) ? $_SESSION['data']['utilisateurTelephone'] : NULL,
      '#required' => TRUE,
  );

  // Mot de passe
  $form['utilisateur']['utilisateur_password'] = array(
      //'#title' => t('Mot de passe'),
      '#type' => 'password_confirm',
      '#required' => TRUE,
      '#size' => 25,
  );

  // Fonctionnalités de l'utilisateur
  $habilitations = shared_get_habilitation();

  $form['utilisateur']['utilisateur_fonctions'] = array(
      '#type'    => 'checkboxes',
      '#title'   => t('Fonctionnalités'),
      '#attributes' => array('class' => array('SelectAll')),
      '#options' => $habilitations,
      '#required' => TRUE
  );
}