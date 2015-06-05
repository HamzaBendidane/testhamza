<?php

function dgf_suivi_demande_form($form, &$form_state) {

  $form['filter_content'] = array(
    '#type' => 'container',
    '#attributes' => array(
        'class' => array('col-md-12')
    ),
  );

  $form['filter_content']['filter_left'] = array(
    '#type' => 'container',
    '#attributes' => array(
        'class' => array('col-md-4')
    ),
  );

  $form['filter_content']['filter_left']['action_number'] = array(
    '#type' => 'textfield',
    '#title' => t('N° action'),
    '#attributes' => array(
        'class' => array('col-md-10')
      ),
  );


  $form['filter_content']['filter_left']['action_nature'] = array(
      '#type' => 'select',
      '#title' => t('Nature de l\'action'),
      '#options' => array(
          0 => t('Veuillez choisirla nature de l\'action'),
          1 => t('default' )
      ),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );


  $form['filter_content']['filter_center'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-sm-4')
      ),
  );

  $form['filter_content']['filter_center']['state'] = array(
      '#type' => 'select',
      '#title' => t('Etat'),
      '#options' => array(
          0 => t('Veuillez choisirla nature de l\'action'),
          1 => t('default')
      ),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );

  $form['filter_content']['filter_center']['year_exercise'] = array(
    '#type' => 'textfield',
    '#title' => t('Année (ou exercice)'),
    '#attributes' => array(
        'class' => array('col-md-10')
    ),
  );

  $form['filter_content']['filter_right'] = array(
      '#type' => 'container',
      '#attributes' => array(
          'class' => array('col-sm-4')
      ),
  );

  $form['filter_content']['filter_right']['worker_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom du Salarié'),
    '#attributes' => array(
        'class' => array('col-md-10')
    ),
  );


  $form['filter_content']['filter_right']['etablishment'] = array(
      '#type' => 'select',
      '#title' => t('Etablissement'),
      '#options' => array(
          0 => t('Veuillez choisir un établissement' ),
          1 => t('default' )
      ),
      '#attributes' => array(
          'class' => array('col-md-10')
      ),
  );


  $form['filter_content']['filter_button'] = array(
      '#type' => 'container',
      '#attributes' => array(
//           'class' => array('col-sm-6 col-sm-offset-5')
      ),
  );

  // TODO refaire les boutons façon drupal
  $form['filter_content']['filter_button']['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="col-sm-6 form-wrapper" id="edit-filter-button">
      <input type="button" id="edit-reset" name="op" value="Réinitialiser" class="form-reset btn btn-warning">
      <input type="button" id="edit-filter" name="op" value="Filtrer" class="form-filter btn btn-primary col-sm-offset-1" href="/dgf/suivi/demande">
      </div>',
  );

//   $form['filter_content']['filter_button']['filter'] = array(
//     '#type' => 'button',
//     '#value' => t('Filtrer'),
//     '#limit_validation_errors' => array(),
//     '#validate' => 'dgf_suivi_demande_data',
//   );

  return $form;
}

// function stagiaire_storage(&$form_state) {
//   // Champs du formulaire
//   $fields = array('etablishment' ,
//       'lastname',
//       'firstname',
//       'birthday',
//       'age',
//       'man_woman',
//       'handicapped_worker',
//       'street_address',
//       'zip_code',
//       'city',
//       'phone_number',
//       'email',
//       'highest_level',
//       'social_beneficiary',
//       'last_status',
//       'pole_emploi_number',
//       'since_month',
//       'pension_fund',
//       'contingency_fund',
//   );
//   foreach ($fields as $field) {
//     $form_state['storage'][$field] = $form_state['values'][$field];
//   }
//   shared_put_session($form_state['storage']);
// }
