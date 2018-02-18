#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

static int dirsize(char *path)
{
	u_int64_t totalsize = 0;
	DIR *directory;
	struct dirent *dir_entry;
	struct stat st;
	char fname[2048] = {0};
	int sz;

	if (!(directory = opendir(path)))
		return 0;

	while ((dir_entry = readdir(directory))) {
		if (!strcmp(dir_entry->d_name,".") ||
				!strcmp(dir_entry->d_name,".."))
			continue;

		sz = 0;
		snprintf(fname, sizeof(fname)-1,"%s/%s", path, dir_entry->d_name);

		if (dir_entry->d_type == DT_REG) {
			if (stat(fname, &st) < 0) {
				continue;
			}
			sz = st.st_size;
		} 
		else if (dir_entry->d_type == DT_DIR) {
			if ((sz = dirsize(fname)) == -1) {
				printf("dirsize error for file %s\n", fname);
				continue;
			}
		}
		totalsize += sz;
	}
	closedir(directory);

	return totalsize;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
		return -1;

	printf("size: %d\n", dirsize(argv[1]));

	return 0;
}

