#include "mod.h"
#include "../lib.h"

/******************************************************************************************/
/*         (i):=> pdate information (country or phone number) of existing account         */
/******************************************************************************************/
//⏬
void updateAccount(User user) {
    Record *record = (Record*) malloc(sizeof(Record));
    FILE *db = dbOpen(RECORDS, "r"), *tempFile = dbOpen(TEMP_FILE, "a");
    char country[255], label[255], option[7];
    long accountNbr, phoneNbr;
    short recordId, valid = 0, selector = -1;

    header();
    strcpy(label, user.name);
    strcat(label, " > UPDATE ACCOUNT INFORMATION");
    frameLabel(label);

    printf("\n\t\tACCOUNT NUMBER:  ");
    scanf("%ld", &accountNbr);
    getchar(); // empty the buffer

    while(!isExistsAccount(accountNbr, user.name, db)) {
        fprintf(stderr, "\n\t \033[1;38;5;208m THIS ACCOUNT DOESN'T EXISTS.\033[0m\n");
        printf("\n\t\tACCOUNT NUMBER:  ");
        scanf("%ld", &accountNbr);
        getchar();
        // Move the file pointer to the beginning of the file
        fseek(db, 0, SEEK_SET);
    }

    printf("\n\t\tWHICH FIELD DO YOU WANT TO CHANGE ?\n\n\t\t\t[1]— COUNTRY\n\t\t\t[2]— PHONE NUMBER\n\n\t\tYOUR CHOICE HERE:  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1")) {
            printf("\n\t\tNEW COUNTRY:  ");
            fgets(country, 255, stdin);
            country[strcspn(country, "\n")] = '\0';
            selector = 0;
            valid = 1;
        } else if(!strcmp(option, "2")) {
            printf("\n\t\tNEW PHONE NUMBER:  ");
            scanf("%ld", &phoneNbr);
            getchar();
            selector = 1;
            valid = 1;
        } else {
            fprintf(stderr, "\n\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }

    // Move the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    while(getAccountData(db, &recordId, record)) {
        if(!strcmp(record->username, user.name) && record->accountNumber == accountNbr) {
            switch(selector) {
                case 0:
                    strcpy(record->country, country);
                    break;

                case 1:
                    record->phoneNumber = phoneNbr;
                    break;
            }
        }
        saveAccountData(tempFile, recordId, *record);
    }

    fclose(db);
    fclose(tempFile);

    remove(RECORDS);
    rename(TEMP_FILE, RECORDS);
    success(user);
}
