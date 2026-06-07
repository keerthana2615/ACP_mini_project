#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "canvas.h"
#include "shapes.h"

// Initialize canvas with empty characters
void init_canvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = EMPTY_CHAR;
        }
    }
}

// Set a pixel on the canvas
static void set_pixel(char canvas[HEIGHT][WIDTH], int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

// Bresenham's line algorithm
static void draw_line(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int x = x1, y = y1;
    while (1) {
        set_pixel(canvas, x, y);
        if (x == x2 && y == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

// Draw rectangle
static void draw_rectangle(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2) {
    int minx = (x1 < x2) ? x1 : x2;
    int maxx = (x1 > x2) ? x1 : x2;
    int miny = (y1 < y2) ? y1 : y2;
    int maxy = (y1 > y2) ? y1 : y2;

    // Draw horizontal lines
    for (int x = minx; x <= maxx; x++) {
        set_pixel(canvas, x, miny);
        set_pixel(canvas, x, maxy);
    }
    // Draw vertical lines
    for (int y = miny; y <= maxy; y++) {
        set_pixel(canvas, minx, y);
        set_pixel(canvas, maxx, y);
    }
}

// Draw circle using midpoint circle algorithm
static void draw_circle(char canvas[HEIGHT][WIDTH], int cx, int cy, int r) {
    if (r < 0) return;
    
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        set_pixel(canvas, cx + x, cy + y);
        set_pixel(canvas, cx - x, cy + y);
        set_pixel(canvas, cx + x, cy - y);
        set_pixel(canvas, cx - x, cy - y);
        set_pixel(canvas, cx + y, cy + x);
        set_pixel(canvas, cx - y, cy + x);
        set_pixel(canvas, cx + y, cy - x);
        set_pixel(canvas, cx - y, cy - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Draw triangle
static void draw_triangle(char canvas[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(canvas, x1, y1, x2, y2);
    draw_line(canvas, x2, y2, x3, y3);
    draw_line(canvas, x3, y3, x1, y1);
}

// Render all shapes on canvas
void render_all_shapes(char canvas[HEIGHT][WIDTH]) {
    init_canvas(canvas);
    for (int i = 0; i < object_count; i++) {
        GraphicObject obj = objects[i];
        switch (obj.type) {
            case SHAPE_LINE:
                draw_line(canvas, 
                         obj.params.line.x1, obj.params.line.y1,
                         obj.params.line.x2, obj.params.line.y2);
                break;
            case SHAPE_RECTANGLE:
                draw_rectangle(canvas,
                              obj.params.rect.x1, obj.params.rect.y1,
                              obj.params.rect.x2, obj.params.rect.y2);
                break;
            case SHAPE_CIRCLE:
                draw_circle(canvas,
                           obj.params.circle.cx, obj.params.circle.cy,
                           obj.params.circle.r);
                break;
            case SHAPE_TRIANGLE:
                draw_triangle(canvas,
                             obj.params.triangle.x1, obj.params.triangle.y1,
                             obj.params.triangle.x2, obj.params.triangle.y2,
                             obj.params.triangle.x3, obj.params.triangle.y3);
                break;
        }
    }
}

// Display canvas with borders
void display_canvas(const char canvas[HEIGHT][WIDTH]) {
    printf("\n\033[1;36m");
    // Top border
    printf("+");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\n");
    
    // Canvas content
    for (int y = 0; y < HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < WIDTH; x++) {
            if (canvas[y][x] != EMPTY_CHAR) {
                printf("\033[1;32m%c\033[1;36m", canvas[y][x]);
            } else {
                printf("%c", canvas[y][x]);
            }
        }
        printf("|\n");
    }
    
    // Bottom border
    printf("+");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\033[0m\n");
}
