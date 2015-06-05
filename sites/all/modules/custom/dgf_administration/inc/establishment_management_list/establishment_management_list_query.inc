<?php

function get_data_for_establishment_management_list($order, $sort, $siret = null,
    $corporateName = null, $responsibleName = null)
{
  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
//   $query->leftJoin('v_contacts_entreprises', 'c', 'c.id_entreprise = e.id');
  $query->fields('e', array(
      'id', 'est_valide', 'est_actif', 'siret',
      'raison_sociale', 'telephone_principal',
    )
  );
//   $query->fields('c', array(
//       'id_civilite', 'prenom',
//       'nom', 'email'
//     )
//   );

  $query->condition('e.est_valide', 0, '=');
  if ($siret != null) {
    $query->condition('siret', '%'.$siret.'%', 'LIKE');
  }

  if ($corporateName != null) {
    $query->condition('raison_sociale', '%'.$corporateName.'%', 'LIKE');
  }

  if ($responsibleName != null) {
    $stringsContact = explode($responsibleName, '>');
    $emailContact = trim($stringsContact[2]);
    $query->condition('email_contact', '%'.$emailContact.'%', 'LIKE');
  }

  $query->distinct('siret')->orderBy('siret');

    // Set order by
    $query->orderBy($order, $sort);

    // Pagination
    $query = $query->extend('TableSort')->extend('PagerDefault')->limit(20);

    // Executing query
    $result = $query->execute();
    // Fermeture de la connexion BDD
    db_set_active();

    // Looping for filling the table rows
    while($data = $result->fetchObject()) {

//       if($data->est_valide = '0') {
        $idEntreprise = rtrim($data->id);

        $actionEdit =
        //               '<div class="glyphicon glyphicon-edit" aria-hidden="true">
        '<a href="/gestion/etablissement/edit/'. $idEntreprise .'">link</a>';
        //          </div>';
        $actionDelete =
        '<button class="listBtn" href="#deleteModal" data-id="'. $idEntreprise .'" data-siret="'.trim($data->siret).'"
           " data-name="'.trim($data->raison_sociale).'" data-toggle="modal">
           <span class="glyphicon glyphicon-remove" aria-hidden="true">
           </span>
         </button>';
        if ($data->est_valide == 0 && $data->est_actif == 0) {
          // quelque chose à faire mais je vois pas comment avec ces infos...
          //       a.       est_valide = 0 ET est_actif = 0 => donnée à supprimer
          //       b.      est_valide = 0 ET est_actif = 1 => donnée à valider
          //       c.       est_valide = 1 ET est_actif = 0 => donnée supprimée
          //       d.      est_valide = 1 ET est_actif = 1 => donnée validée
          $actionButton = $actionDelete;
          $modification = 'suppression';
        } else if ($data->est_valide == 0 && $data->est_actif == 1) {
          $actionButton = $actionEdit; // . $actionDelete
          $modification = 'création/modification';
        } else {
          $actionButton = ' - ';
        }

        // Adding the rows
//         $contact = $data->prenom.' '.$data->nom.'<br />'.$data->email;
        $contact = 'contact';
        // TODO : finaliser l'alimentation de la colone action ou voir plus haut ppour le faire (actionButton)
        // en fonction du statut de l'utilisateur
        //       if ($data->statutUser == XXX) {
        $rows[] = array(trim($data->siret), $modification, trim($data->raison_sociale), trim($data->telephone_principal), trim($contact), $actionButton); // toute action
        //       } else if ($data->statutUser == YYY) {
        //         $rows[] = array(trim($data->siret), $modification, trim($data->raison_sociale), trim($data->telephone_principal_entreprise), trim($contact), $actionEdit . $actionDelete); // action limitée
        //       } else {
        //         $rows[] = array(trim($data->siret), $modification, trim($data->raison_sociale), trim($data->telephone_principal_entreprise), trim($contact), $actionEdit . $actionDelete); // action limitée
        //       }
      }
//     }
//     die;
    return $rows;
}

function get_stored_proc_delete_establishment() {
  db_set_active(@DB_SLAVE);
$id = arg(5);
// $user = 1;

  global $user; // User Drupal

  // Procédure stockée
  $procedure = "EXEC sp_supprimer_entreprise
  @user  = '$user->uid',
  @id_entreprise = '$id'
  ";

  // Execution de la procédure
  $exec = db_query($procedure);

  db_set_active();
}