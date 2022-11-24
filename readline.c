#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main () {
    
    FILE *file = fopen("file.txt", "r");
    char string[100];
    int counter = 0;

    while (fgets(string, 50, file) != NULL)
    {
        counter = counter + 1;
    }
    
    printf("\nThis is how many lines there are in your file: %d", counter);

    return 0;
}