#ifndef AST_H
#define AST_H

#include <memory>
#include <string>

namespace compiler {

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual double accept(class ASTVisitor* visitor) = 0;
};

class NumNode : public ASTNode {
public:
    explicit NumNode(double value);
    double accept(class ASTVisitor* visitor) override;

    double value() const { return value_; }

private:
    double value_;
};

class BinOpNode : public ASTNode {
public:
    BinOpNode(std::unique_ptr<ASTNode> left, char op,
              std::unique_ptr<ASTNode> right);

    double accept(class ASTVisitor* visitor) override;

    ASTNode* left() const { return left_.get(); }
    ASTNode* right() const { return right_.get(); }
    char op() const { return op_; }

private:
    std::unique_ptr<ASTNode> left_;
    char op_;
    std::unique_ptr<ASTNode> right_;
};

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
    virtual double visit(NumNode* node) = 0;
    virtual double visit(BinOpNode* node) = 0;
};

}  // namespace compiler

#endif
