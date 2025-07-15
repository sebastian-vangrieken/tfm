#include "utils.h"
#include <stdio.h>

void SetCursorPosition(struct Point *cursorState, int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
    cursorState->row = row;
    cursorState->col = col;
}
