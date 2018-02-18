#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


static int copyfile(const char *src_name, const char *tar_name)
{
	char buffer[4096] = {0};
	int read = 0;
	FILE *src_file, *tar_file;

	if (!src_name || !tar_name)
		return -1;

	src_file = fopen(src_name, "rb");
	if (src_file == NULL) {
		printf("failed to open %s for reading\n", src_name);
		return -1;
	}

	tar_file = fopen(tar_name, "wb");
	if (tar_file == NULL) {
		printf("failed to open %s for writing\n", tar_name);
		return -1;
	}

	while (!feof(src_file)) {
		read = fread(buffer, 1, 4096, src_file);
		fwrite(buffer, 1, read, tar_file);
	}
	fclose(src_file);
	fclose(tar_file);

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		return -1;

	copyfile(argv[1], argv[2]);

	return 0;
}
	
