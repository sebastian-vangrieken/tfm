#include "utils.h"
#include "variables.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

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
    struct winsize ws;
    struct Point cursorState = {0, 0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0) {
        perror("ioctl");
        exit(1);
    }

    if (argc == 1) {
        SetFileDescriptor(&fd, "/");
    } else {
        SetFileDescriptor(&fd, argv[1]);
    }

    if ((nread = syscall(SYS_getdents, fd, buf, BUF_SIZE)) < 0) {
        perror("getdents");
        exit(1);
    }

    DrawBorder(&cursorState, ws.ws_row, ws.ws_col);
    while (1) {
        // char input;
        // scanf("%c", &input);
        //
        // switch (input) {
        // case ':':
        //     SetCursorPosition(&cursorState, ws.ws_row - 1, 2);
        //     break;
        // case 'h':
        //     break;
        // case 'j':
        //     break;
        // case 'k':
        //     break;
        // case 'l':
        //     break;
        // default:
        //     break;
        // }

        int i = 3, j = 3;
        SetCursorPosition(&cursorState, i, j);
        while (pos < nread) {
            // Set the point _dirent to the address (buf+pos), and let it be
            // recognized as a pointer to a linux_dirent struct
            _dirent = (struct linux_dirent *)(buf + pos);
            printf("%s", _dirent->d_name);
            pos += _dirent->d_reclen;
            i += 1;
            SetCursorPosition(&cursorState, i, j);
        }
    }

    close(fd);
    return 0;
}
