
struct manuscript
{
    char question[450];
    char svar1[300];
    char svar2[300];
};
typedef struct manuscript manuscript;

// prototyper af funktioner som vi kalder i main.c
manuscript *read_manuscript(int file_index, char *file_names[]);
int chat_with_user(int index, manuscript *manuscript_ptr);
void chat_log(int index, manuscript *manuscript_ptr, int answer);
void anxiety_tracker(int climate_anxiety[], int climate_anxiety_counter);
void print_anxiety_graph(int climate_anxiety[]);
void print_graph_comment(int climate_anxiety[]);
void read_context(char context[3][650]);
void print_context(char context[3][650], int file_index);
int print_comment(manuscript *manuscript_ptr, int function_index);
