<?php

function dgf_validation_utilisateur_db_update_lien_rattachement($id_user_drupal, $id_entreprise, $valide = true) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $sql = db_select('user_entreprise', 'u')
  ->fields('u', array('id'))
  ->condition('id_drupal_user', $id_user_drupal, '=')
  ->execute();

  $id_user_entreprise = $sql->fetchField();

  if ($valide) {
    $data = array('est_valide' => 1);
  } else {
    $data = array('est_actif' => 0);
  }
  $sql = db_update('lien_user_entreprise_ref_esclave_entreprise')
  ->fields($data)
  ->condition('id_user_entreprise', $id_user_entreprise, '=')
  ->condition('id_ref_esclave_entreprise', $id_entreprise, '=')
  ->execute();

  db_set_active();
}

 /**
 * Infos de l'utilisateur via le Drupal USER
 *
 */
function dgf_administration_users_verify_get_infos($id_drupal_user) {

  db_set_active(@DB_EXTRANET);

  $sql = db_select('drupal_user' , 'u')
        ->fields('u', array('civilite', 'first_name', 'last_name', 'mail', 'fonction', 'telephone'))
        ->condition('id', $id_drupal_user , '=')
        ->execute();

  $user_infos  = $sql->fetchAll();

  db_set_active();

  return $user_infos;
}

/**
 *   Mise à jour des données en base.
 *   @param : $data - Tableau de données. $id de l'utilisateur.
 *
 *
 */
function dgf_administration_users_verify_save_infos($data , $id) {
  global $user;

  $civilite = $data['user_gender'];
  $user_name = $data['user_name'];
  $user_surname = $data['user_surname'];
  $user_email = $data['user_email'];
  $user_fonction = $data['user_fonction'];
  $user_phone = $data['user_phone'];
  $user_role = $data['roles'];

  $user_habilitations = $data['habilitations'];

  db_set_active(@DB_EXTRANET);

  // Sauvegarde les infos de l'utilisateur.
  $update = db_update('drupal_user')
         ->fields(array(
         'civilite' => $civilite,
         'first_name' => $user_surname,
         'last_name' => $user_name,
         'mail'   => $user_email,
         'fonction' => $user_fonction,
         'telephone' => $user_phone,
         'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
         'id_user_last_edit' =>$user->uid,
         ))
         ->condition('id', $id , '=')
         ->execute();

   // Supprime toutes les habilitations de l'utilisateur associé à l'id
   $delete = db_delete('lien_drupal_user_habilitation')
                 ->condition('id_drupal_user' , $id, '=')
                 ->execute();

   // Sauvegarde les habilitations  // Vaudrait mieux faire un db_update : lien
  foreach ($user_habilitations as $key => $value) {
     if ($value != '') {
       $hab_sql = db_insert('lien_drupal_user_habilitation')
                ->fields(array(
                'id_drupal_user'     => $id,
                'id_habilitation'    => $key,
                ))
                ->execute();
     }
  }

  $query_id_user_drupal = db_select('drupal_user', 'u')
    ->fields('u', array('id_user_drupal'))
    ->condition('id', $id , '=')
    ->execute();


  $id_user_drupal = $query_id_user_drupal->fetchField();

  db_set_active();

  $account = user_load($id_user_drupal);
  user_save($account, array('status' => 1));
}

function dgf_administration_db_get_lien_user_entreprise_ref_esclave_entreprise($id_user_drupal) {
  db_set_active(@DB_EXTRANET);

  $sql = db_select('user_entreprise', 'u')
    ->fields('u', array('id'))
    ->condition('id_drupal_user', $id_user_drupal, '=')
    ->execute();

  $id_user_entreprise = $sql->fetchField();

  $sql = db_select('lien_user_entreprise_ref_esclave_entreprise', 'lue')
    ->fields('lue')
    ->condition('id_user_entreprise', $id_user_entreprise, '=')
    ->execute();

  $lien_user_entreprise_ref_esclave_entreprise = $sql->fetchAll();

  return $lien_user_entreprise_ref_esclave_entreprise;
}

/**
 *  Renvoie l'Id entreprise associé à un Utilisateur Drupal
 *
 *
 *
 */
