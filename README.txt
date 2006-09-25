/* $Id$ */

README
==========================================
This module provides a way to specify a certain level of password
complexity for user passwords on a system.  A password policy can
be defined with a set of constraints which must be met before a 
user password change will be accepted.  

Current constraints include:
	- Digit constraint
	- Letter constraint
	- Letter/Digit constraint (Alphanumeric)
	- Length constraint
	- Uppercase constraint
	- Lowercase constraint
	- Punctuation constraint
	- History constraint

Requirements
==========================================
This module has only been tested with Drupal 4.7.3.

Installation
==========================================
See INSTALL.txt

Author
==========================================
David Ayre <dave at ayre dot com>
Sponsored by Bryght <http://www.bryght.com>