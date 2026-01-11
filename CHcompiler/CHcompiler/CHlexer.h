#pragma once
#include <string>
#include <vector>
#include <cctype>

enum class TokenType { Number, Plus, Minus, Star, Slash, LParen, RParen, End };

// 토큰 구조체
struct Token {
    TokenType type; // 해당 토큰의 타입
	std::string text; // 토큰의 실제 문자열
};

class Lexer {
	std::string input; // 입력 문자열
	size_t pos = 0; // 현재 입력 문자열에서의 위치
public:
    Lexer(const std::string& src) : input(src) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;

        while (pos < input.size()) {
            char c = input[pos];

            // 공백 문자
            if (std::isspace(c)) { pos++; continue; }
            // 숫자 
            if (std::isdigit(c)) {
                std::string num;
                while (pos < input.size() && std::isdigit(input[pos])) {
                    num += input[pos++];
                } // num 문자열에 append 시켜버리자
                tokens.push_back({ TokenType::Number, num }); // TokenType, text 초기화
                continue;
            }

            // 연산자 or 괄호 
            switch (c) { // C++ switch문은 각 조건에 break;가 필수임ㄷㄷㄷ
            case '+': tokens.push_back({ TokenType::Plus, "+" }); break;
            case '-': tokens.push_back({ TokenType::Minus, "-" }); break;
            case '*': tokens.push_back({ TokenType::Star, "*" }); break;
            case '/': tokens.push_back({ TokenType::Slash, "/" }); break;
            case '(': tokens.push_back({ TokenType::LParen, "(" }); break;
            case ')': tokens.push_back({ TokenType::RParen, ")" }); break;
            }
            pos++; // 다음 pos로 이동
        }

        // EOF 역할 토큰 추가
        tokens.push_back({ TokenType::End, "" });
        return tokens;
    }
};
