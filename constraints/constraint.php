<?php

class Constraint {

	var $name;
	var $description;
	var $minimumConstraintValue;
	
	function Constraint($minimumConstraintValue = 0) {
		$this->name = str_replace("_", " ", ucfirst(strtolower(get_class($this))));
	  	$this->minimumConstraintValue = $minimumConstraintValue;
	}

	function validate($plaintext_password, $user = NULL) {
		return TRUE;		
	}

	function getName() {
		return $this->name;
	}
	
	function setName($name) {
		$this->name = $name;
	}
	
	function getValidationErrorMessage($plaintext_password = NULL, $user = NULL) {
		return "";
	}
		
	function getMinimumConstraintValue() {
		return $this->minimumConstraintValue;
	}
	
	function getDescription() {
		return $this->description;
	}
	
	function setDescription($description) {
		$this->description = $description;
	}
}
?>