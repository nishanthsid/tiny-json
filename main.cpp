#include "tokenizer.hpp"
#include <iostream>

int main() {
    auto tok = Tokenizer::JsonOnDemandTokenizer("tt.json");

    Tokenizer::Token curr;
    int indent = 0;
    int index = 0;

    while ((curr = tok.getNextToken()).getTokenType() != Tokenizer::TokenType::END_OF_FILE) {

        auto type = curr.getTokenType();

        if (type == Tokenizer::TokenType::CLOSE_BRACE || 
            type == Tokenizer::TokenType::CLOSE_BRACK) {
            indent--;
        }

        for (int i = 0; i < indent; i++) std::cout << "  ";

        std::cout << "[" << index++ << "] ";

        switch(type) {
            case Tokenizer::TokenType::OPEN_BRACE:  std::cout << "OPEN_BRACE"; break;
            case Tokenizer::TokenType::CLOSE_BRACE: std::cout << "CLOSE_BRACE"; break;
            case Tokenizer::TokenType::OPEN_BRACK:  std::cout << "OPEN_BRACK"; break;
            case Tokenizer::TokenType::CLOSE_BRACK: std::cout << "CLOSE_BRACK"; break;
            case Tokenizer::TokenType::STRING:      std::cout << "STRING"; break;
            case Tokenizer::TokenType::NUMBER:      std::cout << "NUMBER"; break;
            case Tokenizer::TokenType::NULL_VAL:    std::cout << "NULL"; break;
            case Tokenizer::TokenType::BOOL:        std::cout << "BOOL"; break;
            case Tokenizer::TokenType::COMMA:       std::cout << "COMMA"; break;
            case Tokenizer::TokenType::COLON:       std::cout << "COLON"; break;
            default:                                std::cout << "UNKNOWN"; break;
        }

        std::cout << " -> \"" << curr.getRawTokenValue() << "\"" << std::endl;

        if (type == Tokenizer::TokenType::OPEN_BRACE || 
            type == Tokenizer::TokenType::OPEN_BRACK) {
            indent++;
        }
    }

    return 0;
}