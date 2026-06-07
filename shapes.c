#include <stdio.h>
#include <string.h>
#include "shapes.h"

// Global object storage
GraphicObject objects[MAX_OBJECTS];
int object_count = 0;
int next_id = 1;

// Find shape index by ID
int find_shape_index(int id) {
    for (int i = 0; i < object_count; i++) {
        if (objects[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Get shape type name
const char* shape_type_name(ShapeType type) {
    switch (type) {
        case SHAPE_LINE:      return "Line";
        case SHAPE_RECTANGLE: return "Rectangle";
        case SHAPE_CIRCLE:    return "Circle";
        case SHAPE_TRIANGLE:  return "Triangle";
        default:              return "Unknown";
    }
}

// Add line shape
int add_line(int x1, int y1, int x2, int y2) {
    if (object_count >= MAX_OBJECTS) {
        return -1;
    }
    objects[object_count].id = next_id;
    objects[object_count].type = SHAPE_LINE;
    objects[object_count].params.line.x1 = x1;
    objects[object_count].params.line.y1 = y1;
    objects[object_count].params.line.x2 = x2;
    objects[object_count].params.line.y2 = y2;
    object_count++;
    return next_id++;
}

// Add rectangle shape
int add_rect(int x1, int y1, int x2, int y2) {
    if (object_count >= MAX_OBJECTS) {
        return -1;
    }
    objects[object_count].id = next_id;
    objects[object_count].type = SHAPE_RECTANGLE;
    objects[object_count].params.rect.x1 = x1;
    objects[object_count].params.rect.y1 = y1;
    objects[object_count].params.rect.x2 = x2;
    objects[object_count].params.rect.y2 = y2;
    object_count++;
    return next_id++;
}

// Add circle shape
int add_circle(int cx, int cy, int r) {
    if (object_count >= MAX_OBJECTS) {
        return -1;
    }
    objects[object_count].id = next_id;
    objects[object_count].type = SHAPE_CIRCLE;
    objects[object_count].params.circle.cx = cx;
    objects[object_count].params.circle.cy = cy;
    objects[object_count].params.circle.r = r;
    object_count++;
    return next_id++;
}

// Add triangle shape
int add_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (object_count >= MAX_OBJECTS) {
        return -1;
    }
    objects[object_count].id = next_id;
    objects[object_count].type = SHAPE_TRIANGLE;
    objects[object_count].params.triangle.x1 = x1;
    objects[object_count].params.triangle.y1 = y1;
    objects[object_count].params.triangle.x2 = x2;
    objects[object_count].params.triangle.y2 = y2;
    objects[object_count].params.triangle.x3 = x3;
    objects[object_count].params.triangle.y3 = y3;
    object_count++;
    return next_id++;
}

// Modify line shape
int modify_line(int id, int x1, int y1, int x2, int y2) {
    int idx = find_shape_index(id);
    if (idx == -1 || objects[idx].type != SHAPE_LINE) {
        return 0;
    }
    objects[idx].params.line.x1 = x1;
    objects[idx].params.line.y1 = y1;
    objects[idx].params.line.x2 = x2;
    objects[idx].params.line.y2 = y2;
    return 1;
}

// Modify rectangle shape
int modify_rect(int id, int x1, int y1, int x2, int y2) {
    int idx = find_shape_index(id);
    if (idx == -1 || objects[idx].type != SHAPE_RECTANGLE) {
        return 0;
    }
    objects[idx].params.rect.x1 = x1;
    objects[idx].params.rect.y1 = y1;
    objects[idx].params.rect.x2 = x2;
    objects[idx].params.rect.y2 = y2;
    return 1;
}

// Modify circle shape
int modify_circle(int id, int cx, int cy, int r) {
    int idx = find_shape_index(id);
    if (idx == -1 || objects[idx].type != SHAPE_CIRCLE) {
        return 0;
    }
    objects[idx].params.circle.cx = cx;
    objects[idx].params.circle.cy = cy;
    objects[idx].params.circle.r = r;
    return 1;
}

// Modify triangle shape
int modify_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3) {
    int idx = find_shape_index(id);
    if (idx == -1 || objects[idx].type != SHAPE_TRIANGLE) {
        return 0;
    }
    objects[idx].params.triangle.x1 = x1;
    objects[idx].params.triangle.y1 = y1;
    objects[idx].params.triangle.x2 = x2;
    objects[idx].params.triangle.y2 = y2;
    objects[idx].params.triangle.x3 = x3;
    objects[idx].params.triangle.y3 = y3;
    return 1;
}

// Delete shape by ID
int delete_shape(int id) {
    int idx = find_shape_index(id);
    if (idx == -1) {
        return 0;
    }
    // Shift objects array
    for (int i = idx; i < object_count - 1; i++) {
        objects[i] = objects[i + 1];
    }
    object_count--;
    return 1;
}

// Clear all shapes
void clear_shapes(void) {
    object_count = 0;
    next_id = 1;
}
