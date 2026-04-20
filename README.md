# Toy Compiler - Arithmetic Expression Evaluator

A clean, educational compiler implementation demonstrating fundamental compiler design principles. This project implements a minimal "compiler" that lexes, parses, and interprets arithmetic expressions.

## Overview

This project serves as an interview-grade systems software project showcasing:

- **Compiler Architecture**: Classic three-phase pipeline (lexing → parsing → interpretation)
- **Modern C++17**: Smart pointers, RAII, proper encapsulation
- **Design Patterns**: Visitor pattern for AST traversal
- **Software Design**: Modular architecture with clear separation of concerns
- **Recursion**: Recursive descent parser with proper precedence handling

### Core Features

- **Arithmetic operators**: `+`, `-`, `*`, `/`
- **Parentheses**: Full support for grouping expressions
- **Operator precedence**: `*` and `/` bind tighter than `+` and `-`
- **Error handling**: Comprehensive exception handling with meaningful error messages
- **Clean architecture**: Interview-quality code suitable for systems engineering roles

---

## Project Structure

```
toy-compiler/
├── src/                    # Implementation files
│   ├── main.cpp           # Entry point and CLI
│   ├── lexer.cpp          # Tokenization implementation
│   ├── parser.cpp         # Parsing implementation
│   ├── interpreter.cpp    # Evaluation implementation
│   ├── ast.cpp            # AST node implementations
│   └── token.cpp          # Token class implementation
├── include/               # Header files
│   ├── token.h            # Token and TokenType definitions
│   ├── lexer.h            # Lexer interface
│   ├── parser.h           # Parser interface
│   ├── interpreter.h      # Interpreter interface
│   └── ast.h              # AST node and visitor interfaces
├── examples/
│   └── sample_inputs.txt  # Example expressions
├── Makefile               # Build configuration
├── README.md              # This file
└── .gitignore             # Git ignore rules
```

---

## Compiler Architecture

This project implements a classic three-phase compiler pipeline:

### Phase 1: Lexical Analysis (Lexer)

**File**: [src/lexer.cpp](src/lexer.cpp), [include/lexer.h](include/lexer.h)

The lexer performs **tokenization**: converting a stream of characters into a stream of meaningful tokens.

**Process**:
1. Iterate through input characters
2. Skip whitespace
3. Recognize tokens:
   - Multi-digit numbers
   - Operators: `+`, `-`, `*`, `/`
   - Parentheses: `(`, `)`
4. Output: `std::vector<Token>` with sentinel EOF token

**Example**:
```
Input:  "3 + 5 * 2"
Output: [NUMBER(3), PLUS, NUMBER(5), MULTIPLY, NUMBER(2), EOF]
```

### Phase 2: Syntax Analysis (Parser)

**File**: [src/parser.cpp](src/parser.cpp), [include/parser.h](include/parser.h)

The parser performs **parsing**: converting a token stream into an Abstract Syntax Tree (AST).

**Grammar** (Recursive Descent):
```
expr   : term (('+' | '-') term)*
term   : factor (('*' | '/') factor)*
factor : NUMBER | '(' expr ')'
```

**Key Points**:
- **Recursive descent**: Each grammar rule is a recursive function
- **Operator precedence**: Handled implicitly by grammar structure
  - `expr` handles `+` and `-` (lowest precedence)
  - `term` handles `*` and `/` (higher precedence)
  - `factor` handles literals and grouping (highest precedence)
- **Left associativity**: Ensured by iteration (`while` loops)

**Example**:
```
Input:  [NUMBER(3), PLUS, NUMBER(5), MULTIPLY, NUMBER(2), EOF]

AST:              +
                 / \
                3   *
                   / \
                  5   2
```

### Phase 3: Interpretation (Evaluator)

**File**: [src/interpreter.cpp](src/interpreter.cpp), [include/interpreter.h](include/interpreter.h)

The interpreter performs **evaluation**: recursively traversing the AST and computing the result.

**Pattern**: Visitor pattern for clean AST traversal

**Process**:
1. Traverse AST using post-order (depth-first)
2. For leaf nodes (numbers): return value
3. For internal nodes (operations): recursively evaluate children, then apply operator
4. Handle errors: division by zero, invalid operations

**Example**:
```
AST:              +
                 / \
                3   *
                   / \
                  5   2

Evaluation:
- visit(5) → 5
- visit(2) → 2
- visit(*): 5 * 2 = 10
- visit(3) → 3
- visit(+): 3 + 10 = 13
Result: 13
```

---

## Key Design Decisions

### 1. **Recursive Descent Parser**

Why chosen:
- Simple, intuitive, and easy to understand (ideal for interviews)
- Grammar directly maps to code
- Handles operator precedence naturally
- Sufficient for expression parsing

Alternatives considered:
- LL(k) parser: more formal, requires parser generator
- LR parser: more powerful but overkill for this use case

### 2. **Visitor Pattern for AST Traversal**

Why chosen:
- Separates traversal logic from AST structure
- Easy to add new operations (e.g., pretty-printing, optimization passes)
- Standard pattern in compiler design

