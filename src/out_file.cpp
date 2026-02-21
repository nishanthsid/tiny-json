#include "file_utils.hpp"
#include "consts.hpp"
#include <stdexcept>
#include <cstring>
#include <algorithm>

void FileUtils::OutFileWriter::flush(){
    if(buffPushed > 0){
        file.write(textChunk.data(), buffPushed);
        buffPushed = 0;
    }
}

FileUtils::OutFileWriter::OutFileWriter(std::string fileName)  : textChunk(Consts::BUFFER_SIZE){
    file.open(fileName,std::ios::binary);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: " + fileName);
    } 
}

void FileUtils::OutFileWriter::writeChar(char nextChar){
    textChunk[buffPushed++] = nextChar;
    if(buffPushed == Consts::BUFFER_SIZE){
        flush();
    }
}

void FileUtils::OutFileWriter::writeString(std::string& str){
    std::size_t ind = 0;
    while(ind < str.size()){
        size_t remSpace = Consts::BUFFER_SIZE - buffPushed;
        size_t toCopy = std::min(remSpace, str.size() - ind);
        std::memcpy(
            textChunk.data() + buffPushed,
            str.data() + ind,
            toCopy
        );

        buffPushed += toCopy;
        ind += toCopy;

        if(buffPushed == Consts::BUFFER_SIZE){
            flush();
        }
    }
}

void FileUtils::OutFileWriter::fillChars(char c, std::size_t count){
    std::size_t ind = 0;
    while(ind < count){
        size_t remSpace = Consts::BUFFER_SIZE - buffPushed;
        size_t toCopy = std::min(remSpace, count - ind);
        std::fill_n(textChunk.begin() + buffPushed, toCopy, c);
        buffPushed += toCopy;
        ind += toCopy;

        if(buffPushed == Consts::BUFFER_SIZE){
            flush();
        }
    }
}

FileUtils::OutFileWriter::~OutFileWriter() noexcept{
    flush();
}