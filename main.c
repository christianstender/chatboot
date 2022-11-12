//"Chatbot", 2022, by Alberthe Held, Sigurd Kau, Mikkel Nielsen and Christian Stender. Version 0.0.2.
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
    // Vi finder vores fil->
    scan_block();

    // initializing stuff
    // every variable of "structure block"-type contains 3 strings of chars
    int i;
    // functionality starts

    puts(chatter[0].question);
    printf("\n1)%s\n2)%s\n", chatter[0].svar1, chatter[0].svar2);
    scanf("%d", &i);

    // first binary branching
    if (i == 2)
    {
        printf("%s\n1)%s\n2)%s\n", chatter[2].question, chatter[2].svar1, chatter[2].svar2);
        scanf("%d", &i);
    }
    else
    {
        printf("%s\n1)%s\n2)%s\n", chatter[1].question, chatter[1].svar1, chatter[1].svar2);
        scanf("%d", &i);
    }

    return 0;
}
