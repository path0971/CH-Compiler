#include <iostream>
#include "CHparser.h"


using namespace std;

int main() {

    try {
        std::string input;
        std::cout << "식을 짜내봐라: ";
        std::getline(std::cin, input);

        Lexer lexer(input);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto expr = parser.parse();

        std::cout << "결과 = " << expr->eval() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
	}   
    return 0;
}
