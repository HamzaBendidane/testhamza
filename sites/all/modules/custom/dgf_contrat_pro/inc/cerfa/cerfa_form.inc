<?php

function _dgf_contrat_pro_cerfa_require_once() {
  require_once 'cerfa_langs.inc';
  require_once 'cerfa_db.inc';
  require_once 'cerfa_validate.inc';
  require_once('/tcpdf/config/tcpdf_config.php');
  require_once('/tcpdf/tcpdf.php');
  require_once('/tcpdf/tcpdf_import.php');
  require_once('/fpdi/fpdi.php');
}

function _dgf_contrat_pro_include_js_css() {
	drupal_add_css(drupal_get_path( 'module', 'dgf_contrat_pro' ) . '/inc/cerfa/css/cerfa.css');
}

function dgf_contrat_pro_cerfa_form($form, &$form_state) {
  _dgf_contrat_pro_cerfa_require_once();

  _dgf_contrat_pro_include_js_css();

  drupal_add_js('jQuery(document).ready(function () { $("#etape-cerfa").attr("src", $("input[name=\'cerfa-step\']").val());$("#etape-cerfa").show(); });', 'inline');

  global $user;

  // on regarde le 4eme argument de l'url
  if (arg(4) !== null) {
    $id_dgf = (int)arg(4);
  } else {
    return;
  }

  $file_uri = dgf_contrat_pro_cerfa_generate_pdf($id_dgf, 'F');
  $file_url = file_create_url(file_build_uri($file_uri));

  $form['padding'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="padding15"><div id="boutonAction" class="row">',
  );

  $form['cerfa-step'] = array(
      '#type' => 'hidden',
      '#default_value' => '/'.drupal_get_path('theme', 'opcaim').'/images/cerfa.png',
  );

  $form['id_dgf'] = array (
      '#type' => 'hidden',
      '#value' => $id_dgf
  );


  $form ['back'] = array (
      '#type' => 'button',
      '#value' => t ( 'Modifier' ),
      '#limit_validation_errors' => array(),
      '#validate' => array (
          'dgf_contrat_pro_cerfa_form_validate'
      )
  );

  $form ['cerfa-print'] = array (
  		'#type' => 'markup',
  		'#limit_validation_errors' => array(),
      '#markup' => '<a href="'. $file_url.'" target="_blank" class="form-submit">'.t('IMPRIMER').'</a>',
  );

  $form ['next'] = array (
      '#type' => 'button',
      '#value' => t ( 'Valider' ),
      '#validate' => array (
          'dgf_contrat_pro_cerfa_form_validate'
      ),
      '#submit' => array (
          'dgf_contrat_pro_cerfa_form_submit'
      )
  );


  $form['clearfix'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="clearfix"></div>',
  );

  $form['padding_fin'] = array(
      '#type' => 'markup',
      '#markup' => '</div></div>',
  );



  drupal_clear_css_cache();
  drupal_clear_js_cache();

  // Affichage du pdf
  /*$pdf = '<div id="cerfaprint">
  		<iframe src="'. $file_url .'" style="width:100%; height:1000px;" id="pdftoprint" name="pdftoprint">
          [Votre navigateur ne <em>supporte</em> pas les <code>iframes</code> ou n\'est pas configuré pour les afficher. ]
          <a href="'. $file_url . '">Vous pourrez accéder à votre Cerfa via ce lien</a>
        </iframe>
      </div>';*/

  $pdf = '<div id="cerfaprint">
  <object data="'.$file_url.'" type="application/pdf" width="100%" height="1000px" id="pdftoprint">
  <p>[Votre navigateur ne <em>supporte</em> pas les <code>iframes</code> ou n\'est pas configuré pour les afficher. ]
          <a href="'. $file_url . '">Vous pourrez accéder à votre Cerfa via ce lien</a></p>
  </object>
  </div>';

  $form['pdf'] = array(
      '#type' => 'markup',
      '#markup' => $pdf,
  );


  return $form;
}




function drupal_flush_css_js() {
  // Change query-strings on css/js files to enforce reload for all users.
  // The timestamp is converted to base 36 in order to make it more compact.
  variable_set ( 'css_js_query_string', base_convert ( REQUEST_TIME, 10, 36 ) );

  drupal_clear_css_cache();
  drupal_clear_js_cache();

  // Clear the page cache, since cached HTML pages might link to old CSS and
  // JS aggregates.
  cache_clear_all('*', 'cache_page', TRUE);
}

function dgf_contrat_pro_cerfa_generate_pdf($id_dgf, $output) {


  // Extraction des données à pré-remplir
  $infos = dgf_contrat_pro_cerfa_get_datas($id_dgf);

  // chemin du fichier
  $filename = drupal_get_path('module', 'dgf_contrat_pro' ) . '/inc/cerfa/'. @TEMPLATE_CERFA;

  // initiate FPDI
  $pdf = new FPDI();
  // Supression de la ligne noir du header
  $pdf ->setPrintHeader(false);
  // Supression de la ligne noir du header
  $pdf ->setPrintFooter(false);
  // add a page
  $pdf->AddPage('P', 'A4');
  // set the source file
  $pdf->setSourceFile($filename);
  // import page 1
  $tplIdx = $pdf->importPage(1);

  // use the imported page and place it at point 0,0
  // $pdf->useTemplate($tplIdx, 0, 0, 210, 297, true);
  $pdf->useTemplate($tplIdx, 0, 0, null, null, false);

  $pdf->SetFont('Helvetica', '' , 9);

  ///////////////
  // EMPLOYEUR //
  ///////////////
  if(isset($infos['employe'])) {
    dgf_contrat_pro_alimenter_employeur($pdf, $infos['employe']);
  }

   /////////////
   // SALARIE //
   /////////////
   if(isset($infos['salarie'])) {
    dgf_contrat_pro_alimenter_salarie($pdf, $infos['salarie']);
   }

   ////////////
   // TUTEUR //
   ////////////
   if(isset($infos['tuteur'])) {
    dgf_contrat_pro_alimenter_tuteur($pdf, $infos['tuteur']);
   }

   /////////////
   // CONTRAT //
   /////////////
   if(isset($infos['contrat'])) {
    dgf_contrat_pro_alimenter_contrat($pdf, $infos['contrat']);
   }
   ///////////////
   // FORMATION //
   ///////////////
   if(isset($infos['formation'])) {
    dgf_contrat_pro_alimenter_formation($pdf, $infos['formation']);
   }

   ///////////////
   // SIGNATURE //
   ///////////////
   if(isset($infos['signature'])) {
   	dgf_contrat_pro_alimenter_signature($pdf, $infos['signature']);
   }

   if($output == 'F') {
    $name = 'cerfa_' . $infos['employe']['siret'] . '-'. $infos['demande']['num_demande'] . '.pdf';
    $path_uri = 'opcaim/demande/cerfa/' . $name;
    $filename = $_SERVER['DOCUMENT_ROOT'].'sites/default/files/' . $path_uri;
   }
   else {
     $filename = $name;
   }

   ob_get_clean();

   $pdf->Output($filename , $output);

   return $path_uri ;
}


function dgf_contrat_pro_explode_numeric($numeric) {
  $num_retour['entier'] = '';
  $num_retour['decimal'] = '';

  if(isset($numeric)) {
    $num = explode('.', $numeric);
    $num_retour['entier'] = $num[0];
    $num_retour['decimal'] = $num[1];
  }
  return $num_retour;
}

function dgf_contrat_pro_explode_date ($date) {
  $date = substr($date, 0, 10);
  $date_explode['jj'] = '';
  $date_explode['mm'] = '';
  $date_explode['aaaa'] = '';
  $date_retour['jj'] = '';
  $date_retour['mm'] = '';
  $date_retour['aaaa'] = '';

  if(isset($date)) {
    $date_explode = explode('-', $date);
    $date_retour['jj'] = $date_explode[2];
    $date_retour['mm'] = $date_explode[1];
    $date_retour['aaaa'] = $date_explode[0];
  }

  return $date_retour;
}

function dgf_contrat_pro_ecrire_chaine(&$pdf, $str, $x, $y, $l, $h) {
   while ($pdf->GetStringWidth($str) > $l) {
    $str = substr($str,0,-1);
   }
  $pdf->SetXY($x, $y);
  $pdf->Cell($l, $h, $str);


}

function dgf_contrat_pro_ecrire_chaine_multi(&$pdf, $str, $x, $y, $l, $h, $nb_lignes) {
  while ($pdf->GetStringWidth($str) > ($l * $nb_lignes)) {
    $str = substr($str,0,-1);
  }
  $pdf->SetXY($x, $y);
  $pdf->MultiCell($l, $h, $str, 0, 'L');
}



function dgf_contrat_pro_remplir_cases_inverse (&$pdf, $str, $x, $y, $l, $h) {
  // Split de la chaine de caractère
  $chars = preg_split('//', $str, -1, PREG_SPLIT_NO_EMPTY);

  $chars_inverse  = array_reverse($chars);
  // ecriture de la chaine dans le pdf
  foreach ($chars_inverse as $char) {

    $pdf->SetXY($x, $y);
    $pdf->Cell($l, $h, $char);
    $x = $x - $l;
  }
}

function dgf_contrat_pro_remplir_cases(&$pdf, $str, $x, $y, $l, $h) {
  // Split de la chaine de caractère
  $chars = preg_split('//', $str, -1, PREG_SPLIT_NO_EMPTY);

  // ecriture de la chaine dans le pdf
  foreach ($chars as $char) {

    $pdf->SetXY($x, $y);
    $pdf->Cell($l, $h, $char);
    $x = $x + $l;
  }
}

function dgf_contrat_pro_alimenter_employeur(&$pdf, &$infos) {

  // nom et prénom
  if(isset($infos['nom_prenom'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['nom_prenom'], 31, 23, 70, 5);
  }

  // Numéro de voie
  if(isset($infos['num_voie'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['num_voie'], 9, 31.5, 8, 5);
  }

  // Numéro de voie
  if(isset($infos['voie'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['voie'], 25, 31.5, 75, 5);
  }
  // Complément d'adresse
  if(isset($infos['complement'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['complement'], 24, 36, 76, 5);
  }

  // Code postal
  if(isset($infos['code_postal'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['code_postal'], 24, 41.5, 3, 5);
  }

  // commune
  if(isset($infos['commune'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['commune'], 61, 41.5, 39, 5);
  }
  // telephone
  if(isset($infos['telephone'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['telephone'], 20.3, 46, 2.87, 5);
  }

  // telecopie_employe
  if(isset($infos['telecopie'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['telecopie'], 67.4, 46, 2.87, 5);
  }

  // courriel
  if(isset($infos['mail'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['mail'], 17, 49.6, 40, 5);
  }
  if(isset($infos['mail_extension'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['mail_extension'], 60, 49.6, 40, 5);
  }

  // Caisse de retraite
  if(isset($infos['caisse_retraite']))
  dgf_contrat_pro_ecrire_chaine($pdf, $infos['caisse_retraite'], 51, 54.5, 49, 5);

  // organisme prévoyance
  if(isset($infos['orga_prevoyance'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['orga_prevoyance'], 63, 59, 37, 5);
  }

  // Particulier-employeur
  if(isset($infos['particulier_employeur'])) {
    if($infos['particulier_employeur']) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 135.8, 20.4, 10, 5);
    }
    else {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 143.5, 20.4, 10, 5);
    }
  }

  // N°urssaf
  if(isset($infos['urssaf'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['urssaf'], 156.5, 25, 2.87, 5);
  }

  // N°siret
  if(isset($infos['siret'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['siret'], 106.5, 32.9, 2.87, 5);
  }
  // Code naf employe
  if(isset($infos['naf'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['naf'], 122.6, 37, 2.87, 5);
  }
  // Effectif salarié
  if(isset($infos['effectif_salarie'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['effectif_salarie'], 147.6, 41.5, 2.87, 5);
  }
  // convention colective
  if(isset($infos['convention_collective'])) {
    dgf_contrat_pro_ecrire_chaine_multi($pdf, $infos['convention_collective'], 107, 50, 95, 5, 2);
  }
  // Code IDCC
  if(isset($infos['IDCC'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['IDCC'], 173.6, 59, 2.87, 5);
  }
  // MyOPCA
  if(isset($infos['num_myopca'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['num_myopca'], 175, 271.9, 30, 5, 2);
  }

  // Nom OPCAIM
  dgf_contrat_pro_ecrire_chaine($pdf, 'OPCAIM', 28, 271.9, 30, 5, 2);
}


function dgf_contrat_pro_alimenter_salarie (&$pdf, $infos) {

  if(isset ($infos['nom_prenom'])) {
    // nom et prénom
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['nom_prenom'], 4, 71.5, 95, 5);
  }

  if(isset ($infos['num_voie'])) {
    // numéro de voie
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['num_voie'], 21, 77.5, 5, 5);
  }

  if(isset ($infos['voie'])) {
    // voie
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['voie'], 35, 77.2, 65, 5);
  }

  if(isset ($infos['complement'])) {
    // Complément
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['complement'], 23, 82, 77, 5);
  }

  if(isset ($infos['code_postal'])) {
    // code postal
    dgf_contrat_pro_remplir_cases($pdf, $infos['code_postal'], 24.3, 86.5, 3, 5);
  }

  if(isset ($infos['commune'])) {
    // commune
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['commune'], 61, 87, 39, 5);
  }

  if(isset ($infos['telephone'])) {
    // telephone
    dgf_contrat_pro_remplir_cases($pdf, $infos['telephone'], 21.5, 91.3, 2.87, 5);
  }

  if( (isset ($infos['mail'])) && (isset ($infos['mail_extension'])) ) {
    // mail
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['mail'], 18, 94.9, 40, 5);
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['mail_extension'], 62, 94.9, 38, 5);
  }

  if(isset ($infos['date_naissance'])) {
    // date de naissance
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_naissance']['jj'], 133.7, 69, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_naissance']['mm'], 141.3, 69, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_naissance']['aaaa'], 149, 69, 2.87, 5);
  }

  if (isset($infos['sexe'])) {
    // sexe
    if (trim($infos['sexe']) == 'Monsieur') {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 183.2, 68.5, 10, 5);
    } else {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 191.5, 68.5, 10, 5);
    }
  }

  if (isset($infos['handicap'])) {
    // travailleur handicapé
    if ($infos['handicap']) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 185.4, 73.15, 10, 5);
    } else {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 194.5, 73.15, 10, 5);
    }
  }

  if (isset($infos['pole_emploi'])) {
    // pole emploi
    if($infos['pole_emploi']) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 135.5, 77.6, 10, 5);
    }
    else {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 144.85, 77.6, 10, 5);
    }
  }

  if(isset ($infos['num_inscription'])) {
    // num inscription
    dgf_contrat_pro_remplir_cases($pdf, $infos['num_inscription'], 145.2, 82, 2.87, 5);
  }

  if(isset ($infos['duree_inscription'])) {
    // duree
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_inscription'], 191, 82, 3, 5);
  }

  if(isset ($infos['situation'])) {
    // situation av contrat
    dgf_contrat_pro_remplir_cases($pdf, $infos['situation'], 142.85, 87, 3, 5);
  }

  if(isset ($infos['type_min_social'])) {
    // type minimum social
    dgf_contrat_pro_remplir_cases($pdf, $infos['type_min_social'], 161.2, 91.5, 3, 5);
  }

  if(isset ($infos['diplome'])) {
    // diplome
    dgf_contrat_pro_remplir_cases($pdf, $infos['diplome'], 157.2, 95.7, 3.2, 5);
  }
}


