#pragma once
#include <string>

namespace RealNumber{
    class Validator{
        private:
            enum class NumberParserContext{
                START,
                SIGN,
                ESIGN,
                A,
                B,
                C,
                D,
                E,
                F
                
            };
        public:
            static bool isDigit(char ch);
            static bool isRealNum(std::string& num);
    };

}