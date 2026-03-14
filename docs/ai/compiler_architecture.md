# LoneWolf Compiler Architecture

Version: 0.1 (Draft)

This document defines the internal architecture of the **LoneWolf compiler**.

Its purpose is to ensure that the compiler remains:

- modular
- maintainable
- scalable
- predictable

This architecture is intentionally similar to modern compilers such as:

- LLVM-based compilers
- Rust compiler
- Go compiler
- Clang

The compiler will follow a **multi-stage pipeline architecture**.

---

# 1. High-Level Compilation Pipeline

The LoneWolf compiler processes source code in sequential stages.

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
Intermediate Representation (LLVM IR)
↓
Code Generation
↓
Native Binary
```

Each stage must have **clear responsibilities** and must not leak responsibilities into other stages.

---

# 2. Compiler Frontend vs Backend

The compiler is divided into two major components.

### Frontend

Responsible for understanding the language.

```
Lexer
Parser
AST
Semantic Analysis
```

The frontend transforms **source code → structured representation**.

---

### Backend

Responsible for generating executable code.

```
LLVM IR Generation
Optimization
Native Code Generation
```

---

# 3. Source Input Stage

Input to the compiler is a source file:

```
example.lw
```

The compiler reads the file and sends its contents to the **Lexer**.

Future improvements may include:

- multi-file compilation
- module system
- package management

---

# 4. Lexer (Lexical Analysis)

The lexer transforms a stream of characters into **tokens**.

Example input:

```
x = 10 + 5;
```

Output tokens:

```
IDENTIFIER(x)
ASSIGN(=)
NUMBER(10)
PLUS(+)
NUMBER(5)
SEMICOLON(;)
```

Responsibilities:

- character scanning
- token creation
- whitespace skipping
- comment skipping
- basic literal recognition
- lexical error reporting

The lexer must **not understand grammar or syntax**.

---

# 5. Parser (Syntax Analysis)

The parser consumes tokens and builds a structured **Abstract Syntax Tree (AST)**.

Example tokens:

```
x = 10 + 5;
```

AST representation:

```
Assignment
├─ Identifier(x)
└─ BinaryExpression(+)
├─ Number(10)
└─ Number(5)
```

Parser responsibilities:

- grammar validation
- AST creation
- syntax error detection
- operator precedence handling

The parser should use **Recursive Descent Parsing**.

Parser must not perform:

- type checking
- symbol resolution
- code generation

---

# 6. Abstract Syntax Tree (AST)

The AST represents the structured meaning of the program.

AST nodes represent language constructs.

Examples:

```
ASTNode
Statement
Expression
BinaryExpression
LiteralExpression
IdentifierExpression
AssignmentStatement
```

The AST should be implemented using **class hierarchies**.

Example concept:

```
ASTNode
├── Statement
└── Expression
```

Memory management should use:

```
std::unique_ptr
```

---

# 7. Semantic Analysis

Semantic analysis validates the **meaning** of the program.

Responsibilities:

- type checking
- variable declaration validation
- symbol resolution
- scope management
- function resolution

Example errors detected here:

```
use of undefined variable
type mismatch
invalid operations
```

This stage builds and uses **symbol tables**.

---

# 8. Symbol Table

The symbol table tracks identifiers in the program.

Examples:

```
variables
functions
types
classes
```

Symbol tables must support:

- nested scopes
- shadowing
- module boundaries

Example structure:

```
Global Scope
├─ x : int
├─ y : int
└─ add() : function
```

---

# 9. Intermediate Representation (IR)

After semantic analysis, the compiler converts the AST into an intermediate representation.

The LoneWolf compiler will use:

```
LLVM IR
```

LLVM IR provides:

- portability
- optimization
- cross-platform compilation

Example (conceptual):

```
%1 = add i32 10, 5
store i32 %1, i32* %x
```

---

# 10. Optimization Stage

LLVM performs optimizations such as:

```
constant folding
dead code elimination
loop optimization
inline expansion
```

This stage improves performance automatically.

---

# 11. Code Generation

LLVM generates native machine code for the target platform.

Examples:

```
x86_64
ARM
RISC-V
```

The result is a **native executable binary**.

Example output:

```
program
program.exe
```

---

# 12. Error Handling System

The compiler uses a centralized error system.

```
ErrorCollector
```

Responsibilities:

- collect errors from all stages
- avoid immediate termination
- allow multiple errors per compilation

Example:

```
file:line:column error: message
```

---

# 13. File Structure

Recommended repository structure:

```
include/
lexer/
parser/
ast/
semantic/
codegen/

src/
   lexer/
   parser/
   ast/
   semantic/
   codegen/

docs/

examples/

tests/
```

---

# 14. Current Implementation Status

Current progress of the LoneWolf compiler:

```
Lexer implemented
Parser in progress
AST not implemented
Semantic not implemented
LLVM integration not implemented
```

---

# 15. Future Compiler Features

Planned improvements include:

### Module system

```
import math;
import system.io;
```

---

### Package manager

Similar to:

```
cargo
npm
go modules
```

---

### Incremental compilation

Compile only modified modules.

---

### IDE integration

Future LoneWolf IDE will include:

- integrated compiler
- AI code assistant
- static analysis
- automatic refactoring

---

# 16. AI Integration Vision

LoneWolf aims to integrate AI into development workflows.

AI-assisted capabilities may include:

- automatic refactoring
- vulnerability detection
- architecture suggestions
- code translation from other languages

The compiler architecture must remain **AI-friendly**, meaning:

- clear AST
- deterministic grammar
- strong diagnostics

---

# 17. Design Philosophy

The compiler must remain:

- deterministic
- modular
- predictable
- maintainable

Every component must have **one clear responsibility**.

This prevents long-term architectural decay.