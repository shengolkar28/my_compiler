#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <memory>

namespace compiler {

class Interpreter : public ASTVisitor {
public:
    Interpreter() = default;

    double interpret(ASTNode* root);
    double visit(NumNode* node) override;
    double visit(BinOpNode* node) override;

private:
    double applyOp(char op, double left, double right) const;
};

}  // namespace compiler

#endif
