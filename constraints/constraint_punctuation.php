<?php
include_once "constraint_character.php";

class Punctuation_Constraint extends Character_Constraint {
	
	function _charIsValid($character) {
		return parent::_charIsValid($character)
		&& ctype_punct($character);
	}

	function getDescription() {
		return t("Password must contain the specified minimum number of punctuation characters.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars punctuation %characters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%characters' => format_plural($this->minimumConstraintValue, t('character'), t('characters'))));		
	}
	
}
?>