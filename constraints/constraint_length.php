<?php
include_once "constraint_character.php";

class Length_Constraint extends Character_Constraint {
	
	function validate($plaintext_password, $user = NULL) {
		$len = strlen($plaintext_password);
		return $len >= $this->minimumConstraintValue;
	}
	
	function getDescription() {
		return t("Password must be longer than the specified minimum length.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must be a minimum of %numChars %characters in length.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%characters' => format_plural($this->minimumConstraintValue, t('character'), t('characters'))));
	}
	
}
?>