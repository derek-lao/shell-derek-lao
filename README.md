# shell-derek-lao

Features:
----------------------------------------
* Forks and executes commands
* Parses multiple commands on one line
* Redirects using >, <
----------------------------------------
Attempted:
---------------------------------------------
* The following did not end up working, but have been left in the code, commented out:
------------------------------------------------

Bugs:
---------------------------------------------
* Does not work for multiple semi colons
* Does not work when semicolons are not separated by a space from their arguments
* Pipes does not work yet
* cd without any following arguments does not work
  
-------------------------------------------------
Files & Function Headers:
-----------------------------------------------------------
__functions.c__ Handles all functions

*char ** parse_args()*
* Inputs:  char *line
* Returns: Array of arguments (in the form of strings) parsed from line.


*char ** cmdsep()*
* Inputs:  char *** arg 
* Returns: The beginning of the array of arguments pointed to by arg

* Takes in a pointer (arg) to an array of arguments (each argument a string).
* Finds the first occurence of the argument ";", replaces it with a NULL.
* Arg points to the memory one index after the NULL that was just created.

*void execute()*
* Inputs:  char * argv[] 
* Returns: n/a
*
* Checks for cd in the arguments and executes. Checks for < and > to use redirection.
* Checks for | to use pipes. Executes arguments.

__main.c__ The main code that keeps the shell going, takes care of "exit" code
