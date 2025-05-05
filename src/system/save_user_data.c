#include "mod.h"
#include "../lib.h"

/******************************************************************/
/*         (i):=> to save data of an user on the db         */
/******************************************************************/
//⏬
void saveUserData(FILE *db, short id, char *name, char *password) {
    fprintf(db, "%d %s %s\n", id, name, asciize(password));
}
