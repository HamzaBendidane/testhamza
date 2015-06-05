<?php

/**
 *  Sauvegarde les details d'un utilisateur
 *  @param: nom, email, id drupal utilisateur 
 * 
 *  TODO: surname à rajouter
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
  $save_sql = db_update('drupal_user')
              ->fields(array(
                 'civilite' => $genre,
                 'name' => $name,
                 'mail' => $email,
                 'fonction' => $fonction,
                 'telephone'=> $phone,
                 'date_creation' => date('d-m-y H:i:s'),
                 'id_user_creation' => $id_user,
                 'id_user_drupal' => $id_user,
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