#ifndef SHAPES_H
#define SHAPES_H

#define MAX_OBJECTS 100

// Shape type enumeration
typedef enum {
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} ShapeType;

// Geometry structures
typedef struct {
    int x1, y1, x2, y2;
} Line;

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

typedef struct {
    int cx, cy, r;
} Circle;

typedef struct {
    int x1, y1, x2, y2, x3, y3;
} Triangle;

// Union for shape parameters
typedef union {
    Line line;
    Rectangle rect;
    Circle circle;
    Triangle triangle;
} ShapeParams;

// Graphic object structure
typedef struct {
    int id;
    ShapeType type;
    ShapeParams params;
} GraphicObject;

// Global object storage
extern GraphicObject objects[MAX_OBJECTS];
extern int object_count;
extern int next_id;

// Function declarations
int add_line(int x1, int y1, int x2, int y2);
int add_rect(int x1, int y1, int x2, int y2);
int add_circle(int cx, int cy, int r);
int add_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

int modify_line(int id, int x1, int y1, int x2, int y2);
int modify_rect(int id, int x1, int y1, int x2, int y2);
int modify_circle(int id, int cx, int cy, int r);
int modify_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3);

int delete_shape(int id);
void clear_shapes(void);
int find_shape_index(int id);
const char* shape_type_name(ShapeType type);

#endif // SHAPES_H
