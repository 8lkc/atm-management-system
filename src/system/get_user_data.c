#include "mod.h"
#include "../lib.h"

/*******************************************************************/
/*         (i):=> to get data of an user from the db         */
/*******************************************************************/
//⏬
short getUserData(FILE *db, short *id, char *name, char *password) {
    return fscanf(db, "%hd %s %s", id, name, password) != EOF;
}
