struct block
{
    int question_int;
    int svar1_int;
    int svar2_int;
    
    char question[50];
    char svar1[50];
    char svar2[50];

};

struct block chatter[100];
int scan_block(int fil1);
int ask_answer(int index);