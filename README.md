# Lexical Analyzer Project

## Table of Contents
- [Overview](#overview)
- [Project Details](#project-details)
- [Implementation](#implementation)
- [Technologies Used](#technologies-used)
- [Key Learnings](#key-learnings)
- [Getting Started](#getting-started)
- [Testing](#testing)
- [License](#license)

## Overview

This project involves the development and enhancement of a lexical analyzer, a crucial component in compiler construction. The main objective is to extend an existing lexical analyzer to support additional token types, providing practical experience with lexical analysis, regular expressions, and tokenization techniques.

## Project Details

The base lexical analyzer has been extended to recognize three new token types:

1. **REALNUM**: Represents real numbers in the format `NUM.DOTdigit*`
   - `NUM` is an integer
   - `DOT` is a decimal point
   - Followed by one or more digits

2. **BASE08NUM**: Numbers in base-8 format
   - Represented as `((pdigit8 digit8*) + 0) (x) (08)`

3. **BASE16NUM**: Numbers in base-16 format
   - Represented as `((pdigit16 digit16*) + 0) (x) (16)`

## Implementation

The project was implemented through the following steps:

1. **Token Recognition**: 
   - Modified `lexer.cc` and `lexer.h` files
   - Defined regular expressions for new token types
   - Implemented logic for accurate token identification and classification

2. **Compilation**: 
   - Used GCC compiler (g++ version 4.9 or higher) in Ubuntu 19.04 environment
   - Addressed compiler warnings and optimized token recognition

3. **Testing**: 
   - Utilized provided test cases and scripts
   - Implemented standard I/O redirection for comprehensive input-output testing
   - Validated correct identification and categorization of tokens

4. **Submission**: 
   - Submitted modified `lexer.cc` to the evaluation platform
   - Ensured compliance with project requirements
   - Successfully passed all automated test cases

## Technologies Used

- **Programming Language**: C++
- **Compiler**: GCC (g++)
- **Operating System**: Ubuntu 19.04
- **Testing Tools**: Custom test scripts, diff tool for output validation

## Key Learnings

- Gained practical experience in lexical analysis and compiler construction
- Enhanced understanding of regular expressions and tokenization in C++
- Improved skills in debugging and optimizing code for performance and accuracy
- Learned to work with I/O redirection and command-line tools in a Unix-like environment

## Getting Started

To compile and run the lexical analyzer:

1. Ensure you have g++ installed on your system
2. Clone this repository
3. Navigate to the project directory
4. Compile the code:
  ```
  g++ lexer.cc inputbuf.cc -o lexer
  ```
5. Run the analyzer:
  ```./lexer < input_file.txt > output_file.txt```

## Testing

To run the provided test cases:

1. Unzip the test cases in the project directory
2. Make the test script executable:
  ```chmod +x test1.sh```
3. Run the test script:
  ```./test1.sh```

## License

MIT License

Copyright (c) 2024 Ishan Kavdia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
