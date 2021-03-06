<?php

function organisme_formation_db_sp_sauver_organisme_de_formation($form_state) {
  global $user;

  $corporate_name = $form_state['values']['corporate_name'];
  $phone_number = $form_state['values']['phone_number'];
  $email = $form_state['values']['email'];
  $activity_number = $form_state['values']['activity_number'];
  $tva_number = $form_state['values']['tva_number'];
  $siret_number = $form_state['values']['siret_number'];

  // On contrôle avant de lancer la proc s'il existe un OF avec un siret correspondant à celui saisi
  // la fonction get_siret_if_already_exist renvoie false si siret non trouvé et l'id si le siret existe
  if (get_id_if_siret_already_exist($siret_number)) {
    // Si l'id existe la proc lance un update
    $id_organisme_formation_returned = get_id_if_siret_already_exist($siret_number);
    $id_organisme_formation = trim($id_organisme_formation_returned);
    $sp_sauver_organisme_de_formation = " EXEC sp_sauver_organisme_de_formation
    @user  = '$user->uid',
    @id = N'$id_organisme_formation',
    @raison_sociale = N'$corporate_name',
    @siret = N'$siret_number',
    @telephone_principal = N'$phone_number',
    @telephone_secondaire = NULL,
    @fax = NULL,
    @site_web = NULL,
    @email = N'$email',
    @numero_de_declaration_existence = N'$activity_number',
    @date_de_declaration_existence = null,
    @tva_intracommunautaire = N'$tva_number',
    @id_type_organisme = NULL,
    @id_departement = NULL,
    @id_taux_de_tva = NULL
    ";
  } else {
    // Si l'id n'existe pas la proc lance un create
    $sp_sauver_organisme_de_formation = " EXEC sp_sauver_organisme_de_formation
    @user  = '$user->uid',
    @id = null,
    @raison_sociale = N'$corporate_name',
    @siret = N'$siret_number',
    @telephone_principal = N'$phone_number',
    @telephone_secondaire = NULL,
    @fax = NULL,
    @site_web = NULL,
    @email = N'$email',
    @numero_de_declaration_existence = N'$activity_number',
    @date_de_declaration_existence = null,
    @tva_intracommunautaire = N'$tva_number',
    @id_type_organisme = NULL,
    @id_departement = NULL,
    @id_taux_de_tva = NULL
    ";
  }

  // Execution de la procédure
  db_set_active(@DB_SLAVE);
  $result = db_query($sp_sauver_organisme_de_formation);
  $id_ref_esclave_organisme_de_formation = $result->fetchField();

  db_set_active();

  return $id_ref_esclave_organisme_de_formation;
}

function organisme_formation_db_create_temp_dgf_form_organisme_formation($id_dgf,
    $id_ref_esclave_organisme_de_formation, $id_ref_esclave_contact_organisme_de_formation, $form_state) {
  global $user;

  // Données  à sauvegarder - fin de la partie contact
  $pedagogical_cost = ($form_state['values']['pedagogical_cost']) ? $form_state['values']['pedagogical_cost'] : NULL;
  $preformativ_eval = ($form_state['values']['eval_pre_formative']) ? $form_state['values']['eval_pre_formative'] : NULL;
  $certification_passing = ($form_state['values']['certification_passing']) ? $form_state['values']['certification_passing'] : NULL;
  $direct_payment = ($form_state['values']['direct_payment']) ? $form_state['values']['direct_payment'] : 0;
  $data =  array(
      'id_dgf' => $id_dgf,
      'id_ref_esclave_organisme_formation' => $id_ref_esclave_organisme_de_formation,
      'id_ref_esclave_contacts_organisme_formation' => $id_ref_esclave_contact_organisme_de_formation,
      'cout_pedagogique' => $pedagogical_cost,
      'evaluation_preformative' =>$preformativ_eval,
      'passage_certification' => $certification_passing,
      'paiement_direct' => $direct_payment,
      'date_creation' => shared_send_to_mssql_date(null,'datetime'),
      'id_user_creation' => $user->uid,
  );

  db_set_active(@DB_EXTRANET);
  // DB Save
  $sql_insert = db_insert('temp_dgf_form_organisme_formation')
  ->fields($data)
  ->execute();

  db_set_active();
}

