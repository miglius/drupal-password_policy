<?php

include_once "constraint.php";

class Character_Constraint extends Constraint {
	

	function validate($plaintext_password, $user = NULL) {
		$len = strlen($plaintext_password);
		$numValid = 0;
		for ($i = 0; $i < $len; $i++) {
			$numValid = $this->_charIsValid($plaintext_password[$i]) ? $numValid + 1 : $numValid;	
		}
		
		return $numValid >= $this->minimumConstraintValue;
	}
	
	function getDescription() {
		return t("Password must contain the specified minimum number of characters.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars %characters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%characters' => format_plural($this->minimumConstraintValue, t('character'), t('characters'))));		
	}
	
	function _charIsValid($character) {
		return TRUE;
	}

}
?>