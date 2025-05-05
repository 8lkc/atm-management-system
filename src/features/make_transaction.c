#include "mod.h"
#include "../lib.h"

/*********************************************************************************************/
/*         (i):=> make an user to withdrawing or depositing money to certain account         */
/*********************************************************************************************/
//⏬
void makeTransaction(User user) {
    Record *record = (Record*) malloc(sizeof(Record));
    FILE *db = dbOpen(RECORDS, "r"), *tempFile = dbOpen(TEMP_FILE, "a");
    char label[255], option[7];
    double among;
    long accountNbr;
    short recordId, valid = 0, selector = -1;

    header();
    strcpy(label, user.name);
    strcat(label, " > MAKE TRANSACTION");
    frameLabel(label);

    printf("\n\t\tACCOUNT NUMBER:  ");
    scanf("%ld", &accountNbr);
    getchar(); // empty the buffer

    if(!isExistsAccount(accountNbr, user.name, db)) {
        mainMenu(user, "\033[1;38;5;208mOPERATION FAILED !!\n\t   You have tried to make a transaction on a non-existent account.\033[0m");
        return;
    }
    // Move the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    while(getAccountData(db, &recordId, record))
        if(record->accountNumber == accountNbr)
            break;

    if(
        !strcmp(record->accountType, "fixed01") ||
        !strcmp(record->accountType, "fixed02") ||
        !strcmp(record->accountType, "fixed03")
    ) {
        fclose(db);
        fclose(tempFile);
        remove(TEMP_FILE);
        mainMenu(user, "\033[1;38;5;208mTRANSACTIONS NOT ALLOWED ON SELECTED ACCOUNT TYPE !!\033[0m");
        return;
    }
    // Move the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    printf("\n\t\tWHAT DO YOU LIKE TO DO ?\n\n\t\t\t[1]— WITHDRAW\n\t\t\t[2]— DEPOSIT\n\n\t\tYOUR CHOICE HERE:  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1") || !strcmp(option, "2")) {
            if(!strcmp(option, "1")) {
                printf("\n\t\tAMONG TO WITHDRAW:  ");
                selector = 0;
            } else {
                printf("\n\t\tAMONG TO DEPOSIT:  ");
                selector = 1;
            }
            scanf("%lf", &among);
            getchar(); // empty the buffer

            while(getAccountData(db, &recordId, record)) {
                if(!strcmp(record->username, user.name) && record->accountNumber == accountNbr) {
                    switch(selector) {
                        case 0:
                            if(record->among < among) {
                                fclose(db);
                                fclose(tempFile);
                                remove(TEMP_FILE);
                                mainMenu(user, "\033[1;38;5;208mNOT ENOUGH MONEY IN SELECTED ACCOUNT !!\033[0m");
                                return;
                            }
                            else record->among -= among;
                            break;

                        case 1:
                            record->among += among;
                            break;
                    }
                }
                saveAccountData(tempFile, recordId, *record);
            }

            valid = 1;
        } else {
            fprintf(stderr, "\n\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }

    fclose(db);
    fclose(tempFile);

    remove(RECORDS);
    rename(TEMP_FILE, RECORDS);
    success(user);
}
