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
function password_policy_constraint_uppercase_description() {
  return array('name' => t('Uppercase'), 'description' => t('Password must contain the specified minimum number of uppercase letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_uppercase_error($constraint) {
  return t('Password must contain a minimum of %number uppercase '. format_plural($constraint, t('character'), t('characters')) .'.', array('%number' => $constraint));
}

/**
 * Password validation.
 */
function password_policy_constraint_uppercase_validate($password, $constraint, $uid) {
  $length = strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_upper($password[$i])) { $num++; }
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_uppercase_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() != chr.toLowerCase()) {\n";
  $s .= "      if(chr == chr.toUpperCase()) {\n";
  $s .= "        num++;\n";
  $s .= "      }\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_uppercase);\n";
  $s .= "  }\n";
  return $s;
}
