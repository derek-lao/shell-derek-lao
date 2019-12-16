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
* after running ls | wc, program seems to hit "enter" one more time or something like that

---------------------------------------------------
Extra Features (kind of):
---------------------------------------------------
* Pipes will run for multiple pipes!
* If you ask to input redirect from a nonexistent file, will return an error message very similar to an error message bash will return
  
-------------------------------------------------
Files & Function Headers:
-----------------------------------------------------------
__functions.c__ Handles all functions

*char ** parse_args(char * line)*
* Inputs:  char * line
* Returns: Array of arguments (in the form of strings) parsed from line.


*char ** cmdsep(char *** arg)*
* Inputs:  char *** arg 
* Returns: The beginning of the array of arguments pointed to by arg

* Takes in a pointer (arg) to an array of arguments (each argument a string).
* Finds the first occurence of the argument ";", replaces it with a NULL.
* Arg points to the memory one index after the NULL that was just created.

*void execute(char * argv[])*
* Inputs:  char * argv[] 
* Returns: n/a

* Checks for cd in the arguments and executes. 
* Checks for < and > to use redirection and execute (when redirectRun is called)
* Checks for | to use pipes. Executes arguments.

*void redirectRun(char *** argv)*
* Inputs: char *** argv
* Returns: n/a

* When called, will perform redirection, run, and redirect back to stdin and stdout

*void pipeRun(char *** argv);*
* Inputs: char *** argv
* Returns: n/a

* When called, will create a pipe and run, and then redirect back to stdin and stdout.
* Will run for multiple pipes!

__main.c__ The main code that keeps the shell going, takes care of "exit" code
