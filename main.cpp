#include "lexer.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

    void Buffer::read(string value){
        for(int i = 0; i < value.length() && i < 4096; ++i){
            buf[i] = value[i];
        }
    };
    char Buffer::nextChar(){
        return buf[offset++];
    };
    void Lexer::skipSpace(){
        for( ; ; peek = inbuf.nextChar()){
            if(peek == ' ' || peek == '\t'){
                continue;
            }
            else if(peek == '\n'){
                ++line;
                continue;
            }
            else if(peek == '/'){
                peek = inbuf.nextChar();
                if(peek == '/'){
                    while(inbuf.nextChar() != '\n');
                    peek = inbuf.nextChar();
                }
                else if(peek == '*'){
                    for(peek = ' ';;){
                        while(peek != '*' && inbuf.nextChar() != '*');
                        if((peek = inbuf.nextChar()) != '/'){
                            ;
                        }
                        else{
                            peek = inbuf.nextChar();
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
            else{
                break;
            }
        }
        return ;
    }
    Token* Lexer::dealConst(){
        switch(peek){
            case '\'' :
            return dealChar();
            break;
            case '\"' :
            return dealString();
            break;
            default:
            return dealNum();
        }
    }
    Token* Lexer::dealChar(){
        char value = 0;
        peek = inbuf.nextChar();
        if(peek == '\\'){
            peek = inbuf.nextChar();
            switch(peek){
                case 'n' :
                    value = '\n';
                    peek = inbuf.nextChar();
                    break;
                case 'r' :
                    value = '\r';
                    peek = inbuf.nextChar();
                    break;
                case '0' :
                    value = '\0';
                    peek = inbuf.nextChar();
                    break;
                case 't' :
                    value = '\t';
                    peek = inbuf.nextChar();
                    break;
                case 'v' :
                    value = '\v';
                    peek = inbuf.nextChar();
                    break;
                case 'b' :
                    value = '\b';
                    peek = inbuf.nextChar();
                    break;
                case 'f' :
                    value = '\f';
                    peek = inbuf.nextChar();
                    break;
                case 'a' :
                    value = '\a';
                    peek = inbuf.nextChar();
                    break;
                case '\"' :
                    value = '\"';
                    peek = inbuf.nextChar();
                    break;
                case '\'' :
                    value = '\'';
                    peek = inbuf.nextChar();
                    break;
                case '\\' :
                    value = '\\';
                    peek = inbuf.nextChar();
                    break;
                case '\?' :
                    value = '\?';
                    peek = inbuf.nextChar();
                    break;
                case 'x' :
                ;
                default :
                ;
            }
        }
        else{
            value = peek;
            peek = inbuf.nextChar();
            //cout << "peek = " << peek << " and (peek == '\'') = " << (peek == '\'') << endl;
        }
        if(peek != '\''){
            cout << "error!" << endl;
            return NULL;
        }
        else{
             peek = inbuf.nextChar();
            return new Num(value, Num::CHAR_VALUE);
        }
    }
    Token* Lexer::dealString(){
        string value = "";
        for(peek = inbuf.nextChar();;peek = inbuf.nextChar()){
            if(peek == '"'){
                peek = inbuf.nextChar();
                break;
            }

            if(peek == '\\'){
                peek = inbuf.nextChar();
                switch(peek){
                    case 'n' :
                        value += '\n';
                        peek = inbuf.nextChar();
                        break;
                    case 'r' :
                        value += '\r';
                        peek = inbuf.nextChar();
                        break;
                    case '0' :
                        value += '\0';
                        peek = inbuf.nextChar();
                        break;
                    case 't' :
                        value += '\t';
                        peek = inbuf.nextChar();
                        break;
                    case 'v' :
                        value += '\v';
                        peek = inbuf.nextChar();
                        break;
                    case 'b' :
                        value += '\b';
                        peek = inbuf.nextChar();
                        break;
                    case 'f' :
                        value += '\f';
                        peek = inbuf.nextChar();
                        break;
                    case 'a' :
                        value += '\a';
                        peek = inbuf.nextChar();
                        break;
                    case '\"' :
                        value += '\"';
                        peek = inbuf.nextChar();
                        break;
                    case '\'' :
                        value += '\'';
                        peek = inbuf.nextChar();
                        break;
                    case '\\' :
                        value += '\\';
                        peek = inbuf.nextChar();
                        break;
                    case '\?' :
                        value += '\?';
                        peek = inbuf.nextChar();
                        break;
                    default :
                    ;
                }
            }
            else{
                value += peek;
            }
        }

        return new String(value);
    }
    Token* Lexer::dealNum(){
        double value = 0.0;
        bool isPositive = true;
        int eCount = 0;
        bool isFloat = false;
        bool isDouble = false;

        for(;; peek = inbuf.nextChar()){

            if( peek <= '9' && peek >= '0'){
                value = value * 10 + peek - 48;
                if(isDouble) --eCount;
            }
            else if( peek == '.'){
                if(isDouble){
                    cout << "error!" << endl;
                    return NULL;
                }
                isDouble = true;
            }
            else{

                break;
            }
            //cout << value << endl;
        }
        if(peek == 'e' || peek == 'E'){

            //cout << " in find e v = " << value;
            if(isDouble && !eCount){
                cout << "error!" << endl;
                return NULL;
            }
            bool isEPositive = true;
            int Evalue = 0;
            peek = inbuf.nextChar();

            if(peek == '-'){
                isEPositive = false;
                peek = inbuf.nextChar();
            }

            for(;peek <= '9' && peek >= '0'; peek = inbuf.nextChar()){
                Evalue = Evalue * 10 + peek - 48;
                //cout << "ev = " << Evalue;
            }
            if(!isEPositive){
                Evalue = -Evalue;
            }
            isDouble = true;
            eCount = eCount + Evalue;
        }
        if(peek == 'f' || peek == 'F'){
            peek = ' ';
            isFloat = true;
        }
        if(isDouble || isFloat){
            value *= pow(10, eCount);
            //cout << "value = " << value << "ecount = " << eCount << endl;
        }
        if(peek == 'l' || peek == 'L'){
            peek = inbuf.nextChar();cout << "v = " << value;
            if(peek == 'u' || peek == 'U'){
                peek = ' ';
                return new Num((unsigned long)value, Num::UNSIGNED_LONG_NUM);
            }
            else{
                peek = ' ';
                return new Num((long)value, Num::LONG_NUM);
            }
        }
        else if(peek == 'u' || peek == 'U'){
            peek = inbuf.nextChar();
            if(peek == 'L' || peek == 'l'){
                peek = ' ';
                return new Num((unsigned long)value, Num::UNSIGNED_LONG_NUM);
            }
            else{
                return new Num((unsigned)value, Num::UNSIGNED_NUM);
            }
        }
        else{
            if(isFloat){
                return new Num(value, Num::FLOAT_NUM);
            }
            else if(isDouble){
                return new Num(value, Num::DOUBLE_NUM);
            }
            else ;
            return new Num(value, Num::INT_NUM);
        }
    }
    Token* Lexer::dealWord(){
        string value = "";
        for(;;peek = inbuf.nextChar()){
            if((peek <= 'Z' && peek >= 'A') || (peek <= 'z' && peek >= 'a') || (peek <= '9' && peek >= '0') || peek == '$' || peek == '_'){
                value += peek;
            }
            else{
                break;
            }
        }
        map<string, Word>::iterator i = words.find(value);

        if(i != words.end()){
        return new Word(i -> second);
        }
       else return new Word(Tag::ID, value);
    }
    Token* Lexer::dealOperator(){
        Token* t;
        if(peek == '.' || peek == '~' || peek == '(' || peek == ')' ||
            peek == '[' || peek == ']' || peek == '{' || peek == '}' ||
            peek == '?' || peek == ',' || peek == ';' || peek == '#' ){
            t = new Token(peek);
            peek = inbuf.nextChar();
        }
        else{
            switch(peek){
                case '+':
                    peek = inbuf.nextChar();
                    if(peek == '+'){
                        t = &(words.find("++")->second);
                        peek = inbuf.nextChar();
                    }
                    else if (peek == '='){
                        t = &(words.find("+=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('+');
                    }
                    break;
                case '-':
                    peek = inbuf.nextChar();
                    if(peek == '-'){
                        t = &(words.find("--")->second);
                        peek = inbuf.nextChar();
                    }
                    else if (peek == '='){
                        t = &(words.find("-=")->second);
                        peek = inbuf.nextChar();
                    }
                    else if (peek == '>'){
                        t = &(words.find("->")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('-');
                    }
                    break;
                case '*':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("*=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('*');
                    }
                    break;
                case '/':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("/=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('/');
                    }
                    break;
                case '%':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("%=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('%');
                    }
                    break;
                case '!':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("!=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('!');
                    }
                    break;
                case '&':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("&=")->second);
                        peek = inbuf.nextChar();
                    }
                    else if(peek == '&'){
                        t = &(words.find("&&")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('&');
                    }
                    break;
                case '|':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("|=")->second);
                        peek = inbuf.nextChar();
                    }
                    else if(peek == '|'){
                        t = &(words.find("||")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('|');
                    }
                    break;
                case '=':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("==")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('=');
                    }
                    break;
                case '>':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find(">=")->second);
                        peek = inbuf.nextChar();
                    }
                    else if(peek == '>'){
                        peek = inbuf.nextChar();
                        if(peek == '='){
                            t = &(words.find(">>=")->second);
                            peek = inbuf.nextChar();
                        }
                        else{
                            t = &(words.find(">>")->second);
                        }
                    }
                    else{
                        t = new Token('>');
                    }
                    break;
                case '<':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("<=")->second);
                        peek = inbuf.nextChar();
                    }
                    else if(peek == '<'){
                        peek = inbuf.nextChar();
                        if(peek == '='){
                            t = &(words.find("<<=")->second);
                            peek = inbuf.nextChar();
                        }
                        else{
                            t = &(words.find("<<")->second);
                        }
                    }
                    else{
                        t = new Token('<');
                    }
                    break;
                case '^':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &(words.find("^=")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token('^');
                    }
                    break;
                case ':':
                    peek = inbuf.nextChar();
                    if(peek == ':'){
                        t = &(words.find("::")->second);
                        peek = inbuf.nextChar();
                    }
                    else{
                        t = new Token(':');
                    }
                    break;
                default:
                ;
            }
        }
        return t;
    }

    Token* Lexer::scan(){
        if(peek == '\0'){
            return NULL;
        }
        skipSpace();
        if(peek == '\0'){
            return NULL;
        }
        if(peek == '\'' || peek == '\"' || (peek <= '9' && peek >= '0')){
            return dealConst();
        }
        if((peek <= 'Z' && peek >= 'A') || (peek <= 'z' && peek >= 'a') || peek == '_'){
            return dealWord();
        }
        return dealOperator();
    }


