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
function opcaim_establishment_validation_edit_standard_validate($form, &$form_state) {

  if ($form_state['values']['siret'] == NULL) {
    form_set_error('siret', t(@ERR_STD_ESTABL_VALID_SIRET));
  }

  if (!$form_state['values']['street_number']) {
    form_set_error('street_number', t(@ERR_STD_ESTABL_VALID_NUMBER_STREET));
  }

  if (!$form_state['values']['street_name']) {
    form_set_error('street_name', t(@ERR_STD_ESTABL_VALID_NAME_STREET));
  }

//   if (!$form_state['values']['adress_complement']) {
//     form_set_error('adress_complement', t(@ERR_STD_ESTABL_VALID_COMPLEMENT_ADRESS));
//   }

  if (!$form_state['values']['city']) {
    form_set_error('city', t(@ERR_STD_ESTABL_VALID_CITY));
  }

  if (!$form_state['values']['code_naf']) {
    form_set_error('code_naf', t(@ERR_STD_ESTABL_VALID_NAF));
  }

  if (!$form_state['values']['corporate_name']) {
    form_set_error('corporate_name', t(@ERR_STD_ESTABL_VALID_CORP_NAME));
  }

  if (!$form_state['values']['zip_code']) {
    form_set_error('zip_code', t(@ERR_STD_ESTABL_VALID_ZIP));
  }

  if (!$form_state['values']['phone_number']) {
    form_set_error('phone_number', t(@ERR_STD_ESTABL_VALID_PHONE));
  }

//   if (!$form_state['values']['title']) {
//     form_set_error('title', t(@ERR_STD_ESTABL_VALID_TITLE));
//   }

//   if (!$form_state['values']['firstname']) {
//     form_set_error('firstname', t(@ERR_STD_ESTABL_VALID_FIRTSNAME));
//   }

//   if (!$form_state['values']['email']) {
//     form_set_error('email', t(@ERR_STD_ESTABL_VALID_EMAIL));
//   }

//   if (!$form_state['values']['lastname']) {
//     form_set_error('lastname', t(@ERR_STD_ESTABL_VALID_LASTNAME));
//   }

//   if (!$form_state['values']['function']) {
//     form_set_error('function', t(@ERR_STD_ESTABL_VALID_FUNCTION));
//   }
}

//-----------------------------------------
// Validation spécifiques à certains champs
//-----------------------------------------
function opcaim_establishment_validation_edit_specific_validate($form, &$form_state) {

//   if ($form_state['values']['siret']) { // TODO : contr^le sur siret et clé (RGC_VAL-ETA14)
//     form_set_error('siret', t(@ERR_SPE_ESTABL_VALID_SIRET_KO));
//   }

  if (!$form_state['values']['is_modif'] && check_siret_already_exist($form_state['values']['siret'])) {
    form_set_error('siret', t(@ERR_SPE_ESTABL_VALID_SIRET_FOUND));
  }
//   if (!_is_valid_siret_number($form_state['values']['siret'])) { // TODO
//     form_set_error('siret', t(@ERR_SPE_ESTABL_VALID_SIRET_KO));
//   }
}

function _is_valid_siret_number($siret) {
  if (strlen($siret) != 14) return false; // le SIRET doit contenir 14 caractères
	if (!is_numeric($siret)) return false; // le SIRET ne doit contenir que des chiffres

	// on prend chaque chiffre un par un
	// si son index (position dans la chaîne en commence à 0 au premier caractère) est pair
	// on double sa valeur et si cette dernière est supérieure à 9, on lui retranche 9
	// on ajoute cette valeur à la somme totale

	$sum = 0;
	for ($index = 0; $index < 14; $index ++)
	{
		$number = (int) $siret[$index];
		if (($index % 2) == 0) { if (($number *= 2) > 9) $number -= 9; }
		$sum += $number;
	}

	// le numéro est valide si la somme des chiffres est multiple de 10
	if (($sum % 10) != 0) return false; else return true;

}
