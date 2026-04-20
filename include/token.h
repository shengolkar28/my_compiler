#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

namespace compiler {

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    EOF_TOKEN
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value = "");

    std::string typeStr() const;
};

std::ostream& operator<<(std::ostream& os, const Token& token);

}  // namespace compiler

#endif
