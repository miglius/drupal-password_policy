<?php
// $Id$

/**
 * @file
 * Admin page callback file for the password_policy module.
 */

//////////////////////////////////////////////////////////////////////////////
// Password policy admin settings

/**
 * Settings form display.
 */
function password_policy_admin_settings() {
  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['expiration']['password_policy_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin (UID=1) password expires.'),
    '#default_value' => PASSWORD_POLICY_ADMIN,
    '#description' => t('Admin account password will obey expiration policy.'),
  );
  $form['expiration']['password_policy_begin'] = array(
    '#type' => 'radios',
    '#title' => t('Beginning of password expirations'),
    '#default_value' => PASSWORD_POLICY_BEGIN,
    '#options' => array('0' => t('After expiration time from setting a default policy (all passwords are valid during the expiration time from setting the default policy, and after that older than expiration time passwords expire).'), '1' => t('Setting a default policy (passwords older than expiration time expire after setting the default policy, retroactive behaviour).')),
  );
  $form['expiration']['password_policy_block'] = array(
    '#type' => 'radios',
    '#title' => t('Blocking expired accounts'),
    '#default_value' => PASSWORD_POLICY_BLOCK,
    '#options' => array('0' => t('Expired accounts are blocked. Only administrators can unblock them.'), '1' => t('The user with expired account is not blocked, but sent to a change password page. If the password is not changed, the account is blocked and the user cannot login again.')),
  );

  // Visibility
  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['visibility']['password_policy_show_restrictions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show restrictions on password change page.'),
    '#default_value' => PASSWORD_POLICY_SHOW_RESTRICTIONS,
    '#description' => t('Should password restrictions be listed on the password change page. A javascript warning block will be shown anyways if ithe typed in password does not meet the restrictions.'),
  );

  // E-mail notification settings.
  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail notification settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
  );
  $form['email']['password_policy_warning_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_subject'),
    '#maxlength' => 180,
    '#description' => t('Customize the subject of the warning e-mail message, which is sent to remind of password expiration.') .' '. t('Available variables are:') .' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );
  $form['email']['password_policy_warning_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_body'),
    '#rows' => 15,
    '#description' => t('Customize the body of the warning e-mail message, which is sent to remind of password expiration.') .' '. t('Available variables are:') .' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );

  return $form;
}

/**
 * Submit hook for the settings form.
 */
function password_policy_admin_settings_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case t('Save configuration'):
      variable_set('password_policy_admin', $form_state['values']['password_policy_admin']);
      variable_set('password_policy_begin', $form_state['values']['password_policy_begin']);
      variable_set('password_policy_block', $form_state['values']['password_policy_block']);
      variable_set('password_policy_show_restrictions', $form_state['values']['password_policy_show_restrictions']);
      variable_set('password_policy_warning_subject', $form_state['values']['password_policy_warning_subject']);
      variable_set('password_policy_warning_body', $form_state['values']['password_policy_warning_body']);
      drupal_set_message(t('The configuration options have been saved.'));
      break;
    case t('Reset to defaults'):
      variable_del('password_policy_admin');
      variable_del('password_policy_begin');
      variable_del('password_policy_block');
      variable_del('password_policy_show_restrictions');
      variable_del('password_policy_warning_subject');
      variable_del('password_policy_warning_body');
      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }
}

/**
 * The list of the password policies.
 */
function password_policy_admin_list() {
  $header = array(t('Default'), array('data' => t('Name'), 'field' => 'name', 'sort' => 'asc'), t('Enabled'), array('data' => t('Operations'), 'colspan' => 3));
  $form = array();
  $result = db_query('SELECT pid, name, enabled, description, created FROM {password_policy}'. tablesort_sql($header));
  while ($row = db_fetch_array($result)) {
    $pid = $row['pid'];
    $options[$pid] = '';
    if ($row['enabled']) {
      $default_pid = $pid;
      $form[$pid]['created'] = array('#value' => format_date($row['created'], 'medium'));
    }
    $form[$pid]['name'] = array('#value' => $row['name']);
    $form[$pid]['view'] = array('#value' => l(t('view'), 'admin/settings/password_policy/'. $pid));
    $form[$pid]['edit'] = array('#value' => l(t('edit'), 'admin/settings/password_policy/'. $pid .'/edit'));
    $form[$pid]['delete'] = array('#value' => l(t('delete'), 'admin/settings/password_policy/delete/'. $pid));
  }
  $form['default'] = array('#type' => 'radios', '#options' => $options, '#default_value' => isset($default_pid) ? $default_pid : 0);
  $form['submit'] = array('#type' => 'submit', '#value' => t('Set default policy'));
  $form['clear'] = array('#type' => 'submit', '#value' => t('Clear default policy'));
  return $form;
}

/**
 * Submit hook for the form on the default list view for the password policy module.  From the
 * default view, the user can set a new default password policy or clear the default so
 * that no policy is active and the default drupal password mechanism takes affect.
 */
function password_policy_admin_list_submit($form, &$form_state) {
  switch ($form_state['clicked_button']['#value']) {
    case "Clear default policy":
      _password_policy_admin_clear_default();
      drupal_set_message(t('No policy is active, all user passwords will be accepted (Drupal default).'));
      break;
    case "Set default policy":
      $pid = $form_state['values']['default'];
      if (is_numeric($pid)) {
        $policy = _password_policy_load_policy_by_pid($pid);
        if ($policy) {
          _password_policy_admin_clear_default();
          $time = time();
          db_query("UPDATE {password_policy} SET enabled = %d, created = %d WHERE pid = %d", 1, $time, $pid);
          drupal_set_message(t('%name has been set as the default password policy.', array('%name' => $policy['name'])));
        }
      }
      else {
        drupal_set_message(t('Default password policy was not set.'), 'warning');
      }
      break;
  }
}

