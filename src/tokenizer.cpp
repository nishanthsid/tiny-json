#include "tokenizer.hpp"
#include "numbers.hpp"

Tokenizer::Token Tokenizer::JsonOnDemandTokenizer::peekNextToken(){
    if(shouldConsume){
        peek = processNextToken();
        shouldConsume = false;
    }
    return peek;
}

Tokenizer::Token Tokenizer::JsonOnDemandTokenizer::getNextToken(){
    if(!shouldConsume){
        shouldConsume = true;
        return peek;   
    }
    return processNextToken();
}

Tokenizer::Token Tokenizer::JsonOnDemandTokenizer::processNextToken(){
    while (true) {
        char nextChar = 0;
        if(!unProcessedCharPresent){
            nextChar = reader.nextChar();
        }
        else{
            nextChar = unProcessed;
            unProcessedCharPresent = false;
        }
        if (reader.isEof()) {
            return Token("$", TokenType::END_OF_FILE);
        }
        switch (cntx) {
            case TokenizerContext::NORMAL: {
                switch (nextChar) {
                    case '{': return Token("{", TokenType::OPEN_BRACE);
                    case '[': return Token("[", TokenType::OPEN_BRACK);
                    case ']': return Token("]", TokenType::CLOSE_BRACK);
                    case '}': return Token("}", TokenType::CLOSE_BRACE);
                    case ':': return Token(":", TokenType::COLON);
                    case ',': return Token(",", TokenType::COMMA);

                    case ' ':
                    case '\n':
                    case '\r':
                    case '\t': {
                        break;
                    }

                    case '\"': {
                        cntx = TokenizerContext::STRING;
                        buffer.clear();
                        break;
                    }

                    case '-': case '0': case '1': case '2': case '3':
                    case '4': case '5': case '6': case '7': case '8': case '9': {
                        cntx = TokenizerContext::NUMBER;
                        buffer.clear();
                        buffer += nextChar;
                        break;
                    }

                    default: {
                        if (!isalpha(nextChar))
                            throw std::runtime_error(std::string("Invalid character in JSON: ") + nextChar);

                        buffer += nextChar;
                        if (buffer == "null") {
                            buffer.clear();
                            return Token("null", TokenType::NULL_VAL);
                        }
                        if (buffer == "true") {
                            buffer.clear();
                            return Token("true", TokenType::BOOL);
                        }
                        if (buffer == "false") {
                            buffer.clear();
                            return Token("false", TokenType::BOOL);
                        }
                        if (buffer.size() > 5)
                            throw std::runtime_error(std::string("Invalid literal while parsing: ") + buffer);
                        break;
                    }
                }
                break;
            }

            case TokenizerContext::STRING: {
                switch (nextChar) {
                    case '\\': {
                        isEscape = !isEscape;
                        buffer += '\\';
                        break;
                    }
                    case '\"': {
                        if (!isEscape) {
                            cntx = TokenizerContext::NORMAL;
                            std::string val = buffer;
                            buffer.clear();
                            return Token(val, TokenType::STRING);
                        } else {
                            buffer += '\"';
                            isEscape = false;
                        }
                        break;
                    }
                    default: {
                        buffer += nextChar;
                        isEscape = false;
                        break;
                    }
                }
                break;
            }

            case TokenizerContext::NUMBER: {
                if (isdigit(nextChar) || nextChar == '.' || nextChar == 'e' || nextChar == 'E' ||
                    nextChar == '+' || nextChar == '-') {
                    buffer += nextChar;
                } else {
                    if(!RealNumber::Validator::isRealNum(buffer)){
                        throw std::runtime_error(std::string("Invalid number format: ") + buffer);
                    }
                    std::string val = buffer;
                    buffer.clear();
                    cntx = TokenizerContext::NORMAL;
                    
                    unProcessed = nextChar;
                    unProcessedCharPresent = true;

                    return Token(val, TokenType::NUMBER);
                }
                break;
            }
        }
    }

    return Token("$", TokenType::END_OF_FILE);
}