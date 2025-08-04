# DataChef - Virtual Recipe Book

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Unix-lightgrey.svg)]()
[![License](https://img.shields.io/badge/license-Educational-green.svg)]()

## Overview

DataChef is a command-line based virtual recipe book developed in C++ as part of a Data Structures course. This project demonstrates the practical implementation of advanced data structures including doubly linked lists for recipe management and singly linked lists for ingredient storage.

## Features

### 📋 Recipe Management
- **Add Recipes**: Create new recipes with detailed information including name, category, preparation time, ingredients, and step-by-step procedures
- **Edit Recipes**: Modify existing recipes - add/remove ingredients, update procedures, or change recipe details
- **Delete Recipes**: Remove individual recipes or clear the entire recipe book
- **Search Recipes**: Find recipes by name or filter by category

### 🔍 Display Options
- **View All Recipes**: Display the complete recipe collection
- **Category Filtering**: Show recipes organized by category (Desayuno, Comida, Cena, Navidad)
- **Individual Recipe View**: Display detailed information for specific recipes
- **Sorted Display**: View recipes sorted by name, category, or preparation time

### 💾 Data Persistence
- **Save to File**: Export your recipe book to text files
- **Load from File**: Import previously saved recipe collections
- **Data Format**: Custom text format for easy data exchange

### 🎯 Advanced Features
- **Dynamic Sorting**: Sort recipes by name, category, or preparation time
- **Interactive Menus**: User-friendly command-line interface with clear navigation
- **Input Validation**: Robust error handling and data validation
- **Cross-Platform**: Compatible with Windows and Unix-like systems

## Data Structures Used

### Primary Data Structures
- **Doubly Linked List (`LDLCCED.hpp`)**: Manages the main recipe collection with bidirectional navigation
- **Singly Linked List (`LSLLSE.hpp`)**: Stores ingredients for each recipe efficiently

### Classes Architecture
- **`Receta`**: Core recipe class containing all recipe information
- **`Ingrediente`**: Ingredient class with name and quantity attributes
- **`Nombre`**: Author name class for structured name storage
- **`Menu`**: Main interface controller managing user interactions

## Project Structure

```
Data-structures-DataChef/
│
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── receta.cpp         # Recipe implementation
│   ├── ingrediente.cpp    # Ingredient implementation
│   └── nombre.cpp         # Name class implementation
│
├── include/               # Header files
│   ├── LDLCCED.hpp        # Doubly Linked List implementation
│   ├── LSLLSE.hpp         # Singly Linked List implementation
│   ├── receta.hpp         # Recipe class definition
│   ├── ingrediente.hpp    # Ingredient class definition
│   ├── nombre.hpp         # Name class definition
│   └── menu.hpp           # Menu system (header-only)
│
├── data/                  # Sample data files
│   ├── exported_book_sample.txt     # Example exported recipe book
│   └── mock_data_for_injection.txt  # Sample data for testing
│
└── README.md             # Project documentation
```

## Compilation and Usage

### Prerequisites
- C++ compiler with C++11 support or later (GCC, Clang, MSVC)
- Standard C++ library

### Compilation

#### Using g++ (Windows with MinGW or Unix)
```bash
g++ -std=c++11 -I./include src/*.cpp -o datachef
```

#### Using Visual Studio (Windows)
```cmd
cl /EHsc /I.\include src\*.cpp /Fe:datachef.exe
```

### Running the Application

#### Windows
```cmd
.\datachef.exe
```

#### Unix/Linux/macOS
```bash
./datachef
```

## User Interface

### Main Menu Options

```
Bienvenido al recetario, ingrese la opcion que desea:
    0) Salir
    1) Mostrar recetas
    2) Modificar recetario
    3) Guardar o leer en disco
```

### Recipe Categories
- **Desayuno** (Breakfast)
- **Comida** (Lunch)
- **Cena** (Dinner)
- **Navidad** (Christmas)

## Usage Examples

### Adding a New Recipe
1. Select option `2` (Modificar recetario)
2. Select option `1` (Agregar nueva receta)
3. Follow the prompts to enter:
   - Recipe name
   - Ingredients with quantities
   - Category selection
   - Step-by-step procedure
   - Preparation time
   - Author information

### Searching for Recipes
1. Select option `1` (Mostrar recetas)
2. Choose from:
   - Show all recipes
   - Filter by category
   - Search by name
   - Search by category

### Saving Your Recipe Book
1. Select option `3` (Guardar o leer en disco)
2. Select option `1` (Guardar en disco)
3. Enter filename (extension will be added automatically)

## Technical Details

### Memory Management
- Dynamic memory allocation for flexible data storage
- Proper cleanup and destructor implementation
- Exception handling for memory allocation failures

### Sorting Algorithms
- Custom comparison functions for different sorting criteria
- Efficient in-place sorting for linked list structures

### File I/O Format
```
inicioReceta
[Recipe Name]
[Category]
[Preparation Time]
[Author First Name]
[Author Last Name]
[Ingredient Count]
[Ingredient 1 Name] | [Quantity]
[Ingredient 2 Name] | [Quantity]
...
[Procedure]
inicioReceta
...
```

## Learning Objectives

This project demonstrates:
- **Data Structure Implementation**: Custom linked list implementations
- **Object-Oriented Programming**: Class design and encapsulation
- **Memory Management**: Dynamic allocation and deallocation
- **File I/O Operations**: Custom file format handling
- **User Interface Design**: Menu-driven console applications
- **Algorithm Implementation**: Sorting and searching algorithms
- **Error Handling**: Exception management and input validation

## Future Enhancements

- [ ] Recipe rating system
- [ ] Nutritional information tracking
- [ ] Recipe sharing capabilities
- [ ] Advanced search filters (by ingredients, preparation time)
- [ ] Recipe import from popular formats
- [ ] GUI version using a C++ framework
- [ ] Database integration
- [ ] Recipe recommendations based on available ingredients

## Contributing

This is an educational project. If you're using this as a reference:
1. Understand the data structure implementations
2. Study the memory management techniques
3. Analyze the file I/O operations
4. Examine the user interface design patterns

## Educational Context

This project was developed as part of a Data Structures course to demonstrate:
- Practical application of linked list data structures
- Real-world problem solving using custom data structures
- Implementation of complete applications with user interfaces
- File persistence and data management

## Author

Developed as part of a Data Structures course project.

---

*DataChef - Where data structures meet culinary creativity! 👨‍🍳📊*
