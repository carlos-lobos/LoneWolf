# LoneWolf Development Rules
Version: 0.1

This document defines the development rules for the **LoneWolf compiler project**.

The goal of these rules is to ensure the project remains:

- maintainable
- predictable
- consistent
- scalable

These rules apply to both **human contributors and AI assistants**.

---

# 1. General Principles

All development must prioritize:

1. Correctness
2. Simplicity
3. Readability
4. Maintainability
5. Predictable behavior

The compiler must **never sacrifice correctness for speed of development**.

---

# 2. Single Responsibility Rule

Every module must have **one clear responsibility**.

Examples:

Lexer → tokenization

Parser → grammar validation and AST generation

Semantic Analyzer → program meaning validation

Code Generator → machine code generation

Modules must not mix responsibilities.

---

# 3. Small Incremental Changes

Changes should be **small and incremental**.

Avoid:

- rewriting large sections of code
- introducing multiple new subsystems at once

Instead:

- implement one feature at a time
- verify correctness
- then continue

---

# 4. Project Structure

The repository should follow this structure.

```
include/
public headers

src/
implementation files

src/lexer/
src/parser/
src/ast/
src/semantic/
src/codegen/

docs/

examples/

tests/
```

New modules must follow the same pattern.

---

# 5. C++ Coding Style

The project uses **modern C++**.

Minimum standard:

```
C++17
```

Prefer:

- RAII
- smart pointers
- standard library containers

Avoid:

- raw memory management
- macros when unnecessary
- global state

---

# 6. Naming Conventions

### Classes

```
PascalCase
```

Example:

```
Lexer
Parser
ASTNode
SymbolTable
```

---

### Functions

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

### Variables

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

### Constants

```
UPPER_CASE
```

---

# 7. Header Rules

Header files must:

- declare interfaces
- avoid heavy logic
- minimize includes

Prefer:

```
forward declarations
```

when possible.

---

# 8. Source File Rules

Implementation files (`.cpp`) must contain:

- method definitions
- algorithm logic
- internal implementation details

---

# 9. Error Handling

Errors must be handled through the centralized system:

```
ErrorCollector
```

Never print errors directly from compiler components.

Avoid:

```
std::cout
std::cerr
```

inside compiler logic.

Instead:

```
errorCollector.addError(...)
```

---

# 10. Diagnostics

Compiler diagnostics must follow a consistent format.

Example:

```
file:line:column error: message
```

Example output:

```
test.lw:1:5 error: Expected ';'
```

Diagnostics should help the programmer **understand the problem quickly**.

---

# 11. Parser Design

The parser must use:

```
Recursive Descent Parsing
```

Do not introduce:

- parser generators
- external grammar tools
- automatic parser frameworks

The goal is **full control over the grammar**.

---

# 12. AST Design

The AST must be:

- strongly typed
- explicit
- easy to traverse

Example structure:

```
ASTNode
Statement
Expression
BinaryExpression
LiteralExpression
IdentifierExpression
```

Memory management must use:

```
std::unique_ptr
```

---

# 13. Testing

Every major feature should include tests.

Tests should be placed in:

```
tests/
```

Example:

```
tests/lexer_tests.lw
tests/parser_tests.lw
```

Testing should include:

- valid code
- invalid code
- edge cases

---

# 14. Example Programs

Examples should be placed in:

```
examples/
```

Examples help verify:

- language usability
- compiler behavior
- new language features

---

# 15. Documentation Updates

When adding a new feature, update:

```
language_spec.md
compiler_architecture.md
roadmap.md
```

Documentation must evolve with the code.

---

# 16. Commit Rules

Commits should be:

- small
- descriptive
- focused

Preferred commit message style:

```
lexer: add support for string literals
parser: implement assignment parsing
ast: introduce BinaryExpression node
```

Avoid vague commits like:

```
fix stuff
changes
update
```

---

# 17. Refactoring Policy

Refactoring should only occur when:

- code becomes difficult to maintain
- architecture must evolve
- performance issues are identified

Large refactors should be done **in isolated commits**.

---

# 18. Performance Rules

Performance improvements must never:

- break correctness
- reduce readability drastically

Optimization should happen mainly through:

```
LLVM optimization passes
```

---

# 19. AI Contribution Rules

AI assistants helping development should:

- follow this document
- follow ai_rules.md
- respect compiler architecture
- avoid unnecessary rewrites

AI suggestions must favor:

- minimal code changes
- safe improvements
- clear explanations

---

# 20. Long-Term Project Philosophy

The LoneWolf compiler must remain:

- deterministic
- understandable
- maintainable
- scalable

Even if the project grows large, a developer should still be able to **understand each component independently**.
