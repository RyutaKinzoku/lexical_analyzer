#include <stdio.h>
#include <math.h>
#include "scanner.c"

typedef struct Types{
    char color[128];
    char fontFamily[128];
    int hasFamily;
    int isBold;
    int isItalic;
    int isUnderlined;
} type;

int lineQuantity = 0;
int charQuantity = 0;

type operators, intLiterals, floatLiterals, doubleLiterals, charLiterals, stringLiterals, reservedWords, separators, identifiers, errors;

void setCategories(){
    //Operators
    strcpy(operators.color, "\\color{OrangeRed}");
    strcpy(operators.fontFamily, "");
    intLiterals.hasFamily = 0;
    operators.isBold = 0;
    operators.isItalic = 1;
    operators.isUnderlined = 0;

    //IntLiterals
    strcpy(intLiterals.color, "\\color{Purple}");
    strcpy(intLiterals.fontFamily, "qbk");
    intLiterals.hasFamily = 1;
    intLiterals.isBold = 0;
    intLiterals.isItalic = 0;
    intLiterals.isUnderlined = 0;

    //FloatLiterals
    strcpy(floatLiterals.color, "\\color{Turquoise}");
    strcpy(floatLiterals.fontFamily, "qbk");
    floatLiterals.hasFamily = 1;
    floatLiterals.isBold = 1;
    floatLiterals.isItalic = 0;
    floatLiterals.isUnderlined = 0;

    //DoubleLiterals
    strcpy(doubleLiterals.color, "\\color{CadetBlue}");
    strcpy(doubleLiterals.fontFamily, "qbk");
    doubleLiterals.hasFamily = 1;
    doubleLiterals.isBold = 1;
    doubleLiterals.isItalic = 1;
    doubleLiterals.isUnderlined = 1;

    //CharLiterals
    strcpy(charLiterals.color, "\\color{Violet}");
    strcpy(charLiterals.fontFamily, "lmdh");
    charLiterals.hasFamily = 1;
    charLiterals.isBold = 0;
    charLiterals.isItalic = 0;
    charLiterals.isUnderlined = 0;

    //StringLiteral
    strcpy(stringLiterals.color, "\\color{ForestGreen}");
    strcpy(stringLiterals.fontFamily, "lmdh");
    stringLiterals.hasFamily = 1;
    stringLiterals.isBold = 1;
    stringLiterals.isItalic = 0;
    stringLiterals.isUnderlined = 0;

    //ReservedWords
    strcpy(reservedWords.color, "\\color{Olive}");
    strcpy(reservedWords.fontFamily, "");
    reservedWords.hasFamily = 0;
    reservedWords.isBold = 1;
    reservedWords.isItalic = 0;
    reservedWords.isUnderlined = 1;

    //separators
    strcpy(separators.color, "\\color{Black}");
    strcpy(separators.fontFamily, "");
    separators.hasFamily = 0;
    separators.isBold = 1;
    separators.isItalic = 0;
    separators.isUnderlined = 0;
    
    //Identifiers
    strcpy(identifiers.color, "\\color{Blue}");
    strcpy(identifiers.fontFamily, "");
    identifiers.hasFamily = 0;
    identifiers.isBold = 0;
    identifiers.isItalic = 0;
    identifiers.isUnderlined = 0;

    //Errors
    strcpy(errors.color, "\\color{Pink}");
    strcpy(errors.fontFamily, "ptf");
    errors.hasFamily = 1;
    errors.isBold = 0;
    errors.isItalic = 0;
    errors.isUnderlined = 1;
}

void endDocument(){
    FILE* presentation = fopen("beamerPresentation.tex", "a+");
    fprintf(presentation, "%s\n", "\\end{document}");
    fclose(presentation);
}

void openSlide(){
    FILE* presentation = fopen("beamerPresentation.tex", "a+");
    fprintf(presentation, "%s\n", "\\begin{frame}{Font Lines}");
    fclose(presentation);
}

void closeSlide(){
    FILE* presentation = fopen("beamerPresentation.tex", "a+");
    fprintf(presentation, "%s\n", "\\end{frame}");
    fclose(presentation);
}

void fprintfLexeme(char* prefix, char* suffix, FILE* presentation, char* lexeme){
    fprintf(presentation, "%s", prefix);
    for(int i = 0; lexeme[i] != 0; i++) {
        if(lexeme[i] == '%') fprintf(presentation, "%s", "\\%");
        else if (lexeme[i] == '{') {
            fprintf(presentation, "%s", "\\{");
            printf("Soy un bracket");
        } 
        else if (lexeme[i] == '}') fprintf(presentation, "%s", "\\}");
        else if (lexeme[i] == '\\') fprintf(presentation, "%s", "\\textbackslash ");
        else if (lexeme[i] > 127) fprintf(presentation, "%s", "<E>");
        else fprintf(presentation, "%c", lexeme[i]);
    }
    fprintf(presentation, "%s", suffix);
}

