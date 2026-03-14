# LoneWolf Language — Project Context

## 1. Project Overview

**LoneWolf** is a new general-purpose programming language currently under development.

Goals of the language (priority order):

1. Security
2. Ease of use
3. Performance
4. Native AI integration

The long-term objective is to create a language that combines:

- Python-like usability
- C / PHP style explicit syntax
- Near-native performance
- AI-assisted development

The language should eventually become a **widely adopted general-purpose language**.

---

# 2. Language Philosophy

Core principles:

### Security First
The language ecosystem should encourage:

- SOLID principles
- OWASP secure development
- TDD (Test Driven Development)

AI tools integrated into the IDE will help detect:

- bad practices
- security issues
- architectural problems

But developers must be able to **override suggestions** if needed.

---

### Developer Productivity

The language should be:

- simple
- readable
- explicit
- predictable

Syntax should feel familiar to developers coming from:

- C
- PHP
- Python

---

### Performance

The language will compile to **native binaries**.

The compiler backend will eventually use **LLVM**.

---

# 3. Language Characteristics

Type: General-purpose language

Target uses:

- backend services
- CLI tools
- scripting
- system utilities
- eventually operating system components

---

# 4. Programming Paradigms

Required paradigms:

- Object Oriented Programming
- Functional Programming

Future paradigms may include:

- concurrency
- reactive programming
- data-oriented programming

---

# 5. Syntax Design

Syntax style: C / PHP inspired

Rules:

- statements end with `;`
- code blocks use `{ }`
- no indentation-based syntax

Example:
```
x = 10;
y = x + 5;
z = (y * 2) + 3;
```

---

# 6. Type System (Planned)

Typing model:

Static typing with AI-assisted inference.

Core rules:

- compiler maintains strict type safety
- AI layer may infer types or suggest them
- explicit types always allowed

---

# 7. Memory Management

Default:

Garbage Collector

Optional:

Manual memory management

Goal:

Allow both high-level development and low-level system programming.

---

# 8. Compiler Implementation

The compiler is written in:

C++

Reasons:

- performance
- memory control
- LLVM integration
- mature tooling

---

# 9. Repository License

License: MIT

Goal:

- maximum adoption
- minimal restrictions
- open ecosystem

---

# 10. Current Compiler Architecture

The compiler follows a classic pipeline:

```
Source Code
↓
Lexer
↓
Parser
↓
AST (next step)
↓
Semantic Analysis
↓
LLVM IR
↓
Native Binary
```

---

# 11. Current Project Structure

```
LoneWolf/

    include/
        Token.h
        Lexer.h
        Parser.h
        Error.h
        ErrorCollector.h

    src/
        main.cpp

    lexer/
        Lexer.cpp

    parser/
        Parser.cpp

    examples/
        test.lw

    docs/
        project_context.md
```

---

# 12. Lexer Status

Lexer is implemented and functional.

Supported tokens:

```
IDENTIFIER
NUMBER
STRING

PLUS
MINUS
STAR
SLASH

ASSIGN
SEMICOLON

LPAREN
RPAREN

END_OF_FILE
ERROR
```

Features implemented:

- identifiers
- numbers
- strings
- operators
- comments

Supported comments:

```
// single line
/* block comment */
```

Lexer tracks:

- line
- column

for precise diagnostics.

---

# 13. Error Handling System

The compiler uses a dedicated error collection system.

Components:

```
Error
├ message
├ line
└ column
```

Errors are stored in:

```
ErrorCollector
```

Advantages:

- compiler does not stop at first error
- multiple errors can be reported in one run
- reusable across compiler stages

---

# 14. Diagnostics Format

Errors are displayed similar to modern compilers.

Example:

```
test.lw:1:7 error: Expected ';'

x = 10
      ^
```

This requires:

- storing source lines
- computing column positions

---

# 15. Parser Implementation

Parser is implemented using:

Recursive Descent Parsing

Reason:

- full control
- easier integration with AI tooling
- easier maintenance

Main parser functions:

```
parse()
statement()
expression()
term()
factor()
advance()
```

Operator precedence implemented:

```
/
*
```

Parser currently:

- validates syntax
- detects syntax errors
- reports diagnostics

Parser does NOT yet generate an AST.

---

# 16. Current Grammar (v0.1)

```
program ::= statement*
```

```
statement ::= assignment | expression ";"
```

```
assignment ::= IDENTIFIER "=" expression ";"
```

```
expression ::= term (("+" | "-") term)*
```

```
term ::= factor (("" | "/") factor)
```

```
factor ::=
NUMBER
| STRING
| IDENTIFIER
| "(" expression ")"
```

---

# 17. Current Compiler Progress

Approximate progress:

```
Lexer 100%
Parser 60%
AST 0%
Semantic 0%
LLVM backend 0%
```

---

# 18. Next Development Step

Next milestone:

Implement the **AST (Abstract Syntax Tree)**.

Planned node types:

```
ASTNode
Expression
BinaryExpression
Literal
Identifier
Assignment
Statement
```

Example AST:

Code:

```
x = 10 + 5 * 2;
```

Tree:

```
Assignment
├ Identifier(x)
└ +
├ 10
└ *
├ 5
└ 2
```

---

# 19. Long-Term Vision

Future components:

1. AST
2. Semantic analysis
3. Symbol tables
4. Type checking
5. LLVM IR generation
6. Optimization passes
7. Runtime library
8. Dedicated IDE

IDE goals:

- integrated AI assistant
- automatic refactoring
- code security analysis
- ability to import other languages into LoneWolf

---

# 20. Current Development Environment

Development tools:

- Linux (Kubuntu)
- VSCode
- local LLM via Ollama
- CMake
- C++ compiler

Build script example:

```
./build.sh examples/test.lw
```

---

# 21. Current State Summary

The project already has:

- working lexer
- working parser
- error handling infrastructure
- compiler-style diagnostics
- modular architecture

Next step is implementing the AST, which will allow the compiler to understand program structure instead of only validating syntax.