function organisme_formation_db_update_temp_dgf_form_organisme_formation($id_dgf, $id_ref_esclave_organisme_de_formation,
    $id_ref_esclave_contact_organisme_de_formation, $form_state, $temp_dgf_form_organisme_formation) {
  global $user;

  // Données  à sauvegarder - fin de la partie contact
  $pedagogical_cost = ($form_state['values']['pedagogical_cost']) ? $form_state['values']['pedagogical_cost'] : NULL;
  $preformativ_eval = ($form_state['values']['eval_pre_formative']) ? $form_state['values']['eval_pre_formative'] : NULL;
  $certification_passing = ($form_state['values']['certification_passing']) ? $form_state['values']['certification_passing'] : NULL;
  $direct_payment = ($form_state['values']['direct_payment']) ? $form_state['values']['direct_payment'] : 0;
  $data =  array(
      'id_ref_esclave_organisme_formation' => $id_ref_esclave_organisme_de_formation,
      'id_ref_esclave_contacts_organisme_formation' => $id_ref_esclave_contact_organisme_de_formation,
      'cout_pedagogique' => $pedagogical_cost,
      'evaluation_preformative' =>$preformativ_eval,
      'passage_certification' => $certification_passing,
      'paiement_direct' => $direct_payment,
      'date_last_edit' => shared_send_to_mssql_date(null,'datetime'),
      'id_user_last_edit' => $user->uid,
  );

  db_set_active(@DB_EXTRANET);
  // DB Save
  $sql_insert = db_update('temp_dgf_form_organisme_formation')
  ->fields($data)
  ->condition('id', $temp_dgf_form_organisme_formation['id'], '=')
  ->execute();
  db_set_active();
}

function organisme_formation_db_sp_sauver_adresse_organisme_de_formation($form_state,
    $id_ref_esclave_organisme_de_formation) {
  global $user;

  db_set_active(@DB_SLAVE);

  $street_number = $form_state['values']['street_number'];
  $street_name = $form_state['values']['street_name'];
  $address_complement = $form_state['values']['address_complement'];
  $zip_code = $form_state['values']['zip_code'];
  $city = $form_state['values']['city'];
  $sp_sauver_adresse_organisme_de_formation = "EXEC sp_sauver_adresse_organisme_de_formation
    @user  = '$user->uid',
    @id = null,
    @id_type_adresse = NULL,
    @numero_de_rue = N'$street_number',
    @rue = N'$street_name',
    @complement_de_rue = N'$address_complement',
    @complement_de_rue_2 = NULL,
    @code_postal = N'$zip_code',
    @ville = N'$city',
    @id_region = NULL,
    @id_organisme_de_formation = N'$id_ref_esclave_organisme_de_formation'
  ";

  // Execution de la procédure
  $result = db_query($sp_sauver_adresse_organisme_de_formation);
  $id_ref_esclave_adresse_organisme_de_formation = $result->fetchField();

  return $id_ref_esclave_adresse_organisme_de_formation;
}

function organisme_formation_db_sp_sauver_contact_organisme_de_formation( $form_state,
    $id_ref_esclave_organisme_de_formation, $type = 'new') {
  global $user;

  db_set_active(@DB_SLAVE);

  if ($type == 'new') {
    $title = $form_state['values']['new_contact_title'];
    $firstname = $form_state['values']['new_contact_firstname'];
    $lastname = $form_state['values']['new_contact_lastname'];
    $phone = $form_state['values']['new_contact_phone'];
    $mail = $form_state['values']['new_contact_mail'];
    $fonction = $form_state['values']['new_contact_fonction'];
  } else {
    $title = $form_state['values']['modal_contact_title'];
    $firstname = $form_state['values']['modal_contact_firstname'];
    $lastname = $form_state['values']['modal_contact_lastname'];
    $phone = $form_state['values']['modal_contact_phone'];
    $mail = $form_state['values']['modal_contact_mail'];
    $fonction = $form_state['values']['modal_contact_fonction'];
  }
  $sp_sauver_contact_organisme_de_formation = "EXEC sp_sauver_contact_organisme_de_formation
    @user  = '$user->uid',
    @id = null,
    @id_organisme_de_formation = '$id_ref_esclave_organisme_de_formation',
    @id_civilite = '$title',
    @prenom = '$firstname',
    @nom = '$lastname',
    @telephone = '$phone',
    @fax = NULL,
    @email = '$mail',
    @id_fonction = '$fonction',
    @est_contact_principal = 0
  ";

  // Execution de la procédure
  $result = db_query($sp_sauver_contact_organisme_de_formation);
  $id_ref_esclave_contact_organisme_de_formation = $result->fetchField();

  return $id_ref_esclave_contact_organisme_de_formation;
}

