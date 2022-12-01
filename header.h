
// vores struct som indeholder question, svar1 og svar2
struct block
{
    char question[50];
    char svar1[50];
    char svar2[50];
};
typedef struct block block;

// prototyper af funktioner som vi kalder i main.c
block *scan_block(int file_index, char *file_names[]);
int ask_answer(int index, block *chatter);
void chat_log(int index, block *chatter, int answer);
void anxiety_tracker(int climate_anxiety[], int anxiety_counter);
void print_anxiety(int climate_anxiety[]);