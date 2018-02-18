#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    char *addr;
    int fd;
    struct stat st;
    int ret = -1;
	char *fname;

	if (argc != 2)
		return -1;

	fname = argv[1];

    fd = open(fname, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        goto close_file;
    }

    addr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        goto close_file;
    }

	printf("CONTENT START:\n\n");
	printf("%s", addr);
	printf("\nCONTENT END\n");

    ret = 0;
    munmap(addr, st.st_size);

close_file:
    close(fd);
    return ret;
}

