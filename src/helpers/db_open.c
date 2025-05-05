#include "mod.h"
#include "../lib.h"

/************************************************************************************************/
/*         (i):=> try to open a text file (database) and tell if that's succeded or nor         */
/************************************************************************************************/
//⏬
FILE* dbOpen(char* path, char* openingMode) {
    FILE *ptr = fopen(path, openingMode);
    // If the file isn't exists, try to create it.
    if(!ptr) {
        ptr = fopen(path, "w");
        fclose(ptr);
        ptr = fopen(path, openingMode);
    }
    // if the problem persists, display an error message and exit the program.
    if(!ptr) {
        header();
        printf("\t| \t\t\t\t\t\t\t\t\t |\n\t|   😥\033[1m INTERNAL ERROR !!\033[0m \t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
        printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
