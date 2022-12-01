#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "header.h"

char *file_names[3] = {"file.txt", "file2.txt", "file3.txt"};

int main(int argc, char *argv[])
{
    // sætter farve på baggrund og tekst
    system("COLOR 0F");

    // initialiserer heltal til at navigere det binære træ og til at åbne den rigtige .txt fil
    int function_index = 0, file_index = 0, anxiety_counter = 0;
    int climate_anxiety[3];

    // indlæser .txt fil til structen
    block *chatter = scan_block(file_index, file_names);
    
    // overwriting last version of chat_log
    FILE *log_open = fopen("chat_log.txt", "w");
    fclose(log_open);

    // siger hej til brugeren via programparametre
    printf("\n\nHej med dig %s :) Godt at snakke med dig!\n\n", argv[1]);

    // et while-loop, der går gennem det binære træ
    while (function_index < 32)
    {
        if (function_index == 0)
        {
            anxiety_tracker(climate_anxiety, anxiety_counter);
            anxiety_counter++;
        }
        
        // selve funktionen, der printer question, svar1 og svar2 til brugeren
        function_index = ask_answer(function_index, chatter);

        if (function_index >= 32 && anxiety_counter > 2)
        {
            print_anxiety(climate_anxiety);
        } 

        else if (function_index >= 32)
        {
            // genstarter binært træ og gør klar til næste fil
            function_index = 0;
            file_index++;
            free(chatter);

            // indlæser ny fil
            chatter = scan_block(file_index, file_names);
            printf("\n\n------NEW FILE READ------\n\n");
        }
    }

    return 0;
}