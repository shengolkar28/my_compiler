#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"
#include <vector>
#include <memory>
#include <stdexcept>

namespace compiler {

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::unique_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens_;
    size_t current_;

    std::unique_ptr<ASTNode> expr();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> factor();
    const Token& peek() const;
    Token advance();
    bool check(TokenType type) const;
    Token consume(TokenType type, const std::string& message);
    bool isAtEnd() const;
    void error(const std::string& message) const;
};

}  // namespace compiler

#endif
