<?php

function opcaim_establishment_management_form($form, &$form_state) {

  $form['filter_content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filtre'),
    '#attributes' => array(
        'class' => array('col-md-11 form-inline')
    ),
  );

  $form['filter_content']['siret'] = array(
    '#type' => 'textfield',
    '#title' => t('SIRET'),
    '#attributes' => array(
        'class' => array('col-md-offset-2 col-md-3')
      ),
    '#prefix' => '<div class="form-group">',
    '#suffix' => '</div>',
  );


  $form['filter_content']['corporate_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Raison sociale'),
    '#attributes' => array(
        'class' => array('col-md-3')
      ),
    '#prefix' => '<div class="form-group">',
    '#suffix' => '</div>',
  );

  $form['filter_content']['responsible_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Nom du responsable'),
    '#attributes' => array(
        'class' => array('col-md-3')
    ),
    '#prefix' => '<div class="form-group">',
    '#suffix' => '</div>',
  );

  $form['action'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="col-md-offset-4 form-wrapper" id="edit-filter-button">
      <input type="button" id="edit-reset" name="op" value="Réinitialiser" class="form-reset btn btn-warning">
      <input type="button" id="edit-search" name="op" value="Rechercher" class="form-filter btn btn-primary col-sm-offset-1" href="">
      </div>',
  );

  return $form;
}