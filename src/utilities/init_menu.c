#include "mod.h"
#include "../lib.h"

/***********************************************************************************************************/
/*         (i):=> menu that will be displayed at the execution of the project (like a "home page")         */
/***********************************************************************************************************/
//⏬
void initMenu(User user, char *status) {
    char option[7];
    short valid = 0;

    header();
    if(strcmp(status, ""))
        printf("\n\t   %s", status);
    frameLabel("SIGN IN");
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
    frameMessage("IF YOU ARE NEW, PLEASE CREATE AN ACCOUNT (REGISTER)", "");
    printf("\t|\t[1]— LOGIN                                                       |\n");
    printf("\t|\t[2]— REGISTER                                                    |\n");
    printf("\t|\t[3]— EXIT                                                        |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1")) {
            signIn(user);
            valid = 1;
        } else if(!strcmp(option, "2")) {
            signUp(user);
            valid = 1;
        } else if(!strcmp(option, "3")) {
            if(stayOrNot("EXITING", "DO YOU REALLY WANT TO LEAVE THE APPLICATION ?", &initMenu, user)) {
                header();
                printf("\t| \t\t\t\t\t\t\t\t\t |\n\t|   👋🙂\033[1m Good bye !\033[0m \t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
                printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
            }
            valid = 1;
        } else {
            header();
            frameLabel("SIGN IN");
            printf("\t| \t\t\t\t\t\t\t\t\t |\n");
            frameMessage("IF YOU ARE NEW, PLEASE CREATE AN ACCOUNT (REGISTER)", "");
            printf("\t|\t[1]— LOGIN                                                       |\n");
            printf("\t|\t[2]— REGISTER                                                    |\n");
            printf("\t|\t[3]— EXIT                                                        |\n\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
            printf("\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }
}
