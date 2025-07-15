#include "utils.h"
#include "variables.h"
#include <stdio.h>

void SetCursorPosition(struct Point *cursorState, int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
    cursorState->row = row;
    cursorState->col = col;
}

void DrawBorder(struct Point *cursorState, int row, int col) {
    printf("%s", CLEAR);
    fflush(stdout);

    printf("%s", TOP_LEFT_CORNER);
    fflush(stdout);
    for (int i = 2; i < col; i++) {
        printf("%s", HORIZONTAL_LINE);
        fflush(stdout);
    }
    printf("%s", TOP_RIGHT_CORNER);
    fflush(stdout);

    for (int i = 2; i < row; i++) {
        SetCursorPosition(cursorState, i, 1);
        printf("%s", VERTICAL_LINE);
        SetCursorPosition(cursorState, i, col);
        printf("%s", VERTICAL_LINE);
        fflush(stdout);
    }
    SetCursorPosition(cursorState, row, 1);

    printf("%s", BOTTOM_LEFT_CORNER);
    fflush(stdout);
    for (int i = 2; i < col; i++) {
        printf("%s", HORIZONTAL_LINE);
        fflush(stdout);
    }
    printf("%s", BOTTOM_RIGHT_CORNER);
    fflush(stdout);
}
