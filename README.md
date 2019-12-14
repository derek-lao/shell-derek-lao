# shell-derek-lao

From commit "e034356a159ddfa4a592c59849d6e62c32b8f9c7"
There is a major bug, probably in gcc.

While including line 82 of functions.c, with lines 28-30 and lines 32-34 of main.c commented out, the program exits after any call (I tried ls).

When I add in line 28 and/or line 32 in main.c while keeping line 82 of functions.c in, I receive a segmentation fault in the program after a call.

When I add in line lines 29-30 in main.c such that I will now have lines 28-30, and 32 in main.c and line 82 in functions.c, the program will exit after one call. When I add lines 33 and 34 in main.c such that now lines 28-30 and lines 32-34 of main.c and line 82 of functions.c are active, the program runs without exiting or receiving any errors.

I did some further testing, and found that as long as I do any printing of the "commands" pointer XOR the "args" pointer, before the execute function within the while loop is called, the program will run without any visible problems.

I realize that when I use scanf(thing, "%s", thing);, for some reason, the shell does not crash. This must be a bug in the code or a bug in cygwin... wow...
