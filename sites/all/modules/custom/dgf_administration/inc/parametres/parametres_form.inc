<?php

/** Formulaire de gestion du compte Utilisateurs
 * Implements hook_form()
 * @param $form
 * @param $form_state
 * @return mixed
 */
function parametres_form($form, &$form_state) {
  // Choix du référentiel
  $tables_name = array(
      '' => 'Veuillez sélectionner',
      'ref_beneficiaire_minimas_sociaux' => 'Bénéficiaires des minimas sociaux',
      'ref_derniere_situation' => 'Dernière situation avant signature du contrat',
      'ref_diplome' => 'Diplôme',
      'ref_finalite_formation' => 'Finalité de formation',
      'ref_groupe' => 'Groupe',
      'ref_justificatif' => 'Justificatifs',
      'ref_nature_demande' => 'Nature de demande',
      'ref_nature_formation' => 'Nature de formation',
//       'ref_nomenclature_fichier_reporting' => 'Nomenclature nom de fichier reporting',
  );

  // SELECT REF
  $form['choix'] = array(
      '#type'     => 'item',
      '#title'    => t('<h3>Choix du référentiel</h3>'),
  );

  // Label référentiel
  $form['select_referentiel'] = array(
      '#type'     => 'select',
      '#title'    => t('Référentiel: '),
      '#options'  => $tables_name,
      '#default_value' => isset($_GET['select_referentiel']) ? $_GET['select_referentiel'] : null,
  );

  $image_loading = theme_image(array(
      'path' =>  base_path().drupal_get_path('theme', 'opcaim' ).'/images/spinnerwhite.gif',
      'title' => 'Supprimer',
      'attributes' => array()
  ));

  // Chargement AJAX Spinner
  $form['loading'] = array(
   '#type' => 'markup',
     // Données é afficher
   '#prefix' => '<div id="loading">' . $image_loading,
   '#suffix' => '</div>',
  );

  // Affiche les popups
  _parametres_render_popup_add($form);
  _parametres_render_popup_edit($form);
  _parametres_render_popup_delete($form);

  return $form;
}

function _parametres_render_popup_add(&$form) {
  // Define popup
  $popup_header ='<div id="popup-add" class="modal fade">
            <div class="modal-dialog">
              <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                  <h4 class="modal-title">Ajouter un élément</h4>
                </div>';

  $popup_footer ='</div><!-- /.modal-content -->
          </div><!-- /.modal-dialog -->
            </div><!-- /.modal -->';


  $form['popup_add']['header_add'] = array(
      '#type' => 'markup',
      '#prefix' => $popup_header,
      '#suffix'   => '<div class="modal-body">',
  );

  $form['popup_add']['nature_demande_add'] = array(
      '#type'     => 'select',
      '#title'    => t('Nature de demande'),
      '#options' => parametres_db_get_nature_demande(),
  );

  $form['popup_add']['code_add'] = array(
      '#type'     => 'textfield',
      '#title'    => t('Code'),
  );

  $form['popup_add']['label_add'] = array(
      '#type'     => 'textfield',
      '#title'    => t('Libellé'),
  );

  $form['popup_add']['is_mandatory_add'] = array(
      '#type'     => 'checkbox',
      '#title'    => t('Est obligatoire'),
  );

  $form['popup_add']['quit_add'] = array(
      '#type' => 'submit',
      '#value' => t('Annuler'),
      '#prefix'   => '</div><div class="modal-footer">',
      '#attributes' => array('class' => array('btn btn-danger cancel-button')),
  );

  $form['popup_add']['save_add'] = array(
      '#type'     => 'submit',
      '#value'    => t('Ajouter'),
      '#attributes' => array('class' => array('btn btn-success')),
  );

  $form['popup_add']['footer_add'] = array(
      '#type' => 'markup',
      '#prefix'   => '</div>',
      '#markup' => $popup_footer,
  );
}


function _parametres_render_popup_delete(&$form) {
  // Define popup
  $popup_header ='<div id="popup-delete" class="modal fade">
            <div class="modal-dialog">
              <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                  <h4 class="modal-title">Supprimer un élément</h4>
                </div>';

  $popup_body = '<div class="modal-body">';
  $popup_body .= '<div class="msg">Etes-vous sér de vouloir supprimer l\'élément "<span class="element-name"></span>" du référentiel "<span class="referentiel-name"></span>" ?</div>';
  $popup_body .= '</div>';


  $popup_footer ='</div><!-- /.modal-content -->
          </div><!-- /.modal-dialog -->
            </div><!-- /.modal -->';


  $form['popup_delete']['header_delete'] = array(
      '#type' => 'markup',
      '#prefix' => $popup_header . $popup_body,
  );

  $form['popup_delete']['id_rerentiel'] = array(
      '#type'     => 'hidden',
  );

  $form['popup_delete']['quit_delete'] = array(
      '#type' => 'submit',
      '#value' => t('Annuler'),
      '#prefix'   => '<div class="modal-footer">',
      '#attributes' => array('class' => array('btn btn-danger cancel-button')),
  );

  $form['popup_delete']['save_delete'] = array(
      '#type'     => 'submit',
      '#value'    => t('Supprimer'),
      '#attributes' => array('class' => array('btn btn-success')),
  );

  $form['popup_delete']['footer_delete'] = array(
      '#type' => 'markup',
      '#prefix'   => '</div>',
      '#markup' => $popup_footer,
  );
}


function _parametres_render_popup_edit(&$form) {
  // Define popup
  $popup_header ='<div id="popup-edit" class="modal fade">
            <div class="modal-dialog">
              <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                  <h4 class="modal-title">Modifier un élément</h4>
                </div>';

  $popup_footer ='</div><!-- /.modal-content -->
          </div><!-- /.modal-dialog -->
            </div><!-- /.modal -->';

  $form['popup_edit']['header_edit'] = array(
      '#type' => 'markup',
      '#prefix' => $popup_header,
      '#suffix'   => '<div class="modal-body">',
  );

  $form['popup_edit']['nature_demande_edit'] = array(
      '#type'     => 'select',
      '#title'    => t('Nature de demande'),
      '#options' => parametres_db_get_nature_demande(),
  );

  $form['popup_edit']['id_rerentiel_edit'] = array(
      '#type'     => 'hidden',
  );

  $form['popup_edit']['code_edit'] = array(
      '#type'     => 'textfield',
      '#title'    => t('Code'),
  );

  $form['popup_edit']['label_edit'] = array(
      '#type'     => 'textfield',
      '#title'    => t('Libellé'),
  );

  $form['popup_edit']['is_mandatory_edit'] = array(
      '#type'     => 'checkbox',
      '#title'    => t('Est obligatoire'),
  );

  $form['popup_edit']['quit_edit'] = array(
      '#type' => 'submit',
      '#value' => t('Annuler'),
      '#prefix'   => '</div><div class="modal-footer">',
      '#attributes' => array(
          'class' => array('btn btn-danger cancel-button'),
      )
  );

  $form['popup_edit']['save_edit'] = array(
      '#type'     => 'submit',
      '#value'    => t('Modifier'),
      '#attributes' => array('class' => array('btn btn-success')),
  );

  $form['popup_edit']['footer_edit'] = array(
      '#type' => 'markup',
      '#prefix'   => '</div>',
      '#markup' => $popup_footer,
  );
}