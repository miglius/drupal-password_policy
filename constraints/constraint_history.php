<?php

include_once "constraint.php";

class History_Constraint extends Constraint {
	

	function validate($plaintext_password, $user = NULL) {
		
		if (!$this->minimumConstraintValue) return 1;
		
		if (!empty($user) && !empty($user->uid)) {
			
			// note that we specify a limit of the window size, but may not get that if the history isn't there.
			$result = db_query("SELECT * FROM {password_policy_users} WHERE uid = %d ORDER BY created DESC LIMIT %d", $user->uid, $this->minimumConstraintValue);
			$recordedHistorySize = db_num_rows($result);
			
			// if we don't have the history required to match the constraint history size, then reduce the history size to 
			// match the available history.  This allows the constraint to work minimally until enough history has been
			// gathered to operate fully.  
			$testSize = min($this->minimumConstraintValue, $recordedHistorySize);
			
			$count = 0;
			$passwordToCompare = md5($plaintext_password);
			$failed = FALSE;
			while ($values = db_fetch_array($result)) {
				// if we found one password which matches, then we've failed
				if ($values['pass'] == $passwordToCompare) {
			    	$failed = TRUE;
			    }
			} 
			return !$failed;
		}
		return TRUE;
	}
	
	function getDescription() {
		return t("Password must not match any of the user's previous X passwords.") . '<br/>' .
		       '<b>' . t('Note: ') . '</b>' . t("This constraint can only compare a new password with the previous passwords recorded since the password policy module was enabled.  For ") .
		       t("example, if the number of previous passwords is set to 3, the module may have only recorded 2 password changes since the ") .
		       t("module was enabled.  If the recorded password history is not large enough to support the constraint history size, the history size for ") .
		       t("the constraint will be reduced (temporarily during the constraint check) to match the available recorded history.  ") .
		       t("Also note that a history size of 1 means that the user is unable to change their password to their current password.  This ") .
		       t("can be useful in certain situations, but a setting of 2+ will likely be more useful.");
	}
	
	function getValidationErrorMessage() {
		return t("Password must not match %stmt.", 
		array('%windowSize' => $this->minimumConstraintValue, 
			  '%stmt' => format_plural($this->minimumConstraintValue, t('the last password used'), t('any of the previous %windowSize passwords', array('%windowSize' => $this->minimumConstraintValue))),
			  '%password' => format_plural($this->minimumConstraintValue, t('password'), t('passwords'))));		
	}

}
?>