function dgf_contrat_pro_alimenter_tuteur(&$pdf, $infos) {

  // Tuteur etablissement //
  // nom et prénom
  if(isset($infos['etablissement']['nom_prenom'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['etablissement']['nom_prenom'], 4, 111, 96, 5);
  }

  // Emploi
  if(isset($infos['etablissement']['emploi'])) {
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['etablissement']['emploi'], 25.5, 116, 74.5, 5);
  }
  // date de naissance
  if(isset($infos['etablissement']['date_naissance'])) {
    dgf_contrat_pro_remplir_cases($pdf, $infos['etablissement']['date_naissance']['jj'], 31.5, 121, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['etablissement']['date_naissance']['mm'], 40.5, 121, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['etablissement']['date_naissance']['aaaa'], 49, 121, 2.87, 5);
  }


//   // Tuteur entreprise //
//   // nom et prénom
//   if(isset($infos['entreprise']['nom_prenom'])) {
//     dgf_contrat_pro_ecrire_chaine($pdf, $infos['entreprise']['nom_prenom'], 106, 111, 100, 5);

//   // Emploi
//   if(isset($infos['entreprise']['emploi'])) {
//     dgf_contrat_pro_ecrire_chaine($pdf, $infos['entreprise']['emploi'], 127.5, 116, 73, 5);

//   // date de naissance
//   if(isset($infos['entreprise']['date_naissance'])) {
//     dgf_contrat_pro_remplir_cases($pdf, $infos['entreprise']['date_naissance']['jj'], 133.7, 121, 2.87, 5);
//     dgf_contrat_pro_remplir_cases($pdf, $infos['entreprise']['date_naissance']['mm'], 142.5, 121, 2.87, 5);
//     dgf_contrat_pro_remplir_cases($pdf, $infos['entreprise']['date_naissance']['aaaa'], 151, 121, 2.87, 5);
//   }
}

