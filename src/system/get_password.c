#include "mod.h"
#include "../lib.h"

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
