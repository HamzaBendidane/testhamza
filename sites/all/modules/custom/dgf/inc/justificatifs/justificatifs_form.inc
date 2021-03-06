<?php

/**
 * INCLUDES LANGS & VALIDATIONS
 *
 */
function _dgf_justificatifs_require_once() {
  require_once 'justificatifs_db.inc';
  require_once 'justificatifs_langs.inc';
  require_once 'justificatifs_validate.inc';
  require_once 'justificatifs_submit.inc';
}

/**
 *  FICHIERS CSS & JS
 *
 */
 function _dgf_justificatifs_include_js_css() {
  drupal_add_js(drupal_get_path('module', 'dgf' ) . '/inc/justificatifs/assets/js/justificatifs.js' );
  drupal_add_css(drupal_get_path('module', 'dgf' ) . '/inc/justificatifs/assets/css/justificatifs.css' );
}

/**
 *  FORMULAIRE D'UPLOAD DE FICHIERS
 *  @param : $form   et  &$form_state
 *
 */
function dgf_justificatifs_form($form , &$form_state) {
  _dgf_justificatifs_require_once();
  _dgf_justificatifs_include_js_css();

  // on regarde le 3eme argument de l'url pour retrouver s'il y a des données
  $temp_dgf_form_justificatif = array();
  // s'il est rempli, on récupère les informations de la bdd
  if (arg(3) !== null) {
    $id_dgf = arg(3);
    $temp_dgf_form_justificatif = justificatifs_db_get_temp_dgf_form_justificatif($id_dgf);
  } else {
    return;
  }

  //______________________________ Step 1: Choix des pièces à fournir  _____________________________ //

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa.png',
  );

  $form['steps1'] = array(
      '#type' => 'markup',
      '#markup' =>  '<div class="row"><h3><span class="num">1</span> ' . t(@J_FILE_SELECT) . '</h3></div>',
  );
  // Contient les valeurs à afficher
  $render = _dgf_justificatifs_html($form_state, $id_dgf, $temp_dgf_form_justificatif);

  // Listes des pièces à joindre
  $form['convention']['listes'] = array(
      '#type' => 'markup',
      '#markup' =>  $render,
  );

  $form['convention']['info'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="intro">'.t(@J_INTRO).'</div>',
  );

  $form['convention']['error_select_file'] = array(
      '#type' => 'textfield',
//       '#attributes' => array('hidden' => true),
  );


  $form['convention']['id_dgf'] = array(
      '#type' => 'hidden',
      "#default_value" => $id_dgf
  );

  // UPLOAD FICHIER
  $form['convention']['id_ref_file'] = array(
      '#type' => 'hidden',
  );

  //______________________________ Step 2: Upload des fichiers  _________________________________ //

  $form['convention']['infos_find'] = array(
      '#type' => 'markup',
      '#markup' =>  '<div class="row"><h3><span class="num">2</span> ' . t(@J_FILE_FIND) . '</h3></div>',
  );

  $form['convention']['infos_plus'] = array(
      '#type' => 'markup',
      '#markup' =>  '<div class="row"><b>' . t(@J_FILE_FORMAT) . '</b></div>',
  );

  $form['convention']['file_to_upload'] = array(
      '#type' => 'file',
      '#title' => t('Fichier à joindre'),
      '#title_display' => 'invisible',
      '#size' => 60,
      '#description' => t(@J_FILE_BROWSE),
      '#attributes'  => array('class' => array('cssfile')),
      '#upload_validators' => array(
          'file_validate_size' => array(1024*1024),
          'file_validate_extensions' => array('gif jpg jpeg'),
       )
  );

//   // AJOUTER UN NOUVEL UPLOAD
//   $form['convention']['button_files'] = array(
//   '#type' => 'button',
//   '#value' => t('AJOUTER'),
//   '#attributes'  => array('class' => array('btn btn-success'))
//   );

  $form['convention']['infos_warning'] = array(
      '#type' => 'markup',
      '#markup' =>  '<div id="limit-size" class="row"><b>' . t(@J_INFOS_WARNING) . '</b></div>',
  );

  //______________________________ Step 3: Bouton envoyer  _________________________________ //

  $form['convention']['infos_join'] = array(
      '#type' => 'markup',
      '#markup' =>  '<div class="row"><h3><span class="num">3</span> ' . t(@J_FILE_CLIC) . '</h3></div>',
  );
  $form['convention']['join_file'] = array(
      '#type' => 'submit',
      '#value' => t('JOINDRE LA PIECE'),
      '#validate' =>  array(
          'dgf_justificatifs_form_standard',
          'dgf_justificatifs_form_specific'
      ),
      '#submit' =>  array('dgf_justificatifs_form_submit_file'),
      '#attributes' => array('class' => array('btn btn-primary')),
  );

  // Affiche le tableau des résults
  $form['convention']['result'] = array(
  '#type' => 'markup',
  '#markup' => _dgf_justificatifs_results($temp_dgf_form_justificatif),
  );

  // utilisation de la modal générique
  $form['clearfix'] = array(
  '#type' => 'markup',
  '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
  '#type' => 'markup',
  '#markup' => '</div></div>',
  );

  // Ajout des boutons d'actions
  $validatorsBoutonNext = array('dgf_justificatifs_final_form_validate');

  $submitsBoutonNext = array('dgf_justificatifs_final_form_submit'); // dgf_justificatifs_prev_form_submit

  dgf_boutons_action_form($form, $validatorsBoutonNext, $submitsBoutonNext);

  // Ajout de la modal quitter
  $validatorsQuit = array('dgf_justificatifs_form_validate');
  $validatorsSave = array('dgf_justificatifs_form_validate');
  $submitsSave = array('dgf_justificatifs_form_validate');

  dgf_modal_quit_form($form, $validatorsQuit, $validatorsSave, $submitsSave);

  return $form;
}



