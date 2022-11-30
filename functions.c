#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CuTest.h"
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

    // en kommando, der gør, at prints virker bedre
    setbuf(stdout, NULL);

    // initialiserer et char-array som er mellemmand i indlæsningen, i til  brug i while-løkken og total som skal indeholde størrelsen af filen vi indlæser
    char string[300];
    int i = 0, total = 0;

    // første læsning af fil char for char, for at finde størrelsen af filen i bytes
    while (!feof(file) && !ferror(file))
    {
        fgetc(file);
        total++;
    }
    // sætter fil-pointeren til at pege på første char i filen igen
    rewind(file);

    // initialiserer dynamisk array med størrelse lige fundet (1 char = 1 byte)
    // størrelsen på malloc er ikke en joke... kan forklare når vi ses
    block *chatter = malloc(15000);

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

    // bruger kan inputte svar
    printf("\nChoose your answer: ");
    scanf("%d", &answer);

    // kalder chatlog for at gemme question, svar1, svar2 og det svar brugeren valgte
    chat_log(function_index, chatter, answer);

    // en lange if-else, der sørger for at returnere det korrekte index til main
    if (answer != 1 && answer != 2)
    {
        printf("\nEXIT - Du indtastede noget andet end 1 eller 2\n");
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
}

void chat_log(int function_index, block *chatter, int answer)
{
    // åbner filen chat_log.txt
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

    // lukker filen chat-log.txt
    fclose(log);
}

void test_til_suites(CuTest *tc)
{
    double acutal = sum_of_sides(0, 0, 1, 0, 1, 1);
    double expected = 1.4142135624 + 1 + 1;

    CuAssertDblEquals(tc, expected, acutal, 0.00001);
}

/****** SUIT *******/

CuSuite *testsuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_til_suites); // NEW
    // TODO: Add more tests

    return suite;
}