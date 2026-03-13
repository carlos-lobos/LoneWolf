# LoneWolf Development Roadmap
Version: 0.1

This document defines the long-term development roadmap for the **LoneWolf programming language and compiler**.

The roadmap is designed for **incremental development**, prioritizing:

- stability
- clear milestones
- maintainable architecture
- gradual feature expansion

The project will evolve in multiple phases.

---

# Phase 0 — Project Foundation

Goal: establish the base repository and minimal compiler structure.

Tasks:

- create GitHub repository
- configure CMake build system
- create project directory structure
- implement initial compiler entry point
- implement basic Token system
- implement basic Lexer
- implement error handling system

Status:

```
COMPLETED
```

---

# Phase 1 — Lexer

Goal: fully implement lexical analysis.

The lexer converts raw source code into tokens.

Features to implement:

- identifiers
- numbers
- strings
- operators
- punctuation
- comments
- whitespace skipping
- keyword recognition
- error reporting

Example output:

```
IDENTIFIER(x)
ASSIGN(=)
NUMBER(10)
PLUS(+)
NUMBER(5)
SEMICOLON(;)
```

Status:

```
MOSTLY COMPLETE
```

Future improvements:

- floating point numbers
- hexadecimal numbers
- escape sequences in strings

Estimated effort:

```
1–2 days
```

---

# Phase 2 — Parser

Goal: transform tokens into an Abstract Syntax Tree.

The parser will use **Recursive Descent Parsing**.

Features:

- assignment parsing
- expression parsing
- operator precedence
- parentheses
- syntax error recovery

Example supported syntax:

```
x = 10 + 5;
y = x * 2;
```

Deliverables:

- Parser class
- AST node structure
- AST generation

Estimated effort:

```
3–5 days
```

---

# Phase 3 — AST System

Goal: define the internal structure representing programs.

AST node hierarchy example:

```
ASTNode
├─ Statement
│ └─ AssignmentStatement
└─ Expression
├─ BinaryExpression
├─ LiteralExpression
└─ IdentifierExpression
```

Responsibilities:

- represent program structure
- allow traversal
- support future code generation

Features:

- base ASTNode class
- expression nodes
- statement nodes

Estimated effort:

```
3–4 days
```

---

# Phase 4 — Semantic Analysis

Goal: validate program meaning.

Responsibilities:

- type checking
- variable existence validation
- scope rules
- symbol table creation

Example errors detected here:

```
undefined variable
invalid operation between types
duplicate variable definitions
```

Components:

- SymbolTable
- Scope management
- Type system basics

Estimated effort:

```
5–10 days
```

---

# Phase 5 — Type System

Goal: implement the core LoneWolf type system.

Initial supported types:

```
int
float
string
bool
```

Features:

- static typing
- optional type inference
- type compatibility checks

Example:

```
int x = 10;
string name = "Carlos";
```

Estimated effort:

```
5–7 days
```

---

# Phase 6 — LLVM Integration

Goal: generate LLVM IR from the AST.

Tasks:

- integrate LLVM libraries
- generate IR for expressions
- generate IR for variables
- generate IR for assignments

Example generated IR:

```
%1 = add i32 10, 5
store i32 %1, i32* %x
```

Benefits:

- platform-independent code generation
- automatic optimization
- native binary output

Estimated effort:

```
10–20 days
```

---

# Phase 7 — Control Flow

Goal: add fundamental programming constructs.

Features:

```
if
else
while
for
```

Example:

```
if (x > 10) {
    y = x * 2;
}
```

Estimated effort:

```
5–10 days
```

---

# Phase 8 — Functions

Goal: implement functions.

Features:

```
function definitions
parameters
return values
local scope
```

Example:

```
fn add(a, b) {
    return a + b;
}
```

Estimated effort:

```
5–8 days
```

---

# Phase 9 — Standard Library

Goal: provide core language utilities.

Modules may include:

```
io
math
string
system
```

Example:

```
print("Hello World");
```

Estimated effort:

```
5–10 days
```

---

# Phase 10 — Modules and Imports

Goal: support multi-file programs.

Example:

```
import math;
import system.io;
```

Features:

- module resolution
- compilation units
- dependency tracking

Estimated effort:

```
7–12 days
```

---

# Phase 11 — Optimization

Goal: improve performance.

Features:

- constant folding
- dead code elimination
- simple compiler optimizations
- leverage LLVM optimization passes

Estimated effort:

```
5–8 days
```

---

# Phase 12 — Language Expansion

Future features may include:

### Classes and OOP

```
class User {
    name;
    age;
}
```

### Functional programming

```
lambdas
immutability
higher-order functions
```

### Concurrency

```
async
parallel execution
```

Estimated effort:

```
ongoing
```

---

# Phase 13 — Tooling

Goal: create development tools.

Possible tools:

```
LoneWolf CLI
LoneWolf formatter
LoneWolf linter
LoneWolf package manager
```

Estimated effort:

```
20+ days
```

---

# Phase 14 — IDE

Goal: build a dedicated **LoneWolf IDE**.

Features:

- language server
- AI code assistant
- static analysis
- automatic refactoring
- integrated compiler

Estimated effort:

```
long term project
```

---

# Phase 15 — AI Integration

Future vision for LoneWolf:

AI-assisted features:

- automatic code refactoring
- vulnerability detection
- architecture suggestions
- automatic test generation
- code translation from other languages

Estimated effort:

```
long term
```

---

# Estimated Total Timeline (Solo Developer)

Approximate timeline if developed consistently:

```
Minimum viable compiler: 2–3 months
Usable programming language: 6–12 months
Full ecosystem: several years
```

---

# Development Strategy

The project should always follow these rules:

1. Build features incrementally
2. Avoid premature optimization
3. Keep compiler stages isolated
4. Maintain documentation
5. Prefer correctness over speed
