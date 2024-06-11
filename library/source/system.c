#include "../header.h"

/********************************************************************/
/*         (i):=> juste to create a password for a new user         */
/********************************************************************/
//⏬
char* createPassword() {

    char password[255], confirmation[255], *result;

    header();
    frameLabel("PASSWORD CREATION");

    // disabling echo
    system("stty -echo");

    printf("\n\t\tMAKE A PASSWORD:  ");
    fgets(password, 255, stdin);
    printf("\n\n\t\tCONFIRM THE PASSWORD:  ");
    fgets(confirmation, 255, stdin);

    while(strcmp(password, confirmation)) {
        header();
        frameLabel("PASSWORD CREATION");
        printf("\n\t \033[1;38;5;208m THE PASSWORDS ENTERED ARE DIFFERENTS !\033[0m\n");
        printf("\n\t\tMAKE A PASSWORD:  ");
        fgets(password, 255, stdin);
        printf("\n\n\t\tCONFIRM THE PASSWORD:  ");
        fgets(confirmation, 255, stdin);
    }

    // restore terminal
    system("stty echo");

    password[strcspn(password, "\n")] = '\0';
    result = (char*) malloc((1 + strlen(password)) * sizeof(char));
    strcpy(result, password);
    return result;
}

/**********************************************************/
/*         (i):=> returns the password of an user         */
/**********************************************************/
//⏬
char* getPassword(char *username) {

    FILE *db = dbOpen(USERS, "r");
    char name[255], password[637], *result;
    short id;

    while(getUserData(db, &id, name, password))
        if(!strcmp(name, username)) {
            fclose(db);
            result = (char*) malloc((1 + strlen(password)) * sizeof(char));
            strcpy(result, password);
            return result;
        }

    fclose(db);
    return "NO USER FOUND !";
}

/**********************************************************************/
/*         (i):=> to get data of an account from the db         */
/**********************************************************************/
//⏬
short getAccountData(FILE *db, short *id, Record *record) {
    return fscanf(db, "%hd %hd %s %ld %hd/%hd/%hd %s %ld %lf %s", id, &record->userId, record->username, &record->accountNumber,
                                                                        &record->creation.day, &record->creation.month, &record->creation.year,
                                                                        record->country, &record->phoneNumber, &record->among, record->accountType) != EOF;
}

/*******************************************************************/
/*         (i):=> to get data of an user from the db         */
/*******************************************************************/
//⏬
short getUserData(FILE *db, short *id, char *name, char *password) {
    return fscanf(db, "%hd %s %s", id, name, password) != EOF;
}

/************************************************************/
/*         (i):=> returns the identifier of an user         */
/************************************************************/
//⏬
short getUserId(char *username) {

    FILE *db = dbOpen(USERS, "r");
    char name[255], password[637];
    short id;

    while(getUserData(db, &id, name, password))
        if(!strcmp(name, username))
            break;

    fclose(db);
    return id;
}

/*****************************************************************************/
/*         (i):=> to check if an user own an account in the db         */
/*****************************************************************************/
//⏬
short haveAccount(char *username) {

    FILE *db = dbOpen(RECORDS, "r");
    Record record;
    short id, result = 0;

    while(getAccountData(db, &id, &record))
        if(!strcmp(username, record.username)) {
            result = 1;
            break;
        }

    fclose(db);
    return result;
}

/*********************************************************************************/
/*         (i):=> to check if an username already exists in the db         */
/*********************************************************************************/
//⏬
short isExistsAccount(short accountNumber, char *username, FILE *db) {

    Record record;
    short id;

    while(getAccountData(db, &id, &record)) {
        if(record.accountNumber == accountNumber && !strcmp(record.username, username))
            return 1;
    }

    return 0;
}

/*********************************************************************************/
/*         (i):=> to check if an username already exists in the db         */
/*********************************************************************************/
//⏬
short isExistsUsername(char *username, FILE *db) {

    char name[255], password[637];
    short id;

    while(getUserData(db, &id, name, password))
        if(!strcmp(username, name))
            return 1;

    return 0;
}

/*********************************************************************/
/*         (i):=> to save data of an account on the db         */
/*********************************************************************/
//⏬
void saveAccountData(FILE *db, short id, Record record) {
    fprintf(db, "%d %d %s %ld %02d/%02d/%d %s %ld %.3lf %s\n", id, record.userId, record.username, record.accountNumber,
                                                              record.creation.day, record.creation.month, record.creation.year,
                                                              record.country, record.phoneNumber, record.among, record.accountType);
}

/******************************************************************/
/*         (i):=> to save data of an user on the db         */
/******************************************************************/
//⏬
void saveUserData(FILE *db, short id, char *name, char *password) {
    fprintf(db, "%d %s %s\n", id, name, asciize(password));
}
