#**rshell:**

This project, formally and informally known as rshell, is programmed in the C++
programming language and functions as a command shell.

**Introduction:**

rshell simulates a terminal, and has most of the same functionality. As of
right now, rshell is incomplete, but will be as time progresses.

**Installation Instructions:**


    git clone https://github.com/pgior001/rshell.git

    cd rshell

    git checkout hw1

    make

    bin/rshell

**Functionality:**

As of right now, rshell is capable of the following:

1) Reading in commands

2) Parsing connectors to multiple commands

3) Parsing parentheses to denote precedence

4) Executing commands

5) Running test commands to see if a file or directory exists

**Bugs:**


1) cd is not working. This is not really a bug, but rather a flaw in execvp.


2) We are experiencing memory leaks, although they are less than sixty-four
bits, which is less than the value of an integer, so we will not need to
worry about it.


3) When running test scripts, the terminal complains that the commands mkdir and
rm -r and rm -rf are outdated. While we cannot find any evidence of that, the
terminal nonetheless returns warnings.
This is from the makefile. You must also run make clean before using make 
to recompile.

4) If an ls with a flag but no space (ex, ls-a vs ls -a) is called before an or
(||) block, an error will be returned but there will be no progression in the
command. For some reason, this causes problems in the test harness, but not
when executing commands manually in ./a.out.

5) Instead of using /bin/[command], we used /bin/bash/ as the first argument of
a command. This does not cause any problems, but it is still different from the
specs we were "recommended" to follow.
