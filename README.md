# CS4760 Project 1 

This project demonstrates basic process management in C using 'fork()', 'exec()', and 'wait()'. It consists two programs:

**Git Repository:** https://github.com/ananquay15x9/CS4760-P1.git

'oss': The parent process that launches and manages child processes.
'user': The child process that performs a simple loop and prints information

## Compilation

To compile this program, simply run 'make' in your terminal. 
This will use the provided 'Makefile' to compile both 'oss.c' and 'user.c' and 
create the 'oss' and 'user' executables.

## Running 

To run the 'oss' program, use the following command:

''' bash./oss [-h] [-n proc] [-s simul] [-t iter]

## Problems encountered

I've encoutered several challenges:

* **Makefile errors:** There were typos and incorrect dependencies. After reviewing and correcting the Makefile, it was able to compile.
* **Compiler errors:** There were issues in both 'oss.c' and 'user'c', including issues with missing 'main()' functions, incorrect argument, and syntax errors.
* **Git errors:** Git errors related to incorrect branch names and authentication issues. These were resolved by setting up SSH keys for authentication.
* **Logic errors:** Logic error in 'oss.c' that caused all child processes to launch simultaneously, even though the '-s' option set a limit. This was resolved by replacing 'if' with 'while'.
