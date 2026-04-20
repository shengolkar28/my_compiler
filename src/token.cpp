#include "token.h"

namespace compiler {

Token::Token(TokenType type, const std::string& value)
    : type(type), value(value) {}

std::string Token::typeStr() const {
    switch (type) {
        case TokenType::NUMBER:
            return "NUMBER";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::DIVIDE:
            return "DIVIDE";
        case TokenType::LPAREN:
            return "LPAREN";
        case TokenType::RPAREN:
            return "RPAREN";
        case TokenType::EOF_TOKEN:
            return "EOF";
        default:
            return "UNKNOWN";
    }
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Token(" << token.typeStr();
    if (!token.value.empty()) {
        os << ", " << token.value;
    }
    os << ")";
    return os;
}

}  // namespace compiler
