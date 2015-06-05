<?php

/**
 *  Envoie des infos à rechercher
 *  @param: $form , &$form_state
 *
 */
function dgf_administration_users_tabler($data) {
  $header  = array('Numero demande', 'Nom', 'Type de compte', 'Email', 'Siret', 'Statut', 'Action' );
  $rows    = array();

  foreach ($data as $items) {
    $status_message = "Validé";   // Si on refuse l'utilisateur son statut passe à refusé.
    $url = "/gestion/valider/utilisateur/". $items->id;
    $edit_button = " <a class=' glyphicon glyphicon-pencil edit-add-button btn btn-default' href=". $url . "> Edition</a>";
    $id_entreprise =  dgf_administration_users_get_user_id_entreprise($id); // Renvoie l'ID Entreprise
    $user_siret = dgf_administration_users_get_siret('H.6'); // Exemple H.6

        // $id_user = $items->id_user_drupal;
    //
        // $current_user = user_load($id_user);
    //
        // $user_status = $current_user->status;
    //
        // // Status utilisateur
        // if($user_status == '1') {
          // $status_message = "Validé";
        // }
        // else{
          // $status_message = "Bloqué";
        // }
    //
    $rows[] =   $items->numero_demande ;
    $rows[] =   $items->name ;
    $rows[] =   $user_role[3];
    $rows[] =   $items->mail ;
    $rows[] =   trim($user_siret['siret']);
    $rows[] =   $status_message;
    $rows[] =   $edit_button;
  }


  $output  = theme('table',  array('header' => $header, 'rows' => $rows));
  $output .= theme('pager');

  return $output;
}



/**
 *  Affiche les résultats  de la recherche
 *  @param: $data - Tableau de données.
 *
 */
function dgf_administration_users_display_data($data) {
  global $pager_total_items; // Nbre de résultats
  global $user;  // User Drupal

  $user_role = $user->roles; // Type de compte
  $total_res = $pager_total_items[0]; // Nombre de résultats

  if (user_access('GES_AJO_UTI')) {
    $register_button = l('Créer un utilisateur', '/gestion/creer/utilisateur', array(
        'attributes' => array('class' => 'edit-add-button btn btn-default')
    ));
  } else {
    $register_button = '';
  }
  $table_html = $register_button;

  $table_html .= "<table class='table table-striped'>
                  <thead>
                  <tr>
                    <th>" . $total_res ." résultat(s)</th></tr>
                    <th>N° de demande</th>
                    <th>Nom</th>
                    <th>Type de compte</th>
                    <th>Adresse mail</th>
                    <th>N° de siret</th>
                    <th>Statut</th>
                    <th>Action</th>
                  </thead>
                  <tbody>
                  ";
  foreach ($data as $items) {

    $id_user_drupal  = $items->id_user_drupal; // ID Drupal de l'utilisateur
    $user_drupal     = user_load($id_user_drupal);

    if ($user_drupal->status == '1'){
       $status_message = "Validé";
    }
    else{
       $status_message = "Bloqué";
    }

    $url = "/gestion/valider/utilisateur/". $items->id;
    $edit_button = " <a class=' glyphicon glyphicon-pencil edit-add-button btn btn-default' href=". $url . "> Edition</a>";
    $id_entreprise =  dgf_administration_users_get_user_id_entreprise($id); // Renvoie l'ID Entreprise
    $user_siret = dgf_administration_users_get_siret('H.6'); // Exemple H.6

    if (empty($items->numero_demande)){
      $num_demand = "-";
    }
    else {
      $num_demand = $items->numero_demande;
    }
    $table_html .= "<tr>";
    $table_html .= "<td>" .  $num_demand   . "</td>";
    $table_html .= "<td>" .  $items->first_name . ' ' . $items->last_name . "</td>";
    $table_html .= "<td>" .  $user_role[3] . "</td>"; // TODO Afficherle role de l'utilisateur
    $table_html .= "<td>" .  $items->mail  ."</td>";
    $table_html .= "<td>" .  trim($user_siret['siret'])  . "</td>";
    $table_html .= "<td>" .  $status_message   . "</td>";
    $table_html .= "<td>" .  $edit_button ."</td>";
    $table_html .= "</tr>";
  }
  $table_html .= "</tbody></table>";
  // Pagination des résultats
  $table_html .= theme('pager', array('numero_demande' => 1));
  $table_html .= $register_button;
  print $table_html;
}