function organisme_formation_db_get_v_organisme_formation($id_organisme_formation) {
  // On récupère les informations de la table v_organismes_de_formation
  db_set_active(@DB_SLAVE);

  $result = db_select('v_organismes_de_formation', 'vof')
    ->fields('vof')
    ->condition('id', $id_organisme_formation, '=')
    ->condition('est_actif', 1, '=')
//     ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAssoc();

  db_set_active();

  return $result;
}

function organisme_formation_db_get_v_adresse_organisme_formation($id_organisme_formation) {
  // On récupère les informations de la table v_adresses_organismes_de_formation
  db_set_active(@DB_SLAVE);

  $result = db_select('v_adresses_organismes_de_formation', 'vaof')
  ->fields('vaof')
  ->condition('id_organisme_de_formation', $id_organisme_formation, '=')
  ->condition('est_actif', 1, '=')
  //     ->condition('est_valide', 1, '=')
  ->execute()
  ->fetchAssoc();

  db_set_active();

  return $result;
}

function organisme_formation_db_get_v_contact_organisme_formation($id_contact_organisme_formation) {
  // On récupère les informations de la table v_contacts_organismes_de_formation
  db_set_active(@DB_SLAVE);

  $result = db_select('v_contacts_organismes_de_formation', 'vcof')
    ->fields('vcof')
    ->condition('id', $id_contact_organisme_formation, '=')
    ->condition('est_actif', 1, '=')
//     ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAssoc();

  db_set_active();

  return $result;
}

function organisme_formation_db_get_title_contact() {
  db_set_active(@DB_SLAVE);

  $results = db_select('v_civilites', 't')
  ->fields('t', array('id', 'libelle'))
  ->condition('est_actif', 1, '=')
  ->condition('est_valide', 1, '=')
  ->execute()
  ->fetchAll();
  foreach ($results as $result) {
    $return[$result->id] = $result->libelle;
  }
  array_unshift($return, 'Veuillez choisir dans la liste');

  db_set_active();
  return $return;
}

function organisme_formation_db_get_function_contact() {
  db_set_active(@DB_SLAVE);
  $results = db_select('v_fonctions', 't')
    ->fields('t', array('id', 'libelle'))
    ->condition('est_actif', 1, '=')
    ->condition('est_valide', 1, '=')
    ->execute()
    ->fetchAll();

  foreach ($results as $result) {
    $return[$result->id] = $result->libelle;
  }
  array_unshift($return, 'Veuillez choisir dans la liste');
  db_set_active();
  return $return;
}

function organisme_formation_db_get_contact_select($siret) {
  db_set_active(@DB_SLAVE);

  $query = db_select('v_contacts_organismes_de_formation', 'vcof');
  $query->leftJoin('v_civilites', 'vci', 'vcof.id_civilite = vci.id');
  $query->fields('vcof', array('id', 'id_civilite', 'prenom', 'nom', 'email'));
  $query->fields('vci', array('libelle'));
  $query->condition('vcof.siret_organisme_de_formation', $siret, '=');
  $query->condition('vcof.est_actif', '1', '=');
  $results = $query->execute()->fetchAll();

  $contacts = array();
  foreach ($results as $result) {
    $contacts[trim($result->id)] = trim($result->libelle).' '.trim($result->prenom).' '.trim($result->nom)
      .' ('.trim($result->email) . ')';
  }
  db_set_active();

  return $contacts;
}

function organisme_formation_db_check_contact_infos() {
  $idContact = $_GET["contact"];

  // On récupère les informations de la table contacts_organismes_de_formation
  db_set_active(@DB_SLAVE);

  $result = db_select('contacts_organismes_de_formation', 't')
  ->fields('t', array('email', 'id_fonction'))
  ->condition('id', $idContact, '=')
  ->condition('est_actif', 1, '=')
  ->condition('est_valide', 1, '=')
  ->execute()
  ->fetchAll();

  db_set_active();

  $result[0]->email = trim($result[0]->email);
  $result[0]->id_fonction = trim($result[0]->id_fonction);
  drupal_json_output($result[0]);
}

