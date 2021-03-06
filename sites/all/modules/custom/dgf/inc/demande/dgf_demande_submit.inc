<?php

/**
 * Submit for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_demande_form_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-next') {
   //a rajouter à la transmission de tous les formulaires
    $_SESSION['demande']['nature_demande'] = $form_state['values']['nature_demande'];
    $_SESSION['demande']['nature_formation'] = $form_state['values']['nature_formation'];
    if ($form_state['values']['nature_demande'] == 1) {
      if (arg(2)) {
        drupal_goto('/dgf/demande/contrat-pro/stagiaire/'.arg(2));
      } else {
        drupal_goto('/dgf/demande/contrat-pro/stagiaire');
      }
    } else {
      drupal_set_message('Seul les demandes de contrat pro sont implémentées', 'info');
    }
  }
}