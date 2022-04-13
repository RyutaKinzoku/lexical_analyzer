/*Definitions*/
%{
    int count = 0;
%}
%option noyywrap
ID (([a-z]|[A-Z])|_)((([a-z]|[A-Z])|_)|[0-9])*
INTLITERAL (-?)[0-9][0-9]*
FLOATLITERAL (({INTLITERAL}+"."{INTLITERAL}*)|{INTLITERAL})
DOUBLELITERAL (({FLOATLITERAL}+"e"{INTLITERAL})|FLOATLITERAL)
CHARLITERAL (.|\n)

/*Rules*/
%%
if|else|while|for|int|float|double|long|char|short {
    printf( "A keyword: %s\n", yytext );
}
%%

/*User code*/
int main( int argc, char **argv )
{

}