#include "mod.h"
#include "../lib.h"

/*********************************************************************/
/*         (i):=> to save data of an account on the db         */
/*********************************************************************/
//⏬
void saveAccountData(FILE *db, short id, Record record) {
    fprintf(db, "%d %d %s %ld %02d/%02d/%d %s %ld %.3lf %s\n", id, record.userId, record.username, record.accountNumber,
                                                               record.creation.day, record.creation.month, record.creation.year,
                                                               record.country, record.phoneNumber, record.among, record.accountType);
}