int main()
{
    string inname = "test.c";
     ifstream inputStream(inname.c_str());
     ofstream fout("out.txt", ios::trunc);
     if( !inputStream ) {
       cerr << "Error opening input stream" << endl;
       return -1;
     }

    string line;

    while(getline(inputStream, line)){
        fout << "\n\n" << line << endl;
        Lexer lex(line);
        for(;;)
        {
            Token* t = lex.scan();
            if(t == NULL)
            break;
            else{
                switch(t -> tag){
                    case Tag::NUM:
                    Num* n = (Num*)t;
                    if( n -> type == Num::CHAR_VALUE ){
                        fout << "< '" << (char)(n -> value) << "' > ";
                    }
                    else if( n -> type == Num::STRING_VALUE ){
                        String* s = (String*)n;
                        fout << "< \"" << s->svalue << "\" > ";
                    }
                    else{
                        fout << "< " << n -> value << " > " ;
                    }
                    break;
                    case Tag::ID:
                    Word* w = (Word*)t;
                    fout << "< " << w -> lexeme << " > ";
                    break;
                    default:
                    if(t -> tag > 0X101){
                        fout << "< " << RESERVED_STRINGS[t -> tag - Tag::OFFSET] << " > " ;
                    }
                    else{
                        char c = t -> tag;
                        fout << "< " << c << " > " ;
                    }
                }
            }
        }
    }
    inputStream.close();
    fout.close();
    return 0;
}
