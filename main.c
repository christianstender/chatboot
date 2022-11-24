//"Chatbot", 2022, by Alberthe Held, Sigurd Kau, Jens Petersen and Christian Stender. Version 0.0.2.
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

// main starts
int main()
{
    setbuf(stdout, NULL);
    int function_index = 0, file_index = 0;

    block *chatter = scan_block(file_index);

    while (function_index < 8)
    {
        function_index = ask_answer(function_index, chatter);

        if (function_index >= 8)
        {
            function_index = 0;
            file_index++;
            free(chatter);
            chatter = scan_block(file_index);
            // overwrite værdierne i chatteret, så bruger får nye spørgsmål og svarmuligheder
            // brug funktion
            printf("\n\n------NEW FILE READ------\n\n");
        }
    }

    return 0;
}

// function definitions
block *scan_block(int file_index)
{
    FILE *file = fopen(file_names[file_index], "r");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    block *chatter = (block *)malloc(size_of_file(file));
    rewind(file);

    int i;
    int lines = read_lines(file);
    rewind(file);

    for (i = 0; i < lines; i++)
    {
        fgets((chatter + i)->question, 50, file);
        fgets((chatter + i)->svar1, 50, file);
        fgets((chatter + i)->svar2, 50, file);
    }

    fclose(file);

    return chatter;
}

int ask_answer(int function_index, block *chatter)
{
    int answer;

    // question and two answer options
    printf("\nQuestion: %s\n\n", (chatter + function_index)->question);
    printf("1) %s\n", (chatter + function_index)->svar1);
    printf("2) %s\n", (chatter + function_index)->svar2);

    printf("\nChoose your answer: ");
    scanf("%d", &answer);

    // binary tree calculations
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
    else
    {
        function_index = 3;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
}

int size_of_file(FILE *file)
{
    fseek(file, 0L, SEEK_END);

    int result = ftell(file);

    return result;
}

int read_lines(FILE *file)
{
    char string[100];
    int counter = 0;

    while (fgets(string, 50, file) != NULL)
    {
        counter = counter + 1;
    }

    printf("\nLines in file: %d\n", counter);

    return counter;
}