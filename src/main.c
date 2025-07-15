#include "utils.h"
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

#define BUF_SIZE 1024
#define TOP_LEFT_CORNER "\u250C"
#define TOP_RIGHT_CORNER "\u2510"
#define BOTTOM_LEFT_CORNER "\u2514"
#define BOTTOM_RIGHT_CORNER "\u2518"
#define HORIZONTAL_LINE "\u2500"
#define VERTICAL_LINE "\u2502"
#define CLEAR "\033[2J\033[H"

// struct linux_dirent {
//     unsigned long d_ino;
//     unsigned long d_off;
//     unsigned short d_reclen;
//     char d_name[];
// };

int main() {
    // int fd, nread;
    // int pos = 0;
    // char buf[BUF_SIZE] = {0};
    // struct linux_dirent *_dirent;
    struct winsize ws;
    struct Point cursorState = {0, 0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0) {
        perror("ioctl");
        exit(1);
    }

    bool changed = true;

    while (1) {
        if (changed) {
            printf("%s", CLEAR);
            fflush(stdout);

            printf("%s", TOP_LEFT_CORNER);
            fflush(stdout);
            for (int i = 2; i < ws.ws_col; i++) {
                printf("%s", HORIZONTAL_LINE);
                fflush(stdout);
            }
            printf("%s", TOP_RIGHT_CORNER);
            fflush(stdout);

            for (int i = 2; i < ws.ws_row; i++) {
                SetCursorPosition(&cursorState, i, 1);
                printf("%s", VERTICAL_LINE);
                SetCursorPosition(&cursorState, i, ws.ws_col);
                printf("%s", VERTICAL_LINE);
                fflush(stdout);
            }
            SetCursorPosition(&cursorState, ws.ws_row, 1);

            printf("%s", BOTTOM_LEFT_CORNER);
            fflush(stdout);
            for (int i = 2; i < ws.ws_col; i++) {
                printf("%s", HORIZONTAL_LINE);
                fflush(stdout);
            }
            printf("%s", BOTTOM_RIGHT_CORNER);
            fflush(stdout);

            changed = false;
        }
    }
    // if (argc == 1) {
    //     if ((fd = open("/", O_RDONLY | O_DIRECTORY)) < 0) {
    //         perror("open");
    //         exit(1);
    //     }
    // } else {
    //     if ((fd = open(argv[1], O_RDONLY | O_DIRECTORY)) < 0) {
    //         perror("open");
    //         exit(1);
    //     }
    // }
    //
    // if ((nread = syscall(SYS_getdents, fd, buf, BUF_SIZE)) < 0) {
    //     perror("getdents");
    //     exit(1);
    // }
    //
    // while (pos < nread) {
    //     // Set the point _dirent to the address (buf+pos), and let it be
    //     // recognized as a pointer to a linux_dirent struct
    //     _dirent = (struct linux_dirent *)(buf + pos);
    //     printf("%s\n", _dirent->d_name);
    //     pos += _dirent->d_reclen;
    // }
    //
    // close(fd);
    return 0;
}
