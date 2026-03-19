# AGENTS.md - LoneWolf Development Guide

## Project Overview

LoneWolf is a custom programming language compiler/interpreter written in C++20. The project uses CMake as its build system and executes `.lw` test files through the compiled binary.

## Build Commands

### Full Build
```bash
./build.sh
```
This script:
1. Creates/updates the `build/` directory
2. Runs `cmake -DCMAKE_BUILD_TYPE=Debug ..`
3. Compiles with `make -j$(nproc)`
4. Creates a symlink `lonewolf` to the binary
5. Executes all `.lw` test files in `tests/`

### Manual Build
```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
cd ..
```

### Run LoneWolf
```bash
./lonewolf <file.lw>
```

### Test Commands

#### Run All Tests
```bash
./build.sh
```
Or manually:
```bash
cd tests
for test_script in *.lw; do
  ./../lonewolf "$test_script"
done
```

#### Run Single Test
```bash
./lonewolf tests/<testfile.lw>
```

## Code Style Guidelines

### Project Structure
```
LoneWolf/
├── include/          # Header files (.h)
├── src/              # Implementation files (.cpp)
│   ├── lexer/
│   ├── parser/
│   ├── interpreter/
│   └── compiler/
├── tests/            # Test files (.lw)
├── examples/         # Example .lw files
├── build/            # CMake build output
└── CMakeLists.txt   # Build configuration
```

### Naming Conventions

- **Classes**: PascalCase
  - Examples: `Lexer`, `Parser`, `Token`, `ErrorCollector`

- **Functions**: camelCase
  - Examples: `getNextToken()`, `advance()`, `parse()`

- **Variables**: camelCase
  - Examples: `currentChar`, `sourceLines`, `errorCollector`

- **Member Variables**: No prefix, just camelCase
  - Examples: `currentToken`, `previousToken`, `line`, `column`

- **Constants**: camelCase (no ALL_CAPS observed in codebase)
  - Example: `keywords` map in Lexer.cpp

- **Enums**: `enum class` with PascalCase values
  - Example: `TokenType::IF`, `TokenType::NUMBER`

- **Files**: PascalCase for headers, PascalCase for source
  - Examples: `Lexer.h`, `Lexer.cpp`, `Token.h`

### Formatting

- **Indentation**: 4 spaces (tabs not used)
- **Braces**: Same-line style for classes and functions
  ```cpp
  class Lexer {
  public:
      explicit Lexer(std::istream& input, ErrorCollector& errorCollector);
  };
  ```
- **Line Comments**: Use `//` for comments (Spanish language used in existing code)
- **Class Access Specifiers**: `public:`, `private:` at class level indentation
- **Include Order**:
  1. Local headers (quoted)
  2. System/STL headers (angle brackets)
  ```cpp
  #include <cctype>
  #include "Lexer.h"
  ```

### Header Files

- Use `#pragma once` for include guards
- Place class definition in header, implementation in .cpp
- Mark single-argument constructors as `explicit`
- Use forward declarations where possible
- Group members by access specifier (public first, then private)

### Types and References

- Use `const` for parameters that are not modified
- Use `&` for reference parameters
- Use `std::string` for string types
- Use `int` for line/column positions
- Prefer `enum class` over plain enums

### Error Handling

- Use `ErrorCollector` class to collect errors during compilation
- Add errors with line and column information:
  ```cpp
  errorCollector.addError("Error message", line, column);
  ```
- Check for errors after parsing:
  ```cpp
  if (errors.hasErrors()) {
      // Display errors
  }
  ```
- Errors should include: message, line number, column number

### Code Patterns

#### Token Definition
```cpp
struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token() : type(TokenType::END_OF_FILE), lexeme(""), line(0), column(0) {}

    Token(TokenType type, const std::string& lexeme, int line, int column)
        : type(type), lexeme(lexeme), line(line), column(column) {}
};
```

#### Class with Constructor Initialization
```cpp
Lexer::Lexer(std::istream& input, ErrorCollector& errorCollector)
    : input(input),
      errorCollector(errorCollector),
      currentChar(0),
      line(1),
      column(0)
{
    advance();
}
```

#### Lexer Token Generation Pattern
```cpp
Token Lexer::number() {
    std::string lexeme;
    int startLine = line;
    int startColumn = column;
    // ... parsing logic
    Token t;
    t.type = TokenType::NUMBER;
    t.lexeme = lexeme;
    t.line = startLine;
    t.column = startColumn;
    return t;
}
```

### Testing

- Test files are written in the LoneWolf language (`.lw` extension)
- Place test files in the `tests/` directory
- Run tests using: `./lonewolf tests/testfile.lw`
- Expected output: tokens printed line-by-line, then parse results

### Common Patterns

#### Reading Source File
```cpp
std::ifstream file(argv[1]);
if (!file.is_open()) {
    std::cerr << "[ERROR] Could not open file" << std::endl;
    return 1;
}

std::vector<std::string> sourceLines;
std::string lineText;
while (std::getline(file, lineText)) {
    sourceLines.push_back(lineText);
}
```

#### Keyword Lookup
```cpp
const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"return", TokenType::RETURN}
};
```

### Language-Specific Notes

- Current LoneWolf language features:
  - Keywords: `if`, `else`, `while`, `return`
  - Operators: `=`, `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `<=`, `>`, `>=`
  - Delimiters: `(`, `)`, `{`, `}`, `;`
  - Literals: numbers, strings, identifiers
  - Comments: `//` (line) and `/* */` (block)

### CMake Configuration

The project uses CMake 3.20+ with C++20:
```cmake
cmake_minimum_required(VERSION 3.20)
project(LoneWolf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### Best Practices

1. Always initialize all member variables in constructors
2. Use `explicit` for single-argument constructors
3. Pass streams and large objects by reference
4. Track line and column numbers for error reporting
5. Use `static_cast<char>` when converting int to char
6. Handle EOF gracefully in parsing loops
7. Check for errors after each compilation phase
8. Use descriptive variable names (Spanish comments are acceptable)
