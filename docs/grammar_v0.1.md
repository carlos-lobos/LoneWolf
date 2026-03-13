# LoneWolf Grammar Specification
Version: 0.1 (Draft)

This document defines the **formal grammar** of the LoneWolf programming language
using **Extended Backus–Naur Form (EBNF)**.

The grammar describes how LoneWolf programs are structured and provides the
foundation for the parser implementation.

This version focuses on the **minimal viable language syntax** used by the
current compiler implementation.

---

# 1. Notation

This grammar uses **EBNF notation**.

Symbols:

| Symbol | Meaning |
|------|------|
| `::=` | definition |
| `|` | alternative |
| `{ }` | repetition (0 or more) |
| `[ ]` | optional |
| `( )` | grouping |
| `"` | literal token |

Example:

```
A ::= B | C
```

means A can be either B or C.

---

# 2. Program Structure

A LoneWolf program is a sequence of statements.

```
program ::= { statement }
```

---

# 3. Statements

Statements represent executable units.

```
statement ::= assignment_statement
| expression_statement
```

---

# 4. Assignment

Assignment associates a value with a variable.

```
assignment_statement ::= IDENTIFIER "=" expression ";"
```

Example:

```
x = 10;
y = x + 5;
```

---

# 5. Expression Statements

Expressions can appear as standalone statements.

```
expression_statement ::= expression ";"
```

Example:

```
x + 5;
```

---

# 6. Expressions

Expressions represent values or computations.

```
expression ::= additive_expression
```

---

# 7. Additive Expressions

Addition and subtraction.

```
additive_expression ::= multiplicative_expression
{ ("+" | "-") multiplicative_expression }
```

Example:

```
10 + 5 - 2
```

---

# 8. Multiplicative Expressions

Multiplication and division.

```
multiplicative_expression ::= unary_expression
{ ("*" | "/") unary_expression }
```

Example:

```
10 * 5 / 2
```

---

# 9. Unary Expressions

Unary operators applied to values.

```
unary_expression ::= primary_expression
| ("+" | "-") unary_expression
```

Examples:

```
-10 +5
```

---

# 10. Primary Expressions

The most basic elements of expressions.

```
primary_expression ::= NUMBER
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

# 11. Identifiers

Identifiers represent variable names.

```
IDENTIFIER ::= letter { letter | digit | "_" }
```

Examples:

```
x
userName
_value
```

---

# 12. Numbers

Numeric literals.

Version 0.1 supports only integers.

```
NUMBER ::= digit { digit }
```

Examples:

```
10
42
1000
```

---

# 13. Strings

Strings represent sequences of characters.

```
STRING ::= '"' { character } '"'
```

Example:

```
"Hello World"
```

Future versions will support:

- escape sequences
- multiline strings

---

# 14. Comments

Comments are ignored by the lexer.

### Single-line comments

```
"//" { character } newline
```

Example:

```
x = 10; // comment
```

---

### Block comments

```
"/" { character } "/"
```

Example:

```
/*
multi-line comment
*/
```

---

# 15. Whitespace

Whitespace is ignored except as a separator.

Whitespace characters:

```
space
tab
newline
carriage return
```

---

# 16. Operator Precedence

Operator precedence from **highest to lowest**:

```
Parentheses ()

Unary operators + -

Multiplication * /

Addition + -
```

Example:

```
10 + 5 * 2
```

Evaluates as:

```
10 + (5 * 2)
```

---

# 17. Example Program

Example valid LoneWolf program:

```
x = 10;
y = 5;

z = x * y + 20;

message = "result";
```

---

# 18. Planned Grammar Extensions

Future versions of LoneWolf will extend the grammar.

Planned constructs include:

### Control flow

```
if_statement
while_statement
for_statement
```

Example:

```
if (x > 10) {
    y = x * 2;
}
```

---

### Functions


function_declaration ::= "fn" IDENTIFIER "(" parameters ")" block


Example:

```
fn add(a, b) {
    return a + b;
}
```

---

### Blocks

```
block ::= "{" { statement } "}"
```

---

### Classes

```
class_declaration ::= "class" IDENTIFIER block
```

---

# 19. Parser Implementation Strategy

The LoneWolf parser should implement this grammar using
**Recursive Descent Parsing**.

Typical parser functions:

```
parseProgram()
parseStatement()
parseExpression()
parseAdditiveExpression()
parseMultiplicativeExpression()
parseUnaryExpression()
parsePrimaryExpression()
```

Each function corresponds directly to a grammar rule.

---

# 20. Relationship with the Compiler

This grammar is the **contract between the language design and the parser implementation**.

If the grammar changes, the following must be updated:

- parser implementation
- language specification
- compiler tests
