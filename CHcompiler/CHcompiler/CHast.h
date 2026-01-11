#pragma once
#include <memory>
#include <algorithm>
#include <utility>

struct Expr {
    virtual int eval() const = 0; // 상속을 위한 가상 함수, interface 역할
	virtual ~Expr() {}; // 상속 시 소멸자 호출을 위해 가상 소멸자 선언!
};

struct NumberExpr : Expr {
    int value; // 숫자 필드
    NumberExpr(int v) : value(v) {} // 생성자
    int eval() const override { return value; }
};

struct BinaryExpr : Expr {
    char op; // 연산자 필드
	std::unique_ptr<Expr> left, right; // 좌우 피연산자 필드
	// 트리 구조 내 BinaryExpr 노드가 left, right Expr 노드를 소유하도록 unique_ptr 사용!!
    BinaryExpr(char op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), left(std::move(l)), right(std::move(r)) {} // 생성자

    int eval() const override {
		// left나 right나 각자 타입에 맞춰 오버라이드된 eval() 호출됨!!
        try {
            switch (op) {
                // 각 연산자를 만나면 좌-우로 나눠서 연산!
            case '+': return left->eval() + right->eval();
            case '-': return left->eval() - right->eval();
            case '*': return left->eval() * right->eval();
            case '/': return left->eval() / right->eval();
            default: throw std::runtime_error("Unknown operator"); // 혹시 모를 연산자 예외처리
            }
        }
        catch (const std::runtime_error& e) {
            // 예외 발생 시 메시지 출력 후 프로그램 종료
            std::cerr << "Error: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
};
