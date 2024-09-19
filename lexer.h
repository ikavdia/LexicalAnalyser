#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"

// ------- token types -------------------

typedef enum { END_OF_FILE = 0,
    IF, WHILE, DO, THEN, PRINT,
    PLUS, MINUS, DIV, MULT,
    EQUAL, COLON, COMMA, SEMICOLON,
    LBRAC, RBRAC, LPAREN, RPAREN,
    NOTEQUAL, GREATER, LESS, LTEQ, GTEQ,
    DOT, NUM, ID, ERROR, REALNUM, BASE08NUM, BASE16NUM // TODO: Add labels for new token types here - done
} TokenType;

class Token {
  public:
    void Print();

    std::string lexeme;
    TokenType token_type;
    int line_no;
};

class LexicalAnalyzer {
  public:
    Token GetToken();
    TokenType UngetToken(Token);
    LexicalAnalyzer();

  private:
    std::vector<Token> tokens;
    int line_no;
    Token tmp;
    InputBuffer input;

    bool SkipSpace();
    bool IsKeyword(std::string);
    TokenType FindKeywordIndex(std::string);
    Token ScanIdOrKeyword();
    Token ScanNumber();
    bool checkForBase16(char b);  // helper function to check if b is valid digit or hex number
};

#endif  //__LEXER__H__