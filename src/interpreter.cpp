#include "interpreter.h"
#include <stdexcept>
#include <cmath>

namespace compiler {

double Interpreter::interpret(ASTNode* root) {
    if (!root) {
        throw std::runtime_error("Cannot interpret null AST");
    }
    return root->accept(this);
}

double Interpreter::visit(NumNode* node) {
    return node->value();
}

double Interpreter::visit(BinOpNode* node) {
    double left = node->left()->accept(this);
    double right = node->right()->accept(this);
    return applyOp(node->op(), left, right);
}

double Interpreter::applyOp(char op, double left, double right) const {
    switch (op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (std::abs(right) < 1e-9) {
                throw std::runtime_error("Division by zero");
            }
            return left / right;
        default:
            throw std::runtime_error(std::string("Unknown operator: ") + op);
    }
}

}  // namespace compiler
