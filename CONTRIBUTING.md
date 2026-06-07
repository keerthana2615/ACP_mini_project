# Contributing to 2D Character Canvas Editor

Thank you for your interest in contributing! This document provides guidelines for contributing to this project.

## Development Setup

### Prerequisites
- GCC compiler (or compatible C compiler)
- Make build tool
- Git

### Cloning and Building

```bash
git clone https://github.com/keerthana2615/ACP_mini_project.git
cd ACP_mini_project
make
```

## Code Style

- Use 4-space indentation
- Follow C99 standard
- Include proper header guards in .h files
- Comment complex algorithms and logic
- Use meaningful variable and function names

## Making Changes

1. Create a feature branch: `git checkout -b feature/your-feature-name`
2. Make your changes
3. Test your changes: `make clean && make run`
4. Commit with clear messages: `git commit -m "Add descriptive commit message"`
5. Push to your fork and submit a pull request

## Testing

- Test all menu options before submitting
- Verify shape rendering is correct
- Check edge cases (boundary values, empty canvas, etc.)
- Test on both Windows and Unix-like systems if possible

## Bug Reports

When reporting bugs, please include:
- A clear description of the issue
- Steps to reproduce
- Expected vs actual behavior
- Platform and compiler information

## Feature Requests

Feature requests are welcome! Please describe:
- The desired feature
- Use cases
- Potential implementation approach

## Questions?

Feel free to open an issue for any questions or discussions!