function dgf_contrat_pro_alimenter_contrat(&$pdf, $infos) {
  // nature
  if(isset($infos['nature'])) {
    if($infos['nature'] == 0) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 29.6, 130.1, 10, 5);
    }

    if($infos['nature'] == 1) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 39.5, 130.1, 10, 5);
    }

    if($infos['nature'] == 2) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 51, 130.1, 10, 5);
    }
  }

  if(isset($infos['type_contrat'])) {
    // type de contrat
    dgf_contrat_pro_remplir_cases($pdf, $infos['type_contrat'], 129.7, 130.5, 3.2, 5);
  }

  if(isset($infos['emploi_occupe'])) {
    // emploi occupé
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['emploi_occupe'], 76, 134.5, 24, 5);
  }

  if(isset($infos['classification'])) {
    // classification
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['classification'], 77.5, 141, 22, 5);
  }

  if(isset($infos['niveau'])) {
    // niveau
    dgf_contrat_pro_remplir_cases($pdf, $infos['niveau'], 118.2, 142, 3, 5);
  }

  if(isset($infos['coef_hierarchique'])) {
    // coef hierarchique
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['coef_hierarchique'], 182, 142, 3, 5);
  }

  if(isset($infos['date_debut'])) {
    // date de debut
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['jj'], 4.5, 149.5, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['mm'], 12, 149.5, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['aaaa'], 19.8, 149.5, 2.87, 5);
  }

  if(isset($infos['date_fin'])) {
    // date de fin
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['jj'], 106.5, 149.5, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['mm'], 114, 149.5, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['aaaa'], 121.5, 149.5, 2.87, 5);
  }

  if(isset($infos['duree_periode'])) {
    // duree période
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_periode'], 49.9, 153.5, 3, 5);
  }

  if(isset($infos['duree_hebdo_h'])) {
    // duree hebdomadaire
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_hebdo_h'], 51.5, 158.7, 3, 5);
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_hebdo_min'], 69.7, 158.7, 3, 5);
  }

  if(isset($infos['salaire'])) {
    // salaire brut
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['salaire']['entier'], 50.8, 162.9, 2.64, 5);
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['salaire']['decimal'], 58.3, 162.9, 2.64, 5);
  }
}


