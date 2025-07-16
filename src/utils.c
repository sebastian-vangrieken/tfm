#include "utils.h"
#include "variables.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void SetFileDescriptor(int *fd, char *filePath) {
    if ((*fd = open(filePath, O_RDONLY | O_DIRECTORY)) < 0) {
        perror("open");
        exit(1);
    }
}

void SetCursorPosition(struct Point *cursorState, int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
    cursorState->row = row;
    cursorState->col = col;
}

void DrawBorder(struct Point *cursorState, int row, int col) {
    printf("%s", CLEAR);
    fflush(stdout);

    // Top row
    printf("%s", TOP_LEFT_CORNER);
    fflush(stdout);
    for (int i = 2; i < col; i++) {
        printf("%s", HORIZONTAL_LINE);
        fflush(stdout);
    }
    printf("%s", TOP_RIGHT_CORNER);
    fflush(stdout);

    // Left & right sides
    for (int i = 2; i < row - 2; i++) {
        SetCursorPosition(cursorState, i, 1);
        printf("%s", VERTICAL_LINE);
        SetCursorPosition(cursorState, i, col);
        printf("%s", VERTICAL_LINE);
        fflush(stdout);
    }
    SetCursorPosition(cursorState, row - 2, 1);

    // Top row of cmd line
    printf("%s", VERTICAL_LEFT);
    fflush(stdout);
    for (int i = 2; i < col; i++) {
        printf("%s", HORIZONTAL_LINE);
        fflush(stdout);
    }
    printf("%s", VERTICAL_RIGHT);
    fflush(stdout);

    // Left & right side of cmd line
    SetCursorPosition(cursorState, row - 1, 1);
    printf("%s", VERTICAL_LINE);
    fflush(stdout);
    SetCursorPosition(cursorState, row - 1, col);
    printf("%s", VERTICAL_LINE);
    fflush(stdout);
    SetCursorPosition(cursorState, row, 1);

    // Bottom row
    printf("%s", BOTTOM_LEFT_CORNER);
    fflush(stdout);
    for (int i = 2; i < col; i++) {
        printf("%s", HORIZONTAL_LINE);
        fflush(stdout);
    }
    printf("%s", BOTTOM_RIGHT_CORNER);
    fflush(stdout);
}
