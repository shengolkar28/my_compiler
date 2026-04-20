#include <iostream>
#include <string>
#include <stdexcept>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

using namespace compiler;

void printUsage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " \"expression\"\n";
    std::cerr << "Example: " << program_name << " \"3 + 5 * (2 - 1)\"\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string expression = argv[1];

    try {
        // Phase 1: Lexing (tokenization)
        Lexer lexer(expression);
        auto tokens = lexer.tokenize();

        // Optional: Print tokens for debugging
        // std::cout << "Tokens: ";
        // for (const auto& token : tokens) {
        //     std::cout << token << " ";
        // }
        // std::cout << "\n";

        // Phase 2: Parsing (building AST)
        Parser parser(tokens);
        auto ast = parser.parse();

        // Phase 3: Interpretation (evaluating AST)
        Interpreter interpreter;
        double result = interpreter.interpret(ast.get());

        // Output result
        std::cout << "Result: " << result << "\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