/**
 * Gère les champs obligatoires et complémentaires
 *
 */
function _dgf_justificatifs_html($form_state, $id_dgf, $temp_dgf_form_justificatif) {
  // on récupère les réfs justificatifs de cette demande (on récupère la nature de demande correspondante)
  $ref_justificatifs = justificatifs_db_get_ref_justificatif($id_dgf, $temp_dgf_form_justificatif);

   $saisieOrganisme = organisme_formation_db_get_temp_dgf_form_organisme_formation($id_dgf);
  // On construit notre html
  $justificatifs_mandatory = '';
  $justificatifs_complementary = '';
  if ($ref_justificatifs) {

    foreach ($ref_justificatifs as $justificatif) {

        if (!$saisieOrganisme['evaluation_preformative'] && $justificatif->id ==5) continue;

      if (isset($form_state['input']['id_ref_file']) && $form_state['input']['id_ref_file'] == $justificatif->id) {
        $classSelected = 'select';
      } else {
        $classSelected = '';
      }
      if ($justificatif->is_mandatory) {
        $justificatifs_mandatory .= '<li id="'.$justificatif->id.'" class="justif-select '.$classSelected.'">'
            .$justificatif->label.'<span class="required">*</span></li>';
      } else {
        $justificatifs_complementary .= '<li id="'.$justificatif->id.'" class="justif-select '.$classSelected.'">'
            .$justificatif->label.'</li>';
      }
    }
  }

  $justif_required = "<div class='col-lg-6'>
                        <p>Type de pièce(s) à joindre <b>impérativement</b></p>
                        <ul class='list-unstyled justifs'>
                           $justificatifs_mandatory
                        </ul>
                      </div>";
  $justif_comp = "<div class='col-lg-6'>
                    <p>Type de pièce(s) complémentaires éventuelles</p>
                    <ul class='list-unstyled justifs-complements'>
                      $justificatifs_complementary
                    </ul>
                  </div>";

  $html = "<div class='row'>";
  $html .= $justif_required;
  $html .= $justif_comp;
  $html .= "</div>";

  return $html;
}

/**
 *  Gère l'affichage des fichiers d'upload
 *
 *
 */
function _dgf_justificatifs_results($temp_dgf_form_justificatif) {
  // TODO : utiliser un fichier template !
  $html  = '<table id="listfiles" class="table table-condensed small-margin-top">';
  $html .= '<thead>';
  $html .= '<th>Type de la pièce jointe</th>';
  $html .= '<th class="center">Nom du fichier</th>';
  $html .= '<th class="center"></th>';
  $html .= '</thead>';
  $html .= '<tbody>';
  if ($temp_dgf_form_justificatif) {
    foreach ($temp_dgf_form_justificatif as $just) {

      // Gestion du lien document
      $link_doc = '/' . conf_path() . '/files/opcaim' . $just->repertoire_fichier . $just->nom_fichier;
      $link_doc = l($just->nom_fichier, $link_doc, array('html' => false));
      // Gestion du lien supprimer
      $image_sup = theme_image(array(
          'path' =>  base_path().drupal_get_path('theme', 'opcaim' ).'/images/delete.png',
          'title' => 'Supprimer',
          'attributes' => array()
      ));
      $link_sup = l($image_sup, '/dgf/demande/justificatifs/'.$just->id_dgf.'/sup/'.$just->id, array('html' => true));
      // Affichage du html
      $html .= '<tr id="res">';
      $html .= '<td class="types">'.$just->label.'</td>';
      $html .= '<td align="center">'.$link_doc.'</td>';
      $html .= '<td align="center">'.$link_sup.'</td>';
      $html .= '</tr>';
    }
  }
  $html .= '</tbody>';
  $html .= '</table>';

  return $html;
}

function justificatifs_delete_files($id_dgf, $id_justificatif) {

  _dgf_justificatifs_require_once();

  // supprimer le document du serveur
  $temp_dgf_form_justificatif = justificatifs_db_get_temp_dgf_form_justificatif($id_dgf, $id_justificatif);
  drupal_unlink(DEFAULT_FILE_PATH.$temp_dgf_form_justificatif['repertoire_fichier'].$temp_dgf_form_justificatif['nom_fichier']);

  // supprimer la ligne de la bdd
  justificatifs_db_delete_temp_dgf_form_justificatif($id_justificatif);
  drupal_set_message(t("Le fichier ".$temp_dgf_form_justificatif['nom_fichier']." a bien été supprimé."));
  drupal_goto('/dgf/demande/justificatifs/'.$id_dgf);
}