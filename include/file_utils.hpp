#pragma once
#include<string>
#include<fstream>
#include<vector>
#include "consts.hpp"

namespace FileUtils{
    
    class InpFileReader{
        std::vector<char> textChunk;
        std::ifstream file;
        size_t buffRead = 0;
        size_t buffLeft = 0;
        bool eof = false;

        void updateBuffParams();
        void readChunk();

        public:

        explicit InpFileReader(std::string);
        bool isEof() const;
        int nextChar();
    };

    class OutFileWriter{
        std::vector<char> textChunk;
        std::ofstream file;
        size_t buffPushed = 0;
        void flush();
        public:
        explicit OutFileWriter(std::string);
        void writeChar(char);
        ~OutFileWriter() noexcept;

    };
};