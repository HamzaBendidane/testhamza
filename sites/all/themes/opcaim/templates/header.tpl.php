<div id="header">
     <div class="row">
          <div class="col-lg-1 col-md-1 col-sm-1 col-xs-1">
             <?php if ($logo): ?>
                <a href="/">
                    <img src="<?php print $logo ?>" alt="logo"
                        title="logo" id="logo" class="logo" />
                </a>
               <?php endif; ?>
          </div>

          <div class="col-lg-2 col-md-2 col-sm-2 col-xs-2 ">
                <img class="title pull-left"
                src="/<?php print drupal_get_path('theme', 'opcaim'); ?>/images/title.png"
                alt="Organisme Paritaire Collecteur Agréé des Industries de la Métallurgie">
                <br>
                <img
                src="/<?php print drupal_get_path('theme', 'opcaim'); ?>/images/slogan.png"
                alt="Organisme Paritaire Collecteur Agréé des Industries de la Métallurgie">

          </div>

          <div class="col-lg-4 col-lg-offset-5 col-md-4 col-md-offset-5 col-sm-4 col-sm-offset-5 col-xs-4 col-xs-offset-5 <?php print isset($user->name) ? 'profilConnexion' : ''; ?>">
          <div class="profilConnexionImage">

              <img class="title pull-left"
                src="/<?php print drupal_get_path('theme', 'opcaim'); ?>/images/encadre.png"
                alt="" style="width:100%;height:85px">

          </div>
            <div class="profildate col-lg-8 col-md-8 col-sm-8 col-xs-8">
                <div class="opcaimBleuP profil"><?php print isset($user->name) ? $user->name : ''; ?>
                </div>
                <div> <?php if (isset($user->login)) {
                        		$dateUser = date('d/m/Y H:i', $user->login);
                        		$date = str_replace(' ',' <br />à ',$dateUser);
                        		print isset($user->login) ? 'Dernière connexion : ' . $date : 'Inconnue';
                			}
                       ?>
                </div>
            </div>

            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-4 profilCo opcaimBlanc">
                <?php
                  print l(t('MON PROFIL'), 'opcaim/mon-compte');
                  print '<br />';
                  print isset($user->name) ? l(t('Déconnexion'), 'user/logout', array('query' => array('destination' => 'login'))) : '';
                ?>
            </div>
          </div>

     </div>
     <div class = "row">
         <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 separator"> <img src="<?php print base_path() . path_to_theme() . '/' . 'images/title-separator.png'; ?>" /> </div>
     </div>
      <div class = "row">
         <div class="col-lg-2 col-lg-offset-10 header-icons">
         <a href=<?php print base_path()?> ><img src="<?php print base_path() . path_to_theme() . '/' . 'images/home.png'; ?>" /> </a>
            <img src="<?php print base_path() . path_to_theme() . '/' . 'images/info.png'; ?>" />
         </div>
     </div>

     <?php print render($page['header']); ?>
</div>