<?php

function contrat_db_get_temp_dgf_form_salarie($id_dgf) {
  db_set_active(@DB_EXTRANET);
  $result = db_select('temp_dgf_form_contrat', 'sa')
    ->fields('sa')
    ->condition('id_dgf', $id_dgf, '=')
    ->condition('is_delete', 0, '=')
    ->execute()
    ->fetchAssoc();

  db_set_active();

  return $result;
}

function contrat_db_get_type_de_contrat() {
  db_set_active(@DB_SLAVE);

  $results = db_select('types_de_contrats', 't')
    ->fields('t', array('id', 'libelle'))
    ->condition('est_actif', 1, '=')
    ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAllKeyed();

  // Sauvegarde en session
  array_unshift($results, 'Veuillez choisir dans la liste');

  db_set_active();

  return $results;
}

function contrat_db_get_convention_collective() {
  db_set_active(@DB_SLAVE);

  $results = db_select('conventions_collectives', 'cc')
    ->fields('cc', array('id', 'libelle'))
    ->condition('est_actif', 1, '=')
    ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAll();

  $convention_collective = array();
  foreach ($results as $result) {
    $convention_collective[trim($result->id)] = trim($result->libelle);
  }

  // Sauvegarde en session
  array_unshift($convention_collective, 'Veuillez choisir dans la liste');

  db_set_active();

  return $convention_collective;
}

function contrat_db_get_age_salarie($id_dgf) {
  db_set_active(@DB_EXTRANET);
  $id_salarie = db_select('temp_dgf_form_salarie', 'sa')
    ->fields('sa', array('id_ref_esclave_salarie'))
    ->condition('id_dgf', $id_dgf, '=')
    ->condition('is_delete', 0, '=')
    ->execute()
    ->fetchColumn();

  db_set_active(@DB_SLAVE);

  $date_de_naissance = db_select('v_salaries', 'sa')
    ->fields('sa', array('date_de_naissance'))
    ->condition('id', $id_salarie, '=')
    ->condition('est_actif', 1, '=')
    ->execute()
    ->fetchColumn();

  $age = calculate_age(shared_parse_mssql_datetime($date_de_naissance));

  db_set_active();

  return $age;
}

function contrat_db_get_minimum_salaire_salarie($id_dgf, $age) {
  db_set_active(@DB_EXTRANET);
  $id_ref_diplome = db_select('temp_dgf_form_salarie', 'sa')
    ->fields('sa', array('id_ref_diplome'))
    ->condition('id_dgf', $id_dgf, '=')
    ->condition('is_delete', 0, '=')
    ->execute()
    ->fetchColumn();

  db_set_active();

  if ($age >= 26) {
    return @SMIC;
  } else if ($age >= 21 && $age < 26) {
    if ($id_ref_diplome >= 41 && $id_ref_diplome <= 60) {
      return \number_format(70 * @SMIC /100, 2, '.', '');
    } else {
      return \number_format(80 * @SMIC /100, 2, '.', '');
    }
  } else {
    if ($id_ref_diplome >= 41 && $id_ref_diplome <= 60) {
      return \number_format(55 * @SMIC /100, 2, '.', '');
    } else {
      return \number_format(65 * @SMIC /100, 2, '.', '');
    }
  }
}

function calculate_age($date_de_naissance) {
  if ($date_de_naissance) {
    $today = new DateTime('today');
    return $date_de_naissance->diff($today)->y;
  } else {
    return;
  }
}

function contrat_db_insert_temp_dgf_form_contrat($form_data) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $query = db_insert(@TABLE_TEMP_CONTRAT)
  ->fields(array(
      'id_dgf' => intval($form_data['values']['id_dgf']),
      'id_ref_type_contrat' => $form_data['values']['nature'],
      'id_ref_esclave_type_contrat' => trim($form_data['values']['type']),
      'id_ref_esclave_convention_collective' => trim($form_data['values']['collective_convention']),
      'id_ref_groupe' => $form_data['values']['group'] ? $form_data['values']['group'] : null,
      'date_debut' => shared_send_to_mssql_date($form_data['values']['date_begin']),
      'date_fin' => shared_send_to_mssql_date($form_data['values']['date_end']),
      'duree_contrat_mois' => $form_data['values']['training_duration'],
      'duree_essai_jour' => $form_data['values']['test_period'],
      'duree_hebdo_travail_heure' => $form_data['values']['weekly_hour'],
      'duree_hebdo_travail_minute' => $form_data['values']['weekly_minute'],
      'niveau' => $form_data['values']['niveau'] ? $form_data['values']['niveau'] : null,
      'coefficient' => $form_data['values']['coefficient'] ? $form_data['values']['coefficient'] : null,
      'salaire_brut_mensuel' => floatval($form_data['values']['monthly_gross_pay']),
      'emploi_occupe' => $form_data['values']['position_held'],
      'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_creation' => $user->uid,
  ));
  $query->execute();

  db_set_active();
}

