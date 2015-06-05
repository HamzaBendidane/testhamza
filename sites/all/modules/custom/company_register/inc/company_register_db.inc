<?php

/**
 *  Sauvegarde les infos d'une entreprise
 *  Nom de la table: entreprises
 *  Procédure stockée: sp_sauver_entreprise
 */
function company_register_db_save_company_infos($data_information, $data_confirmation, $nb_siret) {

  global $user; // User Drupal

  db_set_active(@DB_SLAVE);

  $id_entreprises = array();
  for ($i=0; $i < $nb_siret ; $i++) {
    $raison_sociale = $data_information['company_raison_sociale_'.$i]; // Valeur à passer à la procédure stockée
    $siret = $data_information['company_siret_'.$i];
    $tel = $data_information['company_telephone_'.$i];
    $id_naf = $data_information['code_naf_'.$i];
    $id = company_register_get_id($siret);

    if($id != NULL) {
      $param_id_company = "@id = N'$id'";
    }
    else{
      $param_id_company = "@id = null";
    }
    if ($tel != NULL) {
      $tel = $data_information['company_telephone_'.$i];
    }
    else{
      $tel = 'NULL';
    }

   // Procédure stockée sp_sauver_entreprise
   $procedure = "EXEC sp_sauver_entreprise
                  @user  = $user->uid,
                  $param_id_company,
                  @raison_sociale = N'$raison_sociale',
                  @siret = N'$siret',
                  @id_naf =  N'$id_naf',
                  @id_nace = NULL,
                  @est_en_cours_immatriculation = 0,
                  @telephone_principal = N'$tel',
                  @telephone_secondaire = NULL,
                  @fax = NULL,
                  @site_web = NULL,
                  @email = NULL,
                  @tva_intracommunautaire = NULL,
                  @id_categorie = NULL,
                  @id_departement = NULL,
                  @est_hors_branche = 0,
                  @id_taux_de_tva = NULL,
                  @id_secteur_activite = NULL,
                  @id_convention_collective = NULL,
                  @est_geiq = 0
                  ";
    $result = db_query($procedure);

    $id_entreprise = $result->fetchField();

    if (isset($data_confirmation['nom_adefim_'.$i])) {
      // Procédure stockée sp_sauver_entreprise
      $id_adefim = $data_confirmation['nom_adefim_'.$i];
      $procedure = "EXEC sp_lier_adefim_entreprise
        @user  = $user->uid,
        @id_adefim = N'$id_adefim',
        @id_entreprise = N'$id_entreprise'
      ";
      db_query($procedure);
var_dump($procedure);
    }
    $id_entreprises[] = $id_entreprise;


  }
//   die('test');
  db_set_active();

  return $id_entreprises;
}


/**
 *  Sauvegarde les infos d'une entreprise
 *  Nom de la table: adresses_entreprises
 *  @Procedure: sp_sauver_adresse_entreprise
 *  @param : $data - Les données du formulaire
 *
 *
 */
 function company_register_db_save_company_adresses($data, $nb_siret) {
  global $user;

  db_set_active(@DB_SLAVE);

  for ($i=0; $i < $nb_siret ; $i++) {
    $id = NULL;
    $numero_de_rue = $data['company_adresse_street_number_'.$i];
    $rue = $data['company_adresse_street_name_'.$i];
    $complement_de_rue =  $data['company_adresse_street_name_more_'.$i];
    $complement_de_rue_2 =  $data['company_adresse_street_name_more_'.$i];
    $ville =  $data['company_adresse_town_'.$i];
    $code_postal =  $data['company_code_postal_'.$i];
    $id_region =  NULL;
    $siret = $data['company_siret_'.$i];
    $id_entreprise =  company_register_get_id($siret);

    $procedure = "EXEC sp_sauver_adresse_entreprise
                   @user = $user->uid
                  ,@id  = NULL
                  ,@id_type_adresse = NULL
                  ,@numero_de_rue = '$numero_de_rue'
                  ,@rue = '$rue'
                  ,@complement_de_rue = '$complement_de_rue'
                  ,@complement_de_rue_2 = '$complement_de_rue_2'
                  ,@code_postal = '$code_postal'
                  ,@ville = '$ville'
                  ,@id_region = NULL
                  ,@id_entreprise = '$id_entreprise'
                 ";
    // Execution de la procédure
    $exec = db_query($procedure);
  }
  db_set_active();
}

