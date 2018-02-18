#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	int i = 0;
	FILE *fp = NULL;
	char *fname = "/proc/mounts";

	//if (argc != 2)
	//	return -1;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	do {
		char line[1024];

		bzero(line, sizeof(line));
		if (fgets(line, sizeof(line), fp) == NULL)
			break;

		printf("line %02d: %s", i++, line);
	} while (!ferror(fp));

	fclose(fp);

	return 0;
}

