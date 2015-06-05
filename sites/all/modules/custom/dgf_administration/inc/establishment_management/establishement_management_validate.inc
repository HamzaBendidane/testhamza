<?php

///-----------------------------------------------------
// Validation standard (les champs ne devant être vides)
//-----------------------------------------------------

/**
 * Validation standard for the contract step
 *
 * @param type $form
 * @param type $form_state
 */
function opcaim_establishment_management_standard_validate($form, &$form_state) {

  if ($form_state['values']['siret'] == NULL) {
    form_set_error('siret', t(@ERR_STD_ESTABL_MANAG_SIRET));
  }

  if (!$form_state['values']['street_number']) {
    form_set_error('address', t(@ERR_STD_ESTABL_MANAG_NUMBER_STREET));
  }

  if (!$form_state['values']['street_name']) {
    form_set_error('address', t(@ERR_STD_ESTABL_MANAG_NAME_STREET));
  }

  if (!$form_state['values']['adress_complement']) {
    form_set_error('address', t(@ERR_STD_ESTABL_MANAG_COMPLEMENT_ADRESS));
  }

  if (!$form_state['values']['city']) {
    form_set_error('city', t(@ERR_STD_ESTABL_MANAG_CITY));
  }

  if (!$form_state['values']['code_naf']) {
    form_set_error('code_naf', t(@ERR_STD_ESTABL_MANAG_NAF));
  }

  if (!$form_state['values']['corporate_name']) {
    form_set_error('corporate_name', t(@ERR_STD_ESTABL_MANAG_CORP_NAME));
  }

  if (!$form_state['values']['zip_code']) {
    form_set_error('zip_code', t(@ERR_STD_ESTABL_MANAG_ZIP));
  }

  if (!$form_state['values']['phone_number']) {
    form_set_error('phone_number', t(@ERR_STD_ESTABL_MANAG_PHONE));
  }

  if (!$form_state['values']['code_nace']) {
    form_set_error('code_nace', t(@ERR_STD_ESTABL_MANAG_NACE));
  }

  if (!$form_state['values']['title']) {
    form_set_error('title', t(@ERR_STD_ESTABL_MANAG_TITLE));
  }

  if (!$form_state['values']['firstname']) {
    form_set_error('firstname', t(@ERR_STD_ESTABL_MANAG_FIRTSNAME));
  }

  if (!$form_state['values']['email']) {
    form_set_error('email', t(@ERR_STD_ESTABL_MANAG_EMAIL));
  }

  if (!$form_state['values']['lastname']) {
    form_set_error('lastname', t(@ERR_STD_ESTABL_MANAG_LASTNAME));
  }

  if (!$form_state['values']['function']) {
    form_set_error('function', t(@ERR_STD_ESTABL_MANAG_FUNCTION));
  }
}

//-----------------------------------------
// Validation spécifiques à certains champs
//-----------------------------------------
function opcaim_establishment_management_specific_validate($form, &$form_state) {

//   if ($form_state['values']['siret']) { // TODO : contr^le sur siret et clé (RGC_VAL-ETA14)
//     form_set_error('siret', t(@ERR_SPE_ESTABL_VALID_SIRET_KO));
//   }

  if (check_siret_already_exist($form_state['values']['siret'])) { // TODO : contr^le sur siret déjà trouvé (RGC_VAL-ETA15)
    form_set_error('siret', t(@ERR_SPE_ESTABL_MANAG_SIRET_FOUND));
  }
}
