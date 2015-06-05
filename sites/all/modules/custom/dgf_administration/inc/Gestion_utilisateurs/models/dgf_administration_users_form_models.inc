<?php

 /**
 *  Recherche dans la base des informations utilisateurs
 *
 */
function dgf_administration_users_query() {
  db_set_active(@DB_EXTRANET);

  $num_demande = $_POST['num_demand'];
  $nom         = $_POST['nom'];
  $prenom      = $_POST['prenom'];
  $email       = $_POST['email'];
  $siret       = $_POST['siret'];
  $is_valid    = $_POST['valid'];

  $search_fields = !empty($num_demande) || !empty($nom) || !empty($prenom) || !empty($email) || !empty($siret);
  $query = db_select('drupal_user' , 'u');

  if ($search_fields) {
    if (!empty($num_demande)) {
      $query->join('user_entreprise' , 'e' , 'u.id = e.id_drupal_user ' );
      $query->fields('e' , array('numero_demande'));
      $query->fields('u' , array('first_name', 'last_name', 'mail', 'id_user_drupal','id'))
           ->condition('numero_demande' , $num_demande , '=')
           ->condition('name', '%' . db_like($nom) . '%' , 'LIKE') // RG Contient le nom  //->condition('surname', '%' . db_like($prenom) , 'LIKE') // RG Commence par le nom
           ->condition('mail' , '%' . db_like($email) . '%' , 'LIKE');
    }
    else{
     $query->fields('u' , array('first_name', 'last_name',  'mail' , 'id_user_drupal','id')) // Select le nom, prénom et et email
           ->condition('name', '%' . db_like($nom) . '%' , 'LIKE') // RG Contient le nom
           ->condition('mail' ,  '%' . db_like($email) . '%' , 'LIKE'); // RG  ? //->condition('surname', '%' . db_like($prenom) , 'LIKE') // RG Commence par le nom
    }
  }
  else {
    $query->leftJoin('user_entreprise' , 'e' , 'u.id = e.id_drupal_user ' );
    $query->fields('e' , array('numero_demande')); // Numéro de demande
    $query->fields('u' , array('first_name', 'last_name', 'mail', 'id_user_drupal','id')); // Select le nom, prénom et et email  //$query->distinct('id_user_drupal');
    $query->orderBy('numero_demande', 'DESC');
  }
  $results =  $query->extend('PagerDefault')->limit(10)->execute();  // Pagination des résultats

  db_set_active();
  return $results;
}

/**
 *
 * Ramène toutes les données par défaut des utilisateurs de l'extranet.
 *
 *
 */
function dgf_administration_users_query_all() {

  db_set_active(@DB_EXTRANET);

  $query = db_select('drupal_user' , 'd');

  $query->distinct('last_name');

  $query->leftJoin('user_entreprise' , 'c' , 'd.id = c.id_drupal_user' );

  $query->fields('c' , array('numero_demande')); // Numéro de demande

  $query->fields('d' , array('first_name', 'last_name', 'mail', 'id_user_drupal','id')); // Select le nom, prénom et et email


  // Pagination des résultats
  $data =  $query->extend('PagerDefault')->limit(10)->execute();

  db_set_active();

  return $data;
}

/**
 *  Renvoie le numéro de demande l'ID USER
 *
 *  @param: $id User Entreprise = Id User Drupal
 *
 */
function dgf_administration_users_get_demand_number($id) {

  db_set_active(@DB_EXTRANET);

  // Renvoie le numéro de demande
  $sql = db_select('user_entreprise', 'e')
         ->fields('e' , array('numero_demande'))
         ->condition('id' , $id, '=')
         ->execute();

  $num_demande = $sql->fetchAssoc();

  db_set_active();

  return $num_demande;
}

/**
 *  Renvoie le numéro de siret de l'entreprise lié à un utilisateur entreprise
 *
 *  @param: $id entreprises
 *
 */
function dgf_administration_users_get_siret($id) {

  db_set_active(@DB_SLAVE);

  // Renvoie le numéro de demande
  $siret_entreprise = db_select('entreprises', 'e')
         ->fields('e' , array('siret'))
         ->condition('id' , $id, '=')
         ->execute();

  $numero_siret = $siret_entreprise->fetchAll();

  db_set_active();

  return $numero_siret;
}

/**
 *  Renvoie les  id utilisateurs et les id entreprises.
 *
 *
 */
function dgf_administration_users_get_ids() {

  db_set_active(@DB_EXTRANET);

  $sql = db_select('lien_user_entreprise_ref_esclave_entreprise', 'l')
         ->fields('l' , array('id_user_entreprise' , 'id_ref_esclave_entreprise'))
         ->execute();

  $ids = $sql->fetchAssoc();

  db_set_active();

  return $ids;
}

/**
 * Renvoie de l'id de l'entreprise associé à l'utilisateur
 *
 */
function dgf_administration_users_get_user_id_entreprise($id_user_entreprise) {
  db_set_active(@DB_EXTRANET);

  $sql = db_select('lien_user_entreprise_ref_esclave_entreprise', 'l')
         ->fields('l' , array('id_ref_esclave_entreprise'))
         ->condition('id_user_entreprise', $id_user_entreprise, '=')
         ->execute();

  $id = $sql->fetchAssoc();

  $id_ref_esclave_entreprise  = trim($id['id_ref_esclave_entreprise']);

  db_set_active();

  return $id_ref_esclave_entreprise;
}

/**
 *  Renvoie le siret et le statut associé à un utilisateur user_entreprise
 *
 *
 */
 function dgf_administration_users_get_entreprise_infos($id_ref_esclave_entreprise){
   db_set_active(@DB_SLAVE);

   $select_entreprises = db_select('entreprises', 'ref_ent')
                        ->fields('ref_ent', array('est_actif', 'est_valide', 'siret'))
                        ->condition('id', $id_ref_esclave_entreprise, '=')
                        ->execute();

   $data_entreprises = $select_entreprises->fetchAll();

   db_set_active();

   return $data_entreprises;
}