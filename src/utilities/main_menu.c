#include "mod.h"
#include "../lib.h"

/*************************************************************************************************************/
/*         (i):=> main main / "Home page" for each user (sure, if the authentification is correct !)         */
/*************************************************************************************************************/
//⏬
void mainMenu(User user, char *status) {
    char option[7];
    short valid = 0, ownedAccount = haveAccount(user.name);

    header();
    if(strcmp(status, ""))
        printf("\n\t   %s", status);
    if(!ownedAccount)
        printf("\n\n\t   \033[1;38;5;208mYou don't have an account yet !\n\t   So, only the first and last operations are allowed.\033[0m");
    frameLabel(user.name);
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|\t[1]— CREATE A NEW ACCOUNT                                        |\n");
    conditionalMenu(ownedAccount);
    printf("\t|\t[8]— LOG OUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1") || !strcmp(option, "2") || !strcmp(option, "3") || !strcmp(option, "4") || !strcmp(option, "5") || !strcmp(option, "6") || !strcmp(option, "7") || !strcmp(option, "8")) {
            if(!strcmp(option, "1")) {
                creatAccount(user);
                valid = 1;
            } else if(!strcmp(option, "2") || !strcmp(option, "3") || !strcmp(option, "4") || !strcmp(option, "5") || !strcmp(option, "6") || !strcmp(option, "7")) {
                if(!ownedAccount) {
                    header();
                    if(!ownedAccount)
                        printf("\n\t   \033[1;38;5;208mYou don't have an account yet !\n\t   So, only the first and last operations are allowed.\033[0m");
                    frameLabel(user.name);
                    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
                    printf("\t|\t[1]— CREATE A NEW ACCOUNT                                        |\n");
                    conditionalMenu(ownedAccount);
                    printf("\t|\t[8]— LOG OUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
                    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
                    printf("\t \033[1;38;5;208m OPERATION NO ALLOWED !\033[0m\n\n");
                    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
                    fgets(option, 7, stdin);
                    option[strcspn(option, "\n")] = '\0';
                } else {
                    if(!strcmp(option, "2")) {
                        updateAccount(user);
                        valid = 1;
                    } else if(!strcmp(option, "3")) {
                        accountDetails(user);
                        valid = 1;
                    } else if(!strcmp(option, "4")) {
                        listOwnedAccounts(user);
                        valid = 1;
                    } else if(!strcmp(option, "5")) {
                        makeTransaction(user);
                        valid = 1;
                    } else if(!strcmp(option, "6")) {
                        // TODO: remove existing account
                        valid = 1;
                    } else {
                        // TODO: ransfer owner
                        valid = 1;
                    }
                }
            } else {
                if(stayOrNot("LOGGING OUT", "DO YOU REALLY WANT TO SIGN OUT ?", &mainMenu, user))
                    initMenu(user, "\033[1;32mLOG OUG SUCCEDED !\033[0m");
                valid = 1;
            }
        } else {
            header();
            if(!ownedAccount)
                printf("\n\t   \033[1;38;5;208mYou don't have an account yet !\n\t   So, only the first and last operations are allowed.\033[0m");
            frameLabel(user.name);
            printf("\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|\t[1]— CREATE A NEW ACCOUNT                                        |\n");
            conditionalMenu(ownedAccount);
            printf("\t|\t[8]— LOG OUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
            printf("\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }
}
