/* $Id$ */

README
==========================================
This module provides a way to specify a certain level of password 
complexity (aka. "password hardening") for user passwords on a 
system by defining a password policy.

A password policy can be defined with a set of constraints which 
must be met before a user password change will be accepted. Each 
constraint has a parameter allowing for the minimum number of valid 
conditions which must be met before the constraint is satisfied.

Example: an uppercase constraint (with a parameter of 2) and a 
digit constraint (with a parameter of 4) means that a user password 
must have at least 2 uppercase letters and at least 4 digits for it 
to be accepted.

Current constraints include:

    * Digit constraint
    * Letter constraint
    * Letter/Digit constraint (Alphanumeric)
    * Length constraint
    * Uppercase constraint
    * Lowercase constraint
    * Punctuation constraint
    * Character types constraint (allows the adminstrator to set the minimum 
      number of character types required, but without actually dictating which 
      ones must be used.  Example - Windows requires any 3 (user's choice) of 
      uppercase, lowercase, numbers, or punctuation.
    * History constraint (checks hashed password against a 
      collection of users previous hashed passwords looking for 
      recent duplicates)

The development of this module was sponsored by Bryght 
(http://www.bryght.com)


Requirements
==========================================
This module has only been tested with Drupal 4.7.3.

Installation
==========================================
See INSTALL.txt

Author
==========================================
David Ayre <drupal at ayre dot ca>
Sponsored by Bryght <http://www.bryght.com>