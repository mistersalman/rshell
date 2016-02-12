**rshell:**

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

**Bugs:**


1) cd is not working. This is not really a bug, but rather a flaw in execvp.


2) We are experiencing memory leaks, although they are less than sixty-four
bits, which is less than the value of an integer, so we will not need to
worry about it.


3) When running test scripts, the terminal complain that the commands mkdir and
rm -r and rm -rf are outdated. While we cannot find any evidence of that, the
terminal nonetheless returns warnings.
