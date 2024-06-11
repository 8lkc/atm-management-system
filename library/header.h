#if !defined(HEADER_HEADER_FILE_H)
#define HEADER_HEADER_FILE_H

/*****************************************/
/*         LIBRARIES AND MACROS          */
/*****************************************/
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #define USERS "./database/users.txt"
    #define RECORDS "./database/records.txt"
    #define TEMP_FILE "./database/tempfile.txt"



/************************************/
/*         DATA STRUCTURES          */
/************************************/
    //⏬ for easiest handles of dates
    typedef struct {
        short  day, month, year;
    } Date;

    //⏬ fields for each account
    typedef struct {
        Date    creation;
        char    username[255], country[255], accountType[255];
        long    accountNumber, phoneNumber;
        short   userId;
        double  among;
    } Record;

    //⏬ fields for each user
    typedef struct {
        char   *name;
        short  id;
    } User;



/******************************/
/*         FUNCTIONS          */
/******************************/
    //⏬ features
        void accountDetails(User user);
        void creatAccount(User user);
        void listOwnedAccounts(User user);
        void makeTransaction(User user);
        void signIn(User user);
        void signUp(User user);
        void updateAccount(User user);

    //⏬ functions helpers
        char* asciize(char *password);

        FILE* dbOpen(char* path, char* openingMode);

        short contentBlank(char *password);
        short isConform(char *username);
        short isLeapYear(short year);
        short isValidDate(short day, short month, short year);
        short isValidDateFormat(char *date, short *day, short *month, short *year);
        short makeAccountId(char *username);
        short numberOfDigits(int number);

        void borderRight(short blank);
        void setUser(User *user, short id, char *username);

    //⏬ system functions
        char* createPassword();
        char* getPassword(char *username);

        short getAccountData(FILE *db, short *id, Record *record);
        short getUserData(FILE *db, short *id, char *name, char *password);
        short getUserId(char *username);
        short haveAccount(char *username);
        short isExistsAccount(short accountNumber, char *username, FILE *db);
        short isExistsUsername(char *username, FILE *db);

        void saveAccountData(FILE *db, short id, Record record);
        void saveUserData(FILE *db, short id, char *name, char *password);

    //⏬ utilities functions
        short stayOrNot(char *banner, char *message, void (*func)(User, char*), User user);
        short stayOrReturn(char *banner, char *message, void (*func)(User), User user);

        void conditionalMenu(short boolean);
        void frameLabel(char *banner);
        void frameMessage(char *message, char *color);
        void header();
        void initMenu(User user, char *status);
        void mainMenu(User user, char *status);
        void success(User user);

#endif
