#include "file_utils.hpp"
#include "json_fmt.hpp"
#include <iostream>

int main(){
    JFormat::Fomatter fmt;
    fmt.format("t.json", "tt.json", 4);
}