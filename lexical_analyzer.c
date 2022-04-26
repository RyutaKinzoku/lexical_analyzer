#include <stdio.h>
#include "preprocessing.c"
#include "scanner.c"
#include "createPresentation.c"

int main()
{
    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = {};
    scanf("%s", fileName);
    remove("cTemp.c");
    preprocessing(fileName);
    remove("interTemp.c");
    compileFlex("cTemp.c");
    for(token t = getToken(); t.code < ENDOF; t = getToken()){
        printf("Lexema: %s, code: %d\n", t.lexeme, t.code);
    }
    remove("cTemp.c");
    createPresentation();
    setCategories();
    command("cd beamer");
    command("pdflatex beamerPresentation.tex");
    command("evince -f beamerPresentation.pdf");
    return 0;
}