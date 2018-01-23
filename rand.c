#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int j, r, nloops;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <nloops>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	nloops = atoi(argv[1]);

	srand(time(NULL));
	for (j = 0; j < nloops; j++) {
		r = rand();
		if (r < 0x10000000 || r > 0xffffffff)
			continue;
		fprintf(stdout, "%x\n", r);
	}

	exit(EXIT_SUCCESS);
}

