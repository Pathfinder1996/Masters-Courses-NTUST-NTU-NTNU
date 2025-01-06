#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define ERR (-1)
#define READ 0 // pipe read
#define WRITE 1 // pipe write
#define STDIN 0
#define STDOUT 1

int main(void) {
	int pid_1, pid_2, pid_3;
	int pfd_1[2], pfd_2[2];
	
	// pipe1
	if (pipe(pfd_1) == ERR) {
		perror("pfd_1 failed");
		exit(ERR);
	}

	if ((pid_1 = fork()) == ERR) {
		perror("fork1 failed");
		exit(ERR);
	}

	// 1st child: ps aux
	if (pid_1 == 0) {
		close(STDOUT);
		dup(pfd_1[WRITE]);
		close(pfd_1[READ]);
		close(pfd_1[WRITE]);
		
		execlp("ps", "ps", "aux", (char *)NULL);
		perror("1st child execlp failed");
		exit(ERR);
	}
	
	// pipe2
	if (pipe(pfd_2) == ERR) {
		perror("pfd_2 failed");
		exit(ERR);
	}

	if ((pid_2 = fork()) == ERR) {
		perror("fork2 failed");	
		exit(ERR);
	}
	
	// 2nd child grep 
	if (pid_2 == 0) {
		close(STDIN);
		dup(pfd_1[READ]);
		close(STDOUT);
		dup(pfd_2[WRITE]);
		close(pfd_1[READ]);
		close(pfd_1[WRITE]);
		close(pfd_2[READ]);
		close(pfd_2[WRITE]);
		
		execlp("grep", "grep", "M11212913", (char *)NULL);
		perror("2nd child execlp failed");
		exit(ERR);
	}
	
	if((pid_3 = fork()) == ERR) {
		perror("fork3 failed");
		exit(ERR);
	}	

	if(pid_3 == 0) {
		close(STDIN);
		dup(pfd_2[READ]);
		close(pfd_1[READ]);
		close(pfd_1[WRITE]);
		close(pfd_2[READ]);
		close(pfd_2[WRITE]);
		
		int fd1 = open("the_result", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd1 == ERR) {
			perror("open file failed");
			exit(ERR);
		}
		
		close(STDOUT);
		dup(fd1);
		close(fd1);

		execlp("wc", "wc", (char *)NULL);
		perror("3rd child execlp failed");
		exit(ERR);
	}
	
	// parent ex
	close(pfd_1[READ]);
	close(pfd_1[WRITE]);
	close(pfd_2[READ]);
	close(pfd_2[WRITE]);
	
	wait(NULL);
 	wait(NULL);
	wait(NULL);
	
	return 0;
}

