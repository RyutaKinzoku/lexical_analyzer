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
STRINGLITERAL \"(([^\"]|\\\")*[^\\])?\"

/*Rules*/
%%
auto {
    printf( "An auto keyword: %s\n", yytext );
}
break {
    printf( "A break keyword: %s\n", yytext );
}
case {
    printf( "A case keyword: %s\n", yytext );
}
char {
    printf( "A char keyword: %s\n", yytext );
}
const {
    printf( "A const keyword: %s\n", yytext );
}
continue {
    printf( "A continue keyword: %s\n", yytext );
}
default {
    printf( "A default keyword: %s\n", yytext );
}
do {
    printf( "A do keyword: %s\n", yytext );
}
else {
    printf( "An else keyword: %s\n", yytext );
}
enum {
    printf( "An enum keyword: %s\n", yytext );
}
extern {
    printf( "An extern keyword: %s\n", yytext );
}
double {
    printf( "A double keyword: %s\n", yytext );
}
float {
    printf( "A float keyword: %s\n", yytext );
}
for {
    printf( "A float keyword: %s\n", yytext );
}
goto {
    printf( "A goto keyword: %s\n", yytext );
}
if {
    printf( "An if keyword: %s\n", yytext );
}
int {
    printf( "An int keyword: %s\n", yytext );
}
long {
    printf( "A long keyword: %s\n", yytext );
}
register {
    printf( "A register keyword: %s\n", yytext );
}
return {
    printf( "A return keyword: %s\n", yytext );
}
short {
    printf( "A short keyword: %s\n", yytext );
}
signed {
    printf( "A signed keyword: %s\n", yytext );
}
sizeof {
    printf( "A sizeof keyword: %s\n", yytext );
}
static {
    printf( "A static keyword: %s\n", yytext );
}
struct {
    printf( "A struct keyword: %s\n", yytext );
}
switch {
    printf( "A switch keyword: %s\n", yytext );
}
typedef {
    printf( "A typedef keyword: %s\n", yytext );
}
union {
    printf( "A union keyword: %s\n", yytext );
}
unsigned {
    printf( "An unsigned keyword: %s\n", yytext );
}
void {
    printf( "A void keyword: %s\n", yytext );
}
volatile {
    printf( "A volatile keyword: %s\n", yytext );
}
while {
    printf( "A while keyword: %s\n", yytext );
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