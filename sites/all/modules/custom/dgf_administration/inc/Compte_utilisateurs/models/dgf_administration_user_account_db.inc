<?php

/***
 *  DB Update
 */
function dgf_administration_update_user_infos($data, $id) {
  db_set_active(@DB_EXTRANET);
  
  $sql =  db_update('drupal_user')
          ->fields($data)
          ->condition('id', $id, '=')
          ->execute(); 
          
  db_set_active();
} 
      
