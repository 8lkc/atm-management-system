#include "mod.h"
#include "../lib.h"

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
