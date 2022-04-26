#include "preprocessing.c"
#include "scanner.c"

int main()
{
    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = {};
    scanf("%s", fileName);
    remove("cTemp.c");
    preprocessing(fileName);
    remove("interTemp.c");
    compileFlex("cTemp.c");
    for(token t = getToken(); t.code < 52; t = getToken()){
        printf("Lexema: %s, code: %d\n", t.lexeme, t.code);
    }
    return 0;
}