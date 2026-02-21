#include "json_fmt.hpp"
#include "file_utils.hpp"

void JFormat::Fomatter::format(std::string inputFile, std::string outputFile, int indent = 4){
    FileUtils::InpFileReader inputJson(inputFile);
    FileUtils::OutFileWriter outPutJson(outputFile);

    long level = 0;
    int nextChar;
    int isNewLine = 0;
    int isEscapedChar = 0;
    while(true){
        nextChar = inputJson.nextChar();
        if(inputJson.isEof()){
            break;
        }
        switch(context){
            case JFormatContext::NORMAL:{
                switch(nextChar){
                    case '{':
                        if(isNewLine){
                            isNewLine = 0;
                            outPutJson.fillChars(' ', level * indent);
                        }
                        outPutJson.writeChar('{');
                        outPutJson.writeChar('\n');
                        isNewLine = 1;
                        level += 1;
                        break;
                    case '[':
                        if(isNewLine){
                            isNewLine = 0;
                            outPutJson.fillChars(' ', level * indent);
                        }
                        outPutJson.writeChar('[');
                        outPutJson.writeChar('\n');
                        isNewLine = 1;
                        level += 1;
                        break;
                    case ':':
                        outPutJson.writeChar(':');
                        outPutJson.writeChar(' ');
                        break;
                    case ' ':
                    case '\n':
                    case '\t':
                        break;
                    case '}':
                        outPutJson.writeChar('\n');
                        level -= 1;
                        outPutJson.fillChars(' ', level * indent);
                        outPutJson.writeChar('}');
                        break;
                    case ']':
                        outPutJson.writeChar('\n');
                        level -= 1;
                        outPutJson.fillChars(' ', level * indent);
                        outPutJson.writeChar(']');
                        break;
                    case ',':
                        outPutJson.writeChar(',');
                        outPutJson.writeChar('\n');
                        isNewLine = 1;
                        break;
                    case '\"':
                        context = JFormatContext::STRING;
                    default:
                        if(isNewLine){
                            isNewLine = 0;
                            outPutJson.fillChars(' ', level * indent);
                        }
                        outPutJson.writeChar(nextChar);
                        break;
                        
                }
                break;
            }
            case JFormatContext::STRING:{
                switch(nextChar){
                    case '\\':
                        isEscapedChar = 1;
                        outPutJson.writeChar(nextChar);
                        break;
                    case '\"':
                        outPutJson.writeChar('\"');
                        if(isEscapedChar == 0){
                            context = JFormatContext::NORMAL;
                        }
                        else{
                            isEscapedChar = 0;
                        }
                        break;
                    default:
                        if(isEscapedChar){
                            isEscapedChar = 0;
                        }
                        outPutJson.writeChar(nextChar);
                        break;
                    
                }
                break;

            }
        }
    }
}


