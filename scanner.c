#include <stdlib.h>
#include <stdio.h>

typedef char string [512];
FILE* tokens;
int start = 0;
char token_buffer[512];
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
    enum tokenCode {AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, ELSE, ENUM, EXTERN, DOUBLE, FLOAT, FOR,
        GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, 
        VOID, VOLATILE, WHILE, PLUSOP, MINUSOP, ASTERISKOP, SLASHOP, ASSIGNOP, NEWLINE, LPAREN, RPAREN, LSQBRACKET, RSQBRACKET,
        LBRACKET, RBRACKET, COMMA, SEMICOLON, ID, INTLITERAL, FLOATLITERAL, DOUBLELITERAL, CHARLITERAL, INVALIDSUFFIX, ENDOF} code;
    char lexeme[512];
} token;

const char* tokenNames[] = {"AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "ELSE", "ENUM", "EXTERN", "DOUBLE", "FLOAT", "FOR",
        "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", 
        "VOID", "VOLATILE", "WHILE", "PLUSOP", "MINUSOP", "ASTERISKOP", "SLASHOP", "ASSIGNOP", "NEWLINE", "LPAREN", "RPAREN", "LSQBRACKET", "RSQBRACKET",
        "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON", "ID", "INTLITERAL", "FLOATLITERAL", "DOUBLELITERAL", "CHARLITERAL", "INVALIDSUFFIX", "ENDOF"};

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

    while((c = getc(tokens)) != '\n'){
        if(c == EOF){
            tok.code = 52;
            strcpy(tok.lexeme, "");
            fclose(tokens);
            return tok;
        } else {
            clear_token_buffer();
            token_buffer_char(c);
            for(c = getc(tokens); c != ' '; c = getc(tokens)){
                printf("%c\n", c);
                token_buffer_char(c);
            }
            printf("%s\n", token_buffer);
            printf("%s\n", tok.lexeme);
            strcpy(tok.lexeme, token_buffer);
            printf("Hola");
            clear_token_buffer();
            for(c = getc(tokens); c != '\n'; c = getc(tokens)){
                token_buffer_char(c);
            }
            ungetc(c, tokens);
            for(int i = 0; i < sizeof tokenNames; i++){
                if(!strcmp(tokenNames[i], token_buffer)){
                    tok.code = i;
                }
            }
        }
    }
    return tok;
}