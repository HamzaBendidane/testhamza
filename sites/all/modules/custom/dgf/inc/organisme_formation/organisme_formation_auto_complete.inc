<?php

function dgf_of_siret_autocomplete() {
  $value = $_GET["term"];
  $results = organisme_formation_db_get_autocomplete($value.'%', 'siret');

  drupal_json_output($results);
}

function dgf_of_activity_number_autocomplete() {
  $value = $_GET["term"];
  $results = organisme_formation_db_get_autocomplete($value.'%', 'numero_de_declaration_existence');

  drupal_json_output($results);
}

function dgf_of_corporate_name_autocomplete() {
  $value = $_GET["term"];
  $results = organisme_formation_db_get_autocomplete('%'.$value.'%', 'raison_sociale');

  drupal_json_output($results);
}

function organisme_formation_db_get_autocomplete($value, $tableColumn) {
  db_set_active(@DB_SLAVE);

  $query = db_select('v_organismes_de_formation', 'vof');
  $query->leftJoin('v_adresses_organismes_de_formation','adr', "adr.id_organisme_de_formation = vof.id");
  $query->fields('vof', array('id', 'raison_sociale', 'siret', 'numero_de_declaration_existence',
      'tva_intracommunautaire', 'email'))
    ->fields('adr', array('numero_de_rue', 'rue', 'complement_de_rue', 'complement_de_rue_2', 'code_postal', 'ville'))
    ->condition("vof.".$tableColumn, $value, 'LIKE')
    ->condition('vof.est_actif', '1', '=');
  $query->distinct(true);

  $results = $query->execute()->fetchAll();

  $data = array();
  foreach ($results as $result) {
    $data[] = array(
        'value' => trim($result->$tableColumn),
        'label' => trim($result->$tableColumn),
        'data'  => $result,
    );
  }

  db_set_active();

  return $data;
}

function organisme_formation_db_get_contact_from_organisme_formation() {
  $id_organisme_formation = $_GET["id_organisme_formation"];

  db_set_active(@DB_SLAVE);

  $query = db_select('v_contacts_organismes_de_formation', 'vcof');
  $query->leftJoin('v_civilites', 'vci', 'vcof.id_civilite = vci.id');
  $query->fields('vcof', array('id', 'id_civilite', 'prenom', 'nom', 'email'));
  $query->fields('vci', array('libelle'));
  $query->condition('vcof.id_organisme_de_formation', $id_organisme_formation, '=');
  $query->condition('vcof.est_actif', '1', '=');

  $results = $query->execute()->fetchAll();

  $contacts = array();
  foreach ($results as $result) {
    $contacts[] = array(
        'id' => trim($result->id),
        'civilite' => trim($result->libelle),
        'prenom' => trim($result->prenom),
        'nom' => trim($result->nom),
        'email' => trim($result->email),
        'est_contact_principal' => $result->est_contact_principal,
    );
  }

  db_set_active();

  drupal_json_output($contacts);
}