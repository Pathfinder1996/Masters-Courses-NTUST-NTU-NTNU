#include <stdlib.h>
#include <sys/signal.h>
#include <fcntl.h>
#include <unistd.h>

int times_up();
int control_up();

int main() {
	signal(SIGALRM, times_up);
	signal(SIGINT, control_up);

	alarm(10);

	for (;;) {
	}
		
	return 0;
}

int times_up(sig) 
int sig; {
	pid_t i = fork();
	
	if (i == 0) {
		execlp("uptime", "uptime", (char *)NULL);
		exit(sig);
	}
	
	i = fork();
	if (i == 0) {
		execlp("who", "who", (char *)NULL);
		exit(sig);
	}
	
	alarm(10);
	 
}

int control_up(sig)
int sig; {	
	pid_t i = fork();
	
	if (i == 0) {
		execlp("uptime", "uptime", (char *)NULL);		
	}
	
	i = fork();
	if (i == 0) {
		execlp("who", "who", (char *)NULL);
	}
}
