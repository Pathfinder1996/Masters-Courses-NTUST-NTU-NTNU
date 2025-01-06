#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	unsigned int status;
	int fd1, fd2;
	char input[100];
	scanf("%s", input);
	fd1 = open(input, O_RDONLY);
	pid_t i = fork();
	
	if (i == 0) {
		fd2 = open("result", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(0);
		dup(fd1);
		close(fd1);
		
		close(1);
		dup(fd2);
		close(fd2);

		execlp("wc", "wc", (char *)NULL);	
	}
	else {	
		close(fd1);		

		wait(&status);
		
		fd2 = open("result", O_RDONLY);
		
		char buffer[100];
		int rd1 = read(fd2, buffer, sizeof(buffer) - 1);
		buffer[rd1] = '\0';

		int num1, num2;
		sscanf(buffer, "%d %d", &num1, &num2);
		printf("%d %d\n", num1, num2);
		
		close(fd2);
	}

	return 0;
}
