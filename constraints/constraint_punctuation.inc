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
function password_policy_constraint_punctuation_description() {
  return array('name' => t('Punctuation'), 'description' => t('Password must contain the specified minimum number of punctuation (not whitespace or an alphanumeric) characters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_punctuation_error($constraint) {
  return t('Password must contain a minimum of %number punctuation (not whitespace or an alphanumeric) '. format_plural($constraint, t('characters'), t('characters')) .'.', array('%number' => $constraint));
}

/**
 * Password validation.
 */
function password_policy_constraint_punctuation_validate($password, $constraint, $uid) {
  $length = strlen($password);
  $num = 0;
  for ($i = 0; $i < $length; $i++) {
    if (ctype_punct($password[$i])) { $num++; }
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_punctuation_js($constraint, $uid) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() == chr.toLowerCase() && \"1234567890\".indexOf(chr) == -1 && chr != ' ') {\n";
  $s .= "      num++;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_punctuation);\n";
  $s .= "  }\n";
  return $s;
}

