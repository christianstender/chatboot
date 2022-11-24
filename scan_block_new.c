#include <stdio.h>
#include <stdlib.h>

struct block
{
    char question[50];
    char svar1[50];
    char svar2[50];
};
typedef struct block block;

int main()
{
    block *dyna = (block *)malloc(283);

    FILE *file = fopen("file.txt", "r");

    char line[100];
    int i;

    for (i = 0; i < 2; i++)
    {
        fgets((dyna+i)->question, 50, file);
        fgets((dyna+i)->svar1, 50, file);
        fgets((dyna+i)->svar2, 50, file);

        printf("%s\n", (dyna+i)->question);
        printf("%s\n", (dyna+i)->svar1);
        printf("%s\n", (dyna+i)->svar2);

        printf("\n\n--------------\n\n");
    }

    fclose(file);

    return 0;
}