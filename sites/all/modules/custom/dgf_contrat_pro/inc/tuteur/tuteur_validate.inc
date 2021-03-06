<?php

/**
 * Validation for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_contrat_pro_tuteur_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    $idDgf = arg(4);
    // Vérifie si la case "formation interne" a été cochée
    // Dans ce cas on revient vers formation au lieu de organisme de formation
    $intern = check_is_intern_training($idDgf);
    if (isset($intern[0]) && $intern[0] == '1') {
      drupal_goto('/dgf/demande/formation/'.$idDgf);
    } else {
      drupal_goto('/dgf/demande/organisme-formation/'.$idDgf);
    }
  } else if ($form_state['triggering_element']['#id'] == 'edit-modal-quit--2') {
    drupal_goto('/dashboard');
  }
}

function dgf_contrat_pro_tuteur_specific_form_validate($form, &$form_state) {
  if ($form_state['values']['nb_salarie'] && ! is_numeric($form_state['values']['nb_salarie'] )) {
    form_set_error('nb_salarie', 'Veuillez saisir un nombre de salarié valide.' );
  }
  if ($form_state['values']['nb_salarie']
          &&  is_numeric($form_state['values']['nb_salarie'])
                  &&  $form_state['values']['nb_salarie'] > 3) {
    form_set_error('nb_salarie', '« Attention : Un tuteur ne peut pas exercer ses fonctions tutorales auprès de plus de 3 salariés simultanément, veuillez changer de tuteur ' );
  }
  if ($form_state['values']['telephone'] && ! preg_match('`[0-9]{10}`', $form_state['values']['telephone'] )) {
    form_set_error('telephone', t('Veuillez saisir un numéro de téléphone valide. ' ) );
  }

  if ($form_state['values']['email'] && ! valid_email_address($form_state['values']['email'] )) {
    form_set_error('email', 'Veuillez saisir une adresse courriel valide.' );
  }
}

function dgf_contrat_pro_tuteur_standard_form_validate($form, &$form_state) {
  if (!$form_state['values']['etablishment']) {
    form_set_error('etablishment', t('Le champ établissement est obligatoire.'));
  }
  if (!$form_state['values']['lastname']) {
    form_set_error('lastname', t('Le champ nom est obligatoire.'));
  }
  if (!$form_state['values']['firstname']) {
    form_set_error('firstname', t('Le champ prénom est obligatoire.'));
  }
  if (!$form_state['values']['birthday']) {
    form_set_error('birthday', t('Le champ date de naissance est obligatoire.'));
  }
  if ($form_state['values']['nb_salarie'] == '') {
    form_set_error('nb_salarie', t('Le champ nombre de salariés encadrés par ce tuteur est obligatoire.'));
  }
  if (!$form_state['values']['emploi_occupe']) {
    form_set_error('emploi_occupe', t('Le champ emploi occupé est obligatoire.'));
  }
  if (! $form_state['values']['telephone'] && ! $form_state['values']['email']) {
    form_set_error('telephone', '');
    form_set_error('email', t('Veuillez renseigner obligatoirement un numéro de téléphone ou une adresse courriel.'));
  }

}

function dgf_contrat_pro_tuteur_attestation_form_validate($form, &$form_state) {
  if (strcmp($form_state['values']['certifier']['A été informé sur son rôle de tuteur'], "A été informé sur son rôle de tuteur") !== 0
      || strcmp($form_state['values']['certifier']['Bénéficie de plus de 2 ans d\'ancienneté'], "Bénéficie de plus de 2 ans d'ancienneté") !== 0) {
    form_set_error('certifier', t('Vous devez certifier avoir respecté vos obligations liées au tutorat.'));
  }

  if ($form_state['values']['beneficier'] != 0 && $form_state['values']['beneficier'] != 1) {
    form_set_error('beneficier', t('Le champ formation du tuteur est obligatoire.'));
  }

  if (strcmp($form_state['values']['beneficier'], "a déjà bénéficié d’une formation") == 0){
    if (!$form_state['values']['dateFormation']) {
      form_set_error('dateFormation', t('Le champ date de formation est obligatoire.'));
    }
    if (!$form_state['values']['dureeFormation']) {
      form_set_error('dureeFormation', t('Le champ durée de formation est obligatoire.'));
    }
    if (!$form_state['values']['nomOrganisme']) {
      form_set_error('nomOrganisme', t('Le champ nom de l organisme est obligatoire.'));
    }
  }

  if ($form_state['values']['duree_formation'] && !is_numeric($form_state['values']['duree_formation'])) {
    form_set_error('duree_formation', t('Le champ durée de formation doit être un entier.'));
  }

}