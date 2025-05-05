#include "mod.h"
#include "../lib.h"

/**************************************************************************************************************************************************/
/*         (i):=> check if an user really want to leave a section [TARGET_PROTOTYPE: void (*func)(User)] (like a confirmation dialog box)         */
/**************************************************************************************************************************************************/
//⏬
short stayOrReturn(char *banner, char *message, void (*func)(User), User user) {
    char option[7];

    header();
    frameLabel(banner);
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
    frameMessage(message, "");
    printf("\t|\t[1]— YES                                                         |\n");
    printf("\t|\t[2]— NO                                                          |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(1) {
        if(!strcmp(option, "1")) {
            return 1;
        } else if(!strcmp(option, "2")) {
            (*func)(user);
            return 0;
        } else {
            header();
            frameLabel(banner);
            printf("\t| \t\t\t\t\t\t\t\t\t |\n");
            frameMessage(message, "");
            printf("\t|\t[1]— YES                                                         |\n");
            printf("\t|\t[2]— NO                                                          |\n\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
            printf("\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }
}
