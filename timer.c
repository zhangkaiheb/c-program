#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>


void handler(int sig)
{    
	printf("recv a sig=%d\n", sig);
}

int main(int argc, char *argv[])
{ 
	struct timeval tv_interval = {1, 0};
	struct timeval tv_value = {5, 0};
	struct itimerval it;

	if (signal(SIGALRM, handler) == SIG_ERR) {
		perror("signal error");
		exit(EXIT_FAILURE);
	}

	memset(&it, 0, sizeof(it));
	it.it_interval = tv_interval;
	it.it_value = tv_value;
	setitimer(ITIMER_REAL, &it, NULL); 

	while (1) {
		pause();
	}

	return 0;
}

