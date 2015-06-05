<?php

// ----------------------------------------------------------------------------
// Fonctions de mise en mémoire (suivant) et de sauvegarde en BDD pour contrat
// ----------------------------------------------------------------------------

/**
 * Submit for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function establishment_management_form_submit($form, &$form_state) {

//   if ($form_state['triggering_element']['#value'] == 'Suivant') {
//     if ($form_state['storage']['dgf_cp_contract_nature'] = 'CDI') {
//     $natureContract = 1;
//   } else {
//     $natureContract = 2;
//   }

//   if (isset($form_state['type_renewal'])) {
//     $form_state['values']['type'] = $form_state['type_renewal'] + 3;
//   }

//   // Mise au format date
//   $dateBegin = str_replace("/", "-", $form_state['values']['date_begin']);
//   $dateBegin = date('Y-m-d', strtotime($dateBegin));
//   $dateEnd = str_replace("/", "-", $form_state['values']['date_end']);
//   $dateEnd = date('Y-m-d', strtotime($dateEnd));

//   $form_state['rebuild'] = TRUE;

//   db_set_active(@DB_EXTRANET);

//   $query = db_insert(@TABLE_CONTRAT)
//               ->fields(array(
//                     'id' => 4,
//                     'id_ref_type_contrat' => (intval($form_state['values']['type'])) ? $form_state['values']['type'] : NULL,
//                     'id_ref_type_contrat_pro' => (intval($natureContract)) ? $natureContract : NULL,
//                     'date_debut' => ($dateBegin) ? $dateBegin : NULL,
//                     'date_fin' => ($dateEnd) ? $dateEnd : NULL,
//                     'duree_contrat_mois' => ($form_state['values']['training_duration']) ? $form_state['values']['training_duration'] : NULL,
//                     'duree_essai_jour' => ($form_state['values']['test_period']) ? $form_state['values']['test_period'] : NULL,
//                     'duree_hebdo_travail_heure' => ($form_state['values']['weekly_hour']) ? $form_state['values']['weekly_hour'] : NULL,
//                     'duree_hebdo_travail_minute' => NULL,
//                     'coefficient' => ($form_state['values']['coefficient']) ? $form_state['values']['coefficient'] : NULL,
//                     'id_ref_convention_collective' => ($form_state['values']['collective_convention']) ? $form_state['values']['collective_convention'] : NULL,
//                     'id_ref_groupe' => ($form_state['values']['group']) ? $form_state['values']['group'] : NULL,
//                     'salaire_brut_mensuelle' => ($form_state['values']['monthly_gross_pay']) ? $form_state['values']['monthly_gross_pay'] : NULL,
//                     'emploi_occupe' => ($form_state['values']['position_held']) ? $form_state['values']['position_held'] : NULL,
//                     'date_creation' => date("Y-m-d"),
//                     'id_user_creation' => 1, // TO DO récupérer l'id de l'utilisateur connect,
//                     'date_last_edit' => date("Y-m-d"),
//                     'id_user_last_edit' => 1, // TO DO récupérer l'id de l'utilisateur connect,
//               ));
//   $query->execute();

//   db_set_active();
//   drupal_goto('/dgf/demande/formation');

//   }
}
