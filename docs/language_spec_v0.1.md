# LoneWolf Language Specification
Version: 0.1 (Draft)

This document defines the initial specification of the **LoneWolf programming language**.

The purpose of this document is to provide a clear and stable reference for:

- compiler development
- language design decisions
- AI tooling integration
- future language evolution

This is an early specification and will evolve over time.

---

# 1. Language Overview

LoneWolf is a **general-purpose compiled programming language** designed with the following priorities:

1. Security
2. Ease of use
3. Performance
4. AI-assisted development

The language aims to combine:

- Python-level usability
- C/PHP style syntax
- native compiled performance
- AI-assisted development workflows

LoneWolf programs compile to **native machine code**.

The compiler will eventually use **LLVM** as the backend.

---

# 2. Language Philosophy

The design of LoneWolf follows these principles.

### Explicit but simple

The language syntax should be:

- readable
- explicit
- easy to learn
- predictable

---

### Security by design

The language ecosystem encourages:

- SOLID design principles
- OWASP secure development
- Test Driven Development (TDD)

Future IDE tooling will include AI-assisted detection of:

- bad practices
- security vulnerabilities
- architectural problems

---

### Performance

Programs compile to native binaries.

The runtime should be minimal.

Low-level control should remain possible.

---

# 3. Basic Syntax

LoneWolf uses a syntax style inspired by C-like languages.

Rules:

- statements end with `;`
- blocks use `{ }`
- indentation does not affect syntax

Example:

```
x = 10;
y = x + 5;
z = (y * 2) + 3;
```

---

# 4. Program Structure

A LoneWolf program consists of a sequence of statements.

```
program ::= statement*
```

---

# 5. Statements

Currently supported statements in version 0.1:

```
statement ::= assignment
| expression ";"
```

---

# 6. Assignment

Assignment associates a value with a variable.

Syntax:

```
assignment ::= IDENTIFIER "=" expression ";"
```

Example:
```
x = 10;
y = x + 5;
```

---

# 7. Expressions

Expressions evaluate to a value.
```
expression ::= term (("+" | "-") term)*
```

Example:
```
x + 5
10 - 3
```

---

# 8. Terms

Terms represent multiplication or division operations.
```
term ::= factor (("" | "/") factor)
```

Example:
```
10 * 5
a / 2
```

---

# 9. Factors

Factors represent the smallest expression units.
```
factor ::= NUMBER
| STRING
| IDENTIFIER
| "(" expression ")"
```

Examples:

```
10
"hello"
x
(x + 2)
```

---

# 10. Operator Precedence

Operator precedence is defined as follows (highest to lowest):

```
1. ()
2. /
3. *
```

Parentheses override precedence rules.

Example:
```
10 + 5 * 2
```

evaluates as:
```
10 + (5 * 2)
```

---

# 11. Identifiers

Identifiers represent variable names.

Rules:

- must start with a letter or underscore
- may contain letters, digits, and underscores

Examples:
```
x
userName
_value
```

---

# 12. Numbers

Numbers represent numeric literals.

Version 0.1 supports:

integer numbers

Examples:
```
10
42
1000
```

Future versions will support:

- floating point numbers
- hexadecimal
- binary literals

---

# 13. Strings

Strings represent sequences of characters.

Syntax:
```
"hello"
```

Example:
```
message = "Hello World";
```

Future versions may support:

- multi-line strings
- string interpolation

---

# 14. Comments

LoneWolf supports two types of comments.

### Single-line comments
```
// comment
```

Example:
```
x = 10; // assign value
```

---

### Block comments

```
/* comment */
```

Example:

```
/*
multi-line
comment
*/
```

---

# 15. Error Reporting

The compiler reports errors using **compiler-style diagnostics**.

Format:
```
file:line:column error: message
```

Example:
```
test.lw:1:6 error: Expected ';'

x = 10
      ^
```

The compiler should continue parsing to detect multiple errors in one compilation.

---

# 16. Type System (Planned)

The language will use:

```
static typing with AI-assisted inference
```

Core principles:

- strict type safety
- explicit types allowed
- AI may suggest inferred types

Example future syntax:

```
int x = 10;
```

or

```
x = 10;
```

where the type may be inferred.

---

# 17. Memory Management (Planned)

Default memory management:

```
Garbage Collector
```

Optional manual control may be available for:

- system programming
- low-level optimization

---

# 18. Compiler Architecture

The LoneWolf compiler pipeline follows this structure:

```
Source Code
↓
Lexer
↓
Parser
↓
AST
↓
Semantic Analysis
↓
LLVM IR
↓
Native Binary
```

---

# 19. Current Implementation Status

Current progress of the compiler:

```
Lexer complete
Parser partially implemented
AST not implemented
Semantic not implemented
Codegen not implemented
```

---

# 20. Future Language Features

Planned features include:

Variables with explicit types

```
int x = 10;
```

Functions

```
fn add(a, b) {
    return a + b;
}
```

Control flow

```
if (condition) {
}
```

Loops

```
while (condition) {
}
```

Classes and objects

```
class User {
}
```

Functional programming features

- lambdas
- immutability
- pure functions

---

# 21. Long-Term Vision

LoneWolf aims to become a modern programming language with:
 
- native performance
- strong security practices
- AI-assisted development
- a dedicated IDE
- the ability to import code from other languages

The language should remain:

- predictable
- secure
- developer-friendly
