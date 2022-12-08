#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include "header.h"
#include "CuTest.h"

// definitioner af funktioner som vi kalder i main.c

manuscript *read_manuscript(int file_index, char *file_names[3])
{
    FILE *file = fopen(file_names[file_index], "r");

    if (file == NULL)
    {
        printf("\nKunne ikke indlaese fil");
        exit(EXIT_FAILURE);
    }

    manuscript *manuscript_ptr = malloc(32 * sizeof(manuscript));
    int i = 0;

    for (i = 0; i < 32; i++)
    {
        fgets(manuscript_ptr[i].question, 100, file);

        fgets(manuscript_ptr[i].svar1, 100, file);

        fgets(manuscript_ptr[i].svar2, 100, file);
    }

    fclose(file);

    return manuscript_ptr;
}

int chat_with_user(int function_index, manuscript *manuscript_ptr)
{
    int user_answer;

    if (function_index == 0)
    {
        printf("\nQuestion: %s\n\n", manuscript_ptr[function_index].question);
        printf("1) %s\n", manuscript_ptr[function_index].svar1);
        printf("2) %s\n", manuscript_ptr[function_index].svar2);
    }
    else
    {
        printf("\nQuestion: %s\n\n", manuscript_ptr[function_index].question);
        printf("1) %s\n", manuscript_ptr[function_index].svar1);
        printf("2) %s\n", manuscript_ptr[function_index].svar2);
        printf("3) gaa tilbage til sidste spoergsmaal\n");
    }

    printf("\nChoose your answer: ");
    scanf("%d", &user_answer);

    if (user_answer > 2 && function_index == 0)
    {
        printf("\nDu indtastede noget andet end svarmulighederne");
        exit(EXIT_FAILURE);
    }

    chat_log(function_index, manuscript_ptr, user_answer);

    if (user_answer != 1 && user_answer != 2 && user_answer != 3)
    {
        printf("\nEXIT - Du indtastede noget andet end 1, 2 eller 3\n");
        exit(EXIT_FAILURE);
    }

    if (user_answer == 1 && function_index != 0)
    {
        function_index = function_index * 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (user_answer == 2 && function_index != 0)
    {
        function_index = function_index * 2 + 1;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (user_answer == 1 && function_index == 0)
    {
        function_index = 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (user_answer == 2 && function_index == 0)
    {
        function_index = 3;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (user_answer == 3 && function_index % 2 == 0)
    {
        function_index = function_index / 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
    else if (user_answer == 3 && function_index % 2 != 0)
    {
        function_index = (function_index - 1) / 2;
        printf("\n|INDEX : %d|\n", function_index);
        return function_index;
    }
}

void chat_log(int function_index, manuscript *manuscript_ptr, int user_answer)
{
    FILE *chatlog = fopen("chat_log.txt", "a");

    fprintf(chatlog, "\nQuestion: %s---------\n", manuscript_ptr[function_index].question);
    fprintf(chatlog, "1) %s\n", manuscript_ptr[function_index].svar1);
    fprintf(chatlog, "2) %s\n", manuscript_ptr[function_index].svar2);

    if (user_answer == 1)
    {
        fprintf(chatlog, "You chose: 1) %s\n", manuscript_ptr[function_index].svar1);
    }
    else if (user_answer == 2)
    {
        fprintf(chatlog, "You chose: 2) %s\n", manuscript_ptr[function_index].svar2);
    }
    else if (user_answer == 3)
    {
        fprintf(chatlog, "Du gik tilbage til sidste spørgsmål\n");
    }

    fclose(chatlog);
}

void anxiety_tracker(int climate_anxiety[], int climate_anxiety_counter)
{
    int user_answer;

    printf("Hvor meget klima-angst foeler du lige nu paa en skala fra 1-10? ");
    scanf("%d", &user_answer);
    printf("\nTak!\n");

    climate_anxiety[climate_anxiety_counter] = user_answer;
}

void print_anxiety_graph(int climate_anxiety[])
{
    char empty_line[300] = {"|                                                    \n"};
    char graph_lines[15][500];
    int i, k, s;
    char char_integers[12][3] = {"-", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    char *ptr;

    for (i = 0; i < 14; i++)
    {
        strcpy(graph_lines[i], empty_line);
    }

    strcpy(graph_lines[14], "|____________________________\n");

    for (i = 0; i < 3; i++)
    {
        for (k = 0; k < 14; k++)
        {
            if (climate_anxiety[i] == k && k == climate_anxiety[0])
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|");

                for (s = 0; s < 3; s++)
                {
                    strcat(ptr, char_integers[0]);
                }

                strcat(ptr, char_integers[k]);
            }

            else if (climate_anxiety[i] == k && k == climate_anxiety[1])
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|");

                for (s = 0; s < 11; s++)
                {
                    strcat(ptr, char_integers[0]);
                }

                strcat(ptr, char_integers[k]);
            }

            else if (climate_anxiety[i] == k && k == climate_anxiety[2])
            {
                ptr = graph_lines[13 - k];

                strcat(ptr, "|");

                for (s = 0; s < 19; s++)
                {
                    strcat(ptr, char_integers[0]);
                }

                strcat(ptr, char_integers[k]);
            }
        }
    }

    printf("\nHer er progressionen over din klima-angst igennem samtalen: \n\n");

    printf("\n");

    printf("\n       ____________________");
    printf("\n      |x-akse : tid        |\n      |y-akse : klima-angst|\n");
    printf("      |____________________| \n");

    printf("\n");

    for (i = 0; i < 15; i++)
    {
        printf("%s", graph_lines[i]);
    }
}

void print_graph_comment(int climate_anxiety[])
{
    // case 1 - klima-angst er den sammee hele vejen igennem
    if (climate_anxiety[0] == climate_anxiety[1] && climate_anxiety[1] == climate_anxiety[2])
    {
        printf("\nDin klima-angst er helt uaendret! Maaske vi kunne chatte igen snart?\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er nemlig paa et hoejt niveau\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    // case 2 - klima-angst trender nead
    else if (climate_anxiety[0] >= climate_anxiety[1] && climate_anxiety[1] >= climate_anxiety[2])
    {
        printf("\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");
        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    // case 3 - klima-angst trender opad
    else if (climate_anxiety[0] <= climate_anxiety[1] && climate_anxiety[1] <= climate_anxiety[2])
    {
        printf("\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    // case 4, 4-2-4 (tal, mindre, større)
    else if (climate_anxiety[0] >= climate_anxiety[1] && climate_anxiety[1] <= climate_anxiety[2])
    {
        printf("\nSikke noget! Du har faaet mere klima-angst af at chatte med mig! Det er jeg ked af :(\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }

    // case 5, 2-4-2 (tal, større, mindre)
    else if (climate_anxiety[0] <= climate_anxiety[1] && climate_anxiety[1] >= climate_anxiety[2])
    {
        printf("\nDet er godt at se, at jeg kunne hjaelpe med at nedbringe din klima-angst!\n");

        if (climate_anxiety[2] > 5)
        {
            printf("\nDin klima-angst er dog stadig paa et hoejt niveau, saa maaske vi kunne chatte igen snart?\n");
        }
        else
        {
            printf("\nDin klima-angst er heldigvis paa et lavt niveau og det er rigtig godt at se! :)\n");
        }
    }
}

void read_context(char context[3][100])
{
    FILE *file = fopen("1st_context.txt", "r");
    int i;

    for (i = 0; i < 3; i++)
    {
        fgets(context[i], 100, file);
    }

    fclose(file);
}

void print_context(char context[3][100], int file_index)
{
    printf("\n%s\n", context[file_index]);
    sleep(3);
}

int print_comment(manuscript *manuscript_ptr, int function_index)
{
    printf("\n%s\n", manuscript_ptr[function_index].question);

    sleep(3);

    return 16;
}

// unit test med CuTets
void test_print_comment_return_value(CuTest *tc)
{
    char *file_names[3] = {"file.txt", "file2.txt", "file3.txt"};
    int file_index = 0;
    manuscript *manuscript_ptr = read_manuscript(file_index, file_names);

    // bruger function_index "9" fordi det er en af de indexer, hvor funktionen her aktiverer
    int actual = print_comment(manuscript_ptr, 9);
    int expected = 16;
    CuAssertIntEquals(tc, expected, actual);
}

// definiton af test-suite
CuSuite *print_comment_get_suite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_print_comment_return_value);

    return suite;
}