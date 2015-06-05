<?php

function shared_db_get_title($list = false) {
  db_set_active(@DB_SLAVE);

  $results = db_select('v_civilites', 't')
    ->fields('t', array('id', 'libelle'))
    ->condition('est_actif', 1, '=')
    ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAll();
  foreach ($results as $result) {
    $return[trim($result->id)] = trim($result->libelle);
  }
  if ($list) {
    array_unshift($return, 'Veuillez choisir dans la liste');
  }

  db_set_active();
  return $return;
}

/**
 *  Execute un select dans la base de données.
 *  @param: $db - La base de données ,
 *          $table - La table cible,
 *          $fields - Le tableau des champs à ramener lors du select
 *
 *  @return: $data - Les données résulatats de la rêquete.
 *
 */
function shared_db_select($db, $table, $alias, $fields){
  db_set_active($db);

  $sql = db_select($table, $alias)
         ->fields($alias, $fields)
         ->execute();

  $data = $sql->fetchAll();

  db_set_active();

  return $data;
}

function shared_db_insert($db, $table,  $alias, $fields){
  db_set_active($db);

  $sql = db_insert($table, $alias)
         ->fields($alias, $fields)
         ->execute();

  $id = $sql->fetchAll();

  db_set_active();

  return $id;
}

function shared_db_update($db, $table,  $alias, $fields, $id_table, $id_to_update){
  db_set_active($db);

  $sql = db_insert($table)
         ->fields($alias, $fields)
         ->condition($id_table, $id_to_update, '=')
         ->execute();

  db_set_active();
}

/**
 *  Sauvegarde des habilitations utilisateurs
 *  @param: les habilitations utilisateurs, l'id utilisateur drupal
 *
 */
function shared_save_user_habilitations($user_habilitations, $id_drupal_user) {
 db_set_active(@DB_EXTRANET);
 //Supprime toutes les habilitations de l'utilisateur associé à l'id
 $sql_delete = db_delete('lien_drupal_user_habilitation')
               ->condition('id_drupal_user' , $id_drupal_user, '=')
               ->execute();

  // Sauvegarde les habilitations  // Vaudrait mieux faire un db_update : lien_drupal_user_habilitation
  foreach ($user_habilitations as $value) {
     if($value != 0) {
       $hab_sql = db_insert('lien_drupal_user_habilitation')
                ->fields(array(
                'id_drupal_user'     => $id_drupal_user,
                'id_habilitation'    => $value,
                ))
                ->execute();
    }
  }
  db_set_active();
}

/**
 *  Renvoie la liste des Adefims
 */
function shared_get_adefim() {

  db_set_active(@DB_SLAVE);

  $adefims = db_select('adefims' , 'adf')
             ->fields('adf')
             ->orderBy('raison_sociale')
             ->execute();

  $listes_adefims = $adefims->fetchAll();
  $adefims = array();
  foreach ($listes_adefims as $adefim) {
    $adefims[trim($adefim->id)] = trim($adefim->raison_sociale);
  }

  db_set_active();

  return $adefims;
}


/**
 *  Renvoie l'ADEFIM liée à une entreprise via son siret entreprise
 *  @param: $siret
 *  @return: l'ADEFIM de l'entreprise.
 */
function shared_get_adefim_from_siret($siret) {

  db_set_active(@DB_SLAVE);

  // Renvoie l'id entreprise
  $get_id_entreprise = db_select('entreprises', 'e')
         ->fields('e', array('id'))
         ->condition('siret' , $siret , '=')
         ->execute();

  $data_id_entreprise = $get_id_entreprise->fetchAssoc();

  $id_entreprise = trim($data_id_entreprise['id']);

  // Renvoie l'id ADEFIM  associé à une entreprise
  $query = db_select('liens_adefim_entreprise' , 'lae');
  $query->leftJoin('adefims', 'ade', 'ade.id = lae.id_adefim');
  $query->fields('lae', array('id_adefim'));
  $query->fields('ade', array('raison_sociale'));
  $query->condition('id_entreprise', $id_entreprise, '=');
  $query_liens_adefim_entreprise = $query->execute();

  $adefims = $query_liens_adefim_entreprise->fetchAll();

  db_set_active();

  return $adefims;
}


/**
 *  Renvoie l'id de l'utilisateur entreprise via l'id drupal
 *  @param: $id_user
 */
