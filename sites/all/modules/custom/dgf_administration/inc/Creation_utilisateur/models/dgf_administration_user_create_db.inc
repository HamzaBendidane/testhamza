<?php

 /**
 *  CREE UN UTILISATER DRUPAL
 *  @param: $name - $pass - $email - $roles
 */
function share_create_drupal_user($name, $pass, $email, $roles) {
  db_set_active();
  $new_user = array(
     'name' => $name,
     'pass' => $pass,
     'mail' => $email,
     'status' => 1,
     'init' => $email,
     'roles' => array(
      DRUPAL_AUTHENTICATED_RID => 'authenticated user',
      11 => $roles,
    ), 
   );
  user_save('', $new_user);
}

/**
 *  Sauvegarde de l'utilisateur dans la table de l'utilisateur entreprise
 * 
 * 
 */
function save_user_entreprise_infos() {
  
}

 /**
 *  Sauvegarde des infos entreprises
 * 
 */
function save_company_infos($id_user, $id_entreprise, $raison_sociale, $siret, $id_naf, $tel) {
    
  db_set_active(@DB_SLAVE);
  $sql_proc = "EXEC sp_sauver_entreprise  
                 @user  = $id_user,
                 @id = $id_entreprise,
                 @raison_sociale = '$raison_sociale',
                 @siret = '$siret', 
                 @id_naf =  '$id_naf' ,
                 @id_nace = NULL,
                 @est_en_cours_immatriculation = 0,
                 @telephone_principal = '$tel',
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
  $exec = db_query($procedure); 
  db_set_active();
  
}

/**
 *  Adresses entreprises
 * 
 */
function save_company_adress_infos($id_user, $numero_de_rue, $complement_de_rue, $complement_de_rue_2, $code_postal, $ville,  $id_entreprise) {
    
  db_set_active(@DB_SLAVE);
  $procedure = "EXEC sp_sauver_adresse_entreprise
                   @user = $id_user,
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
  $exec = db_query($procedure); 
  db_set_active();
  
}

/**
 *  Sauvegarde les details d'un utilisateur
 *  @param: nom, email, id drupal utilisateur 
 *   
 * 
 */
function save_user_infos($gender, $name, $email, $phone, $fonction, $id_user) {
  db_set_active(@DB_EXTRANET);  
  
  // CREATE USER
  if (strcmp($gender, "Mr")) {
    $genre = 0;
  }
  elseif (strcmp($gender, "Mme")) {
    $genre = 1;
  }
  
  // Sauvegarde de l'utilisateur Drupal
  $roles = 'COLLABORATEUR ENTREPRISE';
  share_create_drupal_user($name, $pass = '', $email, $roles);
 
  // Récuppère l'id créée.
  $user = user_load_by_name($name);
  $id_drupal_user = $user->uid;
  
  if (user_load($id_drupal_user) == FALSE) {
    drupal_set_message('Un utilisateur existe déjà avec ce nom' , 'error');
  }
   
  // Retour vers la base DB EXTRANET
  db_set_active(@DB_EXTRANET); 
  
  $save_sql = db_insert('drupal_user')
              ->fields(array(
                 'civilite' => $genre,
                 'name' => $name,
                 'mail' => $email,
                 'fonction' => $fonction,
                 'telephone'=> $phone,
                 'date_creation' => shared_send_to_mssql_date(null, 'datetime'),
                 'id_user_creation' => $id_user,
                 'id_user_drupal' => $id_drupal_user,
               ))
              ->execute();    
        
}

/**
 *  Sauvegarde des habilitations utilisateurs
 *  @param: les habilitations utilisateurs, l'id utilisateur drupal
 * 
 */
function save_user_habilitations($user_habilitations, $id_user_drupal) {
 db_set_active(@DB_EXTRANET);   
 //Supprime toutes les habilitations de l'utilisateur associé à l'id
 $sql_delete = db_delete('lien_drupal_user_habilitation')
               ->condition('id_drupal_user' , $id_user_drupal, '=')
               ->execute();   
                        
  // Sauvegarde les habilitations  // Vaudrait mieux faire un db_update : lien_drupal_user_habilitation
  foreach ($user_habilitations as $value) {
     if($value != 0) {
       $hab_sql = db_insert('lien_drupal_user_habilitation')
                ->fields(array(
                'id_drupal_user'     => $id_user_drupal,
                'id_habilitation'    => $value,
                ))
                ->execute();
    }
  }
  db_set_active();
}