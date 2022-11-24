#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(file, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(file);

    int res2 = (sizeof(char) * 4);

    printf("\nThis is the functions result: %d\n\nThis is the actual result: %d", res, res2);

    // closing the file
    fclose(file);

    return 0;
}