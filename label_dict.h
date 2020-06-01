#define NAME_LEN 40
#define NUMBER_LISTS 26
#define ERROR -1
#define CORRECTLY 0
#define True 1
#define False 0



typedef struct label 
{

    char name[NAME_LEN];
    int offset;   

} Label;



typedef struct label_list_item
{

    Label *label_ptr;                       
    struct label_list_item *next_item_ptr;
    struct label_list_item *previous_item_ptr;

} Label_list_item;



extern Label_list_item *label_lists_ptrs[NUMBER_LISTS];



void initLabelDict();



int addNewLabel(char[], int);



int getLabelOffset(char[]);



void clearLabelDict();