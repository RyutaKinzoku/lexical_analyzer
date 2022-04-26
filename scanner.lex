/*Definitions*/
%{
    #include <stdio.h>
    FILE* tokensTemp;
%}
%option noyywrap
LPAREN "("
RPAREN ")"
LSQBRACKET "["
RSQBRACKET "]"
LBRACKET "{"
RBRACKET "}"
SEMICOLON ";"
COMMA ","
NEWLINE "\n"
ID (([a-z]|[A-Z])|_)((([a-z]|[A-Z])|_)|[0-9])*
INTLITERAL [0-9][0-9]*
FLOATLITERAL ({INTLITERAL}+"."{INTLITERAL}*)
DOUBLELITERAL ({FLOATLITERAL}+"e"{INTLITERAL})
CHARLITERAL [^( |\n)]
INVALIDSUFFIX [0-9]([a-z]|[A-Z]|_|[0-9])*

/*Rules*/
%%
auto {
    fprintf(tokensTemp, "%s AUTO\n", yytext);
}
break {
    fprintf(tokensTemp, "%s BREAK\n", yytext);
}
case {
    fprintf(tokensTemp, "%s CASE\n", yytext);
}
char {
    fprintf(tokensTemp, "%s CHAR\n", yytext);
}
const {
    fprintf(tokensTemp, "%s CONST\n", yytext);
}
continue {
    fprintf(tokensTemp, "%s CONTINUE\n", yytext);
}
default {
    fprintf(tokensTemp, "%s DEFAULT\n", yytext);
}
do {
    fprintf(tokensTemp, "%s DO\n", yytext);
}
else {
    fprintf(tokensTemp, "%s ELSE\n", yytext);
}
enum {
    fprintf(tokensTemp, "%s ENUM\n", yytext);
}
extern {
    fprintf(tokensTemp, "%s EXTERN\n", yytext);
}
double {
    fprintf(tokensTemp, "%s DOUBLE\n", yytext);
}
float {
    fprintf(tokensTemp, "%s FLOAT\n", yytext);
}
for {
    fprintf(tokensTemp, "%s FOR\n", yytext);
}
goto {
    fprintf(tokensTemp, "%s GOTO\n", yytext);
}
if {
    fprintf(tokensTemp, "%s IF\n", yytext);
}
int {
    fprintf(tokensTemp, "%s INT\n", yytext);
}
long {
    fprintf(tokensTemp, "%s LONG\n", yytext);
}
register {
    fprintf(tokensTemp, "%s REGISTER\n", yytext);
}
return {
    fprintf(tokensTemp, "%s RETURN\n", yytext);
}
short {
    fprintf(tokensTemp, "%s SHORT\n", yytext);
}
signed {
    fprintf(tokensTemp, "%s SIGNED\n", yytext);
}
sizeof {
    fprintf(tokensTemp, "%s SIZEOF\n", yytext);
}
static {
    fprintf(tokensTemp, "%s STATIC\n", yytext);
}
struct {
    fprintf(tokensTemp, "%s STRUCT\n", yytext);
}
switch {
    fprintf(tokensTemp, "%s SWITCH\n", yytext);
}
typedef {
    fprintf(tokensTemp, "%s TYPEDEF\n", yytext);
}
union {
    fprintf(tokensTemp, "%s UNION\n", yytext);
}
unsigned {
    fprintf(tokensTemp, "%s UNSIGNED\n", yytext);
}
void {
    fprintf(tokensTemp, "%s VOID\n", yytext);
}
volatile {
    fprintf(tokensTemp, "%s VOLATILE\n", yytext);
}
while {
    fprintf(tokensTemp, "%s WHILE\n", yytext);
}

"+" {
    fprintf(tokensTemp, "%s PLUSOP\n", yytext);
}

"-" {
    fprintf(tokensTemp, "%s MINUSOP\n", yytext);
}

"*" {
    fprintf(tokensTemp, "%s ASTERISKOP\n", yytext);
}

"/" {
    fprintf(tokensTemp, "%s SLASHOP\n", yytext);
}

"=" {
    fprintf(tokensTemp, "%s ASSIGNOP\n", yytext);
}

{NEWLINE} fprintf(tokensTemp, "%s NEWLINE", yytext);

{LPAREN} fprintf(tokensTemp, "%s LPAREN\n", yytext);

{RPAREN} fprintf(tokensTemp, "%s RPAREN\n", yytext);

{LSQBRACKET} fprintf(tokensTemp, "%s LSQBRACKET\n", yytext);

{RSQBRACKET} fprintf(tokensTemp, "%s RSQBRACKET\n", yytext);

{LBRACKET} fprintf(tokensTemp, "%s LBRACKET\n", yytext);

{RBRACKET} fprintf(tokensTemp, "%s RBRACKET\n", yytext);

{COMMA} fprintf(tokensTemp, "%s COMMA\n", yytext);

{SEMICOLON} fprintf(tokensTemp, "%s SEMICOLON\n", yytext);

{ID} fprintf(tokensTemp, "%s ID\n", yytext);

{INTLITERAL} fprintf(tokensTemp, "%s INTLITERAL\n", yytext);

{FLOATLITERAL} fprintf(tokensTemp, "%s FLOATLITERAL\n", yytext);

{DOUBLELITERAL} fprintf(tokensTemp, "%s DOUBLELITERAL\n", yytext);

{CHARLITERAL} fprintf(tokensTemp, "%s CHARLITERAL\n", yytext);

{INVALIDSUFFIX} fprintf(tokensTemp, "%s INVALIDSUFFIX\n", yytext);

[ \t]+ /* eat up whitespace */

%%

/*User code*/
int main()
{
    tokensTemp = fopen("tokensTemp", "w");
    yyin = fopen( "cTemp.c", "r" );
    yylex();
}