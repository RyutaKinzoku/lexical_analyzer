#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char string [64];
FILE *cCode;
FILE *cTemp;

void preprocessing(){
    cTemp = fopen("cTemp.c", "a+");
}

int main()
{
    printf("Welcome to the lexical analyzer, please type the name of the file that you want to analyze:\n");
    string fileName = "";
    scanf("%s", fileName);
    cCode = fopen(fileName, "r");
    if (cCode == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1);
    }
    preprocessing();
    fclose(cCode);
    return 0;
}