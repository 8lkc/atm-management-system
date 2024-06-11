#include "../header.h"

/*********************************************************************************************************************/
/*         (i):=> to 'ascize' a slice of characters (replace every character of the slice by its ascii code)         */
/*********************************************************************************************************************/
//⏬
char* asciize(char *password) {

    char *result, asciiSlice[637], value[5];
    int asciiCode;

    asciiCode = password[0];
    sprintf(asciiSlice, "%d", asciiCode);

    for(short i = 1; password[i] != '\0'; i++) {
        asciiCode = password[i];
        sprintf(value, "%d", asciiCode);
        strcat(asciiSlice, value);
    }

    result = (char*) malloc((1 + strlen(asciiSlice)) * sizeof(char));
    strcpy(result, asciiSlice);
    return result;
}

/************************************************************************************************/
/*         (i):=> try to open a text file (database) and tell if that's succeded or nor         */
/************************************************************************************************/
//⏬
FILE* dbOpen(char* path, char* openingMode) {
    FILE *ptr = fopen(path, openingMode);
    // If the file isn't exists, try to create it.
    if(!ptr) {
        ptr = fopen(path, "w");
        fclose(ptr);
        ptr = fopen(path, openingMode);
    }
    // if the problem persists, display an error message and exit the program.
    if(!ptr) {
        header();
        printf("\t| \t\t\t\t\t\t\t\t\t |\n\t|   😥\033[1m INTERNAL ERROR !!\033[0m \t\t\t\t\t\t |\n\t| \t\t\t\t\t\t\t\t\t |\n");
        printf("\t|████████████████████████████████████████████████████████████████████████|\n\n\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/*****************************************************************************/
/*         (i):=> check if a string contains blank (space character)         */
/*****************************************************************************/
//⏬
short contentBlank(char *password) {

    for(short i = 0; password[i] != '\0'; i++)
        if(password[i] == ' ')
            return 1;

    return 0;
}

/***************************************************************************************/
/*         (i):=> check if an string (username) contains any special character         */
/***************************************************************************************/
//⏬
short isConform(char *username) {

    for(short i = 0; username[i] != '\0'; i++)
        if(username[i] < '0' || '9' < username[i] && username[i] < 'A' || 'Z' < username[i] && username[i] < 'a' || 'z' < username[i])
            return 0;

    return 1;
}

/***************************************************************/
/*         (i):=> check if a given year is a leap year         */
/***************************************************************/
//⏬
short isLeapYear(short year) {
    if(!(year % 100) && !(year % 400) || (year % 100) && !(year % 4))
        return 1;

    return 0;
}

/*****************************************************/
/*         (i):=> check if a date is correct         */
/*****************************************************/
//⏬
short isValidDate(short day, short month, short year) {

    if(1967 <= year && year <= 2023 && 1 <= month && month <= 12 && 1 <= day && day <= 31) {
        if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30 || month == 2 && (isLeapYear(year) && day > 29 || !isLeapYear(year) && day > 28))
            return 0;

        return 1;
    }

    return 0;
}

/******************************************************************************************/
/*         (i):=> check if a date format matches the expected format (dd/mm/yyyy)         */
/******************************************************************************************/
//⏬
short isValidDateFormat(char *date, short *day, short *month, short *year) {

    if(sscanf(date, "%hd/%hd/%hd", day, month, year) != 3)
        return 0;

    return 1;
}

/************************************************************************************/
/*         (i):=> generate an identifier to a new account for an given user         */
/************************************************************************************/
//⏬
short makeAccountId(char *username) {

    FILE *db = dbOpen(RECORDS, "r");
    Record record;
    short id, counter = 0;

    while(getAccountData(db, &id, &record))
        if(!strcmp(username, record.username))
            counter++;

    fclose(db);
    return counter;
}

/*******************************************************************/
/*         (i):=> count the number of digits in an integer         */
/*******************************************************************/
//⏬
short numberOfDigits(int number) {
    short counter = 1;

    while(number > 0) {
        number /= 10;
        counter++;
    }

    return counter > 1 ? --counter : counter;
}

/****************************************************/
/*         (i):=> to place the right border         */
/****************************************************/
//⏬
void borderRight(short blank) {
    for(short i = 0; i < blank; i++)
        printf(" ");
    printf("|\n");
}

/*******************************************************************/
/*         (i):=> to allocate and set up fields of an user         */
/*******************************************************************/
//⏬
void setUser(User *user, short id, char *username) {

    // case that the attribute 'user' was previously used
    if(user->name)
        free(user->name);

    user->id = id;
    user->name = (char*) malloc((1 + strlen(username)) * sizeof(char));
    strcpy(user->name, username);
}
