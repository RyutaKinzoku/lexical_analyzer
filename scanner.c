#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char string [512];
FILE* tokens;
int start = 0;
string token_buffer;
int token_buffer_index = 0;

void clear_token_buffer(void){
    memset(token_buffer, 0, sizeof token_buffer);
    token_buffer_index = 0;
}

void token_buffer_char(char c){
    token_buffer[token_buffer_index] = c;
    token_buffer_index++;
    if (token_buffer_index > 512-1)
    {
        printf("Buffer overflow\n");
        exit(-1);
    }
}

typedef struct Tokens{
    char lexeme[256];
    enum tokenCode {AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, ELSE, ENUM, EXTERN, DOUBLE, FLOAT, FOR,
        GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, 
        VOID, VOLATILE, WHILE, PLUSOP, MINUSOP, ASTERISKOP, SLASHOP, ASSIGNOP, NEWLINE, LPAREN, RPAREN, LSQBRACKET, RSQBRACKET,
        LBRACKET, RBRACKET, COMMA, SEMICOLON, ID, INTLITERAL, FLOATLITERAL, DOUBLELITERAL, CHARLITERAL, INVALIDSUFFIX, PLUSEQOP, ENDOF} code;
} token;

const string tokenNames[] = {"AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "ELSE", "ENUM", "EXTERN", "DOUBLE", "FLOAT", "FOR",
        "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", 
        "VOID", "VOLATILE", "WHILE", "PLUSOP", "MINUSOP", "ASTERISKOP", "SLASHOP", "ASSIGNOP", "NEWLINE", "LPAREN", "RPAREN", "LSQBRACKET", "RSQBRACKET",
        "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON", "ID", "INTLITERAL", "FLOATLITERAL", "DOUBLELITERAL", "CHARLITERAL", "INVALIDSUFFIX", "PLUSEQOP", "ENDOF"};

void command(char c []){
    char command[256];
    strcpy(command, c);
    system(command);
}

void compileFlex(string file){
    command("lex scanner.lex");
    command("gcc lex.yy.c");
    command("./a.out");
}

token getToken(){
    if(start == 0){
        tokens = fopen("tokensTemp", "r");
        start++;
    }
    char c;
    token tok;
    char tokenName[512];
    c = getc(tokens);
    if(c == '\n') {
        tok.code = 37;
        strcpy(tok.lexeme, "\n");
        return tok;
    }
    while(c != '\n'){
        if(c == EOF){
            tok.code = ENDOF;
            strcpy(tok.lexeme, "");
            fclose(tokens);
            return tok;
        } else {
            clear_token_buffer();
            token_buffer_char(c);
            for(c = getc(tokens); !isspace(c); c = getc(tokens)){
                token_buffer_char(c);
            }
            strcpy(tok.lexeme, token_buffer);
            clear_token_buffer();
            for(c = getc(tokens); c != '\n'; c = getc(tokens)){
                token_buffer_char(c);
            }
            tok.code = atoi(token_buffer);
        }
    }
    
    return tok;
}