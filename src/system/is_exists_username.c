#include "mod.h"
#include "../lib.h"

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
