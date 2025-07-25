#ifndef UTILS_H
#define UTILS_H

struct Point {
    int row;
    int col;
};

void SetFileDescriptor(int *, char *);
void SetCursorPosition(struct Point *, int, int);
void DrawBorder(struct Point *, int, int);

#endif
