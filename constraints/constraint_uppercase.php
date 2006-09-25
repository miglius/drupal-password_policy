<?php
include_once "constraint_letter.php";

class Uppercase_Constraint extends Letter_Constraint {
	
	function _charIsValid($character) {
		return parent::_charIsValid($character)
		&& ctype_upper($character);
	}
	
	function getDescription() {
		return t("Password must contain the specified minimum number of uppercase letters.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars uppercase %characters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%characters' => format_plural($this->minimumConstraintValue, t('character'), t('characters'))));
	}
	
}
?>