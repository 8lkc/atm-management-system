#include "mod.h"
#include "../lib.h"

/**********************************************************************/
/*         (i):=> to get data of an account from the db         */
/**********************************************************************/
//⏬
short getAccountData(FILE *db, short *id, Record *record) {
    return fscanf(db, "%hd %hd %s %ld %hd/%hd/%hd %s %ld %lf %s", id, &record->userId, record->username, &record->accountNumber,
                                                                  &record->creation.day, &record->creation.month, &record->creation.year,
                                                                  record->country, &record->phoneNumber, &record->among, record->accountType) != EOF;
}
