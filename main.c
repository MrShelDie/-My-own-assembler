#include "stdio.h"
#include "label_dict.h"




FILE* open_file(int argc, const char *argv[]){
    if (argc != 2) {
        printf("%s", "No arguments \nPlease enter a file name\n");
        return NULL;
    }

    const char *file_name = argv[1];

    FILE *file_ptr = fopen(file_name, "r");

    if (!file_ptr){
        printf("%s", "Unknown file name\nCheck the entered file name or its location\n");
        return NULL;
    }

    return file_ptr;
}




int main(int argc, const char *argv[]) {

    const FILE *file_ptr = open_file(argc, argv);
    
    if (file_ptr == NULL)
        return 0;

    
    

    return 0;
}