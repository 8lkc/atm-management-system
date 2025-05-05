#if !defined(HEADER_SYSTEM_MOD_FILE_H)
#define HEADER_SYSTEM_MOD_FILE_H

    #include "../data.h"

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

#endif // HEADER_SYSTEM_MOD_FILE_H
