#include "lexer.h"
#include <cctype>
#include <stdexcept>

namespace compiler {

Lexer::Lexer(const std::string& input)
    : input_(input), pos_(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();

        if (isAtEnd()) {
            break;
        }

        char ch = peek();

        if (isDigit(ch)) {
            tokens.push_back(readNumber());
        } else if (ch == '+') {
            tokens.push_back(Token(TokenType::PLUS, "+"));
            advance();
        } else if (ch == '-') {
            tokens.push_back(Token(TokenType::MINUS, "-"));
            advance();
        } else if (ch == '*') {
            tokens.push_back(Token(TokenType::MULTIPLY, "*"));
            advance();
        } else if (ch == '/') {
            tokens.push_back(Token(TokenType::DIVIDE, "/"));
            advance();
        } else if (ch == '(') {
            tokens.push_back(Token(TokenType::LPAREN, "("));
            advance();
        } else if (ch == ')') {
            tokens.push_back(Token(TokenType::RPAREN, ")"));
            advance();
        } else {
            throw std::runtime_error(std::string("Unexpected character: ") + ch);
        }
    }

    tokens.push_back(Token(TokenType::EOF_TOKEN));
    return tokens;
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }
    return input_[pos_];
}

char Lexer::advance() {
    if (isAtEnd()) {
        return '\0';
    }
    return input_[pos_++];
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && isWhitespace(peek())) {
        advance();
    }
}

Token Lexer::readNumber() {
    std::string number;

    while (!isAtEnd() && isDigit(peek())) {
        number += advance();
    }

    return Token(TokenType::NUMBER, number);
}

bool Lexer::isAtEnd() const {
    return pos_ >= input_.length();
}

bool Lexer::isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool Lexer::isWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

}  // namespace compiler
