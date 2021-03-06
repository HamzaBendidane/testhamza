<?php

function attestation_db_get_dgf($id_dgf) {
  db_set_active(@DB_EXTRANET);

  $result = db_select('dgf', 'd')
  ->fields('d')
  ->condition('id', $id_dgf, '=')
  ->condition('is_delete', 0, '=')
  ->execute()
  ->fetchAssoc();

  db_set_active();

  return $result;
}

function attestation_db_get_id_ref_esclave_entreprise($id_dgf) {
  db_set_active(@DB_EXTRANET);

  $query = db_select('lien_dgf_ref_esclave_entreprise' , 'lre')
  ->fields('lre', array('id_ref_esclave_entreprise'))
  ->condition('id_dgf', $id_dgf, '=')
  ->condition('is_delete', 0, '=')
  ->execute();
  $id_ref_esclave_entreprise = $query->fetchField();

  db_set_active();

  return trim($id_ref_esclave_entreprise);
}

function attestation_db_get_liste_adefims($id_ref_esclave_entreprise) {
  db_set_active(@DB_SLAVE);

  // Renvoie l'id ADEFIM  associé à une entreprise
  $query = db_select('v_adefims_entreprise' , 'vae');
  $query->join('v_adefims', 'va', 'va.id = vae.id_adefim');
  $query->fields('vae');
  $query->fields('va')
    ->condition('vae.id_entreprise', $id_ref_esclave_entreprise, '=');

  $adefims = $query->execute()->fetchAll();

  db_set_active();

  if (count($adefims) === 1) {
    return trim($adefims[0]->id_adefim);
  } else {
    $adefims_liste = array('Veuillez sélectionner votre ADEFIM de gestion');
    foreach ($adefims as $adefim) {
      $adefims_liste[trim($adefim->id)] = trim($adefim->raison_sociale);
    }

    return $adefims_liste;
  }
}

function attestation_db_get_adefim() {
  db_set_active(@DB_SLAVE);

  // Ramène les infos entreprises
  $adefims_sql = db_select('v_adefims', 'ad')
    ->fields('ad')
    ->condition('est_actif' , 1 , '=')
    ->condition('est_valide' , 1 , '=')
    ->execute();

  $results = $adefims_sql->fetchAll();

  $adefims = array('Veuillez sélectionner votre ADEFIM de gestion');
  foreach ($results as $adefim) {
    $adefims[trim($adefim->id)] = trim($adefim->raison_sociale);
  }
  db_set_active();

  return $adefims;
}

function attestation_db_update_dgf($id_dgf, $form_state) {
  global $user;

  db_set_active(@DB_EXTRANET);
  // On met à jour la table dgf
  db_update('dgf')
    ->fields(array(
      'id_ref_esclave_adefim'=> $form_state['values']['id_adefim'],
      'statut' => 2,
      'date_synthese' => shared_send_to_mssql_date(null, 'datetime'),
      'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_last_edit' => $user->uid,
  )
  )
  ->condition('id', $id_dgf, '=')
  ->execute();

  db_set_active();
}






function get_dgf_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT * FROM [dgf] where id = '$id_dgf'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}


function get_dgf_data_referenciel($id_ref_adefim) {

    db_set_active(@DB_SLAVE);

    $query = "SELECT raison_sociale as t_adefim FROM [adefims] where id = '$id_ref_adefim'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;

}


function update_dgf($data,$id)
{
    db_set_active(@DB_EXTRANET);
    $nid = db_update('dgf')
        ->fields(array(
            't_adefim' => $data['t_adefim'],
        ))
        ->condition('id_ref_esclave_adefim', $id, '=')->execute();

    db_set_active();
}


function get_entreprise_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT * FROM lien_dgf_ref_esclave_entreprise where id_dgf = '$id_dgf'";

    $result = db_query($query);

    $resultdata  = $result->fetchAll();
    db_set_active();

    return $resultdata;
}


function get_entreprise_data_referenciel($id_ref_entre) {

    db_set_active(@DB_SLAVE);

    $query = "SELECT
      [raison_sociale] as t_raison_sociale
      ,[siret] as t_siret
      ,[id_naf] as t_code_naf
      ,[id_convention_collective] as t_convention_collective
  FROM entreprises where id = '$id_ref_entre'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;

}


function update_entreprise($data,$id)
{

    db_set_active(@DB_EXTRANET);
    $nid = db_update('lien_dgf_ref_esclave_entreprise')
        ->fields($data)
        ->condition('id', $id, '=')->execute();

    db_set_active();
}