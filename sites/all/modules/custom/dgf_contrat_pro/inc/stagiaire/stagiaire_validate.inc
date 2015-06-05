<?php

/**
 * Validation for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_contrat_pro_stagiaire_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    drupal_goto('/dgf/demande');
  } else if ($form_state['triggering_element']['#id'] == 'edit-modal-quit--2') {
    drupal_goto('/dashboard');
  }
}

function dgf_contrat_pro_stagiaire_specific_form_validate($form, &$form_state) {
  if ($form_state['values']['num_rue'] && ! is_numeric($form_state['values']['num_rue'] )) {
    form_set_error('num_rue', 'Veuillez saisir un numéro de rue valide.' );
  }
  if ($form_state['values']['zip_code'] && ! is_numeric($form_state['values']['zip_code'] )) {
    form_set_error('zip_code', t('Veuillez saisir un code postal valide.' ) );
  }

  if ($form_state['values']['phone_number'] && ! preg_match('`[0-9]{10}`', $form_state['values']['phone_number'] )) {
    form_set_error('phone_number', t('Veuillez saisir un numéro de téléphone valide. ' ) );
  }

  if ($form_state['values']['email'] && ! valid_email_address($form_state['values']['email'] )) {
    form_set_error('email', 'Veuillez saisir une adresse courriel valide.' );
  }

//   if ($form_state['values']['age'] > 26 && ! $form_state['values']['pole_emploi_number']) {
//      echo ("Attention : Pour être éligible au contrat de professionnalisation, le stagiaire de plus de 26 ans doit posséder un numéro d’identification « demandeur d’emploi », pour ce faire, il suffit de s’inscrire au pôle emploi.");
//   }

  if ( $form_state['values']['pole_emploi_number'] && ! is_numeric($form_state['values']['since_month'] )) {
    form_set_error('pole_emploi_number', 'Veuillez saisir un numéro du pole emploi valide.' );
  }

  if ( $form_state['values']['since_month'] && ! is_numeric($form_state['values']['since_month'] )) {
    form_set_error('since_month', t('Veuillez saisir une durée valide. ' ) );
  }
}

function dgf_contrat_pro_stagiaire_standard_form_validate($form, &$form_state) {
    if (!$form_state['values']['etablishment']) {
        form_set_error('etablishment', t('Le champ établissement est obligatoire.'));
    }
    if (!$form_state['values']['lastname']) {
        form_set_error('lastname', t('Le champ nom est obligatoire.'));
    }
    if (!$form_state['values']['firstname']) {
        form_set_error('firstname', t('Le champ prenom est obligatoire.'));
    }
    if (!$form_state['values']['birthday']) {
        form_set_error('birthday', t('Le champ date de naissance est obligatoire.'));
    }
    if (!$form_state['values']['man_woman']) {
        form_set_error('man_woman', t('Le champ H/F est obligatoire.'));
    }
    if (!$form_state['values']['num_rue']) {
        form_set_error('num_rue', t('Les champs adresse sont obligatoires.'));
    }
    if (!$form_state['values']['nom_rue']) {
        form_set_error('nom_rue', t('Les champs adresse sont obligatoires.'));
    }
    if (!$form_state['values']['zip_code']) {
        form_set_error('zip_code', t('Le champ code postal  est obligatoire.'));
    }
    if (!$form_state['values']['city']) {
      form_set_error('city', t('Le champ ville est obligatoire.'));
    }
    if (!$form_state['values']['highest_level']) {
        form_set_error('highest_level', t('Le champ diplome le plus élevé est obligatoire.'));
    }
    if (!$form_state['values']['last_status']) {
        form_set_error('last_status', t('Le champ dernière situation est obligatoire.'));
    }
    if (!$form_state['values']['contingency_fund']) {
        form_set_error('contingency_fund', t('Le champ caisse de prévoyance est obligatoire.'));
    }
    if (!$form_state['values']['phone_number'] && !$form_state['values']['email']) {
        form_set_error('phone_number', t('Veuillez renseigner obligatoirement un numéro de téléphone ou une adresse courriel. ' ) );
        form_set_error('email', '' );
    }

    return $form;

}