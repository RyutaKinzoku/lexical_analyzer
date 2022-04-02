#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTLEN 64
typedef char string [MAXSTLEN];
char token_buffer[MAXSTLEN];
int token_buffer_index = 0;
FILE *cCode;
FILE *cTemp;

void clear_buffer(void){
    memset(token_buffer, 0, sizeof token_buffer);
    token_buffer_index = 0;
}

void buffer_char(char c){
    token_buffer[token_buffer_index] = c;
    token_buffer_index++;
}

void preprocessing(string fileName){
    if (!strcmp(fileName, ""))
        return;

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1);
    }
    int in_char, c;

    clear_buffer();
    if(feof(file))
        return;
    while ((in_char = getc(file)) != EOF){
        printf("hola %s \n", fileName);
        if (in_char == '#'){
            for (c = getc(file); isalpha(c); c = getc(file)){
                buffer_char(c);
            }
            ungetc(c, file);
            if (!strcmp(token_buffer, "include"))
            {
                clear_buffer();
                int quotes = 0;
                for (c = getc(file); quotes < 2; c = getc(file)){
                    if (c == '\"')
                    {   
                        quotes++;
                    }else if (c == '\n')
                    {
                        printf("There are not enough quotes in the #include directive");
                        fclose(file);
                        exit(-1);
                    } else if (c == '/' && c == 0)
                    {
                        printf("Invalid character in a file");
                        fclose(file);
                        exit(-1);
                    } else if (quotes >= 1)
                    {
                        buffer_char(c);
                    }
                    
                }
                while (c != '\n'){
                    if (!isspace(c))
                    {
                        printf("Extra characters after #include directive");
                        fclose(file);
                        exit(-1);
                    }
                    c = getc(file);
                }
                if (token_buffer_index == 0)
                {
                    printf("Expected filename");
                    fclose(file);
                    exit(-1);
                }

                
            } else if (!strcmp(token_buffer, "define"))
            {
                /* code */
            }else
            {
                /* code */
            }
        }
        else
            continue; 
    }
    fclose(file);
    //cTemp = fopen("cTemp.c", "a+");
}

int main()
{
    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = {};
    scanf("%s", fileName);
    preprocessing(fileName);
    return 0;
}