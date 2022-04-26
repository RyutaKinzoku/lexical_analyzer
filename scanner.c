#include <stdlib.h>
typedef char string [512];
static string fileName = {};

void command(char c []){
    char command[256];
    strcpy(command, c);
    system(command);
}

void compileFlex(string file){
    strcpy(fileName, file);
    
    command("lex scanner.lex");
    command("gcc lex.yy.c");
    command("./a.out");
}

void getToken(){
}