#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int opt;
	int num_children = 5;
	int simul_children = 3;
	int user_iterations = 7;

	while ((opt = getopt(argc,(char * const *)argv, "hn:s:t:"))!= -1) {
		switch(opt) {
			case 'h':
				printf("Usage: %s [-h] [-n proc] [-s simul] [-t iter]\n", argv[0]);
				exit(0);
			case 'n':
				num_children = atoi(optarg);
				break;
			case 's':
				simul_children = atoi(optarg);
				break;
			case 't':
				user_iterations = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-h] [-n proc] [-s simul] [-t iter]\n", argv[0]);
				exit(1);
		}
	}

	if (num_children <= 0 || simul_children <= 0 || user_iterations <= 0 || simul_children > num_children) {
		fprintf(stderr, "Invalid input values. Please check the arguments.\n");
		exit(1);
	}

	int children_running = 0;
	printf("OSS: Master process %d is ready to launch child processes.\n", getpid());

	for (int i = 0; i < num_children; i++) {
		if (children_running >= simul_children) {
			printf("OSS: Waiting for a child process to finish...\n");
			wait(NULL);
			children_running--;
		}

		pid_t pid = fork();
		if (pid == 0) {
			char iterations_str[32];
			sprintf(iterations_str, "%d", user_iterations);
			printf("USER: Child process %d reporting for duty! (Parent is %d)\n", getpid(), getppid());
			execl("./user", "user", iterations_str, (char *)NULL);
			perror("USER: Error: execl failed!");
			exit(1);
		} else if (pid > 0) {
			printf("OSS: Launched child process %d.\n", pid);
			children_running++;
		} else {
			perror("OSS: Error: fork failed!");
			exit(1);
		}
	}

	while (children_running > 0) {
		wait(NULL);
		children_running--;
	}

	printf("OSS: All child processes have finished.\n");
	return 0;
}

