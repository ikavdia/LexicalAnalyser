#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

string reserved[] = { "END_OF_FILE",
    "IF", "WHILE", "DO", "THEN", "PRINT",
    "PLUS", "MINUS", "DIV", "MULT",
    "EQUAL", "COLON", "COMMA", "SEMICOLON",
    "LBRAC", "RBRAC", "LPAREN", "RPAREN",
    "NOTEQUAL", "GREATER", "LESS", "LTEQ", "GTEQ",
    "DOT", "NUM", "ID", "ERROR", "REALNUM", "BASE08NUM", "BASE16NUM"
};

#define KEYWORDS_COUNT 5
string keyword[] = { "IF", "WHILE", "DO", "THEN", "PRINT" };

void Token::Print()
{
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
}

LexicalAnalyzer::LexicalAnalyzer()
{
    this->line_no = 1;
    tmp.lexeme = "";
    tmp.line_no = 1;
    tmp.token_type = ERROR;
}

bool LexicalAnalyzer::SkipSpace()
{
    char c;
    bool space_encountered = false;

    input.GetChar(c);
    line_no += (c == '\n');

    while (!input.EndOfInput() && isspace(c)) {
        space_encountered = true;
        input.GetChar(c);
        line_no += (c == '\n');
    }

    if (!input.EndOfInput()) {
        input.UngetChar(c);
    }
    return space_encountered;
}

bool LexicalAnalyzer::IsKeyword(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return true;
        }
    }
    return false;
}

TokenType LexicalAnalyzer::FindKeywordIndex(string s)
{
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (s == keyword[i]) {
            return (TokenType) (i + 1);
        }
    }
    return ERROR;
}

