<?php

/**
 * Validation for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_contrat_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    drupal_goto('/dgf/demande/contrat-pro/stagiaire/'.arg(3));
  } else if ($form_state['triggering_element']['#id'] == 'edit-modal-quit--2') {
    drupal_goto('/dashboard');
  }
}

///-----------------------------------------------------
// Validation standard (les champs ne devant être vides)
//-----------------------------------------------------

function dgf_cp_contract_date_standard_validate($form, &$form_state) {
  if (!$form_state['values']['date_begin']) {
    form_set_error('date_begin', t(@ERR_STD_CONTRAT_DATE_BEGIN));
  }

  if (!$form_state['values']['date_end']) {
    form_set_error('date_end', t(@ERR_STD_CONTRAT_DATE_END));
  }
}

function dgf_cp_contract_date_specific_validate($form, &$form_state) {
  $date = date('Y-m-d');
  $now = new DateTime($date);
  if ($form_state['values']['date_begin']) {
    $dateBegin = date_format(date_create_from_format('d/m/Y', $form_state['values']['date_begin']), 'Y-m-d');
    $dateBegin = new DateTime($dateBegin);
    $difference = date_diff($dateBegin, $now);

    if ($dateBegin < $now) {
      if (intval($difference->format('%a')) >= 25) {
        form_set_error('date_begin', t(@ERR_SPE_DATE_DIFF_NOW));
      }
    }
  }
}

/**
 * Validation standard for the contract step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_cp_contract_standard_validate($form, &$form_state) {
  if ($form_state['values']['nature'] == NULL) {
    form_set_error('nature', t(@ERR_STD_CONTRAT_NATURE));
  }

  if (!$form_state['values']['type']) {
    form_set_error('type', t(@ERR_STD_CONTRAT_TYPE));
  }

  dgf_cp_contract_date_standard_validate($form, $form_state);

  if (!$form_state['values']['training_duration']) {
    form_set_error('training_duration', t(@ERR_STD_CONTRAT_TRAINING_DURATION));
  }

  if (!$form_state['values']['test_period']) {
    form_set_error('test_period', t(@ERR_STD_CONTRAT_TEST_PERIOD));
  }

  if (!$form_state['values']['weekly_hour']) {
    form_set_error('weekly_hour', t(@ERR_STD_CONTRAT_WEEKLY_HOUR));
  }

  if (!$form_state['values']['weekly_minute'] && $form_state['values']['weekly_minute'] != 0) {
    form_set_error('weekly_minute', t(@ERR_STD_CONTRAT_WEEKLY_HOUR));
  }

  if (!$form_state['values']['position_held']) {
    form_set_error('position_held', t(@ERR_STD_CONTRAT_POSITION_HELD));
  }

  if (!$form_state['values']['collective_convention']) {
    form_set_error('collective_convention', t(@ERR_STD_CONTRAT_COLLECTIVE_CONVENTION));
  }

  if (!$form_state['values']['monthly_gross_pay']) {
    form_set_error('monthly_gross_pay', t(@ERR_STD_CONTRAT_MONTHLY_PAY));
  }

  if ($form_state['values']['niveau'] && !is_numeric($form_state['values']['niveau'])) {
    form_set_error('niveau', t(@ERR_STD_CONTRAT_NIVEAU_INT));
  }
}

//-----------------------------------------
// Validation spécifiques à certains champs
//-----------------------------------------
function dgf_cp_contract_specific_validate($form, &$form_state) {
  dgf_cp_contract_date_specific_validate($form, $form_state);

	// Validation du champ durée de la formation
	$duration = $form_state['values']['training_duration'];
    if ($form_state['values']['modal_save'] == "Oui") return;

    if ( !shared_check_date_contrat_formation($form_state['values']['date_begin'],$form_state['values']['date_end'])){
        form_set_error('training_duration', t(@ERR_SPE_CONTRAT_TRAINING_DURATION));
    }

  // validation du champ période d'essai
  if (!is_int(intval($form_state['values']['test_period']))) {
    form_set_error('test_period', t(@ERR_SPE_CONTRAT_TEST_PERIOD));
  }

  if ($form_state['values']['nature'] == '1' && $form_state['values']['test_period'] > 30) {
    form_set_error('test_period', t(@ERR_SPE_CONTRAT_TEST_PERIOD_CDD));
  }

  if (!is_int(intval($form_state['values']['weekly_hour']))) {
     form_set_error('weekly_hour', t(@ERR_SPE_CONTRAT_WEEKLY_HOUR));
  }

  // validation des champs en relation coefficient / niveau et groupe
  if (!$form_state['values']['group'] && (!$form_state['values']['coefficient'] || !$form_state['values']['niveau'])) {
    form_set_error('coefficient', '');
    form_set_error('niveau', '');
    form_set_error('group', t(@ERR_SPE_CONTRAT_COEFF_GROUP));
  }

  if ($form_state['values']['coefficient'] || $form_state['values']['coefficient'] === '0') {
    // validation du champ coefficient
    if (!is_int(intval($form_state['values']['coefficient']))) {
      form_set_error('coefficient', t(@ERR_SPE_CONTRAT_COEFF));
    }

    if ($form_state['values']['coefficient'] < 140 || $form_state['values']['coefficient'] > 255) {
      form_set_error('coefficient', t(@ERR_SPE_CONTRAT_COEFF_VALUE));
    }
  }

  // validation du champ salaire brut mensuel
  if ($form_state['values']['monthly_gross_pay'] < $form_state['values']['min_monthly_gross_pay']) {
    form_set_error('monthly_gross_pay',
      t(@ERR_SPE_CONTRAT_MONTHLY_PAY_START . $form_state['values']['min_monthly_gross_pay']
      . @ERR_SPE_CONTRAT_MONTHLY_PAY_END));
  }
}