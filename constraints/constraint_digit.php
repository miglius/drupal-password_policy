<?php
include_once "constraint_character.php";

class Digit_Constraint extends Character_Constraint {
	
	function _charIsValid($character) {
		return parent::_charIsValid($character)
		&& ctype_digit($character);
	}
	
	function getDescription() {
		return t("Password must contain the specified minimum number of digits.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars %digits.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%digits' => format_plural($this->minimumConstraintValue, t('digit'), t('digits'))));		
	}

}
?>