Token LexicalAnalyzer::ScanNumber() {
    char c;   //declaring a character variable C
    char x = 'x';  //Declaring a character vatiable x and assigning it the value of 'x'

    input.GetChar(c);   //reading the character c into the input stream
    switch (c) {
        case '0':
            tmp.lexeme = "0";  //setting lexme of temporary token to 0
            break;
        default:
            if (!isdigit(c)) {  //check if the character is not a digit
                if (!input.EndOfInput()) {   //check for not the end of input
                    input.UngetChar(c);  //if not end of input then put the character back ito input stream
                }
                tmp.lexeme = "";   // setting lexeme of temporary Token to an empty string
                tmp.token_type = ERROR;  // set the token type to ERROR
                tmp.line_no = line_no;   // set the line number of the token
                return tmp;  // return the temporary Token object
            }
            tmp.lexeme = "";   // setting lexeme of temporary Token to an empty string
            while (!input.EndOfInput() && isdigit(c)) {  // loop while it's not the end of input and the character is a digit
                tmp.lexeme += c;  // append character to lexeme of the temporary Token
                input.GetChar(c);   //read next character form input stream
            }
            if (!input.EndOfInput()) {   //check for not the end of input
                input.UngetChar(c);  //if not end of input then put the character back ito input stream
            }
            break;
    }

    input.GetChar(c);  // reading the character c into the input stream
    switch (c) {
        case '.':
            input.GetChar(c);  //reading the character c into the input stream
            if (isdigit(c)) {  //check if the character is a digit
                tmp.lexeme += "."; // append a dot to the lexeme of the temporary Token
                tmp.lexeme += c;  // append character to lexeme of the temporary Token
                input.GetChar(c);  // read next character form input stream
                while (!input.EndOfInput() && isdigit(c)) {   // loop while it's not the end of input and the character is a digit
                    tmp.lexeme += c;  // append character to lexeme of the temporary Token
                    input.GetChar(c); // read next character form input stream
                }
                if (!input.EndOfInput()) {  // check for not the end of input
                    input.UngetChar(c);  // if not end of input then put the character back ito input stream
                }
                tmp.token_type = REALNUM;  // set the token type to REALNUM
                tmp.line_no = line_no;  // Set the line number of the token
                return tmp;  // Return the temporary Token object
            } 
            else {
                input.UngetChar(c);  // return character to input stream
                input.UngetChar('.');  //return dot to input stream
            }
            break;
        case 'x':
            input.GetChar(c);  // read next character from input stream into  C
            if (isdigit(c)) {  // check if the character following 'x' is a digit
                char c2 = c;  // store the current character in c2
                input.GetChar(c);  // read next character from input stream into  C
                if (c2 == '0' && c == '8') {  // Check if the characters following 'x' are '0' and '8'
                    bool isBase08 = true;
                    for (int i = 0; i < tmp.lexeme.length(); i++) {  // loop through the lexeme of the temporary Token
                        if (tmp.lexeme[i] == '8' || tmp.lexeme[i] == '9') {  // if any digit is 8 or 9, it's not a valid base 08 number
                            isBase08 = false;
                            break;
                        }
                    }
                    if (isBase08) {  // if it's a valid base 08 number
                        tmp.lexeme += "x08";  // append "x08" to the lexeme of the temporary Token object
                        tmp.token_type = BASE08NUM;  // set the token type to BASE08NUM
                        tmp.line_no = line_no;  // set the line number of the token
                        return tmp;  // return the temporary Token object
                    } 
                    else {  //If not a valid base of 08 the put the characters back into the input stream
                        input.UngetChar(c2);
                        input.UngetChar(c);
                        input.UngetChar(x);
                    }
                } 
                else if (c2 == '1' && c == '6') {  // check if the characters following 'x' are '1' and '6'
                    tmp.lexeme += "x16";  // append "x16" to the lexeme of the temporary Token 
                    tmp.token_type = BASE16NUM;  // set the token type to BASE16NUM
                    tmp.line_no = line_no;  // set the line number of the token
                    return tmp;  // Return the temporary Token
                } 
                else {  // If not a valid base of 16 the put the characters back into the input stream
                    input.UngetChar(c2);
                    input.UngetChar(c);
                    input.UngetChar(x);
                }
            } 
            else {  // If not a digit the put the characters back into the input stream
                input.UngetChar(c);
                input.UngetChar(x);
            }
            break;
        default:
            if (checkForBase16(c)) {  // function to check if the character is part of a base 16 number
                vector<char> collection;  // vector to collect characters of the base 16 number
                string templexeme = ""; // temporary string to store the lexeme of the base 16 number
                while (!input.EndOfInput() && checkForBase16(c)) {  // loop while it's not the end of input and the character is part of a base 16 number
                    collection.push_back(c);  // add the character to the collection vector
                    templexeme += c;  // append the character to the temporary lexeme string
                    input.GetChar(c);  // read the next character from the input stream into c
                }
                if (c == 'x') {  // if 'x' is found after the base 16 number
                    input.GetChar(c); // read next character from input stream into  C
                    char c1 = c;  // store the next character in c1
                    input.GetChar(c); // read next character from input stream into  C
                    char c2 = c;  // store the next character in c2
                    input.GetChar(c);  // read next character from input stream into  C
                    if (c1 == '1' && c2 == '6' && !(isdigit(c) || isalpha(c))) {  // check if c1 and c2 form "16" and the next character is not digit and not alphabet
                        input.UngetChar(c);  // put the characters back into the input stream
                        tmp.lexeme += templexeme;  // append the temporary lexeme string to the lexeme of the temporary Token
                        tmp.lexeme += "x16";  // append "x16" to the lexeme of the temporary Token
                        tmp.token_type = BASE16NUM;  // set the token type to BASE16NUM
                        tmp.line_no = line_no; // set the line number of the token
                        return tmp;  // return the temporary Token object
                    }
                    else {  // if characters are not of a valid pattern the put the characters back into the input stream
                        input.UngetChar(c);
                        input.UngetChar(c2);
                        input.UngetChar(c1);
                        input.UngetChar(x);
                        for (auto it = collection.rbegin(); it != collection.rend(); ++it) {  // put the characters of the base 16 back into the input stream
                            input.UngetChar(*it);
                        }
                    }
                } 
                else { // if 'x' is not found after base 16 number
                    input.UngetChar(c);  // put the characters back into the input stream
                    for (auto it = collection.rbegin(); it != collection.rend(); ++it) {  // put the characters of the base 16 back into the input stream
                        input.UngetChar(*it);
                    }
                }
            } 
            else {  //If 'x' not found after base 16 number
                input.UngetChar(c);  // put the characters back into the input stream
            }
            break;
    }
    tmp.token_type = NUM;  // set the token type to NUM
    tmp.line_no = line_no;  // set the line number of the token
    return tmp;  // return the temporary Token object
    if (!input.EndOfInput()) {  // check if it's not the end of input
        input.UngetChar(c);  // put the character back into the input stream
    }
    tmp.lexeme = ""; // set the lexeme of the temporary Token to an empty string
    tmp.token_type = ERROR;  // Set the token type to ERROR
    tmp.line_no = line_no;  // Set the line number of the token
    return tmp;  // return the temporary Token object
}


