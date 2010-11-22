#include "Lexer.h"
#include <iostream>
    static const string Tag::RESERVED_STRINGS = {
            "", "", "",
            "null", "true", "false",
            "->", "<=", ">=", "==", "!=", "&&", "||",
            "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
            "++", "--", "<<", ">>", "",
            "typedef", "const", "static", "extern",
            "long", "short", "signed", "unsigned",
            "int", "float", "double", "char", "enum", "struct", "union", "void", "",
            "if", "else", "else if", "switch", "case", "default", "while", "do",
            "for", "goto", "break", "continue", "return",
            "asm", "auto", "edecl", "far", "huge", "interrupt", "near", "pascal", "register", "volatile"
        };

    void Buffer::read(string value){
        for(int i = 0; i < value.lenth && i < 4096; ++i){
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

                default :

            }
        }
        else{
            value = peek;
            peek = inbuf.nextChar();
        }
        if(peek != '\''){
            cout << "error!" << endl;
            return NULL;
        }
        else{
            peek == ' ';
            return new Num<char>(value);
        }
    }
    Token* Lexer::dealString(){
        string value = "";
        peek = inbuf.nextChar();
        return new Num<string>(value);
    }
    Token* Lexer::dealNum(){
        double value = 0.0;
        bool isPositive = true;
        int eCount = 0;
        bool isFloat = false;

        for(;; peek = inbuf.nextChar()){
            if( peek <= '9' && peek >= '0'){
                value = value * 10 + peek - 48;
                if(isFloat) --eCount;
            }
            if( peek == '.'){
                if(isFloat){
                    cout << "error!" << endl;
                    return NULL;
                }
                isFloat = true;
            }
            else{
                break;
            }
        }
        if(peek == 'e' || peek == 'E'){
            if(isFloat && !ECount){
                cout << "error!" << endl;
                return NULL;
            }
            bool isEPositive = true;
            int Evalue = 0;
            if(peek == '-'){
                isEPositive = false;
                peek = inbuf.nextChar();
            }
            for(;peek <= '9' && peek >= '0'; peek = inbuf.nextChar()){
                Evalue = Evalue * 10 + peek - 48;
            }
            if(!isEPositive){
                Evalue = -Evalue;
            }
            isFloat = true;
            ECount = Evalue + ECount;
        }
        if(peek == 'f' || peek == 'F'){
            peek = ' ';
            return new Num<float>(value);
        }
        else if(peek == 'l' || peek == 'L' || isFloat){
            peek = inbuf.nextChar();
            if(peek == 'u' || peek == 'U'){
                peek = ' ';
                return new Num<unsigned long>(value);
            }
            else{
                peek = ' ';
                return new Num<long>(value);
            }
        }
        else if(peek == 'u' || peek == 'U'){
            peek = inbuf.nextChar();
            if(peek == 'L' || peek == 'l'){
                peek = ' ';
                return Num<unsigned long>(value);
            }
            else{
                peek = ' ';
                return new Num<unsigned>(value);
            }
        }
        else{
            return new Num<int>(value);
        }
    }
    Token Lexer::dealWord(){
        string value = "";
        for(;;peek = inbuf.nextChar()){
            if((peek <= 'Z' && peek >= 'A') || (peek <= 'z' && peek >= 'a') || (peek <= '9' && peek >= '0') || peek == '$' || peek == '_'){
                value += peek;
            }
            else{
                break;
            }
        }
        Word * w = &words.find(value);
        if(w != NULL)return w;
        w = new Word(Tag::ID, value);
        return w;
    }
    Token Lexer::dealOperator(){
        Token* t;
        if(peek == '.' || peek == '~' || peek == '(' || peek == ')' ||
            peek == '[' || peek == ']' || peek == '{' || peek == '}' ||
            peek == '?' || peek == ',' || peek == ';'){
            t = new Token(peek);
            peek == ' ';
        }
        else{
            switch(peek){
                case '+':
                    peek = inbuf.nextChar();
                    if(peek == '+'){
                        t = &words.find("++");
                        peek == ' ';
                    }
                    else if (peek == '='){
                        t = &words.find("+=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('+');
                    }
                    break;
                case '-':
                    peek = inbuf.nextChar();
                    if(peek == '-'){
                        t = &words.find("--");
                        peek == ' ';
                    }
                    else if (peek == '='){
                        t = &words.find("-=");
                        peek == ' ';
                    }
                    else if (peek == '>'){
                        t = &words.find("->");
                        peek == ' ';
                    }
                    else{
                        t = new Token('-');
                    }
                    break;
                case '*':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("*=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('*');
                    }
                    break;
                case '/':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("/=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('/');
                    }
                    break;
                case '%':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("%=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('%');
                    }
                    break;
                case '!':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("!=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('!');
                    }
                    break;
                case '&':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("&=");
                        peek == ' ';
                    }
                    else if(peek == '&'){
                        t = &words.find("&&");
                        peek == ' ';
                    }
                    else{
                        t = new Token('&');
                    }
                    break;
                case '|':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("|=");
                        peek == ' ';
                    }
                    else if(peek == '|'){
                        t = &words.find("||");
                        peek == ' ';
                    }
                    else{
                        t = new Token('|');
                    }
                    break;
                case '=':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("==");
                        peek == ' ';
                    }
                    else{
                        t = new Token('=');
                    }
                    break;
                case '>':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find(">=");
                        peek == ' ';
                    }
                    else if(peek == '>'){
                        peek = inbuf.nextChar();
                        if(peek == '='){
                            t = &words.find(">>=");
                            peek == ' ';
                        }
                        else{
                            t = &words.find(">>");
                        }
                    }
                    else{
                        t = new Token('>');
                    }
                    break;
                case '<':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("<=");
                        peek == ' ';
                    }
                    else if(peek == '<'){
                        peek = inbuf.nextChar();
                        if(peek == '='){
                            t = &words.find("<<=");
                            peek == ' ';
                        }
                        else{
                            t = &words.find("<<");
                        }
                    }
                    else{
                        t = new Token('<');
                    }
                    break;
                case '^':
                    peek = inbuf.nextChar();
                    if(peek == '='){
                        t = &words.find("^=");
                        peek == ' ';
                    }
                    else{
                        t = new Token('^');
                    }
                    break;
                case ':':
                    peek = inbuf.nextChar();
                    if(peek == ':'){
                        t = &words.find("::");
                        peek == ' ';
                    }
                    else{
                        t = new Token(':');
                    }
                    break;
                default:
            }
        }
        return t;
    }

    Token* Lexer::scan(){
        skipSpace();
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
        cout << .2f<< "Hello world!" << endl;
        Lexer lex("for(int i = 0; i < 3.8; i++){i = kill;}");
        for(;;)
        {
            Token* t =
            lex.scan();
            if(t != NULL)
            break;
            else
             cout << t->tag << endl;
        }
        return 0;
}
