<?php

include_once "constraint.php";

class Character_Types_Constraint extends Constraint {
	

	function validate($plaintext_password, $user = NULL) {
		$len = strlen($plaintext_password);
		$numTypes = 0;

		$hasUpper = 0;
		$hasLower = 0;
		$hasDigit = 0;
		$hasPunct = 0;
		
		for ($i = 0; $i < $len; $i++) {
			
			if (ctype_upper($plaintext_password[$i])) {
				$hasUpper = 1;
			} 
			else if (ctype_lower($plaintext_password[$i])) {
				$hasLower = 1;
			}
			else if (ctype_digit($plaintext_password[$i])) {
				$hasDigit = 1;
			}
			else if (ctype_punct($plaintext_password[$i])) {
				$hasPunct = 1;
			}
			
			$numTypes = $hasUpper + $hasLower + $hasDigit + $hasPunct;	
		}
		
		return $numTypes >= $this->minimumConstraintValue;
	}
	
	function getDescription() {
		return t("Password must contain the specified minimum number of character types.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must contain a minimum of %numChars different %types of characters.", 
		array('%numChars' => $this->minimumConstraintValue, 
			  '%types' => format_plural($this->minimumConstraintValue, t('type'), t('types'))));		
	}
	
}
?>
