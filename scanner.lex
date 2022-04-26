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
    fprintf(tokensTemp, "%s\n", yytext);
}
break {
    fprintf(tokensTemp, "%s\n", yytext);
}
case {
    fprintf(tokensTemp, "%s\n", yytext);
}
char {
    fprintf(tokensTemp, "%s\n", yytext);
}
const {
    fprintf(tokensTemp, "%s\n", yytext);
}
continue {
    fprintf(tokensTemp, "%s\n", yytext);
}
default {
    fprintf(tokensTemp, "%s\n", yytext);
}
do {
    fprintf(tokensTemp, "%s\n", yytext);
}
else {
    fprintf(tokensTemp, "%s\n", yytext);
}
enum {
    fprintf(tokensTemp, "%s\n", yytext);
}
extern {
    fprintf(tokensTemp, "%s\n", yytext);
}
double {
    fprintf(tokensTemp, "%s\n", yytext);
}
float {
    fprintf(tokensTemp, "%s\n", yytext);
}
for {
    fprintf(tokensTemp, "%s\n", yytext);
}
goto {
    fprintf(tokensTemp, "%s\n", yytext);
}
if {
    fprintf(tokensTemp, "%s\n", yytext);
}
int {
    fprintf(tokensTemp, "%s\n", yytext);
}
long {
    fprintf(tokensTemp, "%s\n", yytext);
}
register {
    fprintf(tokensTemp, "%s\n", yytext);
}
return {
    fprintf(tokensTemp, "%s\n", yytext);
}
short {
    fprintf(tokensTemp, "%s\n", yytext);
}
signed {
    fprintf(tokensTemp, "%s\n", yytext);
}
sizeof {
    fprintf(tokensTemp, "%s\n", yytext);
}
static {
    fprintf(tokensTemp, "%s\n", yytext);
}
struct {
    fprintf(tokensTemp, "%s\n", yytext);
}
switch {
    fprintf(tokensTemp, "%s\n", yytext);
}
typedef {
    fprintf(tokensTemp, "%s\n", yytext);
}
union {
    fprintf(tokensTemp, "%s\n", yytext);
}
unsigned {
    fprintf(tokensTemp, "%s\n", yytext);
}
void {
    fprintf(tokensTemp, "%s\n", yytext);
}
volatile {
    fprintf(tokensTemp, "%s\n", yytext);
}
while {
    fprintf(tokensTemp, "%s\n", yytext);
}

"+" {
    fprintf(tokensTemp, "%s\n", yytext);
}

"-" {
    fprintf(tokensTemp, "%s\n", yytext);
}

"*" {
    fprintf(tokensTemp, "%s\n", yytext);
}

"/" {
    fprintf(tokensTemp, "%s\n", yytext);
}

"=" {
    fprintf(tokensTemp, "%s\n", yytext);
}

{NEWLINE} fprintf(tokensTemp, "%s", yytext);

{LPAREN} fprintf(tokensTemp, "%s\n", yytext);

{RPAREN} fprintf(tokensTemp, "%s\n", yytext);

{LSQBRACKET} fprintf(tokensTemp, "%s\n", yytext);

{RSQBRACKET} fprintf(tokensTemp, "%s\n", yytext);

{LBRACKET} fprintf(tokensTemp, "%s\n", yytext);

{RBRACKET} fprintf(tokensTemp, "%s\n", yytext);

{COMMA} fprintf(tokensTemp, "%s\n", yytext);

{SEMICOLON} fprintf(tokensTemp, "%s\n", yytext);

{ID} fprintf(tokensTemp, "%s\n", yytext);

{INTLITERAL} fprintf(tokensTemp, "%s\n", yytext);

{FLOATLITERAL} fprintf(tokensTemp, "%s\n", yytext);

{DOUBLELITERAL} fprintf(tokensTemp, "%s\n", yytext);

{CHARLITERAL} fprintf(tokensTemp, "%s\n", yytext);

{INVALIDSUFFIX} fprintf(tokensTemp, "%s\n", yytext);

[ \t]+ /* eat up whitespace */

%%

/*User code*/
int main()
{
    tokensTemp = fopen("tokensTemp", "w");
    yyin = fopen( "cTemp.c", "r" );
    yylex();
}