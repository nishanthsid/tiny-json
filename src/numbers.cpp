#include "numbers.hpp"
#include <string>

bool RealNumber::Validator::isDigit(char ch){
    return ch >= '0' && ch <= '9';
}

bool RealNumber::Validator::isRealNum(std::string& num){
    int index = 0;
    char ch;
    NumberParserContext cntx = NumberParserContext::START;
    int len = num.length();
    while(index <= len){
        if(index == len){
            ch = '$';
        }
        else{
            ch = num[index];
        }

        switch(cntx){
            case NumberParserContext::START:{
                if(ch == '+' || ch == '-'){
                    cntx = NumberParserContext::SIGN;
                    index += 1;
                }
                else if(ch == '.'){
                    index += 1;
                    cntx = NumberParserContext::A;
                }
                else if(isDigit(ch)){
                    index += 1;
                    cntx = NumberParserContext::C;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::SIGN:{
                if(isDigit(ch)){
                    index += 1;
                    cntx = NumberParserContext::C;
                }
                else if(ch == '.'){
                    index += 1;
                    cntx = NumberParserContext::A;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::A:{
                if(isDigit(ch)){
                    index += 1;
                    cntx = NumberParserContext::B;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::C:{
                if(isDigit(ch)){
                    index += 1;
                }
                else if(ch == '.'){
                    index += 1;
                    cntx = NumberParserContext::D;
                }
                else if(ch == '$'){
                    return true;
                }
                else if(ch == 'e' || ch == 'E'){
                    index += 1;
                    cntx = NumberParserContext::E;
                }
                else{
                    return false;
                }
                break;
            }

            case NumberParserContext::B:{
                if(ch == '$'){
                    return true;
                }
                else if(isDigit(ch)){
                    index += 1;
                }
                else if(ch == 'e' || ch == 'E'){
                    index += 1;
                    cntx = NumberParserContext::E;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::D:{
                if(ch == '$'){
                    return true;
                }
                else if(isDigit(ch)){
                    index += 1;
                }
                else if(ch == 'E' || ch == 'e'){
                    index += 1;
                    cntx = NumberParserContext::E;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::E:{
                if(ch == '+' || ch == '-'){
                    index += 1;
                    cntx = NumberParserContext::ESIGN;
                }
                else if(isDigit(ch)){
                    index += 1;
                    cntx = NumberParserContext::F;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::ESIGN:{
                if(isDigit(ch)){
                    index += 1;
                    cntx = NumberParserContext::F;
                }
                else{
                    return false;
                }
                break;
            }
            case NumberParserContext::F:{
                if(isDigit(ch)){
                    index += 1;
                }
                else if(ch == '$'){
                    return true;
                }
                else{
                    return false;
                }
                break;
            }
        }
    }
    return false;
}