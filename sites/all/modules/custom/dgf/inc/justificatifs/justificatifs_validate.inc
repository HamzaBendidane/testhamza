<?php

function dgf_justificatifs_form_validate($form, &$form_state) {

  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    drupal_goto('/dgf/demande/contrat-pro/cerfa/'.arg(3));
  } else if (in_array($form_state['triggering_element']['#id'] ,array( 'edit-modal-quit--2','edit-modal-save'))) {
    drupal_goto('/dashboard');
  }

}

function dgf_justificatifs_final_form_validate($form, &$form_state) {
  $id_dgf = $form_state['values']['id_dgf'];
  $temp_dgf_form_justificatif = justificatifs_db_get_temp_dgf_form_justificatif($id_dgf);
  $ref_justificatifs = justificatifs_db_get_ref_justificatif($id_dgf, $temp_dgf_form_justificatif);
  $error = false;
  foreach ($ref_justificatifs as $justificatif) {
    if ($justificatif->is_mandatory) {
      $error = true;
    }
  }
  if ($error) form_set_error('files[file_to_upload]', @J_ERROR_MANDATORY);
}

function dgf_justificatifs_form_standard($form, &$form_state) {
  if (!$form_state['values']['id_ref_file']) {
//     drupal_set_message(t("Veuillez sélectionner le document à uploader de l'étape 1"), 'error');
    form_set_error('error_select_file', t("Veuillez sélectionner le document à joindre de l'étape 1"));
  }
  if (!$_FILES['files']['name']['file_to_upload']) {
//     drupal_set_message(t("Veuillez sélectionner le fichier à uploader"), 'error');
    form_set_error('files[file_to_upload]', t("Veuillez sélectionner le fichier à uploader"));
  }
}

/**
 * Validation du formulaire d'envoie de fichiers
 */
function dgf_justificatifs_form_specific($form, &$form_state) {
  if ($_FILES['files']['name']['file_to_upload']) {
    $file_name = $_FILES['files']['name']['file_to_upload']; // Nom fichier
    $file_size = $_FILES['files']['size']['file_to_upload']; // Taille du fichier

    $max_file_size =  5242880; // Taille Max des fichiers

    // Extension fichier
    $get_file_ext = new SplFileInfo($file_name);

    $file_ext = $get_file_ext->getExtension();

    $allow_ext = array('pdf' , 'doc' , 'docx' , 'xls' , 'xlsx' , 'jpeg', 'jpg' , 'png');

    // Check file Extension
    if (!in_array(strtolower($file_ext), $allow_ext)) {
      form_set_error('files[file_to_upload]', t("Votre document " . $file_name . " n'est pas conforme au format suivant : .pdf, .doc, .docx, .xls, .xlsx, .jpeg, .jpg, .png"));
    }

    // Check file size
    if ($file_size > $max_file_size) {
      form_set_error('files[file_to_upload]', t('Votre document ' . $file_name . ' dépasse les 5 Mo autorisés'));
    }
  }
}

