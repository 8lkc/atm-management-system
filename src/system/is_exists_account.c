#include "mod.h"
#include "../lib.h"

/*********************************************************************************/
/*         (i):=> to check if an username already exists in the db         */
/*********************************************************************************/
//⏬
short isExistsAccount(short accountNumber, char *username, FILE *db) {

    Record record;
    short id;

    while(getAccountData(db, &id, &record)) {
        if(record.accountNumber == accountNumber && !strcmp(record.username, username))
            return 1;
    }

    return 0;
}
