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
function password_policy_constraint_lowercase_description() {
  return array('name' => t('Lowercase'), 'description' => t('Password must contain the specified minimum number of lowercase letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_lowercase_error($constraint) {
  return t('Password must contain a minimum of %number lowercase '. format_plural($constraint, t('character'), t('characters')) .'.', array('%number' => $constraint));
}

/**
 * Password validation.
 */
function password_policy_constraint_lowercase_validate($password, $constraint, $uid) {
  $length = strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_lower($password[$i])) { $num++; }
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_lowercase_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() != chr.toLowerCase()) {\n";
  $s .= "      if(chr == chr.toLowerCase()) {\n";
  $s .= "        num++;\n";
  $s .= "      }\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_lowercase);\n";
  $s .= "  }\n";
  return $s;
}

