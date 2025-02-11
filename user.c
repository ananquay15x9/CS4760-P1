// Author: Tu Le
// Date: 2/9/2025
// CS4760 Lab 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc!=2) {
	fprintf(stderr, "Usage: %s <number_of_iterations>\n", argv[0]); 
	exit(1);
	}

	int iterations = atoi(argv[1]);

	for(int i = 1; i <= iterations; i++) {
		printf("Greetings from child process %d! (Parent is %d)\n", getpid(), getppid());
		printf("Iteration %d: Is ready to take a nap...\n", i);
		sleep(1);
		printf("Iteration %d: Ah, I'm waking up again!\n",  i);
	}
	printf("Child process %d signing off. Peace!\n", getpid());
	return 0;
}
