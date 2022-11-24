struct block
{
    char question[50];
    char svar1[50];
    char svar2[50];
};
typedef struct block block;

char *file_names[3] = {"file.txt", "file2.txt", "file3.txt"};


block *scan_block(int file_index);
int ask_answer(int index, block *chatter);
int size_of_file(FILE *file);
int read_lines(FILE *file);