<?php

function get_data_for_establishment_validation($id) {
  db_set_active(@DB_SLAVE);
  $query = db_select('v_entreprises', 'e');
  $query->leftJoin('v_adresses_entreprises', 'a', 'a.id_entreprise = e.id');
//   $query->leftJoin('v_contacts_entreprises', 'c', 'c.id_entreprise = e.id');
//   $query->leftJoin('v_fonctions', 'f', 'f.id = c.id_fonction');
  $query->fields('e', array(
      'siret', 'raison_sociale', 'telephone_principal', 'id_naf', 'id_nace', 'id'
    )
  );
  $query->fields('a', array(
      'numero_de_rue', 'rue', 'complement_de_rue',
      'complement_de_rue_2', 'code_postal', 'ville', 'id'
    )
  );
//   $query->fields('c', array(
//       'id_civilite', 'prenom',
//       'nom', 'email', 'id'
//     )
//   );
//   $query->fields('f', array('libelle'));
  $query->condition('e.est_valide', 0, '=');
  $query->condition('e.est_actif', 1, '=');
//   $query->condition('c.est_contact_principal', 1, '=');
  $query->condition('e.id', $id, '=');
  $datas = $query->execute()->fetchAll();
  db_set_active();

  return $datas;
}

// Fonction récupérant les anciennes valeurs de l'entreprise
// function get_info_for_establishment_validation($siret) {
//   db_set_active(@DB_SLAVE);
//   $query = db_select('v_entreprises', 'e');
//   $query->leftJoin('v_adresses_entreprises', 'a', 'a.id_entreprise = e.id');
//   $query->leftJoin('v_contacts_entreprises', 'c', 'c.id_entreprise = e.id');
//   $query->leftJoin('v_fonctions', 'f', 'f.id = c.id_fonction');
//   $query->fields('e', array(
//       'siret', 'raison_sociale', 'telephone_principal', 'id_naf', 'id_nace', 'id'
//     )
//   );
//   $query->fields('a', array(
//       'numero_de_rue', 'rue', 'complement_de_rue',
//       'complement_de_rue_2', 'code_postal', 'ville'
//     )
//   );
//   $query->fields('c', array(
//       'id_civilite', 'prenom',
//       'nom', 'email'
//     )
//   );
//   $query->fields('f', array('libelle'));
//   $query->condition('e.est_valide', 1, '=');
//   $query->condition('e.est_actif', 1, '=');
// //   $query->condition('c.est_contact_principal', 1, '=');
//   $query->condition('e.siret', $siret, '=');
//   $datas = $query->execute()->fetchAll();
//   db_set_active();

//   return $datas;
// }

function get_stored_proc_valid_establishment_submit($form, &$form_state) {
  $id = $form_state['storage']['id'];
//   $idContact = $form_state['storage']['id_contact'];
  $idAddress = $form_state['storage']['id_address'];
  db_set_active(@DB_SLAVE);

  global $user; // User Drupal

  // Procédure stockée
  $procedure = "EXEC sp_valider_modification_entreprise
  @user  = '$user->uid',
  @id_entreprise = '$id'
  ";
  $exec = db_query($procedure);

//   $procedure = "EXEC sp_valider_modification_contact_entreprise
//   @user  = '$user->uid',
//   @id_contact = '$idContact'
//   ";
//   $exec = db_query($procedure);

  $procedure = "EXEC sp_valider_modification_adresse_entreprise
  @user  = '$user->uid',
  @id_adresse_entreprise = '$idAddress'
  ";
  $exec = db_query($procedure);

  db_set_active();
  drupal_goto('/validation/etablissement/list/');
}

function get_stored_proc_refuse_establishment_submit($form, &$form_state) {
  $id = $form_state['storage']['id'];
//   $idContact = $form_state['storage']['id_contact'];
  $idAddress = $form_state['storage']['id_address'];

  db_set_active(@DB_SLAVE);

  global $user; // User Drupal

  // Procédure stockée
  $procedure = "EXEC sp_annuler_modification_entreprise
  @user  = '$user->uid',
  @id_entreprise = '$id'
  ";
  $exec = db_query($procedure);

//   $procedure = "EXEC sp_annuler_modification_contact_entreprise
//   @user  = '$user->uid',
//   @id_contact = '$idContact'
//   ";
//   $exec = db_query($procedure);

  $procedure = "EXEC sp_annuler_modification_adresse_entreprise
  @user  = '$user->uid',
  @id_adresse_entreprise = '$idAddress'
  ";
  $exec = db_query($procedure);


  db_set_active();
  drupal_goto('/validation/etablissement/list/');
}

function check_siret_already_exist($siret) {

  db_set_active(@DB_SLAVE);
  $query = db_select('v_entreprises', 'e');
  $query->fields('e', array('id', 'siret'));

  $query->condition('est_actif', 1, '=');
  $query->condition('est_valide', 1, '=');
  $query->condition('siret', $siret, '=');

  $result = $query->execute()->fetchCol('siret');
  db_set_active();
  if ($result) {
    return true;
  } else {
    return false;
  }
}

function get_all_adefim() {
  db_set_active(@DB_SLAVE);
  $query = db_select('v_adefims', 'a');
  $query->fields('a', array('raison_sociale'));

  $query->condition('est_actif', 1, '=');
  $query->condition('est_valide', 1, '=');

  $results = $query->execute()->fetchCol();
  db_set_active();
//   foreach ($results as $result) {
//     $result[] = $results->
//   }

  return $results;
}

function get_entreprise_adefim($id) {
  db_set_active(@DB_SLAVE);
  $query = db_select('v_adefims', 'a');
//   $query->leftJoin('v_adefims_entreprise', 'ae', 'ae.id_adefim = a.id');
  $query->fields('a', array('raison_sociale'));

//   $query->condition('ae.id_entreprise', $id, '=');
  $query->condition('a.est_actif', 1, '=');
  $query->condition('a.est_valide', 1, '=');

  $results = $query->execute()->fetchCol();
  db_set_active();
//   foreach ($results as $result) {
//     $result[] = $results->
//   }

  return $results;
}