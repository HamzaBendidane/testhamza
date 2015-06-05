<?php

function _dgf_attestation_require_once_files() {
  require_once 'attestation_db.inc';
  require_once 'attestation_langs.inc';
  require_once 'attestation_submit.inc';
  require_once 'attestation_validate.inc';
}

function _dgf_attestation_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf' ) . '/inc/attestation/js/attestation.js' );
  drupal_add_css(drupal_get_path('module', 'dgf' ) . '/inc/attestation/css/attestation.css' );
}

// --------------------------------------------------
// Création du formulaire
// --------------------------------------------------
function dgf_attestation_form($form, &$form_state) {
  _dgf_attestation_require_once_files();
  _dgf_attestation_include_js_css();

  // on regarde le 3eme argument de l'url pour retrouver s'il y a des données
  $temp_dgf_form_attestation = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(3) !== null) {
    $id_dgf = arg(3);
    $dgf = attestation_db_get_dgf($id_dgf);
    $id_ref_esclave_entreprise = attestation_db_get_id_ref_esclave_entreprise($id_dgf);
  } else {
    return;
  }

  $adefims = attestation_db_get_liste_adefims($id_ref_esclave_entreprise);

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['center'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="center col-md-8 col-md-offset-2">',
  );

  $form['title']  = array(
      '#type' => 'markup',
      '#markup' => '<h1>'.t(@ATT_TITRE).'</h1>',
  );

  $form['id_dgf'] = array(
      '#type' => 'hidden',
      '#default_value' => $id_dgf,
      '#title' => t('Id demande' )
  );

  $form['modal'] = array(
      '#type' => 'hidden',
      '#default_value' => isset($_GET['modal']) ? $_GET['modal'] : null,
      '#title' => t('Modal fin de saisie')
  );

  $form['certifie'] = array(
      '#type' => 'checkbox',
      '#title' => t(@ATT_LABEL),
      '#default_value' => $dgf && $dgf['date_synthese'] ? true : false,
  );

  if (is_array($adefims)) {
    $form['id_adefim'] = array(
        '#type' => 'select',
        '#title' => t('ADEFIM'),
        '#default_value' => $dgf ? $dgf['id_ref_esclave_adefim'] : null,
        '#options' => $adefims,
    );
  } else {
    $form['id_adefim'] = array(
        '#type' => 'hidden',
        '#title' => t('ADEFIM'),
        '#default_value' => $adefims,
    );
  }

  $form['message'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="message-merci">'.t(@ATT_MSG_MERCI).'</div>',
  );

  $form['transmettre'] = array(
      '#type' => 'submit',
      '#value' => t(@ATT_BOUTON),
      '#attributes' => array(
          'class' => array('btn btn-primary'),
      ),
  );

  $form['fin_center'] = array(
      '#type' => 'markup',
      '#markup' => '</div>',
  );

  $form['clearfix'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div></div>',
  );

  _dgf_attestation_form_fin_saisie($form, $dgf);

  return $form;
}

function _dgf_attestation_form_fin_saisie(&$form, $dgf) {
  // Gestion de l'afichage en modal
  $prefix = '<div id="modal-fin-saisie" class="modal" tabindex="-1" role="dialog" aria-hidden="true">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                        <h4 class="modal-title">Fin de saisie</h4>
                    </div>';

  $body_prefix    = '<div class="modal-body">';
  $body_suffix    = '</div>';


  $footer_prefix     = '<div class="modal-footer">';
  $footer_suffix     = '</div>';
  $suffix  =       '</div><!-- /.modal-content -->
            </div><!-- /.modal-dialog -->
          </div><!-- /.modal -->';



  // TODO : Pour affichage en modal
  $form['modalheader'] = array(
      '#type' => 'markup',
      '#markup' => $prefix,
  );

  $form ['modalbody'] = array (
      '#type' => 'fieldset',
      '#title' => '',
      // TODO : Pour affichage en modal
      '#prefix' => $body_prefix,
      '#suffix' => $body_suffix,
  );

  $form['modalbody']['messagefinsaisie'] = array(
      '#type' => 'markup',
      '#markup' => @MSG_FIN_DE_SAISIE,
  );

  $form['modalbody']['framework'] = array(
      '#type' => 'fieldset',
  );

  $form['modalbody']['framework']['list'] = array(
      '#type' => 'markup',
      '#title' => t(''),
      '#markup' => '<p><b>Numéro demande : '. $dgf['numero_demande'] .'</b></p>',
  );

  $form['modalbody']['voir_cerfa'] = array(
      '#type' => 'submit',
      '#value' => @MSG_FIN_DE_SAISIE_BUTTON_EDIT_CERFA,
      '#attributes' => array(
          'class' => array('btn btn-primary'),
      ),
      '#prefix' => $footer_prefix,
  );

  if(isset($formation_tuteur)) {
    $form['modalbody']['tuteur_demande'] = array(
        '#type' => 'submit',
        '#value' => @MSG_FIN_DE_SAISIE_BUTTON_FUNDING_REQUEST,
        '#attributes' => array(
            'class' => array('btn btn-primary'),
        ),
    );
  }

  $form['modalbody']['nouvelle_demande'] = array(
      '#type' => 'submit',
      '#value' => @MSG_FIN_DE_SAISIE_BUTTON_NEW_REQUEST,
      '#attributes' => array(
          'class' => array('btn btn-primary'),
      ),
  );

  $form['modalbody']['accueil'] = array(
      '#type' => 'submit',
      '#value' => @MSG_FIN_DE_SAISIE_BUTTON_QUIT,
      '#suffix' => $footer_suffix,
  );

  // Pour affichage en modal
  $form['modal_quit']['footer'] = array(
      '#type' => 'markup',
      '#markup' => $suffix,
  );
}