void addToken(token t){
    if(t.code == NEWLINE) {
        lineQuantity += ceil(charQuantity/46);
        if(lineQuantity >= 16){
            closeSlide();
            lineQuantity = 0;
            charQuantity = 0;
            openSlide();
        }
        FILE* presentation = fopen("beamerPresentation.tex", "a+");
        fprintf(presentation, "%s\n", "\\\\");
        fclose(presentation);
    } else if (t.code == ENDOF){
        closeSlide();
    } else {
        charQuantity++;
        for(int i = 0; t.lexeme[i] != 0; i++) {
            charQuantity++;
        }
        if(46*lineQuantity+charQuantity>736) {
            closeSlide();
            openSlide();
        } 

        FILE* presentation = fopen("beamerPresentation.tex", "a+");
        if(t.code >= PLUSOP && t.code < INTLITERAL){
            fprintf(presentation, "%s\n", operators.color);
            fprintfLexeme("\\emph{", "} \n", presentation, t.lexeme);
        } else if(t.code == INTLITERAL){
            fprintf(presentation, "%s\n", intLiterals.color);
            fprintf(presentation, "{\\fontfamily{%s", intLiterals.fontFamily);
            fprintfLexeme("} \\selectfont ", "} \n", presentation, t.lexeme);
        } else if(t.code == FLOATLITERAL){
            fprintf(presentation, "%s\n", floatLiterals.color);
            fprintf(presentation, "{\\fontfamily{%s", floatLiterals.fontFamily);
            fprintfLexeme("} \\selectfont \\textbf{", "}} \n", presentation, t.lexeme);
        } else if(t.code == DOUBLELITERAL){
            fprintf(presentation, "%s\n", doubleLiterals.color);
            fprintf(presentation, "{\\fontfamily{%s", doubleLiterals.fontFamily);
            fprintfLexeme("} \\selectfont \\textbf{\\underline{\\emph{", "}}}} \n", presentation, t.lexeme);
        } else if(t.code == CHARLITERAL){
            fprintf(presentation, "%s\n", charLiterals.color);
            fprintf(presentation, "{\\fontfamily{%s", charLiterals.fontFamily);
            fprintfLexeme("} \\selectfont ", "} \n", presentation, t.lexeme);
        } else if(t.code == STRINGLITERAL){
            fprintf(presentation, "%s\n", stringLiterals.color);
            fprintf(presentation, "{\\fontfamily{%s", stringLiterals.fontFamily);
            fprintfLexeme("} \\selectfont \\textbf{", "}} \n", presentation, t.lexeme);
        } else if(t.code >= AUTO && t.code < LPAREN){
            fprintf(presentation, "%s\n", reservedWords.color);
            fprintfLexeme("\\textbf{\\underline{", "}} \n", presentation, t.lexeme);
        } else if(t.code >= LPAREN && t.code < ID){
            fprintf(presentation, "%s\n", separators.color);
            fprintfLexeme("\\textbf{", "} \n", presentation, t.lexeme);
        } else if(t.code == ID){
            fprintf(presentation, "%s\n", identifiers.color);
            fprintfLexeme("", " \n", presentation, t.lexeme);
        } else if(t.code >= INVALIDSUFFIX && t.code < NEWLINE){
            fprintf(presentation, "%s\n", errors.color);
            fprintf(presentation, "{\\fontfamily{%s", errors.fontFamily);
            fprintfLexeme("} \\selectfont \\underline{", "}} \n", presentation, t.lexeme);
        }
        
        fclose(presentation);
    }
}

