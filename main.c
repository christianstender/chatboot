//"Chatboot", 2022, by Alberthe Held, Sigurd Kau, Mikkel Nielsen and Christian Stender. Version 0.0.2.

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

//main starts
int main () {
    int function_index = 1, function_index_calculation, record_receiver, file_counter = 1;

    record_receiver = scan_block(file_counter);
    file_counter = file_counter + 1;

    printf("---------------------\n");

    while (function_index < 8)
    {
        function_index_calculation = ask_answer(function_index);
        function_index = function_index_calculation;

        if (function_index >= 8)
        {
            function_index = 1;
            //overwrite værdierne i chatteret, så bruger får nye spørgsmål og svarmuligheder
            //brug funktion
            printf("\n\n-------------\n\n");
        }
    }

    return 0;
}


//function definitions
int scan_block(int fil1)
{
    FILE *file;

    switch (fil1)
    {
    case 1:
        file = fopen("file.txt", "r"); //<- Vi forsøger at åbne filen i 'read' mode
        if (file == NULL)              // Vi laver et exit hvis filen ikk kan åbne
        {
            printf("Error opening file.\n");
            return 1;
        }
        break;
    case 2:
        file = fopen("file2.txt", "r"); //<- Vi forsøger at åbne filen i 'read' mode
        if (file == NULL)               // Vi laver et exit hvis filen ikk kan åbne
        {
            printf("Error opening file.\n");
            return 1;
        }
        break;
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

    return records;
}

int ask_answer(int function_index)
{
    int answer, function_function_index = function_index;
    
    //question and two answer options
    printf("\n%d ) %s\n\n", chatter[function_index].question_int, chatter[function_index].question);
    printf("%d ) %s\n", chatter[function_index].svar1_int, chatter[function_index].svar1);
    printf("%d ) %s\n", chatter[function_index].svar2_int, chatter[function_index].svar2);

    printf("\nChoose your answer: ");
    scanf("%d", &answer);

    if (answer == chatter[function_index].svar1_int)
    {
        function_index = function_index + answer;
        printf("%d", function_index);
        return function_index;
    }
    else
    {
        function_index = function_index + answer;
        printf("%d", function_index);
        return function_index;
    }
    //else if(answer == 3)
    //tuborgklammer 
    //( return function index = function(function index))

    // else if ('q' indtastet så quit, goodbye)
    
    //

}

//Vi tilføjer vores switchcase som skal gøre det muligt at springe tilbage.
// Function: switch (function_index) case 2, function = 0, osv.
