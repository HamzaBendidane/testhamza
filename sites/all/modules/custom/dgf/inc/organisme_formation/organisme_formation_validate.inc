<?php

/**
 * Validation for the trainee step
 *
 * @param type $form
 * @param type $form_state
 */
function dgf_organisme_formation_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#id'] == 'edit-back') {
    drupal_goto('/dgf/demande/formation/'.arg(3));
  } else if ($form_state['triggering_element']['#id'] == 'edit-modal-quit--2') {
    drupal_goto('/dashboard');
  }
}

function dgf_organisme_formation_standard_validate($form, &$form_state) {
  $id_of = get_id_if_siret_already_exist($form_state['values']['siret_number']);

  if (!$form_state['values']['siret_number']) {
    form_set_error('siret_number', t(@ERR_STD_OF_SIRET));
  }

  if (!$form_state['values']['activity_number']) {
    form_set_error('activity_number', t(@ERR_STD_OF_ACTIVITY));
  }

  if (!$form_state['values']['corporate_name']) {
    form_set_error('corporate_name', t(@ERR_STD_OF_CORP_NAME));
  }

  if ($form_state['values']['direct_payment'] === null) {
    form_set_error('direct_payment', t(@ERR_STD_OF_DIRECT_PAYMENT));
  }

  if (!$form_state['values']['pedagogical_cost']) {
    form_set_error('pedagogical_cost', t(@ERR_STD_OF_PEDAGOGICAL_COST));
  }

  // Si l'of est nouveau
  if ($id_of == false) {

     if (!$form_state['values']['street_number']) {
       form_set_error('street_number', t(@ERR_STD_OF_STREET_NUMBER));
     }

     if (!$form_state['values']['street_name']) {
       form_set_error('street_name', t(@ERR_STD_OF_STREET_NAME));
     }

     if (!$form_state['values']['zip_code']) {
       form_set_error('zip_code', t(@ERR_STD_OF_ZIP_CODE));
     }

     if (!$form_state['values']['city']) {
       form_set_error('city', t(@ERR_STD_OF_CITY));
     }

     if (!$form_state['values']['country']) {
       form_set_error('country', t(@ERR_STD_OF_COUNTRY));
     }

     if (!$form_state['values']['phone_number']) {
       form_set_error('phone_number', t(@ERR_STD_OF_PHONE));
     }

     if (!$form_state['values']['email']) {
       form_set_error('email', t(@ERR_STD_OF_EMAIL));
     }

     if (!$form_state['values']['tva_number'] && $form_state['values']['tva_bool']) {
       form_set_error('tva_number', t(@ERR_STD_OF_TVA));
     }

     if (!$form_state['values']['new_contact_title']) {
       form_set_error('new_contact_title', t(@ERR_STD_OF_TITLE));
     }

     if (!$form_state['values']['new_contact_lastname']) {
       form_set_error('new_contact_lastname', t(@ERR_STD_OF_CONTACT_LASTNAME));
     }

     if (!$form_state['values']['new_contact_firstname']) {
       form_set_error('new_contact_firstname', t(@ERR_STD_OF_CONTACT_FIRSTNAME));
     }

     if (!$form_state['values']['new_contact_fonction']) {
       form_set_error('new_contact_fonction', t(@ERR_STD_OF_CONTACT_FONCTION));
     }

     if (!$form_state['values']['new_contact_mail'] && !$form_state['values']['new_contact_phone']) {
       form_set_error('new_contact_phone', t(@ERR_STD_OF_CONTACT_PHONE_EMAIL));
     }
   }
}

