<?php

function get_data_for_establishment_validation($order, $sort, $siret = null,
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
  $query->condition('e.est_actif', 1, '=');
//   $query->condition('c.est_contact_principal', 1, '=');

  if ($siret != null) {
    $query->condition('siret', '%'.$siret.'%', 'LIKE');
  }

  if ($corporateName != null) {
    $query->condition('raison_sociale', '%'.$corporateName.'%', 'LIKE');
  }

  if ($responsibleName != null) {
    $or = db_or()
          ->conditions('nom', '%'.$responsibleName.'%', 'LIKE')
          ->conditions('prenom', '%'.$responsibleName.'%', 'LIKE');
    $query->condition($or);
  }

  $query->distinct('siret')->orderBy('siret');
  $query->orderBy($order, $sort);
  // Pagination
  $query = $query->extend('TableSort')->extend('PagerDefault')->limit(20);
  // Executing query
  $result = $query->execute();
  db_set_active();

  // Looping for filling the table rows
  while($data = $result->fetchObject()) {
    $idEntreprise = rtrim($data->id);
    $actionButton = '<a class="action" href="/validation/etablissement/edit/'. $idEntreprise .'"><span class="glyphicon glyphicon-eye-open" aria-hidden="true"></span></a>';
    $modification = 'création/modification';

    // Adding the rows
//     $contact = trim($data->titre).' '.trim($data->prenom).' '.trim($data->nom).'<br />'.trim($data->email);
    $contact = '';
    $rows[] = array(trim($data->siret), $modification, trim($data->raison_sociale), trim($data->telephone_principal), $contact, $actionButton);
  }
  return $rows;
}
