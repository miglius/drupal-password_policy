<?php
// $Id$
/**
 * @file
 * Password policy constraint callbacks.
 */

//////////////////////////////////////////////////////////////////////////////
// Constraint API

/**
 * Description of the constraint.
 */
function password_policy_constraint_digit_description() {
  return array('name' => t('Digit'), 'description' => t('Password must contain the specified minimum number of digits.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_digit_error($constraint) {
  return t('Password must contain a minimum of %number '. format_plural($constraint, t('digit'), t('digits')) .'.', array('%number' => $constraint));
}

/**
 * Password validation.
 */
function password_policy_constraint_digit_validate($password, $constraint, $uid) {
  $length = strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_digit($password[$i])) { $num++; }
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_digit_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(\"1234567890\".indexOf(chr) != -1) {\n";
  $s .= "      num++;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_digit);\n";
  $s .= "  }\n";
  return $s;
}
