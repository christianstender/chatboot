//"Chatbot", 2022, by Alberthe Held, Sigurd Kau, Mikkel Nielsen and Christian Stender. Version 0.0.2.
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int ekstrafunktion(int j);

int main(void)
{
    // Vi finder vores fil-> Vi åbner den-> Vi læser den-> Vi printer den-> Vi lukker den og returnerer records som er antallet af linjer i filen.
    int fil1 = 1;
    int records = scan_block(fil1);

    // initializing stuff
    // every variable of "structure block"-type contains 3 strings of chars
    int i = 0, input, j = 0, k;

    /// Vi skal skal scanne et sted mellem 2 og 3 variable, disse variable må gerne pege på bestemte questions string. der må altså gerne være en standardfordeling og så en ekstra tildeling som kan pege på en question string med et helt andet index tal.
    printf("Records: %d", records);

    while (j <= records)
    {
        int ekstrataeller = ekstrafunktion(j);
        printf("\nSpørgsmål: %s\nTast '1' for %s\nTast '2' for: %s\n",
               chatter[j].question, chatter[j].svar1, chatter[j].svar2);
        if (ekstrataeller != 400)
        {
            printf("Tast '3' for: %s\n", chatter[ekstrataeller].svar1);
        }

        scanf(" %d", &input);
        if (input == 1)
        {
            // printf("\n%s\n", chatter[j].svar1);
            j++;
        }
        else if (input == 2)
        {
            // printf("\n%s\n", chatter[j].svar2);
            j++;
        }
        else if (input == 3)
        {
            //  Her vil vi justere j vores for loop så vi kan gå tilbage til et tidligere spørgsmål.

            j = ekstrafunktion(j);
        }
        else if (input == 0)
        {
            printf("Programmet er afsluttet\n");
            break;
        }
        else
        {
            printf("Ugyldigt input\n");
        }
    }

    return 0;
}

int ekstrafunktion(int j)
{
    if (j == 2 || j == 4)
    {
        switch (j)
        {
        case 2:
            j = 0;
            break;
        case 4:
            j = 10;
            break;
        }
    }
    else
    {
        j = 400;
    }

    return j;
}

int ekstrafunktionrand(int j)
{
    if (j == 2 || j == 4)
    {
        switch (j)
        {
        case 2:
            j = 0;
            break;
        case 4:
            j = 10;
            break;
        }
    }
    else
    {
        j = 400;
    }

    return j;
}