#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTLEN 128
typedef char string [MAXSTLEN];
char token_buffer[MAXSTLEN];
int token_buffer_index = 0;
FILE *cCode;
FILE *cTemp;
char identifiers [MAXSTLEN][MAXSTLEN*2];
char expressions [MAXSTLEN][MAXSTLEN*2];
int defineIndex = 0;

void clear_buffer(void){
    memset(token_buffer, 0, sizeof token_buffer);
    token_buffer_index = 0;
}

void buffer_ids(char c, int index){
    if (index > MAXSTLEN*2-1)
    {
        printf("Buffer overflow\n");
        exit(-1);
    }
    identifiers[defineIndex][index] = c;
}

void buffer_char(char c){
    token_buffer[token_buffer_index] = c;
    token_buffer_index++;
    if (token_buffer_index > MAXSTLEN-1)
    {
        printf("Buffer overflow\n");
        exit(-1);
    }
}

void preprocessing(string fileName){
    printf("file %s\n", fileName);
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
                        printf("There are not enough quotes in the #include directive\n");
                        fclose(file);
                        exit(-1);
                    } else if (c == '/' || c == 0)
                    {
                        printf("Invalid character in a file\n");
                        fclose(file);
                        exit(-1);
                    } else if (quotes >= 1)
                    {
                        buffer_char(c);
                    } else if (!isspace(c))
                    {
                        printf("Expected filename\n");
                        fclose(file);
                        exit(-1);
                    }
                }
                int extraChar = 0;
                while (c != '\n'){
                    if (!isspace(c) && extraChar == 0)
                    {
                        printf("Warning: Extra characters after #include directive\n");
                        extraChar++;
                    }
                    c = getc(file);
                }
                if (token_buffer_index == 0)
                {
                    printf("Expected filename\n");
                    fclose(file);
                    exit(-1);
                }
                preprocessing(token_buffer);
            } else if (!strcmp(token_buffer, "define"))//////////////////////////
            {
                clear_buffer();
                int flag = 0;
                int index = 0;
                for (c = getc(file); c != '\n'; c = getc(file)){
                    if(flag == 0 && (isalpha(c) || c == '_')){
                        buffer_ids(c, index);
                        index++;
                    }
                    if (isspace(c) && flag == 0 && token_buffer_index > 0)
                    {
                        flag++;

                    }
                    
                    if (isdigit(c) && token_buffer_index == 0)
                    {
                        printf("Macro names must be identifiers\n");
                        fclose(file);
                        exit(-1);
                    }
                    if (c == '\"')
                    {   
                        //quotes++;
                    }else if (c == '\n')
                    {
                        printf("There are not enough quotes in the #include directive\n");
                        fclose(file);
                        exit(-1);
                    } else if (c == '/' || c == 0)
                    {
                        printf("Invalid character in a file\n");
                        fclose(file);
                        exit(-1);
                    } /*else if (quotes >= 1)
                    {
                        buffer_char(c);
                    }*/ else if (!isspace(c))
                    {
                        printf("Expected filename\n");
                        fclose(file);
                        exit(-1);
                    }
                }
                int extraChar = 0;
                while (c != '\n'){
                    if (!isspace(c) && extraChar == 0)
                    {
                        printf("Extra characters after #include directive\n");
                        extraChar++;
                    }
                    c = getc(file);
                }
                if (token_buffer_index == 0)
                {
                    printf("Expected filename\n");
                    fclose(file);
                    exit(-1);
                }
                preprocessing(token_buffer);
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