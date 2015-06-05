<?php

function establishments_management_siret_autocomplete() {
  $value = $_GET["term"];
  $results = request_for_of_auto_complete(@DB_SLAVE, 'v_entreprises',
      'siret', '%'.$value.'%');
}

function establishments_management_corporate_name_autocomplete() {
  $value = $_GET["term"];
  $results = request_for_of_auto_complete(@DB_SLAVE, 'v_entreprises',
      'raison_sociale', '%'.$value.'%');
}

function establishments_management_responsible_name_autocomplete() {
  $value = $_GET["term"];
  $columns = array('prenom_contact', 'nom_contact', );
  $results = request_for_of_auto_complete(@DB_SLAVE, 'v_entreprises',
      $columns, '%'.$value.'%');
}

/**
 * Functions return Json for auto-completing
 *
 *  @param $dbName, $table, $column
 *  $dbName : argument one
 *  $table : argument two
 *  $tableColumn : argument three
 *  $tableColumn : argument four
 */
function request_for_of_auto_complete($dbName, $dbTable, $tableColumn, $value) {
  // Connection à la table
  db_set_active($dbName);
  $query = db_select($dbTable, 't');

  // Pour le champ à valeur multiple (nom du responsable)
  if (is_array($tableColumn)) {
    $query->fields('t', array($tableColumn[0], $tableColumn[1])); 
    $query->condition(db_or()->condition($tableColumn[0], $value, 'LIKE')->condition($tableColumn[1], $value, 'LIKE'));
    $results = $query->execute()->fetchAll();
    // Fermeture de la connexion BDD
    db_set_active();

    $data = array();
    foreach ($results as $result) {
      // on supprime les espaces en fin de chaine (probleme avec SQL Server)
      $nom = rtrim($result->$tableColumn[0]);
      $prenom = rtrim($result->$tableColumn[1]);
      $data[] = $nom.' '. $prenom;
    }
    // Pour les champs à valeur unique (siret et raison sociale)
  } else {
    $query->fields('t', array($tableColumn));
    $query->condition($tableColumn, $value, 'LIKE');
    $results = $query->execute()->fetchAll();
    // Fermeture de la connexion BDD
    db_set_active();

    $data = array();
    foreach ($results as $result) {
      // on supprime les espaces en fin de chaine (probleme avec SQL Server)
      $data[] = rtrim($result->$tableColumn);
    }
  }
 
  drupal_json_output($data);
}

