#include "file_utils.hpp"
#include "consts.hpp"
#include <stdexcept>

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

FileUtils::OutFileWriter::~OutFileWriter(){
    flush();
}