<?php

function get_data_for_establishment_management($id) {
  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
  $query->fields('e', array(
      'siret', 'raison_sociale', 'telephone_principal', 'id_naf', 'id_nace', 'id'
    )
  );
  $query->leftJoin('v_adresses_organismes_de_formation', 'a', 'a.id_organisme_de_formation = e.id');
  $query->fields('a', array(
      'numero_de_rue', 'rue', 'complement_de_rue',
      'complement_de_rue_2', 'code_postal', 'ville'
    )
  );
//   $query->leftJoin('v_contacts_organismes_de_formation', 'c');
//   $query->fields('c', array(
//       'id_civilite', 'prenom',
//       'nom', 'email'
//     )
//   );

  $query->condition('e.id', $id, '=');
//   $query->condition('est_actif_entreprise', 1, '=');
//   $query->condition('est_valide_entreprise', 0, '=');

//   $query->distinct('id')->orderBy('siret');

    // Executing query
    $datas = $query->execute()->fetchAll();
    // Fermeture de la connexion BDD
    db_set_active();

    return $datas;
}

function get_stored_proc_valid_establishment() {
  db_set_active(@DB_SLAVE);
  $id = arg(5);
//   $user = 1;

  global $user; // User Drupal

  // Procédure stockée
  $procedure = "EXEC sp_valider_modification_entreprise
  @user  = '$user->uid',
  @id_entreprise = '$id'
  ";

  // Execution de la procédure
  $exec = db_query($procedure);

  db_set_active();
}

function get_stored_proc_refuse_establishment() {
  db_set_active(@DB_SLAVE);
  $id = arg(5);
//   $user = 1;

  global $user; // User Drupal

  // Procédure stockée
  $procedure = "EXEC sp_annuler_modification_entreprise
  @user  = '$user->uid',
  @id = '$id'
  ";

  // Execution de la procédure
  $exec = db_query($procedure);

  db_set_active();
}

function check_siret_already_exist($siret) {
  db_set_active(@DB_SLAVE);
  $query = db_select('v_entreprises', 'e');
  $query->fields('e', array('id_entreprise', 'siret'));

  $query->condition('est_actif', 1, '=');
  $query->condition('est_valide', 1, '=');
  $query->condition('siret', $siret, '=');

  $result = $query->execute();
  db_set_active();
  if ($result) {
    return true;
  } else {
    return false;
  }
}