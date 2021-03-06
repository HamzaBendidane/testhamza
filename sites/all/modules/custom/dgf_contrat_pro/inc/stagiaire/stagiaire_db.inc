<?php

function stagiaire_get_ref_esclave_entreprise() {
  global $user;

  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
  $query->fields('e');
  $query->condition('e.est_valide = ', 1, '=');
  $query->condition('e.est_actif = ', 1, '=');

  // ROLE 6 : DIRECTEUR ADEFIM / ROLE 7 : REFERENT ADEFIM / ROLE 8 : GESTIONNAIRE ADEFIM / ROLE 9 : CONSEILLER ADEFIM
  if (user_has_role(6) || user_has_role(7) || user_has_role(8) || user_has_role(9)) {
    $query->condition('e.id', array_keys($user->data['login']->entreprises), 'in');
  }
  // ROLE 10 : ADMIN ENTREPRISE / ROLE 11 : COLLABORATEUR ENTREPRISE
  if (user_has_role(10) || user_has_role(11)) {
    $query->condition('e.id', array_keys($user->data['login']->entreprises), 'in');
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

function stagiaire_get_salarie_from_name() {
  db_set_active(@DB_SLAVE);

  $term = $_GET["term"];

  $query = db_select('v_salaries', 's');
  $query->fields('s');
  $query->condition('s.est_valide = ', 1, '=');
  $query->condition('s.est_actif = ', 1, '=');
  $query->condition('s.nom',  db_like($term) . '%' , 'LIKE');
  $salaries = $query->execute()->fetchAll();

  $data = array();
  foreach ($salaries as $salarie) {
    if (null !== $salarie->date_de_naissance) {
      $date_de_naissance = shared_parse_mssql_datetime($salarie->date_de_naissance);
      $salarie->date_de_naissance = $date_de_naissance->format('d/m/Y');
    }
    if (null !== $salarie->date_embauche) {
      $date_embauche = shared_parse_mssql_datetime($salarie->date_embauche);
      $salarie->date_embauche = $date_embauche->format('d/m/Y');
    }

    $data[] = array(
        'value' => trim($salarie->nom),
        'label' => trim($salarie->nom).' '.trim($salarie->prenom) .' ('.trim($salarie->date_de_naissance).')',
        'data'  => $salarie,
    );
  }

  db_set_active();

  // Renvoie des résultats en json
  drupal_json_output($data);
}

function stagiaire_db_sp_sauver_salarie($form_data, $person = 'stagiaire') {
  global $user;

  //Si l'utilisateur quitte le formulaire avant d'avoir entré les données obligatoire à la création d'un formulaire on ne crée pas de salarié
  if ($form_data['values']['lastname'] == ""
      || $form_data['values']['firstname'] == ""
      || $form_data['values']['birthday'] == "") {
        return;
  }

  // cas $id existe si on retrouve le stagiaire
  if ($form_data['values']['id_salarie'] != '') {
    $previous_salarie_infos = salarie_db_get_v_salarie($form_data['values']['id_salarie']);
    $date_de_naissance_previous = shared_parse_mssql_datetime($previous_salarie_infos['date_de_naissance']);
    $id_salarie = $form_data['values']['id_salarie'];


    // Si le nom, prénom ou date de naissance a été modifié, c'est un nouveau stagiaire
    if (trim($previous_salarie_infos['prenom']) === trim($form_data['values']['firstname'])
        && trim($previous_salarie_infos['nom']) === trim($form_data['values']['lastname'])
        && $date_de_naissance_previous->format('d/m/Y') === $form_data['values']['birthday']) {
          $param_id_salarie = "@id = N'$id_salarie'";
    } else {
      $param_id_salarie = "@id = null";
    }
  } else {
    $param_id_salarie = "@id = null";
  }

  // On récupère les valeurs du formulaire
  $param_id_civilite = "@id_civilite = null";
  if (isset($form_data['values']['man_woman'])) {
    $sex = $form_data['values']['man_woman'];
    $param_id_civilite = "@id_civilite = N'$sex'";
  }
  $prenom = $form_data['values']['firstname'];
  $nom = $form_data['values']['lastname'];
  // $numero_securite_sociale = $form_state['values']['number_securite_sociale'];
  $naissance = shared_send_to_mssql_date($form_data['values']['birthday'], 'datetimeoffset');
  // $date_embauche = $form_state['values']['date_embauche'];
  $param_handicap = "@est_travailleur_handicape = null";
  if (isset($form_data['values']['handicapped_worker'])) {
    $handicap = $form_data['values']['handicapped_worker'];
    $param_handicap = "@est_travailleur_handicape = $handicap";
  }

  if ($person == 'stagiaire') {
    $est_stagiaire = 1;
  } else {
    $est_stagiaire = 0;
  }

  // Procédure stockée
  db_set_active(@DB_SLAVE);
  $save_salarie_query = "EXEC sp_sauver_salarie
    @user = N'$user->uid',
    $param_id_salarie,
    $param_id_civilite,
    @prenom = N'$prenom',
    @nom = N'$nom',
    @numero_de_securite_sociale = NULL,
    @date_de_naissance = N'$naissance',
    @date_embauche = NULL,
    $param_handicap,
    @est_stagiaire = $est_stagiaire,
    @id_niveau_de_formation = NULL,
    @id_categorie_socio_professionnelle = NULL,
    @id_type_de_contrat = NULL
  ";

  // Execution de la procédure
  $result = db_query($save_salarie_query);
  $id_ref_esclave_salarie = $result->fetchField();

  db_set_active();

  return $id_ref_esclave_salarie;
}

function stagiaire_db_insert_temp_dgf_form_demande($id_dgf, $id_dgf_nature_demande, $id_dgf_nature_formation) {
  global $user;
  db_set_active(@DB_EXTRANET);
  // On insert dans la table extranet temp_dgf_form_demande
  $query = db_insert('temp_dgf_form_demande')->fields(array(
      'id_dgf' => $id_dgf,
      'id_dgf_nature_demande' => $id_dgf_nature_demande,
      'id_dgf_nature_formation' => $id_dgf_nature_formation,
  ));

  $id_temp_dgf_form_demande = $query->execute();

  db_set_active();

  return $id_temp_dgf_form_demande;
}

function stagiaire_db_insert_dgf($form_state) {
  global $user;
  db_set_active(@DB_EXTRANET);
  // On insert dans la table extranet dgf :
  $query = db_insert('dgf')->fields(array(
      'statut' => '1',
      'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_creation' => $user->uid,
      'multi_etablissement' => 0,
  ));

 $id_dgf = $query->execute();

  // On met à jour la table dgf pour le numéro de demande
  db_update('dgf')->fields(array(
    'numero_demande' => $id_dgf,
    )
  )
  ->condition('id', $id_dgf, '=')
  ->execute();

  db_set_active();

  return $id_dgf;
}

function stagiaire_db_insert_lien_dgf_ref_esclave_entreprise($form_state, $id_dgf) {
  global $user;
  db_set_active(@DB_EXTRANET);
  // On insert dans la table extranet lien_dgf_ref_esclave_entreprise :
  $query = db_insert('lien_dgf_ref_esclave_entreprise')->fields(array(
      'id_dgf' => $id_dgf,
      'id_ref_esclave_entreprise' => trim($form_state['values']['etablishment']),
      'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_creation' => $user->uid,
  ));

  $id = $query->execute();

  db_set_active();

  return $id;
}

function stagiaire_db_update_lien_dgf_ref_esclave_entreprise($form_state, $id_dgf) {
  global $user;

  db_set_active(@DB_EXTRANET);
  // On insert dans la table extranet lien_dgf_ref_esclave_entreprise :
  $query = db_update('lien_dgf_ref_esclave_entreprise')->fields(array(
      'id_ref_esclave_entreprise' => trim($form_state['values']['etablishment']),
      'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_last_edit' => $user->uid,
  ))
  ->condition('id_dgf', $id_dgf, '=')
  ->execute();

  db_set_active();
}

function stagiaire_db_update_dgf($id_dgf) {
  global $user;

  db_set_active(@DB_EXTRANET);
  // On met à jour la table dgf
  db_update('dgf')->fields(array(
      'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_last_edit' => $user->uid,
  )
  )
  ->condition('id', $id_dgf, '=')
  ->execute();

  db_set_active();
}

function stagiaire_db_insert_temp_dgf_form_salarie($form_data, $id_dgf, $id_ref_esclave_salarie) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $id_temp_dgf_form_salarie = db_insert('temp_dgf_form_salarie')->fields(array(
      'id_dgf'=> $id_dgf,
      'id_ref_esclave_salarie' => $id_ref_esclave_salarie,
      'id_ref_esclave_entreprise' => $form_data['values']['etablishment'],
      'id_ref_beneficiaire_minimas_sociaux' => $form_data['values']['social_beneficiary'] ? $form_data['values']['social_beneficiary'] : null,
      'id_ref_derniere_situation' => $form_data['values']['last_status'],
      'id_ref_diplome' => $form_data['values']['highest_level'],
      'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
      'id_user_creation' => $user->uid,
      'is_delete' => '0',
      'numero_rue' => $form_data['values']['num_rue'],
      'nom_rue' => $form_data['values']['nom_rue'],
      'complement_adresse' => $form_data['values']['complement_adresse'],
      'code_postal' => $form_data['values']['zip_code'],
      'ville' => $form_data['values']['city'],
      'telephone' => $form_data['values']['phone_number'],
      'email' => $form_data['values']['email'],
      'numero_inscrit_pole_emploi' => $form_data['values']['pole_emploi_number'],
      'nombre_mois_inscrit_pole_emploi' => $form_data['values']['since_month'],
      'caisse_retraite' => $form_data['values']['pension_fund'],
      'caisse_prevoyance' => $form_data['values']['contingency_fund'],
  )
  )->execute();

  db_set_active();

  return $id_temp_dgf_form_salarie;
}

function stagiaire_db_update_temp_dgf_form_salarie($form_data, $id_dgf, $id_ref_esclave_salarie) {
  global $user;

  db_set_active(@DB_EXTRANET);

  db_update('temp_dgf_form_salarie')
    ->fields(array(
        'id_dgf'=> $id_dgf,
        'id_ref_esclave_salarie' => $id_ref_esclave_salarie,
        'id_ref_esclave_entreprise' => $form_data['values']['etablishment'],
        'id_ref_beneficiaire_minimas_sociaux' => $form_data['values']['social_beneficiary'] ? $form_data['values']['social_beneficiary'] : null,
        'id_ref_derniere_situation' => $form_data['values']['last_status'],
        'id_ref_diplome' => $form_data['values']['highest_level'],
        'date_last_edit' => shared_send_to_mssql_date(null, 'datetime'),
        'id_user_last_edit' => $user->uid,
        'is_delete' => '0',
        'numero_rue' => $form_data['values']['num_rue'],
        'nom_rue' => $form_data['values']['nom_rue'],
        'complement_adresse' => $form_data['values']['complement_adresse'],
        'code_postal' => $form_data['values']['zip_code'],
        'ville' => $form_data['values']['city'],
        'telephone' => $form_data['values']['phone_number'],
        'email' => $form_data['values']['email'],
        'numero_inscrit_pole_emploi' => $form_data['values']['pole_emploi_number'],
        'nombre_mois_inscrit_pole_emploi' => $form_data['values']['since_month'],
        'caisse_retraite' => $form_data['values']['pension_fund'],
        'caisse_prevoyance' => $form_data['values']['contingency_fund'],
    ))
    ->condition('id_dgf', $id_dgf, '=')
    ->execute();

  db_set_active();

  return true;
}

/**
 * Récupère les informations concernant le salarié
 * @return $result
 */
function salarie_db_get_temp_dgf_form_salarie($id_dgf) {
  db_set_active(@DB_EXTRANET);
  $result = db_select('temp_dgf_form_salarie', 'sa')
    ->fields('sa')
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
function salarie_db_get_v_salarie($id) {
  db_set_active(@DB_SLAVE);

  $result = db_select('v_salaries', 'sa')
    ->fields('sa')
    ->condition('id', $id, '=')
    ->condition('est_actif', 1, '=')
    ->execute()
    ->fetchAssoc();

  db_set_active();

  return $result;
}
function get_salarie_data_extranet($id_dgf) {
    db_set_active(@DB_EXTRANET);

    $query = "SELECT
  salform.id_dgf,
    salform.id_ref_esclave_entreprise,
 salform.id_ref_esclave_particularites,
 salform.id_ref_esclave_salarie,

 salform.numero_rue as t_numero_rue,
 salform.nom_rue as t_rue,
 salform.complement_adresse as t_complement_rue,
 salform.code_postal as t_code_postal,
 salform.ville as t_ville,
 salform.telephone as t_telephone,
 salform.email as t_email,
 situa.label as t_derniere_situation,
 salform.caisse_retraite as t_caisse_retraite,
 salform.caisse_prevoyance as t_caisse_prevoyance,
 dipl.label as t_diplome,
 bensau.label as t_beneficiaire_minimas_sociaux,
 salform.numero_inscrit_pole_emploi as t_numero_pole_emploi,
 salform.nombre_mois_inscrit_pole_emploi as t_nombre_mois_inscrit_pole_emploi,
 salform.salaire_horaire_brut as t_salaire_horaire_brut,
 salform.salaire_horaire_net as t_salaire_horaire_net,
 salform.cout_pedagogique as t_cout_pedagogique,
 salform.cout_evaluation_preformative as t_cout_evaluation_preformative,
 salform.frais_transport as t_frais_transport,
 salform.frais_repas as t_frais_repas,
 salform.nb_repas as t_nb_repas,
 salform.frais_nuitee as t_frais_nuitee,
 salform.nb_nuitee as t_nb_nuitee,
 salform.mobilisation_cpf as t_mobilisation_cpf,
 salform.heure_cpf as t_heure_cpf,
 salform.numero_securite_sociale as t_numero_securite_sociale,
 salform.duree_action as t_duree_action,
 salform.duree_action_tt as t_duree_action_tt,
 salform.duree_action_htt as t_duree_action_htt,
 salform.duree_eval_preformative_heure as t_duree_eval_preformative_heure,
 salform.duree_eval_preformative_minute as t_duree_eval_preformative_minute,
 salform.date_creation as date_creation,
 salform.id_user_creation as id_user_creation,
 salform.date_last_edit as date_last_edit,
 salform.id_user_last_edit as id_user_last_edit,
 salform.date_delete as date_delete,
 salform.id_user_delete as id_user_delete,
 salform.is_delete as is_delete

  FROM  [temp_dgf_form_salarie] salform
  left join ref_derniere_situation situa on situa.id = salform.id_ref_derniere_situation
  left join ref_diplome dipl on dipl.id = salform.id_ref_diplome
  left join ref_beneficiaire_minimas_sociaux bensau on bensau.id = salform.id_ref_beneficiaire_minimas_sociaux
  where salform.id_dgf = '$id_dgf'
  ";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}


function get_salarie_data_referenciel($id_ref_esclave_entreprise,$id_ref_esclave_particularites,$id_ref_esclave_salarie) {
    db_set_active(@DB_SLAVE);

    $query = "SELECT
    entr.raison_sociale as t_entreprise,
 adr.numero_de_rue as t_entreprise_numero_rue,
 adr.rue as t_entreprise_rue,
adr.complement_de_rue,
adr.complement_de_rue_2,
 adr.code_postal as t_entreprise_code_postal,
 adr.ville as t_entreprise_ville,
 entr.telephone_principal as t_entreprise_telephone,
 entr.fax as t_entreprise_fax,
 entr.email as t_entreprise_email,
 sal.nom as t_nom,
 sal.prenom as t_prenom,
 sal.date_de_naissance as t_date_naissance,
 0 as t_age,
 sal.id_civilite as t_sexe,
 sal.est_travailleur_handicape as t_travailleur_handicape,
  part.libelle as t_particularite
              FROM salaries sal
              join entreprises entr on entr.id = '$id_ref_esclave_entreprise'
              join adresses_entreprises adr on adr.id_entreprise = entr.id
              left join particularites part on part.id = '$id_ref_esclave_particularites'
              where sal.id = '$id_ref_esclave_salarie'";

    $result = db_query($query);

    $resultdata  = $result->fetchAssoc();
    db_set_active();

    return $resultdata;
}

function convertParam($key,$data){
    switch ($key) {
        case 't_sexe':
            if ($key == "M. "){
                $data[$key] = 1;
            }else $data[$key] = 0;
            break;
        case 'complement_de_rue':
            $data['t_entreprise_complement_rue'] = $data['complement_de_rue'] . "" . $data['complement_de_rue_2'];
            unset ($data['complement_de_rue']);
            unset($data['complement_de_rue_2']);
            break;
    }
    unset ($data['id_ref_esclave_entreprise']);
    unset ($data['id_ref_esclave_particularites']);
    unset ($data['id_ref_esclave_salarie']);
    return $data;
}

function insert_salarie($data)
{
    db_set_active(@DB_EXTRANET);
    $nid = db_insert('dgf_form_salarie');

    $data = convertParam('t_sexe',$data);
    $data = convertParam('complement_de_rue',$data);

    $nid->fields($data);

    $nid->execute();
    db_set_active();
}