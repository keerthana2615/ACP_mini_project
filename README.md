# 2D Character Canvas Editor

A C program that implements a 2D Character Canvas Editor, allowing users to create, display, modify, and delete graphical shapes using a character-based interface.

## Features

- **Add Shapes**: Create lines, rectangles, circles, and triangles
- **Display Canvas**: View all shapes rendered on a 50x20 character canvas
- **Modify Shapes**: Edit existing shapes by their ID
- **Delete Shapes**: Remove individual shapes or clear the entire canvas
- **Robust Input Validation**: Comprehensive error handling for user input
- **ANSI Color Support**: Colored output for better terminal experience
- **Windows Compatibility**: Works on both Windows and Unix-like systems

## Project Structure

```
├── main.c          # Main program with menu and I/O handling
├── canvas.h        # Canvas header file
├── canvas.c        # Canvas implementation
├── shapes.h        # Shapes header file  
├── shapes.c        # Shapes implementation
├── Makefile        # Build configuration
└── README.md       # This file
```

## Compilation

### Using Makefile (Recommended)

```bash
make              # Compile the program
make run          # Compile and run the program
make clean        # Remove object files and executable
```

### Manual Compilation

```bash
gcc -Wall -Wextra -std=c99 -O2 -o canvas_editor main.c canvas.c shapes.c
```

## Usage

Run the program:
```bash
./canvas_editor
```

### Menu Options

1. **Display Canvas** - Shows all shapes rendered on the canvas
2. **List Shapes** - Lists all active shapes with their parameters
3. **Add Shape** - Interactively add a new shape (line, rectangle, circle, or triangle)
4. **Modify Shape** - Update parameters of an existing shape
5. **Delete Shape** - Remove a specific shape by ID
6. **Clear Canvas** - Delete all shapes
7. **Exit** - Exit the program

## Canvas Specifications

- **Canvas Size**: 50 × 20 characters
- **Coordinate Range**: 
  - X: 0-49
  - Y: 0-19

## Shape Types

### Line
- Defined by two endpoints: (x1, y1) and (x2, y2)

### Rectangle
- Defined by two opposite corners: (x1, y1) and (x2, y2)

### Circle
- Defined by center point (cx, cy) and radius r
- Radius range: 0-50

### Triangle
- Defined by three vertices: (x1, y1), (x2, y2), and (x3, y3)

## Input Validation

The program provides robust input validation:
- Checks for empty inputs
- Validates integer parsing
- Enforces coordinate bounds
- Provides helpful error messages

## Features

- **Object Management**: Store up to 100 shapes with unique IDs
- **Shape Rendering**: Uses Bresenham-like algorithms for drawing shapes
- **User-Friendly**: Clear menus and error messages
- **Cross-Platform**: Works on Windows (with ANSI support) and Unix/Linux

## Building on Different Platforms

### Linux/macOS
```bash
make
./canvas_editor
```

### Windows (MinGW)
```bash
make
canvas_editor.exe
```

### Windows (MSVC)
```bash
cl /W4 /O2 main.c canvas.c shapes.c /Fe:canvas_editor.exe
canvas_editor.exe
```

## Technical Details

- **Language**: C (C99)
- **Max Shapes**: 100 concurrent objects
- **ID System**: Auto-incrementing IDs for shape tracking
- **Color Support**: ANSI escape codes for terminal colors
- **Windows Support**: Automatic ANSI mode enablement

## Notes

- ANSI color codes are supported on most modern terminals
- Windows users should use Windows Terminal or enable ANSI mode for full color support
- The canvas uses `*` character to render all shapes
- Shape positions are validated against canvas boundaries
