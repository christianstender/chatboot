#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char scan_block()
{
    FILE *file;
    file = fopen("file.txt", "r"); //<- Vi forsøger at åbne filen i 'read' mode
    if (file == NULL)              // Vi laver et exit hvis filen ikk kan åbne
    {
        printf("Error opening file.\n");
        return 1;
    }

    int read = 0;
    int records = 0;

    do // Hernede læser vi indholdet af filen
    {
        read = fscanf(file,
                      "%49[^,],%49[^,],%49[^\n]\n", // Her indlæser vi 3 strenge, de første to læser vi frem til komma, den sidste læser vi frem til linebreak.
                      chatter[records].question, chatter[records].svar1, chatter[records].svar2);
        if (read == 3) // Hvis den læser 3 elementer i første linje tæller vi records op. 
            records++;

        if (read != 3 && !feof(file)) // Hvis den læser et andet antal så laver vi endnu en exit.
        {
            printf("File format incorrect.\n");
            return 2;
        }

        if (ferror(file)) // Igen en error, hvis vi ikke kan læse selve filen.
        {
            printf("Error reading file.\n");
            return 1;
        }

    } while (!feof(file)); // Vi når til enden af vores fil i vores do while
    fclose(file);
    printf("\n%d records read.\n\n", records); // Vi præsenterer hvor mange records der er læst
    for (int i = 0; i < records; i++)          // Og vi printer det indlæste
        printf("%s %s %s\n",
               chatter[i].question, chatter[i].svar1, chatter[i].svar2);
    printf("\n");
    return 0;
}