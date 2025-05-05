#include "mod.h"
#include "../lib.h"

/**************************************************************************/
/*         (i):=> visualize details of owned accounts for an user         */
/**************************************************************************/
//⏬
void listOwnedAccounts(User user) {
    Record *record = (Record*) malloc(sizeof(Record));
    FILE *db = dbOpen(RECORDS, "r");
    char label[255], option[7];
    short recordId, valid = 0;

    header();
    strcpy(label, user.name);
    strcat(label, " > OWNED ACCOUNT(S)");
    frameLabel(label);
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");

    while(getAccountData(db, &recordId, record)) {
        if(!strcmp(record->username, user.name)) {
            printf("\t| \t\t\t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
            printf("\t|\t   ACCOUNT NUMBER:                 %ld", record->accountNumber);
            borderRight(30 - numberOfDigits(record->accountNumber));
            printf("\t|\t   DATE OF CREATION:               %02hd/%02hd/%hd", record->creation.day, record->creation.month, record->creation.year);
            borderRight(20);
            printf("\t|\t   COUNTRY:                        %s", record->country);
            borderRight(30 - strlen(record->country));
            printf("\t|\t   PHONE NUMBER:                   %ld", record->phoneNumber);
            borderRight(30 - numberOfDigits(record->phoneNumber));
            printf("\t|\t   BALANCE:                        $%.3f", record->among);
            borderRight(30 - (2 + numberOfDigits((int) record->among) + 3));
            printf("\t|\t   TYPE OF ACCOUNT:                %s", record->accountType);
            borderRight(30 - strlen(record->accountType));
        }
    }
    printf("\t| \t\t\t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t| \033[1;32m OPERATION SUCCEDED !\033[0m \t\t\t\t\t\t |\n");
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
            if(stayOrReturn("LOGGING OUT", "DO YOU REALLY WANT TO SIGN OUT ?", &listOwnedAccounts, user))
                initMenu(user, "\033[1;32mLOG OUG SUCCEDED !\033[0m");
            valid = 1;
        } else {
            printf("\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }

    fclose(db);
}
