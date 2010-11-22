#include "string"
#include <map>
#include <iostream>

using namespace std;
    class Tag{
        public :
        static const int NUM    = 0X100;
        static const int ID     = 0X101;

        static const int REVERSE= 0X102;

        static const int P_NULL         = 0X103;
        static const int B_TRUE         = 0X104;
        static const int B_FALSE        = 0X105;

        static const int OP_POINT_TO            = 0X106;
        static const int OP_LESS_OR_EQUAL       = 0X107;
        static const int OP_GREATER_OR_EQUAL    = 0X108;
        static const int OP_EQUAL               = 0X109;
        static const int OP_NOT_EQUAL           = 0X10A;
        static const int OP_BOLL_AND            = 0X10B;
        static const int OP_BOOL_OR             = 0X10C;
        static const int OP_ADD_ASSIGN          = 0X10D;
        static const int OP_SUBTRACT_ASSIGN     = 0X10E;
        static const int OP_MULTY_ASSIGN        = 0X10F;
        static const int OP_DIVISION_ASSIGN     = 0X110;
        static const int OP_REMAINDER_ASSIGN    = 0X111;
        static const int OP_BIT_AND_ASSIGN      = 0X112;
        static const int OP_BIT_OR_ASSIGN       = 0X113;
        static const int OP_BIT_NOT_ASSIGN      = 0X114;
        static const int OP_LEFT_SHIFT_ASSIGN   = 0X115;
        static const int OP_RIGHT_SHIFT_ASSIGN  = 0X116;
        static const int OP_INCREMENT           = 0X117;
        static const int OP_DECREMENT           = 0X118;
        static const int OP_SIZEOF              = 0X119;
        static const int OP_LEFT_SHIFT          = 0X11A;
        static const int OP_RIGHT_SHIFT         = 0X11B;
        static const int OP_RESERVED            = 0X11C;

        static const int MACRO_TYPEDEF   = 0X11D;

        static const int LIM_CONST   = 0X11E;
        static const int LIM_STATIC   = 0X11F;
        static const int LIM_EXTERN   = 0X120;

        static const int TYPE_LONG      = 0X121;
        static const int TYPE_SHORT     = 0X122;
        static const int TYPE_SIGNED    = 0X123;
        static const int TYPE_UNSIGNED  = 0X124;

        static const int TYPE_INT       = 0X125;
        static const int TYPE_FLOAT     = 0X126;
        static const int TYPE_DOUBLE    = 0X127;
        static const int TYPE_CHAR      = 0X128;
        static const int TYPE_ENUM      = 0X129;
        static const int TYPE_STRUCT    = 0X12A;
        static const int TYPE_UNION     = 0X12B;
        static const int TYPE_VOID      = 0X12C;
        static const int TYPE_RESERVED  = 0X12D;

        static const int ST_IF      = 0X12E;
        static const int ST_ELSE    = 0X12F;
        static const int ST_ELSE_IF = 0X130;
        static const int ST_SWITCH  = 0X131;
        static const int ST_CASE    = 0X132;
        static const int ST_DEFUALT = 0X133;
        static const int ST_WHILE   = 0X134;
        static const int ST_DO      = 0X135;
        static const int ST_FOR     = 0X136;
        static const int ST_GOTO    = 0X137;
        static const int ST_BREAK   = 0X138;
        static const int ST_CONTINUE= 0X139;
        static const int ST_REATURN = 0X13A;
        static const int ST_RESERVED= 0X13B;

        static const int ELS_ASM        = 0X13C;
        static const int ELS_AUTO       = 0X13D;
        static const int ELS_EDECL      = 0X13E;
        static const int ELS_FAR        = 0X13F;
        static const int ELS_HUGE       = 0X140;
        static const int ELS_INTERRUPT  = 0X141;
        static const int ELS_NEAR       = 0X142;
        static const int ELS_PASCAL     = 0X143;
        static const int ELS_REGISTER   = 0X144;
        static const int ELS_VOLATILE   = 0X145;

        static const int TOTAL_NUM  = 0X46;
        static const int OFFSET     = 0X100;


    };
    static const string RESERVED_STRINGS[] = {
            "",         "",         "",         "null",     "true",     "false",    "->",       "<=",
            ">=",       "==",       "!=",       "&&",       "||",       "+=",       "-=",       "*=",

            "/=",       "%=",       "&=",       "|=",       "^=",       "<<=",      ">>=",      "++",
            "--",       "sizeof",   "<<",       ">>",       "::",       "typedef",  "const",    "static",

            "extern",   "long",     "short",    "signed",   "unsigned", "int",      "float",    "double",
            "char",     "enum",     "struct",   "union",    "void",     "",         "if",       "else",

            "else if",  "switch",   "case",     "default",  "while",    "do",       "for",      "goto",
            "break",    "continue", "return",   "",         "asm",      "auto",     "edecl",    "far",

            "huge",     "interrupt","near",     "pascal",   "register", "volatile"
        };
    class Token{
        public :
        int tag;
        Token(){
            tag = -1;
        }

        Token(int tag){
            this->tag = tag;
        }
    };
    class Num : public Token{
        public :
        static const int FLOAT_NUM = 0;
        static const int DOUBLE_NUM = 5;
        static const int LONG_NUM = 1;
        static const int UNSIGNED_NUM = 2;
        static const int UNSIGNED_LONG_NUM = 3;
        static const int SHORT_NUM = 4;
        static const int CHAR_VALUE = 6;
        static const int INT_NUM = 7;
        static const int STRING_VALUE = 8;

        double value;
        int type;

        Num(double value, int tag):Token(Tag::NUM){
            type = tag;
            switch(tag){
                case FLOAT_NUM:
                    this->value = (float)value;
                    break;
                case LONG_NUM:
                    this->value = (long)value;
                    break;
                case UNSIGNED_NUM:
                    this->value = (unsigned)value;
                    break;
                case UNSIGNED_LONG_NUM:
                    this->value = (unsigned long)value;
                    break;
                case SHORT_NUM:
                    this->value = (short)value;
                    break;
                case CHAR_VALUE:
                    this->value = (char)value;
                    break;
                case INT_NUM:
                    this->value = (int)value;
                    break;
                default:
                    this->value = value;
                    break;;
            }

        }
    };
    class String : public Num{
    public:
        string svalue;
        String(string svalue):Num(0,Num::STRING_VALUE){
            this->svalue = svalue;
        }
    };
    class Word :public Token{
        public :
        string lexeme;

        Word(int tag, string name):Token(tag){
            lexeme = name;
        }
    };
    class Buffer{
        private :
        char buf[4096];
        unsigned int offset;

        public :
        Buffer(){
            offset = 0;
            memset(buf,0,4096);
        }
        void read(string value);
        char nextChar();
        char first(){
            return buf[0];
        }
    };
    class Lexer{
        private :
        char peek;
        map<string, Word> words;
        Buffer inbuf;

        void skipSpace();
        Token* dealConst();
        Token* dealChar();
        Token* dealString();
        Token* dealNum();
        Token* dealWord();
        Token* dealOperator();

        public :
        int line;
        Token* scan();
        Lexer(string value){

            peek = ' ';
            line = 1;
            for(int i = 2; i < Tag::TOTAL_NUM; ++i){
                words.insert(map<string,Word>::value_type(RESERVED_STRINGS[i], Word(Tag::OFFSET + i, RESERVED_STRINGS[i])));
                //cout << "insert i = " << i << endl;
            }
            //cout << "insert end" << endl;
            inbuf.read(value);
        }

    };