/**
 *  Sauvegarde les infos d'un responsable entreprise
 *  Nom de la table: @TABLE_USER_RESPONSABLE
 */
function company_register_db_save_user_responsable($data) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $Resp_Nom = $data['responsable_nom'];
  $Resp_Prenom =  $data['responsable_prenom'];
  $Resp_Email = $data['responsable_email'];
  $Resp_Fonction = $data['responsable_fonction'];


  $id_user_responsable = db_insert(@TABLE_USER_RESPONSABLE)
         ->fields( array(
         'civilite' => $data['responsable_titre'],
         'nom'      => $Resp_Nom,
         'prenom'   => $Resp_Prenom,
         'email'    => $Resp_Email,
         'fonction' => $Resp_Fonction,
         ))
         ->execute();

  db_set_active();

  return $id_user_responsable;
}

/**
 *  Sauvegarde les infos d'un utilisateur entreprise
 *  Nom de la table: drupal_user
 */
function company_register_db_save_extranet_drupal_user($data, $id_user_drupal) {
  global $user;

  db_set_active(@DB_EXTRANET);

  $id_extranet_drupal_user = db_insert('drupal_user')
         ->fields( array(
             'civilite' => $data['utilisateur_titre'],
             'last_name' => $data['utilisateur_nom'],
             'first_name' => $data['utilisateur_prenom'],
             'mail' => $data['utilisateur_email'],
             'fonction' => $data['utilisateur_fonction'],
             'telephone' => $data['utilisateur_telephone'],
             'date_creation' => shared_send_to_mssql_date(null,'datetime'),
             'id_user_creation' => $user->uid,
             'is_delete' => 0,
             'id_user_drupal' => $id_user_drupal,))
         ->execute();
  db_set_active();

  return $id_extranet_drupal_user;
}

/**
 *  Sauvegarde le numéro de demande
 *  Nom de la table: user_entreprise
 */
function company_register_db_save_user_entreprise($num_demande , $nom_sign, $id_extranet_drupal_user, $id_user_responsable) {
  global  $user;

  db_set_active(@DB_EXTRANET);

  // SQL INSERT
  $id_user_entreprise = db_insert(@TABLE_USER_ENTREPRISE)
  -> fields(array(
      'id_user_responsable' => $id_user_responsable,
      'id_drupal_user' => $id_extranet_drupal_user,
      'numero_demande' => $num_demande,
      'charte_signe'   => 0,
      'nom_signe'   => $nom_sign,
      'date_charte_signe' =>  shared_send_to_mssql_date(null, 'datetime'),
      ))
      ->execute();
  db_set_active();

  return $id_user_entreprise;
}


function company_register_db_update_user_entreprise() {
  global  $user;

  db_set_active(@DB_EXTRANET);

  // SQL INSERT
  $id_user_entreprise = db_update(@TABLE_USER_ENTREPRISE)
  -> fields(array(
      'charte_signe' => 1,
      'date_charte_signe' => shared_send_to_mssql_date(null, 'datetime'),
  ))
  ->condition('id', $_SESSION['id_user_entreprise'])
  ->execute();
  db_set_active();

  return $id_user_entreprise;
}

/**
 *   Sauvegarde les habilitations d'un utilisateur
 *   BDD: DB_EXTRANET
 *   Table : lien drupal user habilitation
 *
 */
