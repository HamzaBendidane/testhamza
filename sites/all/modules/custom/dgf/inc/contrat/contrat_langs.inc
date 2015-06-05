<?php

define('TABLE_CONTRAT', 'dgf_form_contrat');
define('TABLE_TEMP_CONTRAT', 'temp_dgf_form_contrat');
define('TABLE_CONTRAT_PRO', 'dgf_contrat_pro');
define('TABLE_DGF', 'dgf');

define('SMIC', 1457.52);
//---------------------------------------------------------------------
// Liste des constantes des messages d'erreurs standards du formulaire
//---------------------------------------------------------------------

define('ERR_STD_CONTRAT_NATURE', 'Le champ nature du contrat est obligatoire.');
define('ERR_STD_CONTRAT_TYPE', 'Le champ type de contrat est obligatoire.');
define('ERR_STD_CONTRAT_DATE_BEGIN', 'Le champ date de début est obligatoire.');
define('ERR_STD_CONTRAT_DATE_END', 'Le champ date de fin est obligatoire.');
define('ERR_STD_CONTRAT_TRAINING_DURATION', 'Le champ durée du contrat est obligatoire.');
define('ERR_STD_CONTRAT_COEFFICIENT', 'Le champ coefficient est obligatoire.');
define('ERR_STD_CONTRAT_TEST_PERIOD', 'Le champ durée de la période d\'essai est obligatoire.');
define('ERR_STD_CONTRAT_WEEKLY_HOUR', 'Le champ durée hebdomadaire est obligatoire.');
define('ERR_STD_CONTRAT_POSITION_HELD', 'Le champ emploi occupé est obligatoire.');
define('ERR_STD_CONTRAT_COLLECTIVE_CONVENTION', 'Le champ convention colective est obligatoire.');
define('ERR_STD_CONTRAT_MONTHLY_PAY', 'Le champ salaire mensuel brut est obligatoire.');
define('ERR_STD_CONTRAT_NIVEAU_INT', 'Le champ niveau doit être un entier.');

//-----------------------------------------------------------------------
// Liste des constantes des messages d'erreurs spécifiques du formulaire
//-----------------------------------------------------------------------

define('ERR_SPE_CONTRAT_TRAINING_DURATION', 'Le contrat de professionnalisation doit avoir une durée minimale de 6 mois et durée maximale de 24 mois. Veuillez vérifier les dates du contrat.');
define('ERR_SPE_CONTRAT_TEST_PERIOD', 'La période d\'essai doit être un entier positif.');
define('ERR_SPE_CONTRAT_TEST_PERIOD_CDD', 'Si la nature du contrat est un CDD alors la période d\'essai ne peut excéder 30 jours.');
define('ERR_SPE_CONTRAT_COEFF', 'Le coefficient doit être un entier positif.');
define('ERR_SPE_CONTRAT_MONTHLY_PAY_START', 'La rémunération indiquée est inférieure au minimum légale.
  D’après les informations communiquées le montant minimum est de ');
define('ERR_SPE_CONTRAT_MONTHLY_PAY_END', '€.(avec le renseignement automatique du montant dans le champ rémunération indiqué vous pouvez remplacer le montant saisi par le calcul automatique.)');
define('ERR_SPE_CONTRAT_COEFF_GROUP', 'Vous devez soit indiquer le coefficient et le niveau, soit le groupe, pensez à vous reporter à l’aide en ligne si besoin.');
define('ERR_SPE_CONTRAT_COEFF_BETWEEN', 'Vous devez indiquer le groupe.');
define('ERR_SPE_CONTRAT_WEEKLY_HOUR', 'Le champ durée hebdomadaire doit être un entier positif.');
define('ERR_SPE_CONTRAT_COEFF_VALUE', 'Le coefficient doit être compris entre 140 et 255.');
define('ERR_SPE_DATE_DIFF_NOW', 'Nous vous rappelons que pour tout contrat de professionnalisation, le dossier doit nous parvenir au plus tard dans les 5 jours (calendaires) qui suivent la date de  début du contrat, veuillez-vous rapprocher de votre ADEFIM.');