function dgf_administration_get_user_id_entreprise($id_user_drupal) {

  db_set_active(@DB_EXTRANET);

  $sql = db_select('user_entreprise', 'u')
         ->fields('u', array('id'))
         ->condition('id_drupal_user', $id_user_drupal, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  $id_entreprise = trim($data['id']);

  db_set_active();

  return $id_entreprise;
}

/**
 *   Renvoi  l'Id de l'entreprise associé à un utilisateur id entreprise
 *
 *   @param: $id_user - ID Utilisateur entreprise
 *
 */
function dgf_administration_users_etablissement($id_user_entreprise) {

  db_set_active(@DB_EXTRANET);

  // Renvoie l'ID entreprise associé à un utilisateur
  $sql = db_select('lien_user_entreprise_ref_esclave_entreprise', 'l')
         ->fields('l', array('id_ref_esclave_entreprise'))
         ->condition('id_user_entreprise', $id_user_entreprise, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  // TODO Prévoir le cas du multi établissement.

  $id_entreprise = trim($data['id_ref_esclave_entreprise']);

  db_set_active();

  return $id_entreprise;
}

/**
 *  Informations sur les entreprises Raison Social, Siret.
 *  @param: $id_entreprise - Id de l'entreprise
 *  @return: $company_infos() Retourne les Infos des établissements liés à un utilisateur
 *
 *
 */
function dgf_administration_users_get_etablissement_infos($id_entreprise) {
  db_set_active(@DB_SLAVE);

  // Ramène les infos entreprises
  $get_infos_sql = db_select('v_entreprises', 'infos')
                   ->fields('infos', array('id', 'raison_sociale', 'siret', 'est_valide', 'est_actif'))
                   ->condition('id' , $id_entreprise , '=')
                   ->execute();
  $company_infos = $get_infos_sql->fetchAll();

  db_set_active();

  return $company_infos;
}

/**
 *  Informations sur l'Adresse des entreprises Ville, Rue, Code postal etc...
 *  @param: $id_entreprise - Id de l'entreprise
 *  @return: $company_adress Retourne les infos sur l'adresse des établissements
 *
 */
function dgf_administration_users_get_etablissement_adresses($id_entreprise) {
  db_set_active(@DB_SLAVE);

  // Ramène les adresses entreprises
  $get_adress_sql = db_select('v_adresses_entreprises', 'adress')
                         ->fields('adress', array('rue' , 'complement_de_rue','complement_de_rue_2', 'code_postal', 'ville'))
                         ->condition('id_entreprise' , $id_entreprise , '=')
                         ->distinct()
                         ->execute();
  $company_adress = $get_adress_sql->fetchAll();

  db_set_active();

  return $company_adress;
}


/**
*  Renvoie l'ADEFIM Correspondant à un id_entreprise
*
*  @param:  $id_adefim - L'id ADEFIM
*  @return: Infos de l'ADEFIM
*
*/
function dgf_administration_users_get_adefim_id($id_entreprise) {
  db_set_active(@DB_SLAVE);

  $sql = db_select('v_adefims_entreprise', 'alias_adf')
         ->fields('alias_adf', array('id_adefim'))
         ->condition('id_entreprise', $id_entreprise, '=')
         ->execute();

  $data_adefim = $sql->fetchAssoc();

  // TODO GERER LE CAS MULTI-ADEFIM
  $id_adefim = trim($data_adefim['id_adefim']);

  db_set_active();

  return $id_adefim;
}

/**
 *  Informations sur les ADEFIMS
 *  @param:  $id_adefim - L'id ADEFIM
 *  @return: Infos de sur l'ADEFIM
 *
 */
 function dgf_administration_users_get_infos_adefim($id_adefim) {
   db_set_active(@DB_SLAVE);

  // Ramène les infos entreprises
  $get_infos_sql = db_select('v_adefims', 'adf_infos')
                   ->fields('adf_infos', array('raison_sociale', 'siret', 'telephone_principal', 'email'))
                   ->condition('id' , $id_adefim , '=')
                   ->execute();

  $adefims_infos = $get_infos_sql->fetch();

  db_set_active();

  return $adefims_infos;
}

/**
 *  Informations sur les ADEFIMS
 *  @param:  $id_adefim - L'id ADEFIM
 *  @return: Infos de sur l'ADEFIM
 *
 */
 function dgf_administration_users_get_contact_adefim($id_adefim) {
  db_set_active(@DB_SLAVE);

  // Ramène les infos entreprises
  $get_infos_sql = db_select('v_contacts_adefims', 'adf_contact')
                   ->fields('adf_contact', array('id_civilite', 'prenom', 'nom', 'email'))
                   ->condition('id_adefim' , $id_adefim , '=')
                   ->execute();

  $adefims_infos = $get_infos_sql->fetchAll();

  db_set_active();

  return $adefims_infos;
}

/**
 *  Rattaché un établissement à un ADEFIM
 *  @param: $id_entreprise - $id_adefim
 *
 */
function dgf_administration_users_link_adefim($id_entreprise, $id_adefim) {
  db_set_active(@DB_SLAVE);

  $today_date = date("y-m-d");

  $date = shared_sqlsrv_date($today_date);

  $sql_link = db_insert('liens_adefim_entreprise')
              ->fields(array(
                'creation_date' => $date,
                'creation_utilisateur' => $label_user_entreprise, // Nom utilisateur entreprise
                'modification_date' => $date,
                'modification_utilisateur' => $label_user_entreprise, // Nom utilisateur entreprise
                'est_actif' => '1',
                'est_valide' => '1',
                'id_adefim' => $id_adefim,
                'id_entreprise' => $id_entreprise,
                'identifiant_myopca' => NULL,
                ))
              ->execute();
  db_set_active();
}


function old_dgf_administration_delete_user($id_user, $id_user_entreprise){
  db_set_active(@DB_EXTRANET);

  $sql_delete_user_ref_entreprise = db_delete('lien_user_entreprise_ref_esclave_entreprise')
                                   ->condition('id_user_entreprise', $id_user_entreprise, '=')
                                   ->execute();

  $sql_delete_user_hab = db_delete('lien_drupal_user_habilitation')
         ->condition('id_drupal_user', $id_user, '=')
         ->execute();



  $sql_delete_user = db_delete('drupal_user')
         ->condition('id', $id_user, '=')
         ->execute();


  db_set_active();
}

/**
 *  Supprime un utilisateur de la base
 *
 *  SPECS: Cet écran permet de supprimer un utilisateur de manière logique.
 *  Son compte est bloqué et il ne pourra plus se connecter à l’extranet.
 *
 */
function dgf_administration_delete_user($id) {
  db_set_active(@DB_EXTRANET);

  $id_user_entreprise = shared_get_user_id_entreprise($id);

  if(isset($id_user_entreprise)){
    db_set_active(@DB_EXTRANET);
    // Supprime de la table lien user entreprise
    $delete_user_lien_entreprise = db_delete('lien_user_entreprise_ref_esclave_entreprise')
                                   ->condition('id_user_entreprise', $id_user_entreprise, '=')
                                   ->execute();
  }
  // Supprime les habilitations utilisateurs
  $delete_user_link = db_delete('lien_drupal_user_habilitation')
                      ->condition('id_drupal_user', $id, '=')
                      ->execute();


  // Supprime l'id user avec l'entreprise
  $delete_user_entreprise = db_delete('user_entreprise')
                           ->condition('id_drupal_user', $id, '=')
                           ->execute();
  // Supprime de l'extranet
  $delete_user = db_delete('drupal_user')
                 ->condition('id', $id, '=')
                 ->execute();

  // Supprime l'id entreprise
  // if(isset($id_user_entreprise)){
    // db_set_active(@DB_EXTRANET);
    // // Supprime de la table lien user entreprise
    // $delete_user_lien_entreprise = db_delete('lien_user_entreprise_ref_esclave_entreprise')
                                 // ->condition('id_user_entreprise', $id_user_entreprise, '=')
                                 // ->execute();
  // }
  // On bloque son compte
  // $id_user = $user->uid; // On recuppèrre l'uid de l'utilisateur
  // $block_user = db_update('users')
               // ->fields(array('status' => 0))
               // ->condition('uid', $id_user , '=')
               // ->execute();

  db_set_active();
 }


