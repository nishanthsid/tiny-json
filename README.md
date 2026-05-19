# tiny-json

A small, dependency-free C++17 JSON toolkit. It provides a streaming
(on-demand) tokenizer, a state-machine based number validator, and a
formatter that can pretty-print or minify JSON files using buffered file
I/O.

The current `main.cpp` is a demo driver that opens `tt.json` and prints
every token it sees, indented to reflect nesting depth.

## Features

- **On-demand tokenizer** (`Tokenizer::JsonOnDemandTokenizer`) — pulls one
  token at a time from the file, with single-token `peek` support. Tokens
  cover the full JSON grammar: objects, arrays, strings (with escape
  handling), numbers, `true`/`false`/`null`, commas, colons, and EOF.
- **JSON number validator** (`RealNumber::Validator::isRealNum`) — a DFA
  that accepts exactly the numbers allowed by the JSON spec (optional
  sign, integer / fractional / exponent parts).
- **Formatter** (`JFormat::Fomatter`) — `format(in, out, indent)` writes a
  pretty-printed copy; `minify(in, out)` strips insignificant whitespace.
  Both are string-aware so quoted content is preserved verbatim.
- **Buffered file I/O** (`FileUtils::InpFileReader` /
  `FileUtils::OutFileWriter`) — 1 MiB chunked reads and writes; the
  writer flushes on destruction.

## Layout

```
include/
  consts.hpp        # EOF sentinel, buffer size
  file_utils.hpp    # InpFileReader / OutFileWriter
  numbers.hpp       # RealNumber::Validator
  tokenizer.hpp     # Token, TokenType, JsonOnDemandTokenizer
  json_fmt.hpp      # JFormat::Fomatter
src/
  inp_file.cpp
  out_file.cpp
  numbers.cpp
  tokenizer.cpp
  json_fmt.cpp
main.cpp            # demo: tokenize tt.json and print tokens
Makefile
```

## Build

Requires a C++17 compiler (the Makefile uses `g++`).

```sh
make
```

This produces a `main` binary in the project root. To clean build
artifacts:

```sh
make clean
```

## Run the demo

The demo reads a file called `tt.json` from the current directory:

```sh
echo '{"name":"tiny-json","ok":true,"count":3,"tags":["a","b"]}' > tt.json
./main
```

Example output:

```
[0] OPEN_BRACE -> "{"
  [1] STRING -> "name"
  [2] COLON -> ":"
  [3] STRING -> "tiny-json"
  [4] COMMA -> ","
  [5] STRING -> "ok"
  [6] COLON -> ":"
  [7] BOOL -> "true"
  ...
[N] CLOSE_BRACE -> "}"
```

## Using the library

### Tokenizing

```cpp
#include "tokenizer.hpp"

Tokenizer::JsonOnDemandTokenizer tok("input.json");
Tokenizer::Token t;
while ((t = tok.getNextToken()).getTokenType() != Tokenizer::TokenType::END_OF_FILE) {
    // t.getTokenType(), t.getRawTokenValue()
}
```

`peekNextToken()` returns the next token without consuming it; the next
`getNextToken()` will return the same token.

### Formatting and minifying

```cpp
#include "json_fmt.hpp"

JFormat::Fomatter fmt;
fmt.format("input.json", "pretty.json", 4); // indent = 4 spaces
fmt.minify("input.json", "min.json");
```

### Validating a number literal

```cpp
#include "numbers.hpp"

std::string s = "-1.25e+3";
bool ok = RealNumber::Validator::isRealNum(s); // true
```