function dgf_contrat_pro_alimenter_signature(&$pdf, $infos) {
	// Fait le
	if(isset($infos['faitle'])) {
		dgf_contrat_pro_remplir_cases($pdf, $infos['faitle']['jj'], 15.1, 244, 2.87, 5);
		dgf_contrat_pro_remplir_cases($pdf, $infos['faitle']['mm'], 22.9, 244, 2.87, 5);
		dgf_contrat_pro_remplir_cases($pdf, $infos['faitle']['aaaa'], 30.2, 244, 2.87, 5);
	}
}



/**
 * Récupère les informations peuplant le cerfa
 * @return $infos
 */
function dgf_contrat_pro_cerfa_get_datas($id_dgf = null) {

  $infos = array();
  if($id_dgf) {

    $dgf = dgf_contrat_pro_cerfa_get_dgf_infos($id_dgf);
    if($dgf) {
      $infos['demande']['num_demande'] = $dgf['numero_demande'];
    }

    $lien_dgf_ref_esclave_entreprise = dgf_contrat_pro_cerfa_get_lien_dgf_ref_esclave_entreprise_infos($id_dgf);
    if($lien_dgf_ref_esclave_entreprise) {
      $infos['employe']['num_myopca'] = $lien_dgf_ref_esclave_entreprise['numero_myopca'];
    }

    $salarie = dgf_contrat_pro_cerfa_get_salarie_infos($id_dgf);
    if($salarie) {
      $infos['salarie']['situation'] = $salarie['derniere_situation'];
      $infos['salarie']['type_min_social'] = $salarie['min_sociaux'];
      $infos['salarie']['diplome'] = $salarie['diplome'];
      $infos['salarie']['num_voie'] = $salarie['numero_rue'];
      $infos['salarie']['voie'] = $salarie['nom_rue'];
      $infos['salarie']['complement'] = $salarie['complement_adresse'];
      $infos['salarie']['code_postal'] = $salarie['code_postal'];
      $infos['salarie']['commune'] = $salarie['ville'];
      $infos['salarie']['telephone'] = $salarie['telephone'];
      if ($salarie['email']) {
      $mail = explode('@', $salarie['email']);
        if (isset($mail[0]) && isset($mail[1])) {
          $infos['salarie']['mail'] = $mail[0];
          $infos['salarie']['mail_extension'] = $mail[1];
        }
      }

      if(isset($salarie['numero_inscrit_pole_emploi']) && $salarie['numero_inscrit_pole_emploi'] != null && trim($salarie['numero_inscrit_pole_emploi']) !=  '') {
        $infos['salarie']['pole_emploi'] = true;
      }
      else {
        $infos['salarie']['pole_emploi'] = false;
      }
      $infos['salarie']['num_inscription'] = substr($salarie['numero_inscrit_pole_emploi'], 0, 7);
      $infos['salarie']['duree_inscription'] = $salarie['nombre_mois_inscrit_pole_emploi'];
      $infos['employe']['caisse_retraite'] = $salarie['caisse_retraite'];
      $infos['employe']['orga_prevoyance'] = $salarie['caisse_prevoyance'];
    }

    $tuteur = dgf_contrat_pro_cerfa_get_tuteur_infos($id_dgf);
    if($tuteur) {
      $infos['tuteur']['etablissement']['emploi'] = $tuteur['emploi'];
    }

    $contrat = dgf_contrat_pro_cerfa_get_contrat_infos($id_dgf);
    if($contrat) {
      $infos['contrat']['nature'] = $contrat['id_ref_type_contrat'];
      $infos['contrat']['emploi_occupe'] = $contrat['emploi_occupe'];
      $infos['contrat']['coef_hierarchique'] = $contrat['coefficient'];
      $infos['contrat']['date_debut'] = dgf_contrat_pro_explode_date($contrat['date_debut']);
      $infos['contrat']['date_fin'] = dgf_contrat_pro_explode_date($contrat['date_fin']);
      $infos['contrat']['duree_hebdo_h'] = $contrat['duree_hebdo_travail_heure'];
      $infos['contrat']['duree_hebdo_min'] = $contrat['duree_hebdo_travail_minute'];

      $infos['contrat']['salaire'] = dgf_contrat_pro_explode_numeric($contrat['salaire_brut_mensuel']);
      $infos['contrat']['duree_periode'] = $contrat['duree_essai_jour'];
    }

    $type_contrat = dgf_contrat_pro_cerfa_get_type_contrat_infos($contrat['id_ref_type_contrat']);
    if ($type_contrat ) {
      $infos['contrat']['type_contrat'] = $type_contrat['code'];
    }

    $ref_groupe = dgf_contrat_pro_cerfa_get_ref_groupe_infos($contrat['id_ref_groupe']);
    if($ref_groupe) {
      $infos['contrat']['niveau'] = $ref_groupe['code'];
    }

    $formation = dgf_contrat_pro_cerfa_get_temp_dgf_form_formation_infos($id_dgf);
    if($formation) {
      $infos['formation']['intitule'] = $formation['intitule_formation'];
      $infos['formation']['formation_interne'] = $formation['formation_interne'];
      $infos['formation']['duree_totale'] = $formation['duree_totale_heure'];
      $infos['formation']['duree_enseignement'] = $formation['duree_ens_gen_heure'];
      $infos['formation']['date_debut'] = dgf_contrat_pro_explode_date($formation['date_debut']);
      $infos['formation']['date_fin'] = dgf_contrat_pro_explode_date($formation['date_examen']);
      $infos['formation']['attestation_employeur'] = $formation['formation_interne'];
      if ($formation['formation_interne'] == true) {
        $infos['formation']['nbre_organismes'] = '0';
      } else {
        $infos['formation']['nbre_organismes'] = '1';
      }
    }

    $temp_dgf_form_organisme_formation = dgf_contrat_pro_cerfa_get_temp_dgf_form_organisme_formation_infos($id_dgf);

    if(!$formation['formation_interne']) {
      $vue_organismes_de_formation = dgf_contrat_pro_cerfa_get_vue_organismes_de_formation_infos($temp_dgf_form_organisme_formation['id_ref_esclave_organisme_formation']);

      if($vue_organismes_de_formation) {
      	// ORGANISME DE FORMATION
      	$infos['formation']['organisme'] = $vue_organismes_de_formation['raison_sociale'];
      	$infos['formation']['siret'] = $vue_organismes_de_formation['siret'];
      	$infos['formation']['num_declaration'] = $vue_organismes_de_formation['numero_de_declaration_existence'];
      }
    }

    $vue_entreprises = dgf_contrat_pro_cerfa_get_vue_entreprises_infos($lien_dgf_ref_esclave_entreprise['id_ref_esclave_entreprise']);
    if($vue_entreprises) {
      // ENTREPRISE
      $infos['employe']['naf'] = $vue_entreprises['id_naf'];
      $infos['employe']['nom_prenom'] = $vue_entreprises['raison_sociale'];
      $infos['employe']['telephone'] = $vue_entreprises['telephone_principal'];
      $infos['employe']['telecopie'] = $vue_entreprises['fax'];
      $mail = explode('@', $vue_entreprises['email']);
      if(isset($mail[0]) && isset($mail[1])) {
        $infos['employe']['mail'] = $mail[0];
        $infos['employe']['mail_extension'] = $mail[1];
      }
      $infos['employe']['siret'] = $vue_entreprises['siret'];

      // Si formation interne => l'orgamisme de formation est l'entreprise
      if($formation['formation_interne']) {
      	$infos['formation']['organisme'] = $vue_entreprises['raison_sociale'];
      	$infos['formation']['siret'] = $vue_entreprises['siret'];
      }
    }

    $vue_adresses_entreprises = dgf_contrat_pro_cerfa_get_vue_adresses_entreprises_infos($lien_dgf_ref_esclave_entreprise['id_ref_esclave_entreprise']);
    if($vue_adresses_entreprises) {
      // ADRESSE ENTREPRISE
      $infos['employe']['num_voie'] = $vue_adresses_entreprises['numero_de_rue'];
      $infos['employe']['voie'] = $vue_adresses_entreprises['rue'];
      $infos['employe']['complement'] = $vue_adresses_entreprises['complement_de_rue'] . ' ' . $vue_adresses_entreprises['complement_de_rue_2'];
      $infos['employe']['code_postal'] = $vue_adresses_entreprises['code_postal'];
      $infos['employe']['commune'] = $vue_adresses_entreprises['ville'];
    }

    $vue_conventions_collectives = dgf_contrat_pro_cerfa_get_vue_conventions_collectives_infos($vue_entreprises['id_convention_collective']);
    if($vue_conventions_collectives) {
      // CONVENTION COLLECTIVE
      $infos['employe']['convention_collective'] = $vue_conventions_collectives['libelle'];
    }

    $vue_salaries = dgf_contrat_pro_cerfa_get_vue_salaries_infos($salarie['id_ref_esclave_salarie']);
    if($vue_salaries) {
      $infos['salarie']['nom_prenom'] = trim($vue_salaries['nom']) . ' ' . trim($vue_salaries['prenom']);
      $infos['salarie']['date_naissance'] = dgf_contrat_pro_explode_date($vue_salaries['date_de_naissance']);
      $infos['salarie']['sexe'] = $vue_salaries['libelle'];
      $infos['salarie']['handicap'] = $vue_salaries['est_travailleur_handicape'];
    }

    $vue_tuteurs = dgf_contrat_pro_cerfa_get_vue_salaries_infos($tuteur['id_ref_esclave_salarie']);
    if($vue_tuteurs) {
      $infos['tuteur']['etablissement']['nom_prenom'] = $vue_tuteurs['nom'] . ' ' . $vue_tuteurs['prenom'];
      $infos['tuteur']['etablissement']['date_naissance'] = dgf_contrat_pro_explode_date($vue_tuteurs['date_de_naissance']);
    }

    $vue_specialites_de_formation = dgf_contrat_pro_cerfa_get_vue_specialites_de_formation_infos($formation['id_ref_esclave_specialite']);
    if($vue_specialites_de_formation) {
      $infos['formation']['specialite'] = $vue_specialites_de_formation['libelle'];
    }

    $vue_intitules_de_formation = dgf_contrat_pro_cerfa_get_vue_intitules_de_formation_infos($formation['id_ref_esclave_intitule_formation']);
    if($vue_intitules_de_formation) {
      $infos['formation']['diplome'] = $vue_intitules_de_formation['libelle'];
    }



    $date_debut_contrat = shared_parse_mssql_date($contrat['date_debut']);
    if($date_debut_contrat) {
      $dt_jour = new DateTime();
      $date_jour_P5D = new DateTime();
      $date_jour_P5D = $date_jour_P5D->add(new DateInterval('P5D'));
      $date_jour_P25D = new DateTime();;
      $date_jour_P25D = $date_jour_P25D->add(new DateInterval('P25D'));
      if(!(($date_jour_P5D < $date_debut_contrat) && ($date_debut_contrat < $date_jour_P25D))) {
      	$infos['signature']['faitle'] = dgf_contrat_pro_explode_date(date_format($dt_jour,"Y-m-d"));
      }
    }
    // Connection a la base esclave
    //     db_set_active();

    // TODO : DONNEES MANQUANTES

    //   $infos['employe']['caisse_retraite'] = 'CAISSE RETRAITE';
    //   $infos['employe']['orga_prevoyance'] = 'PREVOYANCE';
    //   $infos['employe']['particulier_employeur'] = true;
    //   $infos['employe']['urssaf'] = '17919845123987';

    //   $infos['employe']['effectif_salarie'] = '45646487';
    //   $infos['employe']['IDCC'] = 'AZER';

    //   $infos['formation']['nbre_organismes'] = '9';
    //   $infos['formation']['type_qualification'] = 'BS';
    //   $infos['formation']['diplome'] = 'MS';

    return $infos;
  }
}

