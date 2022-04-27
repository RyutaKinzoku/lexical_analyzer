#include <stdio.h>
#include "preprocessing.c"
#include "createPresentation.c"

int main()
{
    token tok;
    tok.code = ENDOF;

    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = {};
    scanf("%s", fileName);
    remove("cTemp.c");
    preprocessing(fileName);
    remove("interTemp.c");
    compileFlex("cTemp.c");

    createPresentation();
    setCategories();
    openSlide();
    for(token t = getToken(); t.code < ENDOF; t = getToken()){
        printf("Lexema: %s, code: %d\n", t.lexeme, t.code);
        addToken(t);
    }
    addToken(tok);
    endDocument();

    remove("cTemp.c");
    //command("pdflatex beamerPresentation.tex");
    //command("evince -f beamerPresentation.pdf");
    return 0;
}