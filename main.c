#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024

struct linux_dirent {
  unsigned long d_ino;
  unsigned long d_off;
  unsigned short d_reclen;
  char d_name[];
};

int main(int argc, char **argv) {
  int fd, nread;
  int pos = 0;
  char buf[BUF_SIZE] = {0};
  struct linux_dirent *_dirent;

  if (argc == 1) {
    if ((fd = open("/", O_RDONLY | O_DIRECTORY)) < 0) {
      perror("open");
      exit(1);
    }
  } else {
    if ((fd = open(argv[1], O_RDONLY | O_DIRECTORY)) < 0) {
      perror("open");
      exit(1);
    }
  }

  if ((nread = syscall(SYS_getdents, fd, buf, BUF_SIZE)) < 0) {
    perror("getdents");
    exit(1);
  }

  while (pos < nread) {
    // Set the point _dirent to the address (buf+pos), and let it be recognized
    // as a pointer to a linux_dirent struct
    _dirent = (struct linux_dirent *)(buf + pos);
    printf("%s\n", _dirent->d_name);
    pos += _dirent->d_reclen;
  }

  close(fd);
  return 0;
}