function dgf_contrat_pro_alimenter_formation(&$pdf, $infos) {

  if(isset($infos['organisme'])) {
    // organisme
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['organisme'], 4, 175, 96, 5);
  }
  if(isset($infos['formation_interne'])) {
    // formation interne
    if($infos['formation_interne']) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 60, 180, 10, 5);
    }
    else {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 67.8, 180, 10, 5);
    }
  }

  if(isset($infos['attestation_employeur'])) {
    // attestation de l'employeur
    if($infos['attestation_employeur']) {
      dgf_contrat_pro_ecrire_chaine($pdf, 'X', 4, 184.6, 10, 5);
    }
  }

  if(isset($infos['siret'])) {
    // siret
    dgf_contrat_pro_remplir_cases($pdf, $infos['siret'], 106.5, 176, 2.87, 5);
  }

  if(isset($infos['num_declaration'])) {
    // n° declaration
    dgf_contrat_pro_remplir_cases($pdf, $infos['num_declaration'], 168.5, 179.9, 2.87, 5);
  }

  if(isset($infos['nbre_organismes'])) {
    // nbre d'organismes
    dgf_contrat_pro_remplir_cases($pdf, $infos['nbre_organismes'], 171.4, 184.5, 2.87, 5);
  }

  if(isset($infos['type_qualification'])) {
    // type qualification
    dgf_contrat_pro_remplir_cases($pdf, $infos['type_qualification'], 38.25, 196.5, 2.87, 5);
  }

  if(isset($infos['diplome'])) {
    // diplome
    dgf_contrat_pro_remplir_cases($pdf, $infos['diplome'], 135.8, 196.5, 3.25, 5);
  }

  if(isset($infos['intitule'])) {
    // Intitule
    dgf_contrat_pro_ecrire_chaine($pdf, $infos['intitule'], 4, 203.5, 200, 5);
  }

  if(isset($infos['specialite'])) {
    // spécialite
    dgf_contrat_pro_remplir_cases($pdf, $infos['specialite'], 37.8, 208, 3, 5);
  }

  if(isset($infos['duree_totale'])) {
    // durée totale
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_totale'], 123.7, 212.2, 3.1, 5);
  }

  if(isset($infos['duree_enseignement'])) {
    // durée enseignements
    dgf_contrat_pro_remplir_cases_inverse($pdf, $infos['duree_enseignement'], 116.7, 217, 3.1, 5);
  }

  if(isset($infos['date_debut'])) {
    // date debut enseignement
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['jj'], 55.3, 221.2, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['mm'], 63, 221.2, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_debut']['aaaa'], 70.5, 221.2, 2.87, 5);
  }

  if(isset($infos['date_fin'])) {
    // date fin enseignement
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['jj'], 174.5, 221.2, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['mm'], 182.1, 221.2, 2.87, 5);
    dgf_contrat_pro_remplir_cases($pdf, $infos['date_fin']['aaaa'], 189.75, 221.2, 2.87, 5);
  }
}


