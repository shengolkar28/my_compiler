#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>
#include <memory>

namespace compiler {

class Lexer {
public:
    explicit Lexer(const std::string& input);

    std::vector<Token> tokenize();

private:
    std::string input_;
    size_t pos_;

    char peek() const;
    char advance();
    void skipWhitespace();
    Token readNumber();
    bool isAtEnd() const;
    static bool isDigit(char ch);
    static bool isWhitespace(char ch);
};

}  // namespace compiler

#endif  // LEXER_H
