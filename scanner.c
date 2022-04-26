#include <stdlib.h>
#include <stdio.h>

typedef char string [512];
static string fileName = {};
FILE* tokens;
int start = 0;
char buffer[MAXSTLEN*4];
int buffer_index = 0;

void clear_buffer(void){
    memset(buffer, 0, sizeof buffer);
    buffer_index = 0;
}

void buffer_char(char c){
    buffer[buffer_index] = c;
    buffer_index++;
    if (buffer_index > MAXSTLEN*4-1)
    {
        printf("Buffer overflow\n");
        exit(-1);
    }
}

typedef struct token{
    enum tokenCode {AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, ELSE, ENUM, EXTERN, DOUBLE, FLOAT, FOR,
        GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, 
        VOID, VOLATILE, WHILE, PLUSOP, MINUSOP, ASTERISKOP, SLASH, ASSIGNOP, NEWLINE, LPAREN, RPAREN, LSQBRACKET, RSQBRACKET,
        LBRACKET, RBRACKET, COMMA, SEMICOLON, ID, INTLITERAL, FLOATLITERAL, DOUBLELITERAL, CHARLITERAL, INVALIDSUFFIX} code;
    string lexeme;
} token;

const char* tokenNames[] = {"AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "ELSE", "ENUM", "EXTERN", "DOUBLE", "FLOAT", "FOR",
        "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", 
        "VOID", "VOLATILE", "WHILE", "PLUSOP", "MINUSOP", "ASTERISKOP", "SLASH", "ASSIGNOP", "NEWLINE", "LPAREN", "RPAREN", "LSQBRACKET", "RSQBRACKET",
        "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON", "ID", "INTLITERAL", "FLOATLITERAL", "DOUBLELITERAL", "CHARLITERAL", "INVALIDSUFFIX"};

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
        tokens = fopen("tokensTemp.c", "r");
        start++;
    }
    char c;

    while((c = getc(tokens)) != "\n"){
        buffer_char(c);
        for(c = getc(tokens); c != ' '; c = getc(tokens))
        buffer_char(c);

    }
}