function shared_get_user_id_entreprise($id_user) {
  // Renvoie l'id de  l'utilisateur entreprise
  db_set_active(@DB_EXTRANET);

  $sql = db_select('user_entreprise', 'u')
         ->fields('u', array('id'))
         ->condition('id_drupal_user', $id_user, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  $id_user_entreprise = trim($data['id']);

  db_set_active();

  return $id_user_entreprise;
}

/**
 *  Ramène l'id de la table drupal_user
 */
function shared_get_drupal_user_id($email) {
  // Renvoie l'id de  l'utilisateur entreprise
  db_set_active(@DB_EXTRANET);

  $sql = db_select('drupal_user', 'u')
         ->fields('u', array('id'))
         ->condition('mail', $email, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  $id_drupal_user = trim($data['id']);

  db_set_active();

  return $id_drupal_user;
}

/**
 * Renvoie l'id de l'entreprise lié a l'utilisateur entreprise
 *
 */
function shared_get_id_entreprise($id_user_entreprise) {
  // Renvoie l'id de  l'utilisateur entreprise
  db_set_active(@DB_EXTRANET);

  $sql = db_select('lien_user_entreprise_ref_esclave_entreprise', 'l')
         ->fields('l', array('id_ref_esclave_entreprise'))
         ->condition('id_user_entreprise', $id_user_entreprise, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  $id_entreprise = trim($data['id']);

  db_set_active();

  return $id_entreprise;
}

/**
 *  Renvoi le siret via l'id entreprise
 *
 */
function shared_get_siret_entreprise($id_entreprise) {
  // Renvoie l'id de  l'utilisateur entreprise
  db_set_active(@DB_SLAVE);

  $sql = db_select('v_entreprises', 'v')
         ->fields('v', array('siret'))
         ->condition('id', $id_user_entreprise, '=')
         ->execute();

  $data = $sql->fetchAssoc();

  $id_entreprise = trim($data['id']);

  db_set_active();

  return $id_entreprise;
}


function organisme_formation_db_get_temp_dgf_form_organisme_formation($id_dgf) {
    // On récupère les informations de la table temp_dgf_form_organisme_formation
    db_set_active(@DB_EXTRANET);

    $result = db_select('temp_dgf_form_organisme_formation', 'temp_of')
        ->fields('temp_of')
        ->condition('id_dgf', $id_dgf, '=')
        ->condition('is_delete', 0, '=')
        ->execute()
        ->fetchAssoc();

    db_set_active();

    return $result;
}

function shared_db_functions_get_ref_esclave_entreprise() {
  global $user;

  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
  $query->fields('e');
  $query->condition('e.est_valide = ', 1, '=');
  $query->condition('e.est_actif = ', 1, '=');

  // ROLE 6 : DIRECTEUR ADEFIM / ROLE 7 : REFERENT ADEFIM / ROLE 8 : GESTIONNAIRE ADEFIM / ROLE 9 : CONSEILLER ADEFIM
  if (user_has_role(6) || user_has_role(7) || user_has_role(8) || user_has_role(9)) {
    if ($user->data['extranet_user']->entreprises) {
      $query->condition('e.id', array_keys($user->data['extranet_user']->entreprises), 'in');
    } else {
      db_set_active();
      return;
    }
  }
  // ROLE 10 : ADMIN ENTREPRISE / ROLE 11 : COLLABORATEUR ENTREPRISE
  if (user_has_role(10) || user_has_role(11)) {
    if ($user->data['extranet_user']->entreprises) {
      $query->condition('e.id', array_keys($user->data['extranet_user']->entreprises), 'in');
    } else {
      db_set_active();
      return;
    }
  }
  $query->orderBy('raison_sociale', 'asc');
  $results = $query->execute()->fetchAll();

  $entreprises = array();
  $entreprises[] = 'Veuillez choisir dans la liste';
  foreach ($results as $entreprise) {
    $entreprises[trim($entreprise->id)] = trim($entreprise->raison_sociale) . ' - ' . trim($entreprise->siret);
  }

  db_set_active();

  return $entreprises;
}

function shared_db_get_habilitation($id) {
  db_set_active(@DB_EXTRANET);

  $query = db_select('lien_drupal_user_habilitation' , 'duh');
  $query->leftJoin('habilitation', 'h', 'h.cle = duh.id_habilitation');
  $query->fields('duh')
  ->fields('h')
  ->condition('id_drupal_user', $id, '=');
  $result = $query->execute();
  $habilitations = $result->fetchAll();

  $habilitationArray = array();
  foreach ($habilitations as $hab) {
    $habilitationArray[trim($hab->cle)] = $hab;
  }

  db_set_active();

  return $habilitationArray;
}

function shared_db_get_entreprise_data($id_entreprise) {
  db_set_active(@DB_SLAVE);

  // Ramène les infos entreprises
  $query = db_select('v_entreprises', 've');
  $query->innerJoin('v_adresses_entreprises', 'vae', 'vae.id_entreprise = ve.id');
  $query->fields('ve', array('id', 'raison_sociale', 'siret', 'est_valide', 'est_actif'));
  $query->fields('vae', array('numero_de_rue', 'rue', 'complement_de_rue', 'code_postal', 'ville'));
  $query->condition('ve.id' , $id_entreprise , '=');
  $query->range(0, 1);
  $get_infos_sql = $query->execute();
  $company_infos = $get_infos_sql->fetch();

  db_set_active();

  return $company_infos;
}