function get_id_if_siret_already_exist($siret) {

  db_set_active(@DB_SLAVE);
  $query = db_select('v_organismes_de_formation', 'e');
  $query->fields('e', array('id', 'siret'));

  $query->condition('est_actif', 1, '=');
  $query->condition('siret', $siret, '=');

  $result = $query->execute()->fetchCol();
  db_set_active();

  if ($result && $result[0]) {
    return $result[0];
  } else {
    return false;
  }
}






function get_organisme_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT
  formorga.id_dgf as id_dgf,
  formorga.cout_pedagogique as t_cout_pedagogique,
  formorga.evaluation_preformative as t_evaluation_preformative,
  formorga.passage_certification as t_passage_certification,
  formorga.paiement_direct as t_paiement_direct,
  formorga.cout_prestation as t_cout_prestation,
  formorga.ratio_cout_duree as t_ratio_cout_duree,
  formorga.date_creation as date_creation,
  formorga.id_user_creation as id_user_creation,
  formorga.date_last_edit as date_last_edit,
  formorga.id_user_last_edit as id_user_last_edit,
  formorga.date_delete as date_delete,
  formorga.id_user_delete as id_user_delete,
  formorga.is_delete as is_delete,

  formorga.id_ref_esclave_organisme_formation,
  formorga.id_ref_esclave_contacts_organisme_formation


  FROM [temp_dgf_form_organisme_formation] formorga
  where formorga.id_dgf = '$id_dgf'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}


function get_organisme_data_referenciel($id_ref_esclave_organisme_formation,$id_ref_esclave_organisme_formation,$id_ref_esclave_contacts_organisme_formation) {

    db_set_active(@DB_SLAVE);

    $query = "  select
  orga.siret as t_siret,
  orga.numero_de_declaration_existence as t_numero_declaration,
  orga.raison_sociale as t_raison_sociale,

  adr.numero_de_rue as t_numero_adresse,
  adr.rue as t_rue,
  adr.complement_de_rue,
  adr.complement_de_rue_2,
  adr.code_postal as t_code_postal,
  adr.ville as t_ville,

  orga.telephone_principal as t_telephone,
  orga.email as t_email,
  orga.tva_intracommunautaire as t_assujetti_tva,
  orga.tva_intracommunautaire as t_numero_tva,

  cont.nom as t_contact_nom,
  cont.prenom as t_contact_prenom,
  cont.email as t_contact_email,
  cont.telephone as t_contact_telephone,

  fo.libelle as t_contact_fonction

  from organismes_de_formation orga
  left join adresses_organismes_de_formation adr on adr.id = '$id_ref_esclave_organisme_formation'
  left join contacts_organismes_de_formation cont on cont.id = '$id_ref_esclave_contacts_organisme_formation'
  left join fonctions fo on fo.id = cont.id_fonction

  where orga.id = '$id_ref_esclave_organisme_formation'
  ";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    if (is_array($resultdata))
        return $resultdata;
    else
        return array();

}

function organisme_convertParam($key,$data)
{
    switch ($key) {
        case 'complement_de_rue':
            $data['t_complement_rue'] = $data['complement_de_rue'] . "" . $data['complement_de_rue_2'];
            unset ($data['complement_de_rue']);
            unset($data['complement_de_rue_2']);
            break;
        case 't_assujetti_tva':
            if ($data['t_assujetti_tva']  ) $data['t_assujetti_tva'] = 1 ;else $data['t_assujetti_tva'] = 0;
            break;
    }
    unset ($data['id_ref_esclave_organisme_formation']);
    unset ($data['id_ref_esclave_contacts_organisme_formation']);
    return $data;
}

function insert_organisme($data)
{
    db_set_active(@DB_EXTRANET);
    $nid = db_insert('dgf_form_organisme_formation');

    $data = organisme_convertParam('complement_de_rue',$data);
    $data = organisme_convertParam('t_assujetti_tva',$data);

    $nid->fields($data);

    $nid->execute();
    db_set_active();
}