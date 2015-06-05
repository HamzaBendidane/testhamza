<?php

/**
 * dgf_formation_form_validate_standard
 *
 * Description à faire
 *
 * @param array $form
 * @param array $form_state
 */
function dgf_formation_form_validate_standard($form, $form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-modal-quit--2') {
    drupal_goto('/dashboard');
  }

  if (!shared_validate_date($form_state['values']['date_begin'] )) {
    form_set_error('date_begin', @ERR_DATE_NOT_VALID);
  }

  if (!shared_validate_date($form_state['values']['date_end'] )) {
    form_set_error('date_end', @ERR_DATE_NOT_VALID);
  }

  if (!shared_validate_date($form_state['values']['training_start'] )) {
    form_set_error('training_start', @ERR_DATE_NOT_VALID );
  }

  if (!shared_validate_date($form_state['values']['date_exam'] )) {
    form_set_error('date_exam', @ERR_DATE_NOT_VALID );
  }
}

/**
 * Validation for the training step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_formation_form_validate($form, &$form_state) {

  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    drupal_goto('/dgf/demande/contrat/'.arg(3));
  }

  dgf_cp_contract_date_specific_validate($form, $form_state);

  $date_debut_formation = date_create_from_format('d/m/Y', $form_state['values']['training_start']);
  $date_examen = date_create_from_format('d/m/Y', $form_state['values']['date_exam']);
  $date_debut_contrat = date_create_from_format('d/m/Y', $form_state['values']['date_begin']);
  $date_fin_contrat = date_create_from_format('d/m/Y', $form_state['values']['date_end']);

  if ($date_debut_formation > $date_examen) {
    form_set_error('training_start', '');
    form_set_error('date_exam', @ERR_SPE_FORMATION_DATE_EXAMEN);
  }

    if (!shared_check_date_contrat_formation($form_state['values']['date_begin'],$form_state['values']['date_end'])){
        form_set_error('date_end', t(ERR_SPE_CONTRAT_TRAINING_DURATION));
    }


  // RGC_DGF-CP43
  // SI CQPM ET Date de fin de contrat est plus de 30 jours après la date d’examen
  // OU Date de fin de contrat est plus de 60 jours après la date d’examen.
  // => MSG_ERR_DGF-CP42
  if (isset($date_examen) && $date_examen) {
    $date_tmp = $date_examen;

    if (isset($form_state['values']['num_CQPI_CQPM']) && $form_state['values']['num_CQPI_CQPM'] != '') {
      $date_tmp = $date_tmp->add(new DateInterval('P30D'));
    } else {
      $date_tmp = $date_tmp->add(new DateInterval('P60D'));
    }

    if ($date_fin_contrat > $date_tmp) {
      form_set_error('date_end', '');
      form_set_error('date_exam', @ERR_SPE_FORMATION_DATE_EXAMEN_CP42 );
    }
    $date_examen = date_create_from_format('d/m/Y', $form_state['values']['date_exam']);
  }
    if (!shared_check_date_contrat_formation($form_state['values']['date_begin'],$form_state['values']['date_end'])){
        form_set_error('training_duration', t(@ERR_SPE_CONTRAT_TRAINING_DURATION));
    }


    // RGC_DGF-CP44
  // SI la date de début de contrat est plus de 60 jours avant la date de formation
  // => MSG_ERR_DGF-CP43


    if ($date_debut_contrat && $date_debut_formation) {
    $date_debut_contrat_plus60 = $date_debut_contrat->add(new DateInterval('P60D' ) );
    if ($date_debut_formation > $date_debut_contrat_plus60) {
      form_set_error('date_begin','');
      form_set_error('training_start', @ERR_SPE_FORMATION_DATE_DEBUT_CP43);
    }
    $date_debut_contrat = date_create_from_format('d/m/Y', $form_state['values']['date_begin']);
  }

  // RGC_DGF-CP47
  // La durée entre le début dela formation et la date d'examen ne doit pas excédée 24 mois
  if (shared_validate_date($form_state['values']['training_start'] ) && shared_validate_date($form_state['values']['date_exam'] )) {
    $date_debut_formation_plus24 = $date_debut_formation->add(new DateInterval('P24M'));
    $date_examen = date_create_from_format('d/m/Y', $form_state['values']['date_exam']);
    if ($date_debut_formation_plus24 < $date_examen) {
      form_set_error('training_start', '');
      form_set_error('date_exam', @ERR_SPE_FORMATION_DATE_DEBUT_CP47);
    }
    $date_debut_formation = date_create_from_format('d/m/Y', $form_state['values']['training_start']);
  }


    // RGC_DGF-CP45
  // SI non (15 < la durée totale formation/durée totale du contrat (nbre d’heures hebdomadaires) x 100 < 50 )
  // => MSG_ERR_DGF-CP44
  $duree_totale_formation = (int) $form_state['values']['total_duration'] * 60;
  $duree_totale_contrat = _dgf_formation_get_cp_duree_contrat_minute($form_state['values']['id_dgf'],
      $date_debut_contrat, $date_fin_contrat);

  if (isset($duree_totale_formation ) && isset($duree_totale_contrat )) {
    if ($duree_totale_contrat > 0) {
      $ratio = ($duree_totale_formation / $duree_totale_contrat);
      if ($ratio < 0.15 || $ratio > 0.5) {
        form_set_error('total_duration', @ERR_STD_FORMATION_TOTAL_DURATION );
      }
    }
  }

  // RGC_DGF-CP48
  if (isset($form_state['values']['total_duration'])
      && (isset($form_state['values']['duration_main_learning'])
          || isset($form_state['values']['accompanying_actions']))) {
    if ((int)$form_state['values']['duration_main_learning'] + (int)$form_state['values']['accompanying_actions'] >
        $form_state['values']['total_duration']) {
      form_set_error('total_duration', '');
      form_set_error('duration_main_learning', '');
      form_set_error('accompanying_actions', @ERR_SPE_FORMATION_DURATION_MAIN_LEARNING );
    }
  }
  $NumberDays = dgf_cp_test_date_exam($form_state);
  if ($form_state['values']['type_qualification'] == 1 && $NumberDays > 30) {
    // TODO message d'erreur 
    // Et faire le cas soixante jours avec autres cas en dessous
  }

  if ($form_state['values']['type_qualification'] != 1 && $NumberDays > 60) {
    // TODO message d'erreur 
  }
}

function _dgf_formation_get_cp_duree_contrat_minute($id_dgf, $date_debut_contrat, $date_fin_contrat) {
  $temp_dgf_form_contrat = contrat_db_get_temp_dgf_form_salarie($id_dgf);

  $duree = 0;
  if (isset($temp_dgf_form_contrat) && $date_debut_contrat) {
    $nb_minute_hebdo = (int) $temp_dgf_form_contrat['duree_hebdo_travail_heure'] * 60
      + (int) $temp_dgf_form_contrat['duree_hebdo_travail_minute'];

    $interval = $date_debut_contrat->diff($date_fin_contrat );
    $nb_semaines = (int) ($interval->days / 7);

    if (isset($nb_semaines ) && isset($nb_minute_hebdo )) {
      $duree = $nb_semaines * $nb_minute_hebdo;
    }
  }
  return $duree;
}



function dgf_cp_test_date_exam($form_state) {
  $dateEnd = date_format(date_create_from_format('d/m/Y', $form_state['values']['date_end']), 'Y-m-d');
  $dateEnd = new DateTime($dateEnd);

  $dateExam = date_format(date_create_from_format('d/m/Y', $form_state['values']['date_exam']), 'Y-m-d');
  $dateExam = new DateTime($dateExam);

  $interval = $dateExam->diff($dateEnd);
  $result = $interval->m * 30 + $interval->d; 
  
  return $result;

}
