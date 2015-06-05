<?php

function _dgf_demande_require_once() {
  require_once 'dgf_demande_db.inc';
  require_once 'dgf_demande_langs.inc';
  require_once 'dgf_demande_submit.inc';
  require_once 'dgf_demande_validate.inc';
}

function _dgf_demande_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf' ) . '/inc/demande/js/dgf_demande.js' );
  drupal_add_css(drupal_get_path('module', 'dgf' ) . '/inc/demande/css/dgf_demande.css' );
}

function dgf_demande_form($form, &$form_state) {
  _dgf_demande_require_once();
  _dgf_demande_include_js_css();
  shared_get_referentiel_data(array('ref_nature_demande', 'ref_nature_formation'), false);

  if (isset($_SESSION['demande'])) {
    unset($_SESSION['demande']);
  }

  $temp_dgf_form_demande = array();
  if (arg(2)) {
    $id_dgf = (int)arg(2);
    $temp_dgf_form_demande = demande_db_get_temp_dgf_form_demande($id_dgf);
  }

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa.png',
  );

  $form['nature_demande'] = array(
      '#type' => 'radios',
      '#title' => t('Quelle est la nature de votre demande ?
          <span class="form-required" title="Ce champ est requis.">*</span>
          <span class="sublabel">(un seul choix possible)</span>' ),
      '#required' => true,
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_nature_demande'],
      '#prefix' => '<div class="col-md-6">',
      '#suffix' => '</div>',
      '#default_value' => $temp_dgf_form_demande ? $temp_dgf_form_demande['id_dgf_nature_demande'] : null,
  );

  $form['nature_formation'] = array(
      '#type' => 'radios',
      '#title' => t('Nature de la formation
          <span class="sublabel">(un seul choix possible)</span>'),
      '#options' => $_SESSION['referentiel_extranet_datas']['ref_nature_formation'],
      '#prefix' => '<div class="col-md-6"><div class="radio-separator"></div>',
      '#suffix' => '</div>',
      '#default_value' => $temp_dgf_form_demande ? $temp_dgf_form_demande['id_dgf_nature_formation'] : null,
  );

  $form['clearfix'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div></div>',
  );

  // TODO : champ entreprise

  // TODO : champ ADEFIM

  $form['action'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="boutonAction">',
  );

  $form['back'] = array(
      '#type' => 'button',
      '#value' => t('Annuler'),
      '#limit_validation_errors' => array(),
      '#attributes' => array('class' => array('cancel')),
  );

  $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Suivant'),
      '#attributes' => array('class' => array('nextDemande')),
  );

  $form['action_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div>',
  );

  return $form;
}