<?php

//__________________________ MSG FORM  ERRORS ______________________________ //

define('ERROR_MAIL_NOT_EQUAL', "Les deux adresses email ne sont pas identiques");
define('ERROR_MAIL_FORMAT', "Format de l'adresse e-mail non conforme");
define('ERROR_MAIL_EXIST', "Un compte exsite déjà  avec cette adresse email");
define('ERROR_COMPANY_NAME', "Vous n’avez pas sélectionné d’entreprise, le champ raison sociale est obligatoire.");
define('ERROR_ADRESS_STREET_NUMBER', "Le numéro de rue est obligatoire");
define('ERROR_STREET_NAME', "Le champ rue est obligatoire");
define('ERROR_NAF', "Le code naf est obligatoire");
define('ERROR_CHAIRMAN_FUNCTION', "La fonction du responsable est obligatoire");
define('ERROR_CHAIRMAN_NAME', "Le nom du responsable est obligatoire");
define('ERROR_CHAIRMAN_SURNAME', "Le prénom du responsable est obligatoire");
define('ERROR_USER_NAME', "Le nom de l'utilisateur est obligatoire");
define('ERROR_USER_SURNAME', "Le prénom de l'utilisateur est obligatoire");
define('ERROR_USER_FUNCTION', "La fonction de l'utilisateur est obligatoire");
define('ERROR_USER_PHONE', "Le téléphone de l'utilisateur est obligatoire");
define('ERROR_USER_RIGHTS', "Merci de choisir au moins une fonctionnalité pour l'utilisateur.");

//_____________________________ DB TABLES _________________________________ //

define('TABLE_USER_ENTREPRISE'  ,  'user_entreprise');
define('TABLE_USER_RESPONSABLE' ,  'user_responsable');
define('TABLE_DRUPAL_USER' , 'drupal_user');
define('TABLE_ENTREPRISE' , 'entreprises');

//____________________________ FORM REGISTER ______________________________ //

define('USER' , 'L\'UTILISATEUR');
define('REGISTER_CONFIRM_MESSAGE', '<b>Merci de vérifier puis de confirmer ce que vous avez saisi</b>');
define('IMPRIMER', 'Imprimer les informations');
define('MODIFIER_DEMANDE', 'Modifier votre demande');

//____________________________ MSG VALIDATION __________________________ //

