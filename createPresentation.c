#include <stdio.h>

typedef struct Types{
    char color[128];
    char fontFamily[128];
    int hasFamily;
    int isBold;
    int isItalic;
    int isUnderlined;
} type;

type categories[30];
type operators, intLiterals, floatLiterals, doubleLiteral, charLiteral, stringLiteral, reservedWords, separators, identifiers;

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
    strcpy(doubleLiteral.color, "\\color{CadetBlue}");
    strcpy(doubleLiteral.fontFamily, "qbk");
    doubleLiteral.hasFamily = 1;
    doubleLiteral.isBold = 1;
    doubleLiteral.isItalic = 1;
    doubleLiteral.isUnderlined = 1;

    //CharLiterals
    strcpy(charLiteral.color, "\\color{Violet}");
    strcpy(charLiteral.fontFamily, "lmdh");
    charLiteral.hasFamily = 1;
    charLiteral.isBold = 0;
    charLiteral.isItalic = 0;
    charLiteral.isUnderlined = 0;

    //StringLiteral
    strcpy(stringLiteral.color, "\\color{ForestGreen}");
    strcpy(stringLiteral.fontFamily, "lmdh");
    stringLiteral.hasFamily = 1;
    stringLiteral.isBold = 1;
    stringLiteral.isItalic = 0;
    stringLiteral.isUnderlined = 0;

    //ReservedWords
    strcpy(reservedWords.color, "\\color{Olive}");
    strcpy(reservedWords.fontFamily, "");
    reservedWords.hasFamily = 0;
    reservedWords.isBold = 1;
    reservedWords.isItalic = 0;
    reservedWords.isUnderlined = 1;

    //separators
    strcpy(separators.color, "\\color{Cyan}");
    strcpy(separators.fontFamily, "");
    separators.hasFamily = 0;
    separators.isBold = 0;
    separators.isItalic = 1;
    separators.isUnderlined = 0;
    
    //Identifiers
    strcpy(identifiers.color, "\\color{Blue}");
    strcpy(identifiers.fontFamily, "");
    identifiers.hasFamily = 0;
    identifiers.isBold = 0;
    identifiers.isItalic = 0;
    identifiers.isUnderlined = 0;
}

void addToken(token t){
    
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

    fprintf(presentation, "%s\n", "\\begin{frame}{Scanning}");
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
    fprintf(presentation, "%s\n", "\\item \\emph{Separator characters}");
    fprintf(presentation, "%s\n", "\\color{blue}");
    fprintf(presentation, "%s\n", "\\item Identifiers");
    fprintf(presentation, "%s\n", "\\end{itemize}");
    fprintf(presentation, "%s\n", "\\end{frame}");
    fprintf(presentation, "%s\n", "\\end{document}");
    fclose(presentation);
}