void createPresentation(){
    FILE* presentation = fopen("beamerPresentation.tex", "w");
    fprintf(presentation, "%s\n", "\\documentclass [xcolor=svgnames, t] {beamer}"); 
    fprintf(presentation, "%s\n", "\\usepackage[utf8]{inputenc}");
    fprintf(presentation, "%s\n", "\\usepackage{booktabs, comment} "); 
    fprintf(presentation, "%s\n", "\\usepackage[absolute, overlay]{textpos}");
    fprintf(presentation, "%s\n", "\\usepackage{pgfpages}");
    fprintf(presentation, "%s\n\n", "\\usepackage[font=footnotesize]{caption}");

    fprintf(presentation, "%s\n", "\\setbeamercolor{author in head/foot}{bg=darkcyan}");
    fprintf(presentation, "%s\n", "\\setbeamertemplate{page number in head/foot}{}");
    fprintf(presentation, "%s\n\n", "\\usepackage{csquotes}");

    fprintf(presentation, "%s\n", "\\usepackage{amsmath}");
    fprintf(presentation, "%s\n\n", "\\usepackage[makeroom]{cancel}");

    fprintf(presentation, "%s\n\n", "\\usepackage{textpos}");

    fprintf(presentation, "%s\n\n", "\\usepackage{tikz}");

    fprintf(presentation, "%s\n", "\\usetheme{Madrid}");
    fprintf(presentation, "%s\n", "\\definecolor{darkcyan}{RGB}{0, 139, 139}");
    fprintf(presentation, "%s\n", "\\usecolortheme[named=darkcyan]{structure}");
    fprintf(presentation, "%s\n\n", "\\usepackage{tikz}");
    
    fprintf(presentation, "%s\n", "\\title[Lexical Analysis]{Lexical Analysis}");
    fprintf(presentation, "%s\n", "\\subtitle{C Language}");
    fprintf(presentation, "%s\n", "\\author[Project 1]{Reyner Marxell Arias Muñoz, Kenneth Ibarra Vargas, David Benavides Naranjo}");
    fprintf(presentation, "%s\n", "\\institute[]{Project 1, Compilers and Interpreters course, I 2022 Semester}");
    fprintf(presentation, "%s\n\n", "\\date{\\today}");

    fprintf(presentation, "%s\n", "\\begin{document}");
    fprintf(presentation, "%s\n", "\\begin{frame}");
    fprintf(presentation, "%s\n", "\\maketitle");
    fprintf(presentation, "%s\n\n", "\\end{frame}");

    fprintf(presentation, "%s\n", "\\begin{frame}{Scanning}");
    fprintf(presentation, "%s\n", "Since the source file has include and define directives, the preprocessor previously applied each of them correctly so that the scanner receives only a temporary input file.");
    fprintf(presentation, "%s\n", "\\\\Afterwards, the scanner goes through the temporary file returning the tokens one by one and in order, according to the parsed source program. In c there are tokens of different types such as operators, identifiers, literals, reserved words and separator characters.");
    fprintf(presentation, "%s\n", "\\\\Any character not belonging to the c lexicon that can be parsed is returned as a lexical error.\\\\");
    fprintf(presentation, "%s\n", "\\begin{figure}");
    fprintf(presentation, "%s\n", "\\centering");
    fprintf(presentation, "%s\n", "\\includegraphics[scale = 0.14]{Scanner.png}");
    fprintf(presentation, "%s\n", "\\end{figure}");
    fprintf(presentation, "%s\n\n", "\\end{frame}");

    fprintf(presentation, "%s\n", "\\begin{frame}{FLEX}");
    fprintf(presentation, "%s\n", "The scanner is a lex file, which are comprised of three sections:");
    fprintf(presentation, "%s\n", "\\begin{itemize}");
    fprintf(presentation, "%s\n", "\\item The Definition Section: This sections is made up of several regular expressions that act as global declarations that may be used in the next section.");
    fprintf(presentation, "%s\n", "\\item The Rules Section: This section uses the global declarations of the previous section to define what actions must be taken when a specific regular expression is found.");
    fprintf(presentation, "%s\n", "\\item The Code Section: This section is attached at the end of the lex output file and may contain any code written and executed by the C code, due to lex usually being paired with yacc. \\\\");
    fprintf(presentation, "%s\n", "\\end{itemize}");
    fprintf(presentation, "%s\n\n", "\\end{frame}");

    fprintf(presentation, "%s\n", "\\begin{frame}{Tokens}");
    fprintf(presentation, "%s\n", "\\begin{itemize}");
    fprintf(presentation, "%s\n", "\\color{OrangeRed}");
    fprintf(presentation, "%s\n", "\\item \\emph{Operators}");
    fprintf(presentation, "%s\n", "\\color{purple}");
    fprintf(presentation, "%s\n", "{\\fontfamily{qbk} \\selectfont \\item Intliterals}");
    fprintf(presentation, "%s\n", "\\color{Turquoise}");
    fprintf(presentation, "%s\n", "{\\fontfamily{qbk} \\selectfont \\item \\textbf{Floatliterals}}");
    fprintf(presentation, "%s\n", "\\color{CadetBlue}");
    fprintf(presentation, "%s\n", "{\\fontfamily{qbk} \\selectfont \\item \\underline{\\emph{\\textbf{Doubleliteral}}}}");
    fprintf(presentation, "%s\n", "\\color{violet}");
    fprintf(presentation, "%s\n", "{\\fontfamily{lmdh} \\selectfont \\item Charliteral}");
    fprintf(presentation, "%s\n", "\\color{ForestGreen}");
    fprintf(presentation, "%s\n", "{\\fontfamily{lmdh} \\selectfont \\item \\textbf{Stringliteral}}");
    fprintf(presentation, "%s\n", "\\color{olive}");
    fprintf(presentation, "%s\n", "\\item \\underline{\\textbf{Reserved Words}}");
    fprintf(presentation, "%s\n", "\\color{cyan}");
    fprintf(presentation, "%s\n", "\\item \\textbf{Separator characters}");
    fprintf(presentation, "%s\n", "\\color{blue}");
    fprintf(presentation, "%s\n", "\\item Identifiers");
    fprintf(presentation, "%s\n", "\\color{Pink}");
    fprintf(presentation, "%s\n", "{\\fontfamily{ptf} \\selectfont \\item \\underline{Errors}}");
    fprintf(presentation, "%s\n", "\\end{itemize}");
    fprintf(presentation, "%s\n", "\\end{frame}");
    fclose(presentation);
}