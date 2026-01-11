#pragma once
#include "CHlexer.h"
#include "CHast.h"

class Parser {
    std::vector<Token> tokens;
    size_t pos = 0; // 현재 토큰 위치

    const Token& peek() const { return tokens[pos]; } // 현재 토큰 확인
    const Token& get() { return tokens[pos++]; } // 현재 토큰 소비하고 다음 토큰으로 이동

    // Expr --> Term --> Primary 순으로 파싱
    std::unique_ptr<Expr> parsePrimary() {
        try {
            if (this->peek().type == TokenType::Number) {
                int val = std::stoi(get().text); // 숫자형 문자열 토큰을 정수로 변환
                return std::make_unique<NumberExpr>(val); // 노드 동적 생성!
            }
            if (this->peek().type == TokenType::LParen) {
                get();  // '(' 토큰 소비
                auto expr = this->parseExpr();
                if (this->peek().type != TokenType::RParen) throw std::runtime_error("요거 어디감? ')'");
                get();
                return expr;
            }
        }
        catch (...) { throw std::runtime_error("숫자 or '('"); }
    }

    std::unique_ptr<Expr> parseTerm() { // *나 / 연산에 대한 파싱 처리기
        auto left = this->parsePrimary();
        while (this->peek().type == TokenType::Star || this->peek().type == TokenType::Slash) {
            char op = this->peek().text[0];
            get();
            auto right = this->parsePrimary();
            left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
        }
        return left;
    }

    std::unique_ptr<Expr> parseExpr() { // +나 - 연산에 대한 파싱 처리기
        auto left = this->parseTerm(); // 연산자 좌측 처리부터!
        while (this->peek().type == TokenType::Plus || this->peek().type == TokenType::Minus) {
            char op = this->peek().text[0];
            get();
            auto right = this->parseTerm();
            left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
        }
        return left;
    }

public: // api로 사용할 목적임ㅇㅇ
    Parser(std::vector<Token> toks) : tokens(std::move(toks)) {}
    std::unique_ptr<Expr> parse() { return parseExpr(); }
};
