#include "ast.h"

namespace compiler {

NumNode::NumNode(double value) : value_(value) {}

double NumNode::accept(ASTVisitor* visitor) {
    return visitor->visit(this);
}

BinOpNode::BinOpNode(std::unique_ptr<ASTNode> left, char op,
                     std::unique_ptr<ASTNode> right)
    : left_(std::move(left)), op_(op), right_(std::move(right)) {}

double BinOpNode::accept(ASTVisitor* visitor) {
    return visitor->visit(this);
}

}  // namespace compiler