```cpp
class ASTVisitor {
    virtual double visit(NumNode* node) = 0;
    virtual double visit(BinOpNode* node) = 0;
};

class Interpreter : public ASTVisitor {
    double visit(NumNode* node) override;
    double visit(BinOpNode* node) override;
};
```

### 3. **Smart Pointers (std::unique_ptr)**

Why chosen:
- Automatic memory management (RAII)
- Clear ownership semantics
- Modern C++ best practice
- No memory leaks or dangling pointers

### 4. **Namespace Encapsulation**

All components are in the `compiler` namespace to avoid global namespace pollution and improve code organization.

---

## Build & Execution

### Requirements

- **C++17 compatible compiler** (g++, clang, MSVC)
- **Make** (or manual compilation with your compiler)

### Building

```bash
# Compile the project
make

# Run with an example expression
make run

# Run comprehensive tests
make test

# Clean build artifacts
make clean
```

### Manual Compilation (if Make not available)

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude -o toy-compiler \
    src/main.cpp src/lexer.cpp src/parser.cpp \
    src/interpreter.cpp src/ast.cpp src/token.cpp
```

### Running the Program

```bash
# Evaluate an expression
./toy-compiler "3 + 5 * 2"
# Output: Result: 13

# More complex example
./toy-compiler "(10 + 2) * 3"
# Output: Result: 36

# Division example
./toy-compiler "20 / (2 + 3)"
# Output: Result: 4
```

---

## Example Expressions

From [examples/sample_inputs.txt](examples/sample_inputs.txt):

| Expression | Expected Result |
|-----------|-----------------|
| `3 + 5 * 2` | 13 |
| `(10 + 2) * 3` | 36 |
| `100 / 5 - 3` | 17 |
| `(20 - 5) / (3 + 2)` | 3 |
| `2 * 3 * 4` | 24 |
| `15 - 3 - 2` | 10 |
| `(100 + 50) * (2 - 1)` | 150 |

---

## Error Handling

The compiler provides clear, actionable error messages:

```bash
./toy-compiler "3 + "
# Error: Parse error: Expected number or '('

./toy-compiler "10 / 0"
# Error: Division by zero

./toy-compiler "3 + + 5"
# Error: Parse error: Expected number or '('
```

---

## Code Quality Highlights

### Modern C++ Features Used

- **std::unique_ptr**: Automatic memory management
- **std::make_unique**: Safe pointer creation
- **Override keyword**: Explicit virtual function overrides
- **Namespaces**: Proper code organization
- **Header guards**: Protection against multiple inclusion

### Best Practices

- **No global variables**: All state is properly encapsulated
- **No "using namespace std"**: Explicit namespace usage
- **RAII**: Resources managed via constructors/destructors
- **Exception safety**: Proper error handling
- **Clear naming**: Intent is obvious from names
- **Documentation**: Comments explain non-obvious code

---

## Interview-Readiness

This codebase demonstrates understanding of:

1. **Compiler fundamentals**: Lexing, parsing, interpretation
2. **Data structures**: Token streams, AST, visitor pattern
3. **Algorithms**: Recursive descent parsing, tree traversal
4. **Modern C++**: Smart pointers, RAII, proper design
5. **Software architecture**: Modular design, clear separation of concerns
6. **Error handling**: Exception safety, meaningful error messages

Suitable for roles such as:
- Systems software engineer
- Compiler engineer (NVIDIA PTX, LLVM, etc.)
- Language runtime engineer
- Performance engineer

---

## Future Improvements

### Language Features

- **Unary operators**: Support `-`, `+` prefix operators
- **Floating-point precision**: Configurable decimal support
- **Power operator**: `^` for exponentiation
- **Modulo operator**: `%` for remainder
- **Variables**: Symbol table for variable binding
- **Functions**: Support for predefined functions (sin, cos, sqrt, etc.)

### Implementation Enhancements

- **Optimization passes**: Constant folding, dead code elimination
- **Code generation**: Bytecode or machine code generation
- **Multiple phases**: Separate optimization passes
- **Pretty-printing**: AST visualization for debugging
- **Performance profiling**: Benchmark and optimize hot paths

### Testing

- **Unit tests**: For each component (Lexer, Parser, Interpreter)
- **Integration tests**: End-to-end expression evaluation
- **Fuzzing**: Random expression generation for robustness
- **Benchmarking**: Performance metrics

### Developer Experience

- **REPL mode**: Interactive expression evaluation
- **Debug mode**: Print tokens, AST structure
- **Custom input**: Interactive prompt for expressions

---

## References

### Compiler Theory

- Crafting Interpreters (https://craftinginterpreters.com/)
- Engineering a Compiler by Cooper & Torczon
- Compilers: Principles, Techniques, and Tools ("The Dragon Book")

### Design Patterns

- Visitor Pattern: Classic OOP pattern for tree traversal
- Recursive Descent Parsing: Foundational parsing technique

---

## License

This project is provided as-is for educational and interview preparation purposes.

---

## Author Notes

This toy compiler is designed as a teaching and interview tool. It demonstrates mastery of:

- Compiler pipeline architecture
- Recursive descent parsing
- AST-based interpretation
- Modern C++ practices
- Clean code principles

The code prioritizes clarity and correctness over performance, making it ideal for understanding compiler internals and systems software design.