function company_register_db_save_user_habilitations($data, $id_drupal_user, $id_user_entreprise, $nb_siret) {
  db_set_active(@DB_EXTRANET);

  $user_habilitations = $data['utilisateur_fonctions']; // Save user roles and permissions

  $sql_delete = db_delete('lien_drupal_user_habilitation')  // Supprime toutes les habilitations de l'utilisateur associé à l'id
                ->condition('id_drupal_user' , $id_drupal_user, '=')
                ->execute();

  foreach ($user_habilitations as $key => $value) {   // Sauvegarde les habilitations  // Vaudrait mieux faire un db_update : lien_drupal_user_habilitation
     if($value != '0') {
       $hab_sql = db_insert('lien_drupal_user_habilitation')
                  ->fields(array(
                  'id_drupal_user'     => $id_drupal_user,
                  'id_habilitation'    => $key,
                  ))
                  ->execute();
     }
   }

  // Sauvegade du lien user entreprise et id entreprises

  // Sauvegarde des liens entreprises et utilisateurs
  for ($i=0; $i < $nb_siret ; $i++) {

    $siret = $data['company_siret_'.$i];  // Siret entreprise

    $id_entreprise = company_register_get_id($siret);  // ID Entreprise

    db_set_active(@DB_EXTRANET);
    $sql_insert = db_insert('lien_user_entreprise_ref_esclave_entreprise')
    ->fields(array(
        'id_user_entreprise' => $id_user_entreprise,
        'id_ref_esclave_entreprise' => $id_entreprise,
        'est_valide' => '0',
        'est_actif' => '1',
        ))
        ->execute();
  }
  db_set_active();
}

/**
 * Renvoie l'id de l'entreprise associé au siret, si il existe
 *
 */
function company_register_get_id($siret) {
  db_set_active(@DB_SLAVE);

  $sql  = db_select('v_entreprises', 'v')
          ->fields('v' , array('id'))
          ->condition('siret', $siret, '=')
          ->execute();

  $id = $sql->fetchField();

  return trim($id);
}

 /**
 *  Renvoie le numéro de demande
 *
 */
function company_register_get_numero_demande() {

  db_set_active(@DB_EXTRANET);

  // Renvoie le dernier numéro de demande
  $sql = db_select(@TABLE_USER_ENTREPRISE , 'n')
         ->fields('n' , array('numero_demande'))
         ->orderBy('id' , 'DESC')
         ->execute();

  $num_demand = $sql->fetchField();

  db_set_active();

  return intval($num_demand);
}

/**
*
*  Renvoie des codes NAFS
*
*/
function company_register_get_code_naf(){
  // Connection au référentiel OPCAIM
  $fields = array('id', 'libelle');

  $codes_nafs = shared_db_select(@DB_SLAVE, 'nafs', 'n', $fields);

  $nafs = array();

  foreach ($codes_nafs as $value) {
    $id_codes_nafs = trim($value->id); // Id
    $libelles_code_nafs = $value->libelle; // Libelle
    // Sauvegarde en session des codes NAF
    $nafs[$id_codes_nafs] = trim($id_codes_nafs) . ' - ' . $libelles_code_nafs;
  }
  return  $nafs;
}

 /**
 *  SIRET AUTOCOMPLETE
 */
function company_siret_autocomplete() {

  db_set_active(@DB_SLAVE);  // Connection au référentiel

  if (!isset($term)) {
     $term = $_GET["term"];
  }

  //$sql->join('adresses_entreprises' , 'a' , 's.id = a.id_entreprise'); // Jointure avec la table des adresses

  $sql = db_select('entreprises', 'e');//  Requête SQL pour trouver un numéro de siret

  $sql->join('adresses_entreprises' , 'a' , 'e.id = a.id_entreprise');

  $sql->fields('e')
      ->fields('a')
      ->distinct()
      ->condition('siret',  db_like($term) . '%' , 'LIKE');

  $values = $sql->execute()->fetchAll();

  $data = array();

  foreach ($values as $items) {
    $data[] = array(
      'label' => trim($items->siret),
      'value' => trim($items->id),
      'data' =>  $items,
    );
  }
  db_set_active(); // Fermeture de la connexion

  drupal_json_output($data); // Renvoie des résultats en json
}
