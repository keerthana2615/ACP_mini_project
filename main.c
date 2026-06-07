#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "shapes.h"

// Set console mode for Windows ANSI terminal support
#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
void enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enable_ansi_support() {}
#endif

// Robust helper to parse valid integers within a specific range
int get_int_input(const char* prompt, int min_val, int max_val, int* output) {
    char buffer[256];
    int val;
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0; // EOF or read failure
        }
        // Strip trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check if buffer is empty
        if (strlen(buffer) == 0) {
            printf("\033[1;31mError: Input cannot be empty. Please try again.\033[0m\n");
            continue;
        }

        // Try parsing
        char* endptr;
        val = (int)strtol(buffer, &endptr, 10);
        if (endptr == buffer || *endptr != '\0') {
            printf("\033[1;31mError: Invalid number. Please enter an integer.\033[0m\n");
            continue;
        }

        // Bounds checks
        if (val < min_val || val > max_val) {
            printf("\033[1;31mError: Value must be between %d and %d. Please try again.\033[0m\n", min_val, max_val);
            continue;
        }

        *output = val;
        return 1;
    }
}

// Print shape list
void list_active_shapes() {
    if (object_count == 0) {
        printf("\033[1;33mNo active shapes on the canvas.\033[0m\n");
        return;
    }
    printf("\n\033[1;36m=== Active Graphical Objects ===\033[0m\n");
    printf("-------------------------------------------------------------------\n");
    printf("%-5s | %-12s | %-45s\n", "ID", "Type", "Parameters");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < object_count; i++) {
        GraphicObject obj = objects[i];
        printf("%-5d | %-12s | ", obj.id, shape_type_name(obj.type));
        switch (obj.type) {
            case SHAPE_LINE:
                printf("Start: (%d, %d), End: (%d, %d)\n", 
                       obj.params.line.x1, obj.params.line.y1,
                       obj.params.line.x2, obj.params.line.y2);
                break;
            case SHAPE_RECTANGLE:
                printf("Corner 1: (%d, %d), Corner 2: (%d, %d)\n", 
                       obj.params.rect.x1, obj.params.rect.y1,
                       obj.params.rect.x2, obj.params.rect.y2);
                break;
            case SHAPE_CIRCLE:
                printf("Center: (%d, %d), Radius: %d\n", 
                       obj.params.circle.cx, obj.params.circle.cy,
                       obj.params.circle.r);
                break;
            case SHAPE_TRIANGLE:
                printf("P1: (%d, %d), P2: (%d, %d), P3: (%d, %d)\n", 
                       obj.params.triangle.x1, obj.params.triangle.y1,
                       obj.params.triangle.x2, obj.params.triangle.y2,
                       obj.params.triangle.x3, obj.params.triangle.y3);
                break;
        }
    }
    printf("-------------------------------------------------------------------\n\n");
}

