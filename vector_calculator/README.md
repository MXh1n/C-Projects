# Vector Calculator

A C program for performing vector operations with a clean terminal interface.

## ⚙️ Functionality
- **Dot Product** - Works for both 2D and 3D vectors
- **Cross Product** - For 3D vectors only (returns perpendicular vector)

## 🎯 Design
- **`main()` function** - Handles user interface and menu navigation
- **Modular functions** - `dot_product()` and `cross_product()` separate the logic
- **Array storage** - Vectors stored in `vector1[]` and `vector2[]` arrays
- **Clean separation** - UI and calculation logic are independent

## 🚀 Quick Start
```bash
# Compile
gcc -o vector_calc vector_calc.c

# Run
./vector_calc
