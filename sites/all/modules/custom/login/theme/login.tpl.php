<div id="main">
  <div id="login-container">
    <div class="top-mask"></div>
    <div class="left-zone pull-left"></div>
    <div class="right-zone">
      <div class="text"><?php print t(@ESPACE_DEDIE); ?></div>
    </div>
    <div class="bar">
      <form name="LoginForm" method="post" action="/login" id="LoginForm">
        <div class="form">
          <div class="account-container pull-left">
            <span class="v-aligner"></span><span class="arrow"></span>
            <?php print render($login_form['username']); ?>
          </div>
          <div class="password-container pull-left">
            <span class="v-aligner"></span><span class="arrow"></span>
            <?php print render($login_form['password']); ?>
          </div>
          <div class="btn-container pull-left">
              <span class="v-aligner"></span>
              <?php print render($login_form['submit']); ?>

          </div>
          <?php print render($login_form); ?>
        </div>
      </form>
    </div>
  </div>

  <div id="links-blocks" class="clearfix">
    <div class="link-block create-block">
      <div class="title"><?php print t(@TEXTE_BOUTON_1); ?></div>
              <a id="lCrea" class="link orange" href="/nouvelle/entreprise"><?php print t(@TEXTE_BOUTON_LIEN_1); ?></a>
    </div>
    <div class="link-block forgot-block">
      <div class="title"><?php print t(@TEXTE_BOUTON_2); ?></div>
      <a href="javascript:void(0);" id="forgot-password-link" class="link orange"><?php print t(@TEXTE_BOUTON_LIEN_2); ?></a>
    </div>
    <div class="link-block">
      <div class="title"><?php print t(@TEXTE_BOUTON_3); ?></div>
      <a href="javascript:void(0);" id="follow-create-account-link" class="link orange"><?php print t(@TEXTE_BOUTON_LIEN_3); ?></a>
    </div>
  </div>

  <?php
    $errors = drupal_get_messages();
    if (isset($errors['error'])):
      print '<div class="errorlogin">';
      foreach ($errors['error'] as $err):
        print '<div class="">'.$err.'</div>';
      endforeach;
      print '</div>';
    endif;
  ?>
</div>

<div id="test" class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title">Modal title</h4>
      </div>
      <div class="modal-body">
        <p>One fine body&hellip;</p>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        <button type="button" class="btn btn-primary">Save changes</button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->

<div id="forgot-password" class="modal" tabindex="-1" role="dialog" aria-labelledby="forgot-passwordLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
          <h4 class="modal-title"><?php print t(@MODAL_FORGOT_PWD_TITRE); ?></h4>
        </div>
        <form name="LoginForgotPasswordForm" method="post" action="/login" id="LoginForgotPasswordForm">
        <div class="modal-body">
          <p>
          <?php print t(@MODAL_FORGOT_PWD_CONTENT); ?>
          <?php print render($login_password_forgot_form['email']); ?>
          </p>
        </div>
        <div class="modal-footer">
          <?php print render($login_password_forgot_form['submit']); ?>
        </div>
        <?php print render($login_password_forgot_form); ?>
        </form>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->

<div id="follow-create-account" class="modal" tabindex="-1" role="dialog" aria-labelledby="follow-create-accountLabel"
    aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content content">
      <form name="FollowLoginForm" method="post" action="/login" id="FollowLoginForm">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
          <h4 class="modal-title"><?php print t(@MODAL_FOLLOW_LOGIN_TITRE); ?></h4>
        </div>
        <div class="modal-body">
          <p>
          <?php print t(@MODAL_FOLLOW_LOGIN_CONTENT); ?>
          <?php print render($login_follow_form['numero_demande']); ?>
          <?php print render($login_follow_form['email']); ?>
          </p>
        </div>
        <div class="modal-footer">
          <?php print render($login_follow_form['submit']); ?>
        </div>
        <?php print render($login_follow_form); ?>
      </form>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->