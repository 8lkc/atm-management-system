#include "../header.h"

/*********************************************************************************************************************************************************/
/*         (i):=> check if an user really want to leave a section [TARGET_PROTOTYPE: void (*func)(User, char*)] (like a confirmation dialog box)         */
/*********************************************************************************************************************************************************/
//⏬
short stayOrNot(char *banner, char *message, void (*func)(User, char*), User user) {

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
            (*func)(user, "");
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

/************************************************************************************************************************************************/
/*         (i):=> displays a part of the main menu according to the fact that an user own, or not, at least one account in the db         */
/************************************************************************************************************************************************/
//⏬
void conditionalMenu(short boolean) {
    if(boolean) {
        printf("\t|\t[2]— UPDATE ACCOUNT INFORMATION                                  |\n");
        printf("\t|\t[3]— CHECK ACCOUNT(S)                                            |\n");
        printf("\t|\t[4]— CHECK LIST OF OWNED ACCOUNT(S)                              |\n");
        printf("\t|\t[5]— MAKE TRANSACTION                                            |\n");
        printf("\t|\t[6]— REMOVE EXISTING ACCOUNT                                     |\n");
        printf("\t|\t[7]— TRANSFERT OWNERSHIP                                         |\n");
    } else {
        printf("\t|\t\033[90m[2]— UPDATE ACCOUNT INFORMATION\033[0m                                  |\n");
        printf("\t|\t\033[90m[3]— CHECK ACCOUNT(S)\033[0m                                            |\n");
        printf("\t|\t\033[90m[4]— CHECK LIST OF OWNED ACCOUNT(S)\033[0m                              |\n");
        printf("\t|\t\033[90m[5]— MAKE TRANSACTION\033[0m                                            |\n");
        printf("\t|\t\033[90m[6]— REMOVE EXISTING ACCOUNT\033[0m                                     |\n");
        printf("\t|\t\033[90m[7]— TRANSFERT OWNERSHIP\033[0m                                         |\n");
    }
}

/***************************************************************************************************/
/*         (i):=> create a label with a given banner (to make sure the form doesn't spoil)         */
/***************************************************************************************************/
//⏬
void frameLabel(char *banner) {

    short bloc, side, rest, nbr = strlen(banner);
    bloc = 72 - (nbr + 4);
    side = bloc / 2;
    rest = bloc % 2;

    printf("\n\n\t|");

    for(short i = 0; i < side; i++) {
        printf("█");
    }

    printf("  \033[1m%s\033[0m  ", banner);

    for(short i = 0; i < side + rest; i++) {
        printf("█");
    }

    printf("|\n");
}

/**********************************************************************************************************/
/*         (i):=> align a message at the center of the bloc (to make sure the form doesn't spoil)         */
/**********************************************************************************************************/
//⏬
void frameMessage(char *message, char *color) {

    short bloc, side, rest, nbr = strlen(message);
    bloc = 72 - nbr;
    side = bloc / 2;
    rest = bloc % 2;

    printf("\t|");

    for(short i = 0; i < side; i++) {
        printf(" ");
    }

    printf("%s%s\033[0m", color, message);

    for(short i = 0; i < side + rest; i++) {
        printf(" ");
    }

    printf("|\n\t| \t\t\t\t\t\t\t\t\t |\n");
}

/****************************************************************************************************************/
/*         (i):=> top of the application (like a banner) that will visible while the program is running         */
/****************************************************************************************************************/
//⏬
void header() {
    system("clear");
    printf("\n\t ◜ **********************  FEEL FREE TO SURF ON  ********************** ◝\n");
    printf("\t ________________________________________________________________________\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|              ████       ████████████████ ███████         ███████       |\n");
    printf("\t|            ████████     ████████████████ ████████       ████████       |\n");
    printf("\t|           ████  ████          ████       ████ ████     ████ ████       |\n");
    printf("\t|          ████    ████         ████       ████  ████   ████  ████       |\n");
    printf("\t|         ████      ████        ████       ████   ████ ████   ████       |\n");
    printf("\t|        ████████████████       ████       ████    ███████    ████       |\n");
    printf("\t|       ██████████████████      ████       ████     █████     ████       |\n");
    printf("\t|       ████          ████      ████       ████      ███      ████       |\n");
    printf("\t|       ████          ████      ████       ████               ████       |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|========================= \033[1m MANAGEMENT SYSTEM \033[0m ==========================|\n");
}

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
