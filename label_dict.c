#include "string.h"
#include "label_dict.h"
#include "stdlib.h"
#include "stdio.h"


Label_list_item *label_lists_ptrs[NUMBER_LISTS];


void initLabelDict() {
    for (int i = 0; i < NUMBER_LISTS; i++) 
        label_lists_ptrs[i] = NULL;
}




// The hash function converts the first letter of the label name to a pointer number to the first element of the list.
static int hashFunc(char ch) {

    // If uppercase, then lowercase
    if (ch >= 'A' && ch <= 'Z')         
        ch = ch - 'A' + 'a';

    // If this is not a letter, then exit the function, return an error code
    else if (ch < 'a' || ch > 'z')      
        return ERROR; 

    return (int)(ch - 'a');
}




int addNewLabel(char name[], int offset){

    char ch = name[0];

    int num = hashFunc(ch);

    if (num == ERROR)           
        return ERROR;
    
    
    // Copy of pointers to improve code readability
    Label_list_item *current_item_ptr = label_lists_ptrs[num];     
                                                                            
    Label_list_item *previous_item_ptr = NULL;                           


    // Create a new item at the end of the list
    
    if (current_item_ptr == NULL) 
    {
        current_item_ptr = (Label_list_item*)malloc(sizeof(Label_list_item));
        label_lists_ptrs[num] = current_item_ptr;
    }

    else 
    {
        do
        {
            if (strcmp(current_item_ptr -> label_ptr -> name, name) == 0) 
            {  
                current_item_ptr -> label_ptr -> offset = offset;
                return CORRECTLY;
            }

            previous_item_ptr = current_item_ptr;                               
            current_item_ptr = current_item_ptr -> next_item_ptr;                   
        } while (current_item_ptr != NULL);

        current_item_ptr = (Label_list_item*)malloc(sizeof(Label_list_item));
    }

    
    current_item_ptr -> label_ptr = (Label*)malloc(sizeof(Label));     

    strcpy(current_item_ptr -> label_ptr -> name, name);                   
    current_item_ptr -> label_ptr -> offset = offset;

    current_item_ptr -> next_item_ptr = NULL;                                               

    current_item_ptr -> previous_item_ptr = previous_item_ptr;                              

    if (previous_item_ptr != NULL)
        previous_item_ptr -> next_item_ptr = current_item_ptr;                                  

    return CORRECTLY;
}




int getLabelOffset(char name[]) {
    char ch = name[0];

    int num = hashFunc(ch);

    if (num == ERROR)                       
        return ERROR;

    Label_list_item *current_item_ptr = label_lists_ptrs[num];  

    // Check the name of each list item
    while(current_item_ptr != NULL)                                        
    {
        if (!strcmp(current_item_ptr -> label_ptr -> name, name))   
            return current_item_ptr -> label_ptr -> offset;         

        current_item_ptr = current_item_ptr -> next_item_ptr;                 
    }

    return ERROR;
}




void clearLabelDict() {

    // In each list, delete items from the end

    for (int i = 0; i < NUMBER_LISTS; i++)                                      
    {
        Label_list_item *current_item_ptr = label_lists_ptrs[i];      
        Label_list_item *previous_item_ptr = NULL; 

        
        if (current_item_ptr != NULL)                                                                                          
        {    
            while (current_item_ptr -> next_item_ptr != NULL)                      
            {
                previous_item_ptr = current_item_ptr;
                current_item_ptr = current_item_ptr -> next_item_ptr;
            }

            while (current_item_ptr != NULL)                                       
            {
                free(current_item_ptr -> label_ptr);                  
                free(current_item_ptr);                        

                current_item_ptr = previous_item_ptr;

                if (previous_item_ptr != NULL)
                    previous_item_ptr = previous_item_ptr -> previous_item_ptr;
            }

            label_lists_ptrs[i] = NULL;
        }
    }
}