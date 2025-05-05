#include "mod.h"
#include "../lib.h"

/***********************************************************************************************/
/*         (i):=> notify that an operation is succesfully done and check the next move         */
/***********************************************************************************************/
//⏬
void success(User user) {
    char option[7];
    short valid = 0;

    header();
    printf("\n\t \033[1;32m OPERATION SUCCEDED !\033[0m");
    frameLabel("NEXT");
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
    frameMessage("WHAT DO YOU WANT TO DO NOW ?", "");
    printf("\t|\t[1]— BACK TO MAIN MENU                                           |\n");
    printf("\t|\t[2]— LOGGOUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1")) {
            mainMenu(user, "");
            valid = 1;
        } else if(!strcmp(option, "2")) {
            if(stayOrNot("LOGGING OUT", "DO YOU REALLY WANT TO SIGN OUT ?", &mainMenu, user))
                initMenu(user, "\033[1;32mLOG OUG SUCCEDED !\033[0m");
            valid = 1;
        } else {
            header();
            printf("\n\t \033[1;32m OPERATION SUCCEDED !\033[0m");
            frameLabel("NEXT");
            printf("\t| \t\t\t\t\t\t\t\t\t |\n");
            frameMessage("WHAT DO YOU WANT TO DO NOW ?", "");
            printf("\t|\t[1]— BACK TO MAIN MENU                                           |\n");
            printf("\t|\t[2]— LOGGOUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
            printf("\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }
}
