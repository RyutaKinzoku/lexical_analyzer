#include <stdio.h>

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