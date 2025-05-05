#include "mod.h"
#include "../lib.h"

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
