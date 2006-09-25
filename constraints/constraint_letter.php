<?php
include_once "constraint_character.php";

class Letter_Constraint extends Character_Constraint {
	
	function _charIsValid($character) {
		return parent::_charIsValid($character)
		&& ctype_alpha($character);
	}

	function getDescription() {
		return t("Password must contain the specified minimum number of letters.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars %letters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%letters' => format_plural($this->minimumConstraintValue, t('letter'), t('letters'))));				
		
	}
	
}
?>