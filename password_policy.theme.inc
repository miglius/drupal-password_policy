<?php
// $Id$
/**
 * @file
 * Theme callback file for the password_policy module.
 */

//////////////////////////////////////////////////////////////////////////////
// Password policy admin themes

/**
 * Custom theme for rendering a radio list of defined policies.
 * This layout is based on a similar layout found in the "filter" module.
 *
 * @ingroup themeable
 */
function theme_password_policy_admin_list($form) {
  $rows = array();
  foreach ($form as $name => $element) {
    if (isset($element['edit']) && is_array($element['edit'])) {
      $rows[] = array(
        drupal_render($form['default'][$element['pid']['#value']]),
        check_plain($name),
        drupal_render($form[$name]['created']),
        drupal_render($form[$name]['view']),
        drupal_render($form[$name]['edit']),
        drupal_render($form[$name]['delete'])
      );
      unset($form[$name]);
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 5));
    unset($form['submit']);
    unset($form['clear']);
  }
  $header = array(t('Default'), array('data' => t('Name'), 'field' => 'name', 'sort' => 'asc'), t('Enabled'), array('data' => t('Operations'), 'colspan' => 3));
  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

