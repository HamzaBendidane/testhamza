<?php

define('TABLE_OF', 'dgf_form_organisme_formation');
define('TABLE_OF_PRO', 'dgf_contrat_pro');
define('TABLE_DGF', 'dgf');

//---------------------------------------------------------------------
// Liste des constantes des messages d'erreurs standards du formulaire
//---------------------------------------------------------------------

define('ERR_STD_OF_SIRET', 'Le champ numéro de SIRET est obligatoire.');
define('ERR_STD_OF_ACTIVITY', 'Le champ numéro de déclaration d\'activité est obligatoire.');
define('ERR_STD_OF_CORP_NAME', 'Le champ raison sociale est obligatoire.');
define('ERR_STD_OF_EXTRA_COUNT', 'Le champ durée totale est obligatoire.');
define('ERR_STD_OF_STREET_NUMBER', 'Le champ numéro de rue est obligatoire.');
define('ERR_STD_OF_STREET_NAME', 'Le champ nom de rue est obligatoire.');
define('ERR_STD_OF_COMPLEMENT', 'Le champ complément d\'adresse est obligatoire.');
define('ERR_STD_OF_ZIP_CODE', 'Le champ code postal est obligatoire.');
define('ERR_STD_OF_CITY', 'Le champ ville est obligatoire.');
define('ERR_STD_OF_COUNTRY', 'Le champ pays est obligatoire.');
define('ERR_STD_OF_PHONE', 'Le champ numéro de téléphone est obligatoire.');
define('ERR_STD_OF_EMAIL', 'Le champ email est obligatoire.');
define('ERR_STD_OF_TVA', 'Le champ numéro de TVA intracommunautaire est obligatoire.');
define('ERR_STD_OF_TITLE', 'Le champ civilité du contact est obligatoire.');
define('ERR_STD_OF_CONTACT_LASTNAME', 'Le champ nom du contact est obligatoire.');
define('ERR_STD_OF_CONTACT_FIRSTNAME', 'Le champ prénom du contact est obligatoire.');
define('ERR_STD_OF_CONTACT_FONCTION', 'Le champ fonction du contact est obligatoire.');
define('ERR_STD_OF_CONTACT_PHONE_EMAIL', 'Le champ email ou téléphone du contact est obligatoire.');
define('ERR_STD_OF_CONTACT_SELECT', 'Veuillez choisir parmi le(s) contact(s) ou en créer un nouveau.');
define('ERR_STD_OF_DIRECT_PAYMENT', 'Le choix du paiement (direct ou remboursement) est obligatoire.');
define('ERR_STD_OF_PEDAGOGICAL_COST', 'Le champ coût pédagogique est obligatoire.');
define('ERR_STD_OF_EVAL_PRE_FORMATIVE', '@ definir ERR_STD_OF_EVAL_PRE_FORMATIVE');
define('ERR_STD_OF_CERT_PASSING', '@ definir ERR_STD_OF_CERT_PASSING');

//-----------------------------------------------------------------------
// Liste des constantes des messages d'erreurs spécifiques du formulaire
//-----------------------------------------------------------------------
define('ERR_SPE_OF_PHONE_EMAIL', 'Au moins un des deux champs numéro de téléphone ou email est obligatoire.');
define('ERR_SPE_OF_NEW_CONTACT_LAST', 'Le champ prénom du nouveau contact est obligatoire.');
define('ERR_SPE_OF_NEW_CONTACT_FIRST', 'Le champ nom du nouveau contact est obligatoire.');
define('ERR_SPE_OF_NEW_CONTACT_FONCTION', 'Le champ fonction du nouveau contact est obligatoire.');
define('ERR_SPE_OF_NEW_CONTACT_PHONE_MAIL', 'Au moins un des deux champs (numéro de téléphone ou courriel) du nouveau contact est obligatoire.');
define('ERR_SPE_OF_VALID_SIRET', 'Le champ N° de SIRET n’est pas conforme.');
define('ERR_SPE_OF_SIRET_INT', 'Le champ SIRET doit être un nombre valide.');
define('ERR_SPE_OF_ACTIVITY_INT', 'Le champ numéro d\'activité doit être un nombre valide.');
define('ERR_SPE_OF_EXTRA_COUNT_INT', 'Le champ durée totale doit être un nombre valide.');
define('ERR_SPE_OF_STREET_NUMBER_INT', 'Le champ numéro de rue doit être un nombre valide.');
define('ERR_SPE_OF_ZIP_CODE_INT', 'Le champ code postal doit être un nombre valide.');
define('ERR_SPE_OF_PHONE_INT', 'Le champ téléphone doit être un nombre valide.');
define('ERR_STD_OF_CONTACT_PHONE_INT', 'Le champ téléphone du contact doit être un nombre valide.');
define('ERR_STD_OF_EMAIL_PHONE', 'Le champ email du contact n\'est pas un email valide.');
define('ERR_STD_OF_MODAL_CONTACT_PHONE_OR_MAIL_MISS', 'Le champ téléphone ou courriel du nouveau contact est obligatoire.');
define('ERR_STD_OF_MODAL_CONTACT_FUNCTION_MISS', 'Le champ fonction du nouveau contact est obligatoire.');
define('ERR_STD_OF_MODAL_CONTACT_FIRSTNAME_MISS', 'Le champ prénom du nouveau contact est obligatoire.');
define('ERR_STD_OF_MODAL_CONTACT_LASTNAME_MISS', 'Le champ nom du nouveau contact est obligatoire.');
define('ERR_STD_OF_MODAL_CONTACT_TITLE_MISS', 'Le champ civilité du nouveau contact est obligatoire.');
// define('ERR_SPE_OF_CHOSEN_CONTACT', 'Le champ téléphone du contact doit être un nombre valide.');

//-----------------------------------------------------------------------
// Liste des constantes pour remplir les champs select
//-----------------------------------------------------------------------

define('MESS_CHOOSE_CONTACT', 'veuillez choisir un contact.');

//-----------------------------------------------------------------------
// Liste des constantes pour la BDD
//-----------------------------------------------------------------------
define('TABLE_ORGANISME_FORMATION', 'dgf_form_organisme_formation');
define('TABLE_FORMATION', 'dgf_form_formation');
define('TABLE_INTITULE_FORMATION', 'ref_intitule_formation');
define('TABLE_FINALITE_FORMATION', 'ref_finalite_formation');
define('TABLE_FORMATION_REPARTITION', 'dgf_form_formation_repartition');
// define('TABLE_DGF', 'dgf');
define('TABLE_CONTRAT_PRO', 'dgf_contrat_pro');
define('TABLE_CONTRAT', 'dgf_form_contrat');
// define('TABLE_DRUPAL_USER', 'drupal_user');
