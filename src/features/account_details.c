#include "mod.h"
#include "../lib.h"

/************************************************************************/
/*         (i):=> make user to check just one account at a time         */
/************************************************************************/
//⏬
void accountDetails(User user) {
    Record *record = (Record*) malloc(sizeof(Record));
    FILE *db = dbOpen(RECORDS, "r");
    char label[255], option[7];
    short recordId, accountId, valid = 0;

    header();
    strcpy(label, user.name);
    strcat(label, " > CHECK DETAILS OF AN ACCOUNT");
    frameLabel(label);

    printf("\n\t\tACCOUNT NUMBER:  ");
    scanf("%hd", &accountId);
    getchar(); // empty the buffer

    while(!isExistsAccount(accountId, user.name, db)) {
        fprintf(stderr, "\n\t \033[1;38;5;208m THIS ACCOUNT DOESN'T EXISTS.\033[0m\n");
        printf("\n\t\tACCOUNT NUMBER:  ");
        scanf("%hd", &accountId);
        getchar();
        // Move the file pointer to the beginning of the file
        fseek(db, 0, SEEK_SET);
    }

    // Move the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    frameLabel("RESULT");
    while(getAccountData(db, &recordId, record)) {
        if(!strcmp(record->username, user.name) && record->accountNumber == accountId) {
            printf("\t| \t\t\t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
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
            break;
        }
    }
    printf("\t| \t\t\t\t\t\t\t\t\t |\n");
    if(!strcmp(record->accountType, "current"))
        frameMessage("You will not get interests because the account is in type current", "\033[33m");
    else {
        char notification[255];
        double pourcent, total = record->among;
        pourcent = !strcmp(record->accountType, "savings") ? 7 : !strcmp(record->accountType, "fixed01") ? 4 : !strcmp(record->accountType, "fixed02") ? 5 : 8;
        sprintf(notification, "You will get $%.3f as interest on day 10 of every month", (pourcent * total) / 100);
        frameMessage(notification, "\033[32m");
    }
    printf("\t| \t\t\t\t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    frameMessage("WHAT DO YOU WANT TO DO NOW ?", "");
    printf("\t|\t[1]— CHECK FOR AN OTHER ACCOUNT                                  |\n");
    printf("\t|\t[2]— BACK TO MAIN MENU                                           |\n");
    printf("\t|\t[3]— LOGGOUT                                                     |\n\t| \t\t\t\t\t\t\t\t\t |\n");
    printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
    printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1")) {
            accountDetails(user);
            valid = 1;
        } else if(!strcmp(option, "2")) {
            mainMenu(user, "");
            valid = 1;
        } else if(!strcmp(option, "3")) {
            if(stayOrReturn("LOGGING OUT", "DO YOU REALLY WANT TO SIGN OUT ?", &accountDetails, user))
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
