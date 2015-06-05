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
     </div>
     <?php print render($page['header']); ?>
</div>