<?php

function validate_salarie($id_dgf){

    require_once drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/stagiaire/stagiaire_db.inc';
    $dataExtranet = get_salarie_data_extranet($id_dgf);
    $dataReferenciel = get_salarie_data_referenciel($dataExtranet['id_ref_esclave_entreprise'],$dataExtranet['id_ref_esclave_particularites'],$dataExtranet['id_ref_esclave_salarie']);

    $data = array_merge($dataExtranet,$dataReferenciel);

    if (count($data)) insert_salarie($data);
}

function validate_contrat($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/contrat/contrat_db.inc';
    $dataExtranet = get_contrat_data_extranet($id_dgf);
    $dataReferenciel = get_contrat_data_referenciel($dataExtranet['id_ref_esclave_type_contrat'],$dataExtranet['id_ref_esclave_convention_collective']);

    $data = array_merge($dataExtranet,$dataReferenciel);

    if (count($data)) insert_contrat($data);
}

function validate_tuteur($id_dgf){

    require_once drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/tuteur/tuteur_db.inc';
    $dataExtranet = get_tuteur_data_extranet($id_dgf);
    $dataReferenciel = get_tuteur_data_referenciel($dataExtranet['id_ref_esclave_salarie']);

    $data = array_merge($dataExtranet,$dataReferenciel);

    if (count($data)) insert_tuteur($data);
}

function validate_formation($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/formation/formation_db.inc';
    $dataExtranet = get_formation_data_extranet($id_dgf);

    $dataReferenciel = get_formation_data_referenciel($dataExtranet['id_ref_esclave_niveau'],
            $dataExtranet['id_ref_esclave_specialite'],$dataExtranet['id_ref_esclave_intitule_formation']);

    $data = array_merge($dataExtranet,$dataReferenciel);
    if (count($data)) insert_formation($data);
    process_formation_repartition_extranet($id_dgf);
}
function validate_demande($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/demande/dgf_demande_db.inc';
    $dataExtranet = get_demande_data_extranet($id_dgf);

    $dataReferenciel = get_demande_data_referenciel();

    $data = array_merge($dataExtranet,$dataReferenciel);
    if (count($data)) insert_demande($data);
}
function validate_organisation($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/organisme_formation/organisme_formation_db.inc';
    $dataExtranet = get_organisme_data_extranet($id_dgf);

    $dataReferenciel = get_organisme_data_referenciel($dataExtranet['id_ref_esclave_organisme_formation'],
        $dataExtranet['id_ref_esclave_organisme_formation'],
        $dataExtranet['id_ref_esclave_contacts_organisme_formation']);

    $data = array_merge($dataExtranet,$dataReferenciel);
    if (count($data)) insert_organisme($data);
}

function validate_justificatif($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/justificatifs/justificatifs_db.inc';
    get_justificatif_data_extranet($id_dgf);

}

function validate_justificatif_payement($id_dgf){

    require_once drupal_get_path('module', 'dgf' ) . '/inc/justificatifs/justificatifs_db.inc';
    $dataExtranet = get_justificatif_payment_data_extranet($id_dgf);

    $dataReferenciel = get_justificatif_payment_data_referenciel();

    $data = array_merge($dataExtranet,$dataReferenciel);

    if (count($data)) insert_justificatif_payment($data);
}

function validate_dgf($id_dgf){
    $data = get_dgf_data_extranet($id_dgf);

    $dataReferenciel = get_dgf_data_referenciel($data['id_ref_esclave_adefim']);

    update_dgf($dataReferenciel,$data['id_ref_esclave_adefim']);
}

function validate_entreprise($id_dgf){
    $data = get_entreprise_data_extranet($id_dgf);

    foreach ($data as $entreprise) {
      $dataReferenciel = get_entreprise_data_referenciel($entreprise->id_ref_esclave_entreprise);

      update_entreprise($dataReferenciel, $entreprise->id);
    }

}

function dgf_attestation_form_submit($form, &$form_state) {

    $id_dgf = $form_state['values']['id_dgf'];
    validate_salarie($id_dgf);
    validate_contrat($id_dgf);
    validate_tuteur($id_dgf);
    validate_formation($id_dgf);
    validate_demande($id_dgf);
    validate_organisation($id_dgf);
    validate_justificatif($id_dgf);
    validate_justificatif_payement($id_dgf);
    validate_dgf($id_dgf);
    validate_entreprise($id_dgf);


  if ($form_state['triggering_element']['#id'] === 'edit-view-cerfa') {
    // TODO : afficher le CERFA
  } else if ($form_state['triggering_element']['#id'] === 'edit-nouvelle-demande') {
    // TODO : passer les données de la demande faite
    drupal_goto('/dgf/demande');
  } else if ($form_state['triggering_element']['#id'] === 'edit-accueil') {
    drupal_goto('/dashboard');
  } else if ($form_state['triggering_element']['#id'] === 'edit-tuteur-demande') {
    // TODO : passer les données du tuteur
    drupal_goto('/dgf/demande');
  } else {
    // on met à jour dgf : id_ref_esclave_adefim, statut, date_synthese, date_last_edit, id_user_last_edit
    attestation_db_update_dgf($id_dgf, $form_state);

    // TODO : On déplace les données de la demande dans les tables finales
    // attestation_db_move_temp_data($id_dgf);

    // On affiche la pop-up fin de saisie
    drupal_goto('/dgf/demande/attestation/'.$id_dgf,
          array('query'=>array('modal' => 'fin_saisie')));
  }
}
