#include "mod.h"
#include "../lib.h"

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
