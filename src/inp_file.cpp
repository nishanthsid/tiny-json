#include "file_utils.hpp"
#include "consts.hpp"
#include <stdexcept>

void FileUtils::InpFileReader::updateBuffParams(){
    std::streamsize bytesRead = file.gcount();
    if(bytesRead == 0){
        eof = true;
    }
    buffLeft = bytesRead;
}

void FileUtils::InpFileReader::readChunk(){
    file.read(textChunk.data(), Consts::BUFFER_SIZE);
    updateBuffParams();
}

FileUtils::InpFileReader::InpFileReader(std::string fileName) : textChunk(Consts::BUFFER_SIZE){
    file.open(fileName, std::ios::binary);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: " + fileName);
    }
    readChunk();
}

bool FileUtils::InpFileReader::isEof() const{
    return eof;
}

int FileUtils::InpFileReader::nextChar(){
    if(buffRead >= buffLeft){
        readChunk();
        buffRead = 0;
        if(eof){
            return Consts::EOF_CHAR;
        }
    }
    return textChunk[buffRead++];
}