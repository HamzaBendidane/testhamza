<?php

function get_data_for_demande($order, $sort, $actionNumber = null, $actionNature = null, $actionState = null, $yearExercise = null, $workerName = null, $etablishment = null) { // $user en paramètre

  db_set_active(@DB_SLAVE);

  $query = db_select('v_entreprises', 'e');
  $query->fields('e');

  // TODO : finaliser les champs de la table à cibler selon les valeurs du form
  if (isset($actionNumber)) {
    $query->condition('raison_sociale', '%'.$actionNumber.'%', 'LIKE');
  }
//   if (isset($actionNumber)) {
//     $query->condition('colonne', '%'.$actionNumber.'%', 'LIKE');
//   }
//   if (isset($actionNature)) {
//     $query->condition('colonne', '%'.$actionNature.'%', 'LIKE');
//   }
//   if (isset($actionState)) {
//     $query->condition('colonne', '%'.$actionState.'%', 'LIKE');
//   }
//   if (isset($yearExercise)) {
//     $query->condition('colonne', '%'.$yearExercise.'%', 'LIKE');
//   }
//   if (isset($workerName)) {
//     $query->condition('colonne', '%'.$workerName.'%', 'LIKE');
//   }
//   if (isset($etablishment)) {
//     $query->condition('colonne', '%'.$etablishment.'%', 'LIKE');
//   }
//   ->condition($tableColumn, $user, '=')
//   ->condition('e.est_actif', '1', '=');
//   $result = array();

//   $result = $query->execute();
//   ->fetchAllAssoc('id', PDO::FETCH_ASSOC);

  // Fermeture de la connexion BDD
  db_set_active();

//     // Query object
//     $query = db_select("node", "n");

//     // Adding fields
//     $query->fields('n',array('title','type'));

//     // Set order by
    $query->orderBy($order, $sort);

//     // Pagination
    $query = $query->extend('TableSort')->extend('PagerDefault')->limit(20);

//     // Executing query
    $result = $query->execute();

    // Looping for filling the table rows
    while($data = $result->fetchObject()) {
      // Adding the rows
      $rows[] = array($data->raison_sociale, $data->siret);
      // TODO : finaliser l'alimentation de la colone action
      // en fonction du statut de la demande (dossier ou demande)
//       if ($data->statutDgf == 1) {
//         $action = '<a href="urlToEdit'. $idDgf. '"><span class="glyphicon glyphicon-edit"></span></a>';
//       } else {
//         $action = '<a href="urlToShow'. $idDgf. '"><span class="glyphicon glyphicon-edit"></span></a>';
//       }
//       $rows[] .= $action;
    }
    return $rows;
}