Token LexicalAnalyzer::ScanIdOrKeyword()
{
    char c;
    input.GetChar(c);

    if (isalpha(c)) {
        tmp.lexeme = "";
        while (!input.EndOfInput() && isalnum(c)) {
            tmp.lexeme += c;
            input.GetChar(c);
        }
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.line_no = line_no;
        if (IsKeyword(tmp.lexeme))
            tmp.token_type = FindKeywordIndex(tmp.lexeme);
        else
            tmp.token_type = ID;
    } else {
        if (!input.EndOfInput()) {
            input.UngetChar(c);
        }
        tmp.lexeme = "";
        tmp.token_type = ERROR;
    }
    return tmp;
}

// you should unget tokens in the reverse order in which they
// are obtained. If you execute
//
//    t1 = lexer.GetToken();
//    t2 = lexer.GetToken();
//    t3 = lexer.GetToken();
//
// in this order, you should execute
//
//    lexer.UngetToken(t3);
//    lexer.UngetToken(t2);
//    lexer.UngetToken(t1);
//
// if you want to unget all three tokens. Note that it does not
// make sense to unget t1 without first ungetting t2 and t3
//
TokenType LexicalAnalyzer::UngetToken(Token tok)
{
    tokens.push_back(tok);;
    return tok.token_type;
}

Token LexicalAnalyzer::GetToken()
{
    char c;

    // if there are tokens that were previously
    // stored due to UngetToken(), pop a token and
    // return it without reading from input
    if (!tokens.empty()) {
        tmp = tokens.back();
        tokens.pop_back();
        return tmp;
    }

    SkipSpace();
    tmp.lexeme = "";
    tmp.line_no = line_no;
    input.GetChar(c);
    switch (c) {
        case '.':
            tmp.token_type = DOT;
            return tmp;
        case '+':
            tmp.token_type = PLUS;
            return tmp;
        case '-':
            tmp.token_type = MINUS;
            return tmp;
        case '/':
            tmp.token_type = DIV;
            return tmp;
        case '*':
            tmp.token_type = MULT;
            return tmp;
        case '=':
            tmp.token_type = EQUAL;
            return tmp;
        case ':':
            tmp.token_type = COLON;
            return tmp;
        case ',':
            tmp.token_type = COMMA;
            return tmp;
        case ';':
            tmp.token_type = SEMICOLON;
            return tmp;
        case '[':
            tmp.token_type = LBRAC;
            return tmp;
        case ']':
            tmp.token_type = RBRAC;
            return tmp;
        case '(':
            tmp.token_type = LPAREN;
            return tmp;
        case ')':
            tmp.token_type = RPAREN;
            return tmp;
        case '<':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = LTEQ;
            } else if (c == '>') {
                tmp.token_type = NOTEQUAL;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = LESS;
            }
            return tmp;
        case '>':
            input.GetChar(c);
            if (c == '=') {
                tmp.token_type = GTEQ;
            } else {
                if (!input.EndOfInput()) {
                    input.UngetChar(c);
                }
                tmp.token_type = GREATER;
            }
            return tmp;
        default:
            if (checkForBase16(c)) {
                input.UngetChar(c);
                Token currTok = ScanNumber();
                if(currTok.lexeme.length()==0){
                    return ScanIdOrKeyword();
                }
                return currTok;
            } else if (isalpha(c)) {
                input.UngetChar(c);
                return ScanIdOrKeyword();
            } else if (input.EndOfInput())
                tmp.token_type = END_OF_FILE;
            else
                tmp.token_type = ERROR;

            return tmp;
    }
}

// helper function - checks if b is a valid hexadecimal number or a digit. return true if yes and false if not.
bool LexicalAnalyzer::checkForBase16(char b) {
    return isdigit(b) || (b >= 'a' && b <= 'f') || (b >= 'A' && b <= 'F');
}

int main()
{
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != END_OF_FILE)
    {
        token = lexer.GetToken();
        token.Print();
    }
}