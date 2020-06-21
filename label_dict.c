#include "string.h"
#include "label_dict.h"
#include "stdlib.h"
#include "stdio.h"



typedef struct List_item
{

    char name[NAME_LEN];
    int offset;  

    struct List_item *next_item_ptr;
    struct List_item *previous_item_ptr;

} List_item;




List_item *first_lists_items_ptrs[NUMBER_LISTS];




void initLabelDict() {

    for (int i = 0; i < NUMBER_LISTS; i++) 
        first_lists_items_ptrs[i] = NULL;

}



static int hashFunc(char name[]) {

    int sum = 0;
    
    for(int i = 0; name[i] != 0; i++)
        sum += (int)name[i];

    return sum % 255;

}



void addNewLabel(char name[], int offset){


    int number = hashFunc(name);
    
    
    List_item *current_item_ptr = first_lists_items_ptrs[number];                                                                         
    List_item *previous_item_ptr = NULL;                           


    // Create a new item at the end of the list

    if (current_item_ptr == NULL) 
    {
        current_item_ptr = (List_item*)malloc(sizeof(List_item));
        first_lists_items_ptrs[number] = current_item_ptr;
    }

    else 
    {
        do
        {
            if (strcmp(current_item_ptr -> name, name) == 0) 
            {  
                current_item_ptr -> offset = offset;
                return;
            }

            previous_item_ptr = current_item_ptr;                               
            current_item_ptr = current_item_ptr -> next_item_ptr;   

        } while (current_item_ptr != NULL);

        current_item_ptr = (List_item*)malloc(sizeof(List_item));
    }


    strcpy(current_item_ptr -> name, name);                   
    current_item_ptr -> offset = offset;

    current_item_ptr -> next_item_ptr = NULL;                                               

    current_item_ptr -> previous_item_ptr = previous_item_ptr;                              

    if (previous_item_ptr != NULL)
        previous_item_ptr -> next_item_ptr = current_item_ptr;                                  

}




int getLabelOffset(char name[]) {


    int number = hashFunc(name);


    List_item *current_item_ptr = first_lists_items_ptrs[number];  


    // Check the name of each element and if it converges, then return the offset 

    while(current_item_ptr != NULL)                                        
    {
        if (!strcmp(current_item_ptr -> name, name))   
            return current_item_ptr -> offset;         

        current_item_ptr = current_item_ptr -> next_item_ptr;                 
    }

    return ERROR;
}




void clearLabelDict() {

    // In each list, delete items from the end

    for (int i = 0; i < NUMBER_LISTS; i++)                                      
    {
        List_item *current_item_ptr = first_lists_items_ptrs[i];      
        List_item *previous_item_ptr = NULL; 

        
        if (current_item_ptr != NULL)                                                                                          
        {    
            while (current_item_ptr -> next_item_ptr != NULL)                      
            {
                previous_item_ptr = current_item_ptr;
                current_item_ptr = current_item_ptr -> next_item_ptr;
            }

            while (current_item_ptr != NULL)                                       
            {                 
                free(current_item_ptr);                        

                current_item_ptr = previous_item_ptr;

                if (previous_item_ptr != NULL)
                    previous_item_ptr = previous_item_ptr -> previous_item_ptr;
            }

            first_lists_items_ptrs[i] = NULL;
        }
    }
}