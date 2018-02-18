#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    int fd;
	FILE *fp = NULL;
	struct stat st;
	char *fname;
	int size;

	if (argc != 2)
		return -1;

	fname = argv[1];

	// Method 1
	if (access(fname, F_OK) != 0) {
		perror("access");
		return -1;
	}

	if (stat(fname, &st)) {
		perror("stat");
		return -1;
	}
	printf("M1 file:(%s) size is %ld\n", fname, st.st_size);

	// Method 2
	fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	fclose(fp);

	printf("M2 file:(%s) size is %d\n", fname, size);

	// Method 3
	fd = open(fname, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	if (fstat(fd, &st) == -1) {
		perror("fstat");
		close(fd);
		return -1;
	}
	printf("M3 file:(%s) size is %ld\n", fname, st.st_size);

	close(fd);

	return 0;
}