function contrat_db_update_temp_dgf_form_contrat($form_data) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $query = db_update(@TABLE_TEMP_CONTRAT)
  ->fields(array(
      'id_ref_type_contrat' => $form_data['values']['nature'],
      'id_ref_esclave_type_contrat' => trim($form_data['values']['type']),
      'id_ref_esclave_convention_collective' => trim($form_data['values']['collective_convention']),
      'id_ref_groupe' => $form_data['values']['group'] ? $form_data['values']['group'] : null,
      'date_debut' => shared_send_to_mssql_date($form_data['values']['date_begin']),
      'date_fin' => shared_send_to_mssql_date($form_data['values']['date_end']),
      'duree_contrat_mois' => $form_data['values']['training_duration'],
      'duree_essai_jour' => $form_data['values']['test_period'],
      'duree_hebdo_travail_heure' => $form_data['values']['weekly_hour'],
      'duree_hebdo_travail_minute' => $form_data['values']['weekly_minute'],
      'niveau' => $form_data['values']['niveau'] ? $form_data['values']['niveau'] : null,
      'coefficient' => $form_data['values']['coefficient'] ? $form_data['values']['coefficient'] : null,
      'salaire_brut_mensuel' => floatval($form_data['values']['monthly_gross_pay']),
      'emploi_occupe' => $form_data['values']['position_held'],
      'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_last_edit' => $user->uid,
  ))
  ->condition('id', $form_data['values']['id_dgf_contrat'], '=');
  db_set_active();
  $query->execute();

  db_set_active();

}


function get_contrat_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT
  contr.id_dgf as id_dgf,
  contr.id_ref_type_contrat as t_type_contrat,
  contr.date_debut as t_date_debut,
  contr.date_fin as t_date_fin,
  contr.duree_contrat_mois as t_duree_contrat_mois,
  contr.duree_essai_jour as t_duree_essai_jour,
  contr.duree_hebdo_travail_heure as t_duree_hebdo_travail_heure,
  contr.duree_hebdo_travail_minute as t_duree_hebdo_travail_minute,
  contr.coefficient as t_coefficient,
  contr.salaire_brut_mensuel as t_salaire_brut_mensuel,
  contr.emploi_occupe as t_emploi_occupe,
  contr.date_creation as date_creation,
  contr.id_user_creation as id_user_creation,
  contr.date_last_edit as date_last_edit,
  contr.id_user_last_edit as id_user_last_edit,
  contr.date_delete as date_delete,
  contr.id_user_delete as id_user_delete,
  contr.is_delete as is_delete,
  grou.label as t_groupe,
   contr.id_ref_esclave_type_contrat,
   contr.id_ref_esclave_convention_collective

  FROM [temp_dgf_form_contrat] contr
  left join ref_groupe grou on grou.id = contr.id_ref_groupe
  where contr.id_dgf = '$id_dgf'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}


function get_contrat_data_referenciel($id_ref_esclave_type_contrat,$id_ref_esclave_convention_collective) {
    db_set_active(@DB_SLAVE);

    $query = "SELECT
  conv.libelle as t_convention_collective,
  typeesc.libelle as t_type_contrat_pro
  FROM types_de_contrats typeesc
  left join conventions_collectives conv on conv.id = '$id_ref_esclave_convention_collective'
  where typeesc.id = '$id_ref_esclave_type_contrat'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}

function contrat_convertParam($key,$data){

    unset ($data['id_ref_esclave_type_contrat']);
    unset ($data['id_ref_esclave_convention_collective']);
    return $data;
}

function insert_contrat($data)
{
    db_set_active(@DB_EXTRANET);
    $nid = db_insert('dgf_form_contrat');

    $data = contrat_convertParam('',$data);

    $nid->fields($data);

    $nid->execute();
    db_set_active();
}
