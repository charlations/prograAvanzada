#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int pid;
	
	if (argc != 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		return -1;
	}
	
	if ( (pid = fork()) < 0 ) {
		perror(argv[0]);
		return -1;
	} else if (pid == 0) { // CHILD
		sleep(2);
		printf("CHILD PID = %i PPID = %i\n", getpid(), getppid());
		exit(0);	
	} else if (pid > 0) { // PARENT
		printf("PARENT PID = %i PPID = %i\n", getpid(), getppid());
		wait(NULL);
	}
	return 0;
}
