// Author: Tu Le
// Date: 2/9/2025
// CS4760 Project 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc!=2) {
	fprintf(stderr, "Usage: %s <number_of_iterations>\n", argv[0]); 
	exit(1); //Exit if arguments are wrong
	}

	// We'll convert the command line string to an integer
	int iterations = atoi(argv[1]);

	// Loop for iterations
	for(int i = 1; i <= iterations; i++) {
		// Print the child and the parent's ID
		printf("Greetings from child process %d! (Parent is %d)\n", getpid(), getppid());
		// Print current iteration number 
		printf("Iteration %d: Is ready to take a nap...\n", i);
		sleep(1); // Pause for 1 second
		// Waking up after 1 second
		printf("Iteration %d: Ah, I'm waking up again!\n",  i);
	}
	// The loop is done, print out goodbye message
	printf("Child process %d signing off. Peace!\n", getpid());
	return 0; // The end.
}
