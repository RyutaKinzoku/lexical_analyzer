#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTLEN 128
typedef char string [MAXSTLEN];
char buffer[MAXSTLEN*4];
int buffer_index = 0;
FILE *cCode;
FILE *cTemp;

typedef struct Tuples
{
    char identifier[MAXSTLEN];
    char expression[MAXSTLEN*2];
} tuple;

typedef struct NewArrays
{
    tuple defines[512];
    int index;
} newArray;


void clear_buffer(void){
    memset(buffer, 0, sizeof buffer);
    buffer_index = 0;
}

void buffer_char(char c){
    buffer[buffer_index] = c;
    buffer_index++;
    if (buffer_index > MAXSTLEN*4-1)
    {
        printf("Buffer overflow\n");
        exit(-1);
    }
}

void concatArray(newArray* original, newArray* extension){
    for (int i = 0; i < extension->index; i++)
    {
        original->defines[original->index] = extension->defines[i];
        if(original->index >=512){
            printf("Too many define directives");
            exit(-1);
        }
        original->index++;
    }
}

void replace(tuple actualDef){
    FILE* interTemp = fopen("interTemp.c", "a+");
    int in_char, c;
    FILE* tmp = fopen("interTemp.c", "a+");
    int slash = 0;
    int quotes = 0;
    int apostrophe = 0;
    while ((in_char = getc(interTemp)) != EOF)
    {
        clear_buffer();
        for (c = getc(interTemp); isalnum(c) || c == '_'; c = getc(interTemp)){
            buffer_char(c);
        }
        ungetc(c, interTemp);
        if (!isalnum(in_char) && in_char != '_')
        {
            fprintf(tmp, "%c", in_char);
            if(in_char = '/')
                slash++;
            else if(in_char == '\"')
                quotes++;
            else if(in_char == '\"')
                apostrophe++;
        }
        if (!strcmp(actualDef.identifier, buffer))
        {
            if(slash < 2){
                fprintf(tmp, "%s", actualDef.expression);
            } else if(quotes != 1){
                fprintf(tmp, "%s", actualDef.expression);
            } else if(apostrophe != 1){
                fprintf(tmp, "%s", actualDef.expression);
            }
            slash, quotes, apostrophe = 0;
        } else if (buffer_index > 0){
            fprintf(tmp, "%s", buffer);
        }
    }
    fclose(interTemp);
    interTemp = fopen("interTemp.c", "w");
    while ((in_char = getc(tmp)) != EOF)
    {
        clear_buffer();
        if (in_char != '\n' && in_char != EOF)
        {
            buffer_char(in_char);
        }else if (in_char == '\n')
        {
            fprintf(interTemp, "%s\n", buffer);
        } else{
            fprintf(interTemp, "%s", buffer);
        }
    }
    fclose(tmp);
    remove("tmp.c");
    fclose(interTemp);
}

newArray preprocessing(string pfileName){
    newArray localDef, tmpDef;
    string fileName;
    strcpy(fileName, pfileName);

    localDef.index = 0;
    tmpDef.index = 0;

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1);
    }

    int in_char, c;
    while ((in_char = getc(file)) != EOF){
        if (in_char == '#'){
            clear_buffer();
            for (c = getc(file); isalpha(c); c = getc(file)){
                buffer_char(c);
            }
            ungetc(c, file);
            if (!strcmp(buffer, "include"))
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
                while (c != '\n' && c != EOF){
                    if (!isspace(c) && extraChar == 0)
                    {
                        printf("Warning: Extra characters after #include directive\n");
                        extraChar++;
                    }
                    c = getc(file);
                }
                if (buffer_index == 0)
                {
                    printf("Expected filename\n");
                    fclose(file);
                    exit(-1);
                }
                tmpDef = preprocessing(buffer);
                concatArray(&localDef, &tmpDef);
            } 
        }
    }
    
    fclose(file);
    FILE* tmpFile = fopen("interTemp.c", "w");
    file = fopen(fileName, "r");
    while ((in_char = getc(file)) != EOF){
        clear_buffer();
        if (in_char == '#'){
            for (c = getc(file); isalpha(c); c = getc(file)){
                buffer_char(c);
            }
            ungetc(c, file);
            if (!strcmp(buffer, "include"))
            {
                for (c = getc(file); c != '\n' && c != EOF; c = getc(file));
            } else if (!strcmp(buffer, "define"))
            {
                fprintf(tmpFile, "#%s", buffer);
            }
        } else
        {
            fprintf(tmpFile, "%c", in_char);
        }
    }
    fclose(file);
    fclose(tmpFile);
    
    //Replace children defines to the current file
    for(int i = 0; i < localDef.index; i++){
        replace(localDef.defines[i]);
    }

    file = fopen(fileName, "r");
    clear_buffer();
    if(feof(file))
        return;
    while ((in_char = getc(file)) != EOF){
        if (in_char == '#'){
            for (c = getc(file); isalpha(c); c = getc(file)){
                buffer_char(c);
            }
            ungetc(c, file);
            if (!strcmp(buffer, "define"))
            {
                clear_buffer();
                int section = 0;
                tuple actualDef;
                for (c = getc(file); c != '\n' && c != EOF; c = getc(file)){
                    if (section == 0)
                    {
                        if((isalpha(c) || c == '_') && buffer_index == 0){
                            buffer_char(c);
                        }
                        else if ((isalnum(c) || c == '_') && buffer_index > 0)
                        {
                            buffer_char(c);
                        }
                        else if (isspace(c) && buffer_index > 0)
                        {
                            section++;
                            strcpy(actualDef.identifier, buffer);
                            clear_buffer();
                        }
                        else if (!isspace(c))
                        {
                            printf("Macro names must be identifiers\n");
                            fclose(file);
                            exit(-1);
                        }
                    }
                    else if (section == 1)
                    {
                        if (isspace(c) && buffer_index == 0)
                        {
                            continue;
                        } else 
                        {
                            buffer_char(c);
                        }
                    }
                }
                if (buffer_index == 0)
                {
                    printf("Expected an expresion\n");
                    fclose(file);
                    exit(-1);
                }
                strcpy(actualDef.expression, buffer);
                printf("%s:%s\n", actualDef.identifier, actualDef.expression);
                localDef.defines[localDef.index] = actualDef;
                localDef.index++;
                replace(actualDef);
            }
        }
    }
    fclose(file);
    // Add to the final temporary file the inter temp data
    FILE* interTemp = fopen("interTemp.c", "r");
    FILE* cTemp = fopen("cTemp.c", "a+");
    while ((in_char = getc(interTemp)) != EOF){
        if (in_char != '#'){
            clear_buffer();
            buffer_char(in_char);
            for (c = getc(interTemp); c != '\n' && c != EOF; c = getc(interTemp)){
                buffer_char(c);
            }
            fprintf(cTemp, "%s\n", buffer);
        } else{
            for (c = getc(interTemp); c != '\n' && c != EOF; c = getc(interTemp));
        }
    }
    fclose(interTemp);
    fclose(cTemp);
    return localDef;
}

int main()
{
    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = {};
    scanf("%s", fileName);
    remove("cTemp.c");
    preprocessing(fileName);
    //remove("interTemp.c");
    return 0;
}