#include "parser.h"

namespace compiler {

Parser::Parser(const std::vector<Token>& tokens)
    : tokens_(tokens), current_(0) {}

std::unique_ptr<ASTNode> Parser::parse() {
    auto result = expr();
    
    // Ensure we've consumed all tokens (except EOF)
    if (!isAtEnd()) {
        error("Unexpected tokens after expression");
    }
    
    return result;
}

std::unique_ptr<ASTNode> Parser::expr() {
    auto node = term();

    while (check(TokenType::PLUS) || check(TokenType::MINUS)) {
        Token op_token = advance();
        auto right = term();
        node = std::make_unique<BinOpNode>(std::move(node), op_token.value[0],
                                           std::move(right));
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::term() {
    auto node = factor();

    while (check(TokenType::MULTIPLY) || check(TokenType::DIVIDE)) {
        Token op_token = advance();
        auto right = factor();
        node = std::make_unique<BinOpNode>(std::move(node), op_token.value[0],
                                           std::move(right));
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::factor() {
    if (check(TokenType::NUMBER)) {
        Token num_token = advance();
        double value = std::stod(num_token.value);
        return std::make_unique<NumNode>(value);
    }

    if (check(TokenType::LPAREN)) {
        advance();  // consume '('
        auto node = expr();
        consume(TokenType::RPAREN, "Expected ')' after expression");
        return node;
    }

    error("Expected number or '('");
    return nullptr;  // Unreachable, but silences warnings
}

const Token& Parser::peek() const {
    if (current_ >= tokens_.size()) {
        throw std::runtime_error("Attempted to peek beyond token stream");
    }
    return tokens_[current_];
}

Token Parser::advance() {
    if (isAtEnd()) {
        error("Unexpected end of input");
    }
    return tokens_[current_++];
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) {
        return false;
    }
    return peek().type == type;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return advance();
    }
    error(message);
    return Token(TokenType::EOF_TOKEN);  // Unreachable
}

bool Parser::isAtEnd() const {
    return current_ >= tokens_.size() || peek().type == TokenType::EOF_TOKEN;
}

void Parser::error(const std::string& message) const {
    throw std::runtime_error("Parse error: " + message);
}

}  // namespace compiler
