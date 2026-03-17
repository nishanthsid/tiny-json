#pragma once
#include "file_utils.hpp"

namespace Tokenizer{
    enum class TokenType{
        OPEN_BRACE,
        CLOSE_BRACE,
        OPEN_BRACK,
        CLOSE_BRACK,
        STRING,
        NUMBER,
        NULL_VAL,
        BOOL,
        COMMA,
        COLON,
        END_OF_FILE
    };

    class Token{
        private:
            TokenType tokenType;
            std::string rawTokenValue;
        public:
            Token(std::string tokenValue, TokenType type) : tokenType(type), rawTokenValue(tokenValue){}
            Token(){}
            TokenType getTokenType() const{
                return tokenType;
            }
            std::string getRawTokenValue() const{
                return rawTokenValue;
            }
    };

    class JsonOnDemandTokenizer{
        private:
            enum class TokenizerContext{
                NORMAL,
                NUMBER,
                STRING
            };
            FileUtils::InpFileReader reader;
            Token peek;
            Token processNextToken();
            bool shouldConsume = true;
            std::string buffer;
            TokenizerContext cntx = TokenizerContext::NORMAL;
            bool isEscape = false;
            char unProcessed;
            bool unProcessedCharPresent = false;

        public:
            JsonOnDemandTokenizer(std::string fileName) : reader(fileName) {}
            Token peekNextToken();
            Token getNextToken();
    };
}