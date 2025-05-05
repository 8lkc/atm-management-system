#if !defined(HEADER_HELPERS_MOD_FILE_H)
#define HEADER_HELPERS_MOD_FILE_H

    #include "../data.h"

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

#endif // HEADER_HELPERS_MOD_FILE_H
