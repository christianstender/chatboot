#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "header.h"

// definitioner af funktioner som vi kalder i main.c

block *scan_block(int file_index, char *file_names[3])
{
    // åbner fil, hvor vi indlæser question, svar1 og svar2 fra
    FILE *file = fopen(file_names[file_index], "r");

    // fail-safe som er et krav at have, når man åbner en fil
    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    // initialiserer dynamisk array med 32 structs (passer med størrelsen på det binære træ) + initialiserer i og string til brug senere
    // giver ik mening at have funktion, der tæller størrelsen af filen fordi vi kender størrelsen på det binære træ...
    // og det ville giver mere kompliceret arbejde med det binære træ
    block *chatter = malloc(32 * sizeof(block));
    char string[300];
    int i = 0;

    // indlæsning til struct starter! (betingelsen for while-løkken betyder: Læser indtil vi kommer til enden af filen)
    for (i = 0; i < 32; i++)
    {
        fgets(string, 100, file);
        strcpy(chatter[i].question, string);

        fgets(string, 100, file);
        strcpy(chatter[i].svar1, string);

        fgets(string, 100, file);
        strcpy(chatter[i].svar2, string);
    }

    // lukker fil vi indlæser question, svar1 og svar2 fra
    fclose(file);

    // returnerer det dynamiske array til main
    return chatter;
}

int ask_answer(int function_index, block *chatter)
{
    // initialiserer heltal som skal indeholde brugerens svar på spørgsmålet
    int answer;

    // printer question, svar1 og svar2 til bruger
    printf("\nQuestion: %s\n\n", chatter[function_index].question);
    printf("1) %s\n", chatter[function_index].svar1);
    printf("2) %s\n", chatter[function_index].svar2);
    printf("3) gaa tilbage til sidste spoergsmaal\n");

    // bruger kan inputte svar
    printf("\nChoose your answer: ");
    scanf("%d", &answer);

    // kalder chatlog for at gemme question, svar1, svar2 og det svar brugeren valgte
    chat_log(function_index, chatter, answer);

    // en lange if-else, der sørger for at returnere det korrekte index til main
    if (answer != 1 && answer != 2 && answer != 3)
    {
        printf("\nEXIT - Du indtastede noget andet end 1, 2 eller 3\n");
        exit(EXIT_FAILURE);
    }

    if (answer == 1 && function_index != 0)
    {
        function_index = function_index * 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (answer == 2 && function_index != 0)
    {
        function_index = function_index * 2 + 1;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (answer == 1 && function_index == 0)
    {
        function_index = 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (answer == 2 && function_index == 0)
    {
        function_index = 3;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (answer == 3 && function_index % 2 == 0)
    {
        function_index = function_index / 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (answer == 3 && function_index % 2 != 0)
    {
        function_index = (function_index - 1) / 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
}

void chat_log(int function_index, block *chatter, int answer)
{
    // flusher sidste version af chat_log.txt og åbner filen chat_log.txt
    FILE *log = fopen("chat_log.txt", "a");

    // printer question, svar1 og svar2 til filen chat_log.txt
    fprintf(log, "\nQuestion: %s---------\n", chatter[function_index].question);
    fprintf(log, "1) %s\n", chatter[function_index].svar1);
    fprintf(log, "2) %s\n", chatter[function_index].svar2);

    // if-else statement, der printer brugerens svar til chat_log.txt
    if (answer == 1)
    {
        fprintf(log, "You chose: 1) %s\n", chatter[function_index].svar1);
    }
    else if (answer == 2)
    {
        fprintf(log, "You chose: 2) %s\n", chatter[function_index].svar2);
    }
    else if (answer == 3)
    {
        fprintf(log, "Du gik tilbage til sidste spørgsmål\n");
    }

    // lukker filen chat-log.txt
    fclose(log);
}

void anxiety_tracker(int climate_anxiety[], int anxiety_counter)
{
    int answer;

    printf("Hvor meget klima-angst foeler du lige nu paa en skala fra 1-10? ");
    scanf("%d", &answer);
    printf("\nTak!\n");

    climate_anxiety[anxiety_counter] = answer;
}

void print_anxiety(int climate_anxiety[])
{
    // forklarer det her in person :)
    // funktionen her printer en illustration af brugerens klima-angst
    
    char line[12][50];
    char integer1[3];
    char integer2[3];
    char integer3[3];
    int i, k;

    strcpy(line[11], "|___________________________\n");
    
    for (i = 0; i < 11; i++)
    {
        strcpy(line[i], "|                    \n");
    }

    for (k = 0; k < 3; k++)
    {
        for (i = 1; i < 11; i++)
        {
            if (climate_anxiety[k] == i && k == 0)
            {
                strcpy(line[11 - i], "|     ");

                itoa(i, integer1, 10);
                strcat(line[11 - i], integer1);
                strcat(line[11 - i], "\n");
            }
            else if (climate_anxiety[k] == i && k == 1)
            {
                strcpy(line[11 - i], "|             ");
                itoa(i, integer2, 10);
                strcat(line[11 - i], integer2);
                strcat(line[11 - i], "\n");
            }
            else if (climate_anxiety[k] == i && k == 2)
            {
                strcpy(line[11 - i], "|                    ");
                itoa(i, integer3, 10);
                strcat(line[11 - i], integer3);
                strcat(line[11 - i], "\n");
            }
        }
    }

    printf("\n\n\nHer er progressionen over din klima-angst igennem samtalen: \n\n");

    for (i = 0; i < 12; i++)
    {
        printf("%s", line[i]);
    }

    printf("\n\n");
}
