<?php
// Erreur standard
define('ERR_STD_FORMATION_SAISIE_LIBRE', 'Le champ Ou saisie libre est obligatoire.');

// Erreur spécifique
define('ERR_SPE_FORMATION_DATE_EXAMEN', 'La date de l\'examen finale doit être postérieure au début de la formation');
define('ERR_SPE_FORMATION_TOTAL_DURATION', 'La durée de la formation indiquée représente [durée totale formation/durée totale du contrat x 100]%  or celle-ci doit être comprise entre 15% et 50% de la durée du contrat. Veuillez apporter les modifications nécessaires');
define('ERR_SPE_FORMATION_DATE_EXAMEN_CP42', 'Le CQPM doit être passé au plus tard 30 (ou 60 si non CQPM) jours avant la date de fin du contrat.');
define('ERR_SPE_FORMATION_DATE_DEBUT_CP43', 'A définir (RGC_DGF-CP44 - MSG-ERR43) : blocage sur date début formation et date début contrat');
define('ERR_SPE_FORMATION_DATE_DEBUT_CP47', 'La durée entre la date de début de la formation  et la date d’examen ne peut excéder 24 mois');
define('ERR_SPE_FORMATION_DURATION_MAIN_LEARNING', 'La somme des durées d\'enseignements généraux et d\'actions d\'accompagnement et d\'évaluations dépassent la durée totale indiquée.');
define('ERR_STD_FORMATION_TOTAL_DURATION', 'A définir (RGC_DGF-CP45 - MSG-ERR44) : blocage sur ratio durée entre contrat et formation');
define('ERR_SPE_CONTRAT_TRAINING_DURATION', 'Le contrat de professionnalisation doit avoir une durée minimale de 6 mois et durée maximale de 24 mois. Veuillez vérifier les dates du contrat.');

// Infobulle
define('MSG_INFO_FORMATION_DUREES', 'le message Explication des heures');
