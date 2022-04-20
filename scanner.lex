/*Definitions*/
%{
    int count = 0;
%}
%option noyywrap
LPAREN "("
RPAREN ")"
LSQBRACKET "["
RSQBRACKET "]"
LBRACKET "{"
RBRACKET "}"
SEMICOLON ";"
ID (([a-z]|[A-Z])|_)((([a-z]|[A-Z])|_)|[0-9])*
INTLITERAL [0-9][0-9]*
FLOATLITERAL ({INTLITERAL}+"."{INTLITERAL}*)
DOUBLELITERAL ({FLOATLITERAL}+"e"{INTLITERAL})
CHARLITERAL [^( |\n)]

/*Rules*/
%%
auto {
    printf( "A keyword: %s\n", yytext );
}
break {
    printf( "A keyword: %s\n", yytext );
}
case {
    printf( "A keyword: %s\n", yytext );
}
char {
    printf( "A keyword: %s\n", yytext );
}
const {
    printf( "A keyword: %s\n", yytext );
}
continue {
    printf( "A keyword: %s\n", yytext );
}
default {
    printf( "A keyword: %s\n", yytext );
}
do {
    printf( "A keyword: %s\n", yytext );
}
else {
    printf( "A keyword: %s\n", yytext );
}
enum {
    printf( "A keyword: %s\n", yytext );
}
extern {
    printf( "A keyword: %s\n", yytext );
}
double {
    printf( "A keyword: %s\n", yytext );
}
float {
    printf( "A keyword: %s\n", yytext );
}
for {
    printf( "A keyword: %s\n", yytext );
}
goto {
    printf( "A keyword: %s\n", yytext );
}
if {
    printf( "A keyword: %s\n", yytext );
}
int {
    printf( "A keyword: %s\n", yytext );
}
long {
    printf( "A keyword: %s\n", yytext );
}
register {
    printf( "A keyword: %s\n", yytext );
}
return {
    printf( "A keyword: %s\n", yytext );
}
short {
    printf( "A keyword: %s\n", yytext );
}
signed {
    printf( "A keyword: %s\n", yytext );
}
sizeof {
    printf( "A keyword: %s\n", yytext );
}
static {
    printf( "A keyword: %s\n", yytext );
}
struct {
    printf( "A keyword: %s\n", yytext );
}
switch {
    printf( "A keyword: %s\n", yytext );
}
typedef {
    printf( "A keyword: %s\n", yytext );
}
union {
    printf( "A keyword: %s\n", yytext );
}
unsigned {
    printf( "A keyword: %s\n", yytext );
}
void {
    printf( "A keyword: %s\n", yytext );
}
volatile {
    printf( "A keyword: %s\n", yytext );
}
while {
    printf( "A keyword: %s\n", yytext );
}

"+" {
    printf( "A plus operator: %s\n", yytext );
}

"-" {
    printf( "A minus operator: %s\n", yytext );
}

"*" {
    printf( "A multiplication operator: %s\n", yytext );
}

"/" {
    printf( "A division operator: %s\n", yytext );
}

"=" {
    printf( "An equals operator: %s\n", yytext );
}

{LPAREN} printf( "A left parenthesis: %s\n", yytext );

{RPAREN} printf( "A right parenthesis: %s\n", yytext );

{LSQBRACKET} printf( "A left square bracket: %s\n", yytext );

{RSQBRACKET} printf( "A right square bracket: %s\n", yytext );

{LBRACKET} printf( "A left bracket: %s\n", yytext );

{RBRACKET} printf( "A right bracket: %s\n", yytext );

{SEMICOLON} printf( "A semicolon: %s\n", yytext );

{ID} printf( "An identifier: %s\n", yytext );

{INTLITERAL} printf( "An integer: %s\n", yytext );

{FLOATLITERAL} printf( "A float: %s\n", yytext );

{DOUBLELITERAL} printf( "A double: %s\n", yytext );

{CHARLITERAL} printf( "A char: %s\n", yytext );

[ \t\n]+ /* eat up whitespace */

%%

/*User code*/
int main()
{
    typedef char string [512];
    string fileName = {};
    scanf("%s", fileName);
    yyin = fopen( fileName, "r" );
    yylex();
}