void handle_add_shape() {
    printf("\n\033[1;36m--- Add a New Shape ---\033[0m\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");
    printf("5. Cancel\n");
    
    int choice;
    if (!get_int_input("Enter choice (1-5): ", 1, 5, &choice)) return;
    
    if (choice == 5) return;
    
    int x1, y1, x2, y2, x3, y3, cx, cy, r;
    int shape_id = -1;

    switch (choice) {
        case 1: // Line
            printf("\nAdding Line:\n");
            if (!get_int_input("  Enter x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            shape_id = add_line(x1, y1, x2, y2);
            break;
            
        case 2: // Rectangle
            printf("\nAdding Rectangle:\n");
            if (!get_int_input("  Enter diagonal x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter diagonal y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter diagonal x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter diagonal y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            shape_id = add_rect(x1, y1, x2, y2);
            break;
            
        case 3: // Circle
            printf("\nAdding Circle:\n");
            if (!get_int_input("  Enter center cx (0-49): ", 0, WIDTH - 1, &cx)) return;
            if (!get_int_input("  Enter center cy (0-19): ", 0, HEIGHT - 1, &cy)) return;
            if (!get_int_input("  Enter radius r (0-50): ", 0, 50, &r)) return;
            shape_id = add_circle(cx, cy, r);
            break;
            
        case 4: // Triangle
            printf("\nAdding Triangle:\n");
            if (!get_int_input("  Enter x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            if (!get_int_input("  Enter x3 (0-49): ", 0, WIDTH - 1, &x3)) return;
            if (!get_int_input("  Enter y3 (0-19): ", 0, HEIGHT - 1, &y3)) return;
            shape_id = add_triangle(x1, y1, x2, y2, x3, y3);
            break;
    }

    if (shape_id != -1) {
        printf("\033[1;32mSuccess: Shape successfully added with ID %d!\033[0m\n", shape_id);
    } else {
        printf("\033[1;31mError: Canvas object buffer full!\033[0m\n");
    }
}

void handle_modify_shape() {
    if (object_count == 0) {
        printf("\033[1;33mNo shapes available to modify.\033[0m\n");
        return;
    }

    list_active_shapes();
    int id;
    if (!get_int_input("Enter the ID of the shape to modify: ", 1, 9999, &id)) return;

    int idx = find_shape_index(id);
    if (idx == -1) {
        printf("\033[1;31mError: Shape with ID %d not found.\033[0m\n", id);
        return;
    }

    GraphicObject* obj = &objects[idx];
    int x1, y1, x2, y2, x3, y3, cx, cy, r;
    int success = 0;

    printf("\nModifying %s (ID %d):\n", shape_type_name(obj->type), id);

    switch (obj->type) {
        case SHAPE_LINE:
            if (!get_int_input("  Enter new x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter new y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter new x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter new y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            success = modify_line(id, x1, y1, x2, y2);
            break;
            
        case SHAPE_RECTANGLE:
            if (!get_int_input("  Enter new diagonal x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter new diagonal y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter new diagonal x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter new diagonal y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            success = modify_rect(id, x1, y1, x2, y2);
            break;
            
        case SHAPE_CIRCLE:
            if (!get_int_input("  Enter new center cx (0-49): ", 0, WIDTH - 1, &cx)) return;
            if (!get_int_input("  Enter new center cy (0-19): ", 0, HEIGHT - 1, &cy)) return;
            if (!get_int_input("  Enter new radius r (0-50): ", 0, 50, &r)) return;
            success = modify_circle(id, cx, cy, r);
            break;
            
        case SHAPE_TRIANGLE:
            if (!get_int_input("  Enter new x1 (0-49): ", 0, WIDTH - 1, &x1)) return;
            if (!get_int_input("  Enter new y1 (0-19): ", 0, HEIGHT - 1, &y1)) return;
            if (!get_int_input("  Enter new x2 (0-49): ", 0, WIDTH - 1, &x2)) return;
            if (!get_int_input("  Enter new y2 (0-19): ", 0, HEIGHT - 1, &y2)) return;
            if (!get_int_input("  Enter new x3 (0-49): ", 0, WIDTH - 1, &x3)) return;
            if (!get_int_input("  Enter new y3 (0-19): ", 0, HEIGHT - 1, &y3)) return;
            success = modify_triangle(id, x1, y1, x2, y2, x3, y3);
            break;
    }

    if (success) {
        printf("\033[1;32mSuccess: Shape ID %d modified successfully!\033[0m\n", id);
    } else {
        printf("\033[1;31mError: Failed to modify shape.\033[0m\n");
    }
}

void handle_delete_shape() {
    if (object_count == 0) {
        printf("\033[1;33mNo shapes available to delete.\033[0m\n");
        return;
    }

    list_active_shapes();
    int id;
    if (!get_int_input("Enter the ID of the shape to delete: ", 1, 9999, &id)) return;

    if (delete_shape(id)) {
        printf("\033[1;32mSuccess: Shape ID %d deleted successfully!\033[0m\n", id);
    } else {
        printf("\033[1;31mError: Shape with ID %d not found.\033[0m\n", id);
    }
}

int main(void) {
    enable_ansi_support();
    
    char canvas[HEIGHT][WIDTH];
    init_canvas(canvas);

    printf("\033[1;36m====================================================\033[0m\n");
    printf("\033[1;36m*             2D Character Canvas Editor           *\033[0m\n");
    printf("\033[1;36m====================================================\033[0m\n");

    int choice;
    while (1) {
        printf("\n\033[1;33m=== Main Menu ===\033[0m\n");
        printf("1. Display Canvas\n");
        printf("2. List Shapes\n");
        printf("3. Add Shape\n");
        printf("4. Modify Shape\n");
        printf("5. Delete Shape\n");
        printf("6. Clear Canvas (Delete All Shapes)\n");
        printf("7. Exit\n");

        if (!get_int_input("Enter choice (1-7): ", 1, 7, &choice)) {
            printf("\nExiting. Thank you!\n");
            break;
        }

        switch (choice) {
            case 1:
                render_all_shapes(canvas);
                display_canvas(canvas);
                break;
            case 2:
                list_active_shapes();
                break;
            case 3:
                handle_add_shape();
                break;
            case 4:
                handle_modify_shape();
                break;
            case 5:
                handle_delete_shape();
                break;
            case 6:
                clear_shapes();
                printf("\033[1;32mSuccess: All shapes cleared from canvas.\033[0m\n");
                break;
            case 7:
                printf("\nExiting. Thank you for using the 2D Canvas Editor!\n");
                return 0;
        }
    }
    return 0;
}