function dgf_organisme_formation_specific_validate($form, &$form_state) {
  $id_of = get_id_if_siret_already_exist($form_state['values']['siret_number']);
//   if ($form_state['values']['contact'] == t(@MESS_CHOOSE_CONTACT) && $form_state['values']['is_created_contact']) {
//     form_set_error('contact', t(@ERR_SPE_OF_CHOSEN_CONTACT));
//   }
//   if (!is_int(intval($form_state['values']['siret_number']))) {
//     form_set_error('siret_number', t(@ERR_SPE_OF_SIRET_INT));
//   }

  if (!is_numeric($form_state['values']['activity_number'])) {
    form_set_error('activity_number', t(@ERR_SPE_OF_ACTIVITY_INT));
  }

  // Si l'of est nouveau
  if ($id_of == false) {

    if (!is_numeric($form_state['values']['street_number'])) {
      form_set_error('street_number', t(@ERR_SPE_OF_STREET_NUMBER_INT));
    }

    if (!is_numeric($form_state['values']['zip_code'])) {
      form_set_error('zip_code', t(@ERR_SPE_OF_ZIP_CODE_INT));
    }

    if (!is_numeric($form_state['values']['phone_number'])) {
      form_set_error('phone_number', t(@ERR_SPE_OF_PHONE_INT));
    }

    if (!is_numeric($form_state['values']['new_contact_phone'])) {
      form_set_error('new_contact_phone', t(@ERR_STD_OF_CONTACT_PHONE_INT));
    }

    if (!_is_valid_siret_number($form_state['values']['siret_number'])) {
      form_set_error('siret_number', t(@ERR_SPE_OF_VALID_SIRET));
    }

    if (!isset($form_state['values']['new_contact_phone']) && !isset($form_state['values']['new_contact_mail'])) {
      form_set_error('new_contact_phone', t(@ERR_SPE_OF_PHONE_EMAIL));
    }
  } else {
    // si paiement direct et création d'un contact on vérifie les infos
    if ($form_state['values']['direct_payment'] === '1' && !$form_state['values']['select_contact']) {
      if (!$form_state['values']['modal_contact_title']) {
        form_set_error('modal_contact_title', t(@ERR_STD_OF_MODAL_CONTACT_TITLE_MISS));
      }
      if (!$form_state['values']['modal_contact_lastname']) {
        form_set_error('modal_contact_lastname', t(@ERR_STD_OF_MODAL_CONTACT_LASTNAME_MISS));
      }
      if (!$form_state['values']['modal_contact_firstname']) {
        form_set_error('modal_contact_firstname', t(@ERR_STD_OF_MODAL_CONTACT_FIRSTNAME_MISS));
      }
      if (!$form_state['values']['modal_contact_fonction']) {
        form_set_error('modal_contact_fonction', t(@ERR_STD_OF_MODAL_CONTACT_FUNCTION_MISS));
      }
      if (!is_numeric($form_state['values']['modal_contact_phone'])) {
        form_set_error('modal_contact_phone', t(@ERR_STD_OF_CONTACT_PHONE_INT));
      }
      if ($form_state['values']['modal_contact_mail'] && !filter_var($form_state['values']['modal_contact_mail'], FILTER_VALIDATE_EMAIL)) {
        form_set_error('modal_contact_mail', t(@ERR_STD_OF_EMAIL_PHONE));
      }
      if (!$form_state['values']['modal_contact_mail'] && !$form_state['values']['modal_contact_phone']) {
        form_set_error('modal_contact_mail', '');
        form_set_error('modal_contact_phone', t(@ERR_STD_OF_MODAL_CONTACT_PHONE_OR_MAIL_MISS));
      }
    }
  }
}

function _is_valid_siret_number($siret) {
  //longueur de la chaine $num
  $length = strlen($siret);

  //resultat de l'addition de tous les chiffres
  $total = 0;
  for ($i = $length-1 ; $i >= 0 ; $i--) {
    $digit = substr($siret, $i, 1);

    if ((($length - $i) % 2) == 0) {
      $digit = $digit * 2;
      if ($digit > 9) {
        $digit = $digit - 9;
      }
    }

    $total += $digit;
  }

  if (($total % 10) == 0) {
    return true;
  } else {
    return false;
  }
}