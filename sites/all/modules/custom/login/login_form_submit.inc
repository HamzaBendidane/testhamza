<?php

/**
 * check_login
 *
 * Fonction qui permet de connecter l'utilisateur
 *
 * Si l'utilisateur existe dans la BDD Drupal users alors on récupère les infos extranet (login_db_get_extranet_user)
 * Sinon on regarde s'il existe dans la BDD Référentiel compte_adefims (login_db_get_referentiel_user)
 */
function check_login() {
  global $user;
  $username = $_POST['username'];
  $password = $_POST['password'];

  $extranet_user = array();

  // Si on es en post et que l'utilisateur a rempli les champs username et password
  if (!empty($username) && !empty($password)) {
    // Si l'utilisateur existe dans la table user de la BDD opcaim_drupal
    $account = user_load_by_name($username);
    if ($account && $account->status != 0) {
      // on vérifie que les identifiants sont bons
      $uid = user_authenticate($username, $password);
      if ($uid) {
        // on loggue l'utilisateur
        $form_state['uid'] = $uid;
        user_login_submit(array(), $form_state);
        // Récupérer les infos de la table extranet drupal user s'il n'est pas "administrator"
        if (!user_has_role(3)) {
          $extranet_user = login_db_get_extranet_user($uid);
          if ($extranet_user) {
            user_save($account, array('extranet_user' => $extranet_user));
          }
        }
        // On redirige l'utilisateur vers son dashboard
        drupal_goto('/dashboard');
      } else {
        // On va voir si l'utilisateur est dans la table authmap et password OK (external login pour OPCAIM/ADEFIM)
        $user_adefims = login_db_get_drupal_user_authmap($username, $password);
        if ($user_adefims) {
          $user = user_load_by_name($username);

          // on loggue l'utilisateur
          $form_state['uid'] = $user->uid;
          user_login_submit(array(), $form_state);

          // on récupère les infos ADEFIMS dans $extranet_user
          $extranet_user['user_adefim'] = $user_adefims;
          $extranet_user['entreprises'] = login_db_get_adefims_entreprise(trim($user_adefims->id_adefim));
          user_save($account, array('extranet_user' => $extranet_user));

          drupal_goto('/dashboard');
        } else {
          // mot de passe pas bon
          drupal_set_message(@ERROR_CHECK_LOGIN_2, 'error');
        }
      }
    } else {
      // l'utilisateur n'existe pas dans la table user de la BDD opcaim_drupal
      // si l'utilisateur existe dans la table comptes_adefims de la BDD opcaim_referentiel_esclave
      $user_adefims = login_db_get_referentiel_comptes_adefims($username, $password);
      if ($user_adefims) {
        $account = user_external_load($username);
        if (!$account) {
          // Register this new user.
          $user_info = array(
              'name' => $username,
              'pass' => user_password(),
              'init' => $username,
              'mail' => $user_adefims->email,
              'status' => 1,
              'access' => REQUEST_TIME,
              'roles' => array('10' => 'GESTIONNAIRE ADEFIM'),
              'extranet_user' => array(
                  'user_adefim' => $user_adefims,
                  'entreprises' => login_db_get_adefims_entreprise(trim($user_adefims->id_adefim)),
              )
          );
          $account = user_save(drupal_anonymous_user(), $user_info);
          // Terminate if an error occurred during user_save().
          if (!$account) {
            drupal_set_message(t("Error saving user account."), 'error');
            return;
          }
          user_set_authmaps($account, array("authname_adefim" => $username));
        }

        // Log user in.
        $form_state['uid'] = $account->uid;
        user_login_submit(array(), $form_state);

        // On redirige l'utilisateur vers son dashboard
        drupal_goto('/dashboard');
      } else {
        // Utilisateur non trouvé, on affiche un message d'erreur
        drupal_set_message(@ERROR_CHECK_LOGIN_1, 'error');
      }
    }
  } else {
    // Sinon on affiche les messages d'erreurs
    if (empty($username)) {
      // identifiant vide
      drupal_set_message(@ERROR_CHECK_LOGIN_REQUIRE_COMPTE, 'error');
    }
    if (empty($password)) {
      // password vide
      drupal_set_message(@ERROR_CHECK_LOGIN_REQUIRE_PASSWORD, 'error');
    }
  }
}


function password_forgot() {
  $email = $_POST['email'];
  // Si le champ email est vide, on affiche un message d'erreur
  if (empty($email)) {
    drupal_set_message(@ERROR_FORGOT_PWD_MAIL_EMPTY, 'error');
  } else {
    $user = user_load_by_mail($email);
    if (false !== $user) {
      // envoi du mail
      _user_mail_notify('password_reset', $user);
      drupal_set_message(@FORGOT_PWD_VALID, 'status');
    }  else {
      // Si l'email n'est pas connu dans le système, on affiche un message d'erreur
      drupal_set_message(@ERROR_FORGOT_PWD_MAIL_KO, $type = 'error');
    }
  }
}


function follow_login() {
  $numero_demande = $_POST['numero_demande'];
  $email = $_POST['email'];

  if (!empty($numero_demande) && !empty($email)) {
    // TODO : check statut de la demande

  } else {
    if (empty($numero_demande)) {
      drupal_set_message(@ERROR_FOLLOW_LOGIN_NUMERO_EMPTY, 'error');
    }
    if (empty($email)) {
      drupal_set_message(@ERROR_FOLLOW_LOGIN_EMAIL_EMPTY, 'error');
    }
  }
}