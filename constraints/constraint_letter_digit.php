<?php
include_once "constraint_character.php";

class Letter_Digit_Constraint extends Character_Constraint {
	
	function _charIsValid($character) {
		return parent::_charIsValid($character)
		&& ctype_alnum($character);
	}
	
	function getDescription() {
		return t("Password must contain the specified minimum number of letters OR numbers.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars %numbers_or_letters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%numbers_or_letters' => format_plural($this->minimumConstraintValue, t('number or letter'), t('numbers or letters'))));				
	}

}
?>