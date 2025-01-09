#include <unistd.h>
#include <fcntl.h>

int main() {
	
	int fd1, fd2;
	fd1 = open("foo.bar", O_RDONLY);
	close(0);
	dup(fd1);
	close(fd1);

	fd2 = open("result", O_WRONLY | O_CREAT);
	close(1);
	dup(fd2);
	close(fd2);

	execlp("wc", "wc", (char *)NULL);	

	return 0;
}

