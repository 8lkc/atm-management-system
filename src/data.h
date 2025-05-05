#if !defined(HEADER_DATA_FILE_H)
#define HEADER_DATA_FILE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #define USERS "./database/users.txt"
    #define RECORDS "./database/records.txt"
    #define TEMP_FILE "./database/tempfile.txt"

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

#endif // HEADER_DATA_FILE_H