define('OPCAIM_INFOS_VALID' ,'<b class="infos">Validez le texte de la charte pour accéder au formulaire à compléter.</b><br><br>' );
define('OPCAIM_INFOS', '<p>Pour toute question, vous pouvez joindre votre ADEFIM au 01 41 43 96 96, ou envoyer un email à l\'adresse suivante
           : <b>info@adefim-idf.org</b></p>');
// CHARTE
$charte = " <b>Charte d'utilisation du site EXTRANET de l'OPCAIM</b>
            <br><sbr>
              <b>INTRODUCTION</b>
              <br>
                        <p>Bienvenue sur votre nouvel espace EXTRANET qui vous permet d’accéder aux services en ligne de l’OPCAIM. Ces services vous permettent d’effectuer la collecte au titre de la formation professionnelle continue et de la taxe d’apprentissage, de réaliser des demandes de prise en charge pour vos actions de formation, de suivre et gérer l’activité formation de votre entreprise au quotidien.</p>
                        <p>Pour accéder à ces services dématérialisés vous devez respecter les modalités de souscription et accepter les présentes conditions générales. Le présent document vous engage, veuillez le lire attentivement avant de le valider.</p>
                        <b>COMPTE EXTRANET</b>
                        <br>
                        <p>En disposant d’un compte EXTRANET OPCAIM, vous certifiez que vous êtes autorisé par votre employeur à consulter les informations relatives aux données déclarées sur l’activité formation de votre entreprise (et éventuellement aux données salariales) et à procéder selon vos droits aux actes administratifs de déclaration de la collecte au titre de la formation professionnelle continue, de la taxe d’apprentissage, et/ou de demande de prise en charge des actions de formation auprès de l’OPCAIM pour le compte de votre entreprise.</p>
                        <p>A partir de ce compte, vous avez la possibilité de : </p>
                        <ul>
                            <li>consulter les informations liées à l’activité formation de votre entreprise</li>
                            <li>saisir des demandes de prise en charge</li>
                            <li>réaliser la collecte : compléter le bordereau et  le transmettre à l’Adefim</li>
                        </ul>
                        <br>
                        <p>Seules les personnes ayant reçu mandat de la part de l’entreprise adhérente à l’OPCAIM pour agir en son nom et pour son compte peuvent réaliser ces actes via le compte EXTRANET.</p>
                        <p>Il est de la responsabilité de l’employeur d’informer l’OPCAIM de tout changement pouvant amener à la désactivation d’un compte EXTRANET : changement de poste, démission ou licenciement d’un salarié ayant un accès, etc.</p>
                        <b>CONDITIONS GENERALES </b>
                        <br>
                        <p><u>Conditions d’accès :</u></p>
                        <p>Votre identifiant et votre mot de passe vous sont personnels et ne doivent en aucun cas être communiqué à autrui. Ils garantissent la confidentialité des informations mises à disposition et sont à saisir obligatoirement pour accéder aux services en ligne.</p>
                        <p>A l’issue de la procédure d’acceptation des conditions d’utilisation, vous devenez responsable de la conservation du caractère confidentiel de votre identifiant et de votre mot de passe. En conséquence, nous vous recommandons vivement, dès la première utilisation, de modifier votre mot de passe en créant un nouveau mot de passe personnalisé qui garantira la confidentialité totale.</p>
                        <ul>
                            <li>Vous vous engagez également à informer l’OPCAIM de toute utilisation non autorisée de votre identifiant et de votre mot de passe et/ou de toute atteinte à la sécurité, et à vous assurer qu’à l’issue de chaque session vous vous déconnectez explicitement de l’EXTRANET.</li>
                            <li>Enfin, l’OPCAIM ne serait en aucun cas engagé si une personne non habilitée accédait aux services web et à vos informations en utilisant votre identifiant et votre mot de passe.</li>
                        </ul>
                        <br>
                        <p>Si vous perdez votre identifiant et/ou votre mot de passe, vous pouvez faire une demande de renouvellement. Vous recevrez dès le lendemain un nouveau mot de passe provisoire. Vous devrez alors, à nouveau, créer un mot de passe personnalisé.</p>
                        <p><u>Fichier des salariés utilisateurs :</u></p>
                        <p>Le nom et la fonction des salariés utilisateurs du site EXTRANET constituent un fichier informatisé nominatif qui sera déclaré à la CNIL. Conformément aux articles 34 à 36 de la loi « informatique et libertés » du 6 janvier 1978, les salariés utilisateurs bénéficient d’un droit d’accès aux données les concernant et de rectification de celles-ci. Ce droit d’accès et de rectification pourra être exercé auprès de l‘organisme suivant : OPCAIM, 120 boulevard de Courcelles, 75 017 Paris. s/c l’ADEFIM dont votre entreprise dépend.</p>
                        <p>Il est précisé que la validation des conditions, l’acceptation par coche de case, la transmission des éléments à l’OPCAIM ou l’ADEFIM par validation et l'utilisation du code d'accès à l'espace personnel, valent consentement de la part de l'adhérent à la conclusion et au traitement des documents par l’ADEFIM sur la base des informations qu’il a transmis. Ces informations ont seules valeur probante en cas de contestation de l'adhérent.</p>
                        <p>Si vous acceptez ces conditions, merci de bien vouloir cliquer sur le bouton « j’accepte » avant de continuer plus avant.
                        </p><p>En cliquant sur le bouton « j’accepte », vous déclarez et attestez être mandaté par votre entreprise (raison sociale et coordonnées validées en amont), et habilité à réaliser pour son compte les actions de demandes de prise en charge à l’OPCAIM, et/ou la collecte au titre de la formation professionnelle et de la taxe d’apprentissage.</p>
          ";

define('CHARTE_CONFIDENTIALITE', $charte);
define('REFUSER_CHARTE', "Je n'accepte pas");
define('ACCEPTER_CHARTE', "J'accepte");
//_____________________________________________  MSG RAPPEL _____________________________________________ //
define('Rappel',
"<p>
    Ayant pris connaissance du texte de la charte d'utilisation de votre site, je vous confirme en approuver le contenu
    dans son intégralité afin que vous procédiez à l'ouverture d'un compte me permettant d'accéder aux informations
    concernant mon entreprise et relatives aux:
</p>
<ul>
  <li> versements effectués dans le cadre de la contribution au financement de la formation professionnelle continue;</li>
  <li> dossiers de demande de prise en charge au titre de la formation professionnelle continue.</li>
</ul>");