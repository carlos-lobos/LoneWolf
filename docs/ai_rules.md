# LoneWolf Compiler — AI Development Rules

This document defines how an AI assistant should behave when helping develop the **LoneWolf programming language compiler**.

The AI should always prioritize **correct compiler architecture, code clarity, and long-term maintainability**.

---

# 1. Project Awareness

The AI must assume the following:

- The project is the **LoneWolf programming language compiler**.
- The compiler is written in **C++**.
- The project uses **CMake**.
- The project structure is modular.

The AI should read `docs/project_context.md` before suggesting architectural changes.

---

# 2. Core Principles

The AI must prioritize:

1. Clean architecture
2. Readable code
3. Deterministic behavior
4. Compiler correctness
5. Maintainability

The AI must avoid:

- unnecessary abstractions
- overengineering
- experimental patterns
- breaking existing compiler structure

---

# 3. Code Style Rules

The AI must follow these coding rules.

### Language

All code must be written in **modern C++**.

Preferred standard:

```
C++17 or newer
```

---

### Naming Conventions

Classes:

```
PascalCase
```

Example:

```
Lexer
Parser
ErrorCollector
ASTNode
```

---

Functions:

```
camelCase
```

Example:

```
getNextToken
parseExpression
advance
```

---

Variables:

```
camelCase
```

Example:

```
currentToken
previousToken
sourceLines
```

---

Constants:

```
UPPER_CASE
```

---

# 4. Compiler Architecture Rules

The AI must preserve the compiler pipeline:

```
Source
→ Lexer
→ Parser
→ AST
→ Semantic Analysis
→ Code Generation
```

The AI must **never mix responsibilities between layers**.

Examples:

Lexer must NOT:

- understand syntax
- validate grammar

Parser must NOT:

- perform type checking
- generate machine code

Semantic stage must NOT:

- tokenize input
- read files

---

# 5. File Organization Rules

The AI must respect the project structure.

```
include/
    public headers

src/
    implementations

src/lexer/
    lexer implementation

src/parser/
    parser implementation
```

New modules should follow the same pattern.

Example:

```
src/ast/
src/semantic/
src/codegen/
```

---

# 6. Error Handling Rules

All compiler errors must go through:

```
ErrorCollector
```

The AI must NOT:

- print errors directly with `std::cout`
- stop compilation on the first error

Instead:

```
errorCollector.addError(...)
```

The compiler should accumulate errors and report them later.

---

# 7. Diagnostic Output Rules

Error output must follow compiler-style diagnostics.

Format:

```
file:line:column error: message
```

Example:

```
test.lw:1:7 error: Expected ';'

x = 10
      ^
```

---

# 8. Parser Rules

The parser must use **Recursive Descent**.

The AI must NOT suggest:

- parser generators
- ANTLR
- Bison
- yacc

The parser functions should follow this structure:

```
parse()
statement()
expression()
term()
factor()
```

Operator precedence must be respected.

---

# 9. AST Rules

The AST must be implemented using classes.

Typical structure:

```
ASTNode
Expression
Statement
BinaryExpression
Literal
Identifier
Assignment
```

Nodes must be strongly typed and explicit.

Avoid generic containers like `std::any`.

---

# 10. Memory Management Rules

AST nodes should use:

```
std::unique_ptr
```

Avoid raw pointers where possible.

Example:

```
std::unique_ptr<Expression>
```

---

# 11. Future LLVM Integration

Eventually the compiler will generate **LLVM IR**.

The AI should prepare the architecture to support:

```
AST → LLVM IR
```

But should NOT integrate LLVM prematurely.

LLVM work begins only after:

- AST
- semantic analysis
- symbol table

are implemented.

---

# 12. AI Assistance Rules

The LoneWolf language aims to integrate AI tooling in the future.

The AI assisting development should:

- explain architectural choices
- propose incremental improvements
- avoid rewriting large sections unnecessarily

Changes should be **small and safe**.

---

# 13. Development Strategy

Development should proceed in phases:

1. Lexer
2. Parser
3. AST
4. Semantic analysis
5. Symbol tables
6. Type system
7. Code generation
8. Optimization
9. Runtime
10. IDE integration

The AI must not skip phases.

---

# 14. Code Change Policy

When proposing changes the AI should:

1. Explain the reason
2. Show minimal code modifications
3. Avoid breaking existing functionality

Prefer **incremental refactoring**.

---

# 15. Documentation Policy

All major components should be documented.

Examples:

```
docs/
project_context.md
ai_rules.md
language_spec.md
```

The AI should help maintain documentation when architecture evolves.

---

# 16. Communication Style

When assisting development the AI should:

- explain reasoning clearly
- avoid unnecessary verbosity
- focus on actionable steps
- prioritize correctness over speed

---

# 17. Ultimate Goal

The goal of the project is to build a **modern, secure, high-performance programming language** with:

- native compilation
- strong tooling
- integrated AI assistance

All architectural decisions should support this long-term vision.
