#ifndef CANVAS_H
#define CANVAS_H

#define WIDTH 50
#define HEIGHT 20
#define EMPTY_CHAR ' '
#define CANVAS_BORDER '+'

void init_canvas(char canvas[HEIGHT][WIDTH]);
void display_canvas(const char canvas[HEIGHT][WIDTH]);
void render_all_shapes(char canvas[HEIGHT][WIDTH]);

#endif // CANVAS_H
