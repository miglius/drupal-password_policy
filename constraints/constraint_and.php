<?php
include_once "constraint.php";

class And_Constraint extends Constraint {
	
	var $constraints;
	
	function And_Constraint() {
		$this->constraints = array();
	}

	function validate($plaintext_password, $user = NULL) {
		foreach ($this->constraints as $constraint) {
			if (!$constraint->validate($plaintext_password, $user)) {
				return 0;	
			}
		}
		return 1;
	}
	
	function getDescription() {
		return $this->getValidationErrorMessage();
	}
	
	function getValidationErrorMessage($plaintext_password = NULL, $user = NULL) {
		$reason = "<ul>";
		
		foreach ($this->constraints as $constraint) {
			$msg = NULL;
			
			// if we have a password to test, then indicate in the validation error
			// message, which constraints passed and which failed.
			if (isset($plaintext_password)) {
				if ($constraint->validate($plaintext_password, $user)) {
					$msg = t("(PASS)") . " " . $constraint->getValidationErrorMessage();
				}
				else {
					$msg = t("(FAIL)") . " " . $constraint->getValidationErrorMessage();
				}
			}
			// else just display the constraint regardless of passing or failing
			else {
				$msg = $constraint->getValidationErrorMessage();
			}
			$reason .= "<li>$msg</li>";
		}
		return $reason . "</ul>";
	}
	
	function addConstraint($constraint) {
		array_push($this->constraints, $constraint);
	}

	function getConstraints() {
		return $this->constraints;
	}
}
?>