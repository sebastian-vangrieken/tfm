#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

void printFileData(struct stat);

int main(int argc, char**argv) {
	int fd;
	struct stat statbuf;

	if (argc == 1) {
		fd = open("/", O_RDONLY);
		if (fstat(fd, &statbuf) < 0) {
			perror("Failed to get info:");
			exit(1);
		}
	} else {
		if ((fd = open(argv[1], O_RDONLY)) < 0) {
			perror("Failed to open:");
			exit(1);
		}
		if (fstat(fd, &statbuf) < 0) {
			perror("Failed to get info:");
			exit(1);
		}
	}

	printFileData(statbuf);

	return 0;
}

void printFileData(struct stat statbuf) {
	printf("Inode number: %ld\n", statbuf.st_ino);
	switch (statbuf.st_mode & S_IFMT) {
		case S_IFSOCK:
			printf("File type: %s\n", "socket");
			break;
		case S_IFLNK:
			printf("File type: %s\n", "symbolic link");
			break;
		case S_IFREG:
			printf("File type: %s\n", "regular file");
			break;
		case S_IFBLK:
			printf("File type: %s\n", "block device");
			break;
		case S_IFDIR:
			printf("File type: %s\n", "directory");
			break;
		case S_IFCHR:
			printf("File type: %s\n", "character device");
			break;
		case S_IFIFO:
			printf("File type: %s\n", "FIFO");
			break;
	}
	printf("Total size(bytes): %ld\n", statbuf.st_size);
}
