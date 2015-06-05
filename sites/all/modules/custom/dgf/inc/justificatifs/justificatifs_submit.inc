<?php

function dgf_justificatifs_form_submit_file($form , &$form_state) {
  $file_name  =  $_FILES['files']['name']['file_to_upload'];
  $file_size  =  $_FILES['files']['size']['file_to_upload'];
  $file_tmp   =  $_FILES['files']['tmp_name']['file_to_upload'];
  $file_error =  $_FILES['files']['error']['file_to_upload'];

  _dgf_justificatifs_upload_file($form_state, $file_name, $file_size, $file_tmp, $file_error);
}

function dgf_justificatifs_final_form_submit($form, &$form_state) {
  drupal_goto('/dgf/demande/attestation/'.arg(3));
}

/**
 *  FONCTION D'UPLOAD D'UN FICHIER
 *
 *  @param : $file_name, $file_size, $file_tmp, $file_error
 *
 *  $file_name: Nom du fichier
 *
 *  $file_size: Taille du fichier
 *
 *  $file_tmp: Fichier Temporaire
 *
 *  $file_error: Fichier erreur
 *
 */
function _dgf_justificatifs_upload_file($form_state, $file_name, $file_size, $file_tmp, $file_error) {
  // On nettoie le nom de fichier à upload
  $file_name_cleaned = _clean_file_name($file_name);
  $id_dgf = $form_state['values']['id_dgf'];

  // S'il n'y a pas d'erreur
  if ($file_error == UPLOAD_ERR_OK) {
    $directory_info = justificatifs_db_get_directory_info($id_dgf);
    $siren = substr($directory_info['siret'], 0, 5);
    $siret = $directory_info['siret'];
    $num_demande = $directory_info['numero_demande'];

    // On récupère le chemin où copier ce fichier
    $directory_default_files = @DEFAULT_FILE_PATH;
    // demande/[siren]/[siret]/[num_demande]/justificatifs
    $repertoire_fichier = '/'.$siren.'/'.$siret.'/'.$num_demande.'/demande/';
    $destination = $directory_default_files.$repertoire_fichier;
    if (!is_dir($destination)) {
      mkdir($destination, 0775, true);
    }

    // DEPLACE LE FICHIER DANS LE BON REP
    move_uploaded_file($file_tmp, $destination.$file_name_cleaned);

    // UPLOAD DES INFOS FICHIER EN  BASE DE DONNEES
    justificatifs_db_save_files($form_state, $destination, $repertoire_fichier, $file_name_cleaned);

    // Message de fin
    drupal_set_message(t("Le fichier ".$file_name." a bien été uploadé."));
  } else {
    drupal_set_message(t("Une erreur est intervenue lors de l'upload de votre fichier.") , 'error');
  }
}

function _clean_file_name($file_name) {
  $file_name = strtolower(str_replace(" ", "", trim($file_name)));
  $file_name = strtr($file_name, 'ÁÀÂÄÃÅÇÉÈÊËÍÏÎÌÑÓÒÔÖÕÚÙÛÜÝ', 'AAAAAACEEEEEIIIINOOOOOUUUUY');
  $file_name = strtr($file_name, 'áàâäãåçéèêëíìîïñóòôöõúùûüýÿ', 'aaaaaaceeeeiiiinooooouuuuyy');
  return $file_name;
}