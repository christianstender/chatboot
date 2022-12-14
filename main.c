#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "header.h"

char *file_names[3] = {"file.txt", "file2.txt", "file3.txt"};

int main()
{

    int function_index = 0, file_index = 0, climate_anxiety_counter = 0, end_of_tree = 16;
    int climate_anxiety[3];
    char username[20];
    char context[3][650];

    printf("\nHej med dig! Hvad hedder du? ");
    scanf("%s", &username);
    printf("\nGodt at moede dig %s!\n\n", username);

    manuscript *manuscript_ptr = read_manuscript(file_index, file_names);
    read_context(context);

    FILE *chatlog = fopen("chat_log.txt", "w");
    fclose(chatlog);

    while (function_index < end_of_tree)
    {
        if (function_index == 0)
        {
            anxiety_tracker(climate_anxiety, climate_anxiety_counter);
            climate_anxiety_counter++;
            print_context(context, file_index);
        }

        if (function_index > 8 && function_index < end_of_tree && function_index != 8 && function_index != 12)
        {
            chat_log(function_index, manuscript_ptr, 1);
            function_index = print_comment(manuscript_ptr, function_index);
        }
        else
        {
            function_index = chat_with_user(function_index, manuscript_ptr);
        }

        if (function_index >= end_of_tree && climate_anxiety_counter > 2)
        {
            print_anxiety_graph(climate_anxiety);
            print_graph_comment(climate_anxiety);
        }

        else if (function_index >= end_of_tree)
        {
            function_index = 0;
            file_index++;
            free(manuscript_ptr);

            manuscript_ptr = read_manuscript(file_index, file_names);
            printf("\n\n------NEW FILE READ------\n\n");
        }
    }

    return 0;
}