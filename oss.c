// Author: Tu Le
// Date: 2/10/2025
// CS4760 Lab 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int opt;
	int num_children = 5;
	int simul_children = 3;
	int user_iterations = 7;
	
	// Switch statement options aka parse command options
	while ((opt = getopt(argc,(char * const *)argv, "hn:s:t:"))!= -1) {
		switch(opt) {
			case 'h': //Help option
				printf("Usage: %s [-h] [-n proc] [-s simul] [-t iter]\n", argv[0]);
				exit(0);
			case 'n': // Number of child processes
				num_children = atoi(optarg);
				break;
			case 's': // Number of simultaneous child allowed
				simul_children = atoi(optarg);
				break;
			case 't': // Number of iterations for each child
				user_iterations = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-h] [-n proc] [-s simul] [-t iter]\n", argv[0]);
				exit(1);
		}
	}
	// Check input if not within the range
	if (num_children <= 0 || simul_children <= 0 || user_iterations <= 0 || simul_children > num_children) {
		fprintf(stderr, "Invalid input values. Please check the arguments.\n");
		exit(1);
	}

	int children_running = 0;
	printf("OSS: Master process %d is ready to launch child processes.\n", getpid());
	
	//Loop to create child processes
	for (int i = 0; i < num_children; i++) {
		while (children_running >= simul_children) {
			printf("OSS: Waiting for a child process to finish...\n");
			wait(NULL); // to wait for the child to finish
			children_running--;
		}

		// Fork a new child process
		pid_t pid = fork();
		if (pid == 0) { // Child process
			char iterations_str[32];
			sprintf(iterations_str, "%d", user_iterations);
			printf("USER: Child process %d reporting for duty! (Parent is %d)\n", getpid(), getppid());
			execl("./user", "user", iterations_str, (char *)NULL);
			perror("USER: Error: execl failed!"); // If excel fails, print an error
			exit(1); // Exit with error code
		} else if (pid > 0) { // Parent process
			printf("OSS: Launched child process %d.\n", pid);
			children_running++;
		} else { // Fork failed
			perror("OSS: Error: fork failed!");
			exit(1); // Exit with an error code
		}
	}
	// Wait until all children is finished
	while (children_running > 0) {
		wait(NULL);
		children_running--;
	}

	printf("OSS: All child processes have finished.\n");
	return 0;
}

