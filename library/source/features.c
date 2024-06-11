#include "../header.h"

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

/******************************************************************/
/*         (i):=> for authentification of registred users         */
/******************************************************************/
//⏬
void signIn(User user) {

    char username[255], password[255];

    header();
    frameLabel("BANK MANAGEMENT SYSTEM");
    printf("\n\t\tUSERNAME: ");
    fgets(username, 255, stdin);
    username[strcspn(username, "\n")] = '\0';

    // disabling echo
    system("stty -echo");

    printf("\n\t\tPASSWORD: ");
    fgets(password, 255, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    // restore terminal
    system("stty echo");

    switch(strcmp(asciize(password), getPassword(username))) {
        case 0:
            setUser(&user, getUserId(username), username);
            mainMenu(user, "\033[1;32mCONNECTION SUCCEDED !\033[0m");
            break;

        default:
            initMenu(user, "\033[1;38;5;208mWRONG PASSWORD OR USERNAME !!\033[0m");
    }
}

/**********************************************************************************/
/*         (i):=> for registration of users whose aren't be registred yet         */
/**********************************************************************************/
//⏬
void signUp(User user) {

    FILE *db = dbOpen(USERS, "a+");
    char username[255], tempUsername[255], password[637], tempPassword[637];
    short userId = -1;

    header();
    frameLabel("NEW USER");
    printf("\n\t\tGIVE AN USERNAME:  ");
    fgets(username, 255, stdin);
    username[strcspn(username, "\n")] = '\0';

    while(contentBlank(username) || !isConform(username) || isExistsUsername(username, db)) {
        header();
        frameLabel("NEW USER");

        if(contentBlank(username))
            printf("\n\t \033[1;38;5;208m PLEASE, NO BLANK !\033[0m\n");
        else if(!isConform(username))
            printf("\n\t \033[1;38;5;208m ONLY ALPH-NUMERICAL CHARACTERS ALLOWED !\033[0m\n");
        else
            printf("\n\t \033[1;38;5;208m USERNAME ALREADY TAKEN !\033[0m\n");

        printf("\n\t\tGIVE AN USERNAME:  ");
        fgets(username, 255, stdin);
        username[strcspn(username, "\n")] = '\0';

        // Move the file pointer to the beginning of the file
        fseek(db, 0, SEEK_SET);
    }

    // make an identifier for the new user
    while(getUserData(db, &userId, tempUsername, tempPassword));
    if(userId > -1)
        userId++;
    else
        userId = 0;

    saveUserData(db, userId, username, createPassword());
    setUser(&user, userId, username);
    fclose(db);

    initMenu(user, "\033[1;32mOPERATION SUCCEDED !\033[0m");
}

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
