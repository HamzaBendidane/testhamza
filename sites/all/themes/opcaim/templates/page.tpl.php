<?php
?>
  <?php
  if (user_is_logged_in()):
    include 'header.tpl.php';
  else:
    include 'header-not-logged.tpl.php';
  endif;
  ?>
<div class = "row ">

  <?php
  if (user_is_logged_in()):
  ?>
  <!--         Navigation -->
  <div class="col-lg-3 col-md-3 col-sm-3 col-xs-3 Nav opcaimBleuCi">
  <?php if ($page['sidebar_first']): ?>
    <div id="sidebar-first" class="sidebar">
      <?php print render($page['sidebar_first']); ?>
      <?php
      print theme_image(array(
          'path' =>  base_path().drupal_get_path('theme', 'opcaim' ).'/images/cerfa.png',
          'title' => 'Cerfa',
          'width' => '100%',
          'attributes' => array('class' => 'image-cerfa', 'id' => 'etape-cerfa',)
      ));
      ?>
    </div>
  <?php endif; ?>
  </div>
  <!--       Fin Navigation -->

  <div class="col-lg-9 col-md-9 col-sm-9 col-xs-9">
    <div id="center">
      <div id="squeeze">
        <div class="right-corner">
          <div class="left-corner">

            <?php print $messages; ?>

            <div class="clearfix"></div>

            <?php print render($page['content']); ?>

          </div>
        </div>
      </div>
    </div>
  </div>
  <?php
  else:
  print '<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">';

  print $messages;

  print '<div class="clearfix"></div>';
  print render($page['content']);
  print '</div>';
  endif;
  ?>
</div>

<?php include 'footer.tpl.php'; ?>