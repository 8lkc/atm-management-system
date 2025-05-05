#include "mod.h"
#include "../lib.h"

/*************************************************************/
/*         (i):=> to make an new account for an user         */
/*************************************************************/
//⏬
void creatAccount(User user) {
    Record record, temp;
    FILE *db = dbOpen(RECORDS, "a+");
    char date[18], label[255], option[7];
    short valid = 0, recordId = -1;

    header();
    strcpy(label, user.name);
    strcat(label, " > NEW RECORD");
    frameLabel(label);

    record.userId = user.id;
    strcpy(record.username, user.name);

    printf("\n\t\tCREATION DATE (dd/mm/yyyy):  ");
    fgets(date, 18, stdin);
    date[strcspn(date, "\n")] = '\0';

    while(!isValidDateFormat(date, &record.creation.day, &record.creation.month, &record.creation.year) || !isValidDate(record.creation.day, record.creation.month, record.creation.year)) {
        fprintf(stderr, "\n\t \033[1;38;5;208m PLEASE, ENTER A VALID DATE.\033[0m\n");
        printf("\n\t\ttCREATION DATE (dd/mm/yyyy): ");
        fgets(date, 18, stdin);
        date[strcspn(date, "\n")] = '\0';
    }

    printf("\n\t\tACCOUNT NUMBER:              ");
    scanf("%ld", &record.accountNumber);
    getchar(); // empty the buffer

    while(isExistsAccount(record.accountNumber, user.name, db)) {
        fprintf(stderr, "\n\t \033[1;38;5;208m THIS ACCOUNT ALREADY EXISTS.\033[0m\n");
        printf("\n\t\tACCOUNT NUMBER:              ");
        scanf("%ld", &record.accountNumber);
        getchar();
        // Move back the file pointer to the beginning of the file
        fseek(db, 0, SEEK_SET);
    }

    printf("\n\t\tCOUNTRY:                     ");
    fgets(record.country, 255, stdin);
    record.country[strcspn(record.country, "\n")] = '\0';

    printf("\n\t\tPHONE NUMBER:                ");
    scanf("%ld", &record.phoneNumber);
    getchar();

    printf("\n\t\tAMONG TO DEPOSIT:            $");
    scanf("%lf", &record.among);
    getchar();

    printf("\n\t\tCHOOSE THE TYPE OF ACCOUNT:\n\n\t\t\t[1]— SAVINGS\n\t\t\t[2]— CURRENT\n\t\t\t[3]— FIXED01 (FOR 1 YEAR)\n\t\t\t[4]— FIXED02 (FOR 2 YEARS)\n\t\t\t[5]— FIXED03 (FOR 3 YEARS)\n\n\t\tYOUR CHOICE HERE:  ");
    fgets(option, 7, stdin);
    option[strcspn(option, "\n")] = '\0';

    while(!valid) {
        if(!strcmp(option, "1")) {
            strcpy(record.accountType, "savings");
            valid = 1;
        } else if(!strcmp(option, "2")) {
            strcpy(record.accountType, "current");
            valid = 1;
        } else if(!strcmp(option, "3")) {
            strcpy(record.accountType, "fixed01");
            valid = 1;
        } else if(!strcmp(option, "4")) {
            strcpy(record.accountType, "fixed02");
            valid = 1;
        } else if(!strcmp(option, "5")) {
            strcpy(record.accountType, "fixed03");
            valid = 1;
        } else {
            fprintf(stderr, "\n\t \033[1;38;5;208m OPERATION NO CONSIDERED !\033[0m\n\n");
            printf("\t\t\033[1mYOUR CHOICE HERE:\033[0m  ");
            fgets(option, 7, stdin);
            option[strcspn(option, "\n")] = '\0';
        }
    }

    // Move back the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    // make an identifier for the new record
    while(getAccountData(db, &recordId, &temp));
    if(recordId > -1)
        recordId++;
    else
        recordId = 0;

    // Move back the file pointer to the beginning of the file
    fseek(db, 0, SEEK_SET);

    saveAccountData(db, recordId, record);
    fclose(db);
    success(user);
}
