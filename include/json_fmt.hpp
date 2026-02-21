#pragma once
#include "file_utils.hpp"

namespace JFormat{

    class Fomatter{
        enum class JFormatContext{
            NORMAL,
            STRING
        };

        JFormatContext context = JFormatContext::NORMAL;
        public:
        void format(std::string, std::string, int);
        void minify(std::string, std::string);

    };
};