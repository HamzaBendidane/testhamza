<?php

function tuteur_db_insert_temp_dgf_form_tuteur($form_data, $id_ref_esclave_salarie) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $query = db_insert('temp_dgf_form_tuteur')
    ->fields(array(
        'id_dgf' => intval($form_data['values']['id_dgf']),
        'id_ref_esclave_salarie' => $id_ref_esclave_salarie,
        'id_ref_esclave_entreprise' => $form_data['values']['etablishment'],
        'id_ref_diplome' => $form_data['values']['dernier_diplome'] ? $form_data['values']['dernier_diplome'] : null,
        'nb_salarie_encadre' => $form_data['values']['nb_salarie'],
        'emploi' => $form_data['values']['emploi_occupe'],
        'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
        'id_user_creation' => $user->uid,
        'is_delete' => 0,
        'telephone' => $form_data['values']['telephone'],
        'email' => $form_data['values']['email'],
  ));

  $id_form_formation = $query->execute();

  db_set_active();

  return $id_form_formation;
}

function tuteur_db_update_temp_dgf_form_tuteur($form_data, $id_ref_esclave_salarie) {
  global $user;

  db_set_active(@DB_EXTRANET);
  $query = db_update('temp_dgf_form_tuteur')
  ->fields(array(
      'id_dgf' => intval($form_data['values']['id_dgf']),
      'id_ref_esclave_salarie' => $id_ref_esclave_salarie,
      'id_ref_esclave_entreprise' => $form_data['values']['etablishment'],
      'id_ref_diplome' =>  $form_data['values']['dernier_diplome'] ? $form_data['values']['dernier_diplome'] : null,
      'nb_salarie_encadre' => $form_data['values']['nb_salarie'],
      'emploi' => $form_data['values']['emploi_occupe'],
      'formation_tuteur' => $form_data['values']['beneficier'] ? 1 : 0,
      'date_formation' => $form_data['values']['date_formation'] ?
        shared_send_to_mssql_date($form_data['values']['date_formation']) : null,
      'duree_formation' => $form_data['values']['duree_formation'] ? $form_data['values']['duree_formation'] : null,
      'nom_organisme' => $form_data['values']['nom_organisme'],
      'certif_role_tuteur' => !$form_data['values']['certifier']['A été informé sur son rôle de tuteur'] ? false : true,
      'certif_deux_ans_exp' => !$form_data['values']['certifier']['Bénéficie de plus de 2 ans d\'ancienneté'] ? false : true,
      'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_last_edit' => $user->uid,
      'is_delete' => 0,
      'telephone' => $form_data['values']['telephone'],
      'email' => $form_data['values']['email'],
  ))
  ->condition('id', $form_data['values']['id_dgf_tuteur'], '=');

  $id_form_formation = $query->execute();

  db_set_active();

  return $id_form_formation;
}

function tuteur_get_ref_esclave_entreprise() {
  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
  $query->fields('e');
  $query->condition('e.est_valide = ', 1, '=');
  $query->condition('e.est_actif = ', 1, '=');
  $entreprises = $query->execute()->fetchAll();

  $entrepriseArray = array();
  $entrepriseArray[] = 'Veuillez choisir dans la liste';
  foreach ($entreprises as $entreprise) {
    $entrepriseArray[trim($entreprise->id)] = trim($entreprise->siret) . ' - ' . trim($entreprise->raison_sociale);
  }

  db_set_active();

  return $entrepriseArray;
}

/**
 * Récupère les informations concernant le tueur
 * @return $result
 */
function tuteur_db_get_temp_dgf_form_tuteur($id_dgf) {
  db_set_active(@DB_EXTRANET);

  $result = db_select('temp_dgf_form_tuteur', 't')
    ->fields('t')
    ->condition('id_dgf', $id_dgf, '=')
    ->condition('is_delete', 0, '=')
    ->execute()
    ->fetchAssoc();

  db_set_active();

  return $result;
}

/**
 * Récupère les informations concernant le salarié dans ref esclave
 * @return $result
 */
function tuteur_db_get_v_salarie($id) {
  db_set_active(@DB_SLAVE);

  $result = db_select('v_salaries', 'sa')
  ->fields('sa')
  ->condition('id', $id, '=')
  ->condition('est_actif', 1, '=')
  ->condition('est_valide', 1, '=')
  ->execute()
  ->fetchAssoc();

  db_set_active();

  return $result;
}

function check_is_intern_training($id_dgf) {
  db_set_active(@DB_EXTRANET);

  $query = db_select('temp_dgf_form_formation', 'dff')
  ->fields('dff', array('formation_interne'))
  ->condition('dff.formation_interne', 1 , '=')
  ->condition('dff.id_dgf', $id_dgf , '=');
  $result = $query->execute()->fetchCol();

  db_set_active();

  return $result;
}


function get_tuteur_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT
	tut.id_dgf as id_dgf,
	tut.nom_organisme as t_etablissement,
	tut.telephone as t_telephone,
	tut.email as t_email,
	tut.emploi as t_emploi,
	dipl.label as t_diplome,
	tut.nb_salarie_encadre as t_nb_salarie_encadre,
	tut.formation_tuteur as t_formation_tuteur,
	tut.date_formation as t_date_formation,
	tut.duree_formation as t_duree_formation,
	tut.nom_organisme as t_nom_organisme,
	tut.certif_role_tuteur as t_certif_role_tuteur,
	tut.date_creation as date_creation,
	tut.id_user_creation as id_user_creation,
	tut.date_last_edit as date_last_edit,
	tut.id_user_last_edit as id_user_last_edit,
	tut.date_delete as date_delete,
	tut.id_user_delete as id_user_delete,
	tut.is_delete as is_delete,
	tut.id_ref_esclave_salarie

  FROM [temp_dgf_form_tuteur] tut
  left join ref_diplome dipl on dipl.id = tut.id_ref_diplome
  where  tut.id_dgf = '$id_dgf'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}


function get_tuteur_data_referenciel($id_ref_esclave_salarie) {
    db_set_active(@DB_SLAVE);

    $query = "SELECT
  sal.date_de_naissance as t_date_naissance,
  sal.nom as t_nom,
  sal.prenom as t_prenom
  FROM salaries sal
  where sal.id = '$id_ref_esclave_salarie'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}

function tuteur_convertParam($key,$data){

    unset ($data['id_ref_esclave_salarie']);
    return $data;
}

function insert_tuteur($data)
{
    db_set_active(@DB_EXTRANET);
    $nid = db_insert('dgf_form_tuteur');

    $data = tuteur_convertParam('',$data);

    $nid->fields($data);

    $nid->execute();
    db_set_active();
}