/**
 * Resets the enabled flag for all policies in the database to 0.
 */
function _password_policy_admin_clear_default() {
  db_query("UPDATE {password_policy} SET enabled = %d WHERE enabled = %d", 0, 1);
}

/**
 * The default view for the password policy.
 */
function password_policy_admin_view($policy) {
  $output = check_plain($policy['description']);
  $header = array(t('Name'), t('Constraint'));
  $rows = array();
  if (!empty($policy['expiration'])) {
    $rows[] = array(t('Expiration'), $policy['expiration']);
  }
  if (!empty($policy['warning'])) {
    $rows[] = array(t('Warning'), $policy['warning']);
  }
  foreach ($policy['policy'] as $key => $val) {
    $desc = _password_policy_constraint_description($key);
    $rows[] = array($desc['name'], $val);
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 2));
  }
  $output .= theme('table', $header, $rows);

  return $output;
}

/**
 * Form display for new or to be edited password policies.
 */
function password_policy_admin_form($form_state, $policy = NULL) {
  $form['policy']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $policy['name'],
    '#maxlength' => 64,
    '#required' => TRUE,
  );
  $form['policy']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $policy['description'],
  );
  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );
  $form['expiration']['expiration'] = array('#type' => 'textfield',
    '#title' => t('Password Expiration'),
    '#default_value' => $policy['expiration'],
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The passwords will expire after this number of days. The users with expired passwords will be blocked. Leaving this field empty won\'t put any password expiration constraints.'),
  );
  $form['expiration']['warning'] = array('#type' => 'textfield',
    '#title' => t('Password Expiration Warning'),
    '#default_value' => $policy['warning'],
    '#size' => 10,
    '#description' => t('The comma separated list of days. The warning about expiration of the password will be sent out on those days before the expiration. Leaving this field empty won\'t send out or display any warnings.'),
  );

  $form['constraints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Constrains'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  global $_password_policy;
  foreach ($_password_policy as $constraint) {
    $desc = _password_policy_constraint_description($constraint);
    $form['constraints']['constraint_'. $constraint] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#default_value' => isset($policy['policy'][$constraint]) ? $policy['policy'][$constraint] : NULL,
      '#maxlength' => 2,
      '#title' => $desc['name'],
      '#description' => $desc['description'],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => is_array($policy) ? t('Save') : t('Create'),
  );

  if ($policy) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['pid'] = array(
      '#type' => 'hidden',
      '#value' => $policy['pid'],
    );
  }

  return $form;
}

/**
 * Form submission hook for new or edited password policies.
 */
function password_policy_admin_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Delete')) {
    drupal_goto('admin/settings/password_policy/delete/'. $form_state['values']['pid']);
  }

  $policy = array();
  foreach ($form_state['values'] as $key => $value) {
    // If we have no form value, then we have no constraint to set.
    $value = trim($value);
    if ($value != "" && preg_match("/^constraint_/", $key)) {
      $policy[substr($key, 11)] = $value;
    }
  }

  // If we have an pid, update, else save.
  if (isset($form_state['values']['pid'])) {
    db_query("UPDATE {password_policy} SET name = '%s', description = '%s', policy = '%s', expiration = %d, warning = '%s' WHERE pid = %d", $form_state['values']['name'], $form_state['values']['description'], serialize($policy), trim($form_state['values']['expiration']), str_replace(' ', '', $form_state['values']['warning']), $form_state['values']['pid']);
    drupal_set_message(t('Policy %name has been updated.', array('%name' => $form_state['values']['name'])));
    watchdog('password_policy', 'Policy %name updated.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/settings/password_policy/'. $form_state['values']['pid'] .'/edit'));
  }
  else {
    db_query("INSERT INTO {password_policy} (name, description, enabled, policy, expiration, warning) VALUES ('%s', '%s', %d, '%s', %d, '%s')", $form_state['values']['name'], $form_state['values']['description'], 0, serialize($policy), trim($form_state['values']['expiration']), str_replace(' ', '', $form_state['values']['warning']));
    $pid = db_last_insert_id('password_policy', 'pid');
    drupal_set_message(t('Policy %name has been created.', array('%name' =>  $form_state['values']['name'])));
    watchdog('password_policy', 'New policy %name created.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/settings/password_policy/'. $pid .'/edit'));
  }

  drupal_goto('admin/settings/password_policy/list');
}

/**
 * Confirmation form for the deletion of a password policy.  Deletion takes place
 * in password_policy_admin_delete_submit().
 */
function password_policy_admin_delete($form_state, $pid) {
  if (is_numeric($pid) && $policy = _password_policy_load_policy_by_pid($pid)) {
    $form['pid'] = array('#type' => 'hidden', '#value' => $policy['pid']);

    return confirm_form($form, t('Are you sure you want to delete the policy %name?', array('%name' => $policy['name'])), 'admin/settings/password_policy/list', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
  }
  else {
    drupal_not_found();
  }
}

/**
 * Submit hook for the delete policy operation.
 */
function password_policy_admin_delete_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $policy = _password_policy_load_policy_by_pid($pid);

  db_query("DELETE FROM {password_policy} WHERE pid = %d", $pid);
  drupal_set_message(t('Password policy %policy was deleted.', array('%policy' => $policy['name'])));
  watchdog('password_policy', 'Policy %name was deleted.', array('%name' => $policy['name']), WATCHDOG_NOTICE);
  drupal_goto('admin/settings/password_policy/list');
}

