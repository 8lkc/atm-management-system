#include "mod.h"
#include "../lib.h"

/*******************************************************************/
/*         (i):=> to allocate and set up fields of an user         */
/*******************************************************************/
//⏬
void setUser(User *user, short id, char *username) {
    // case that the attribute 'user' was previously used
    if(user->name)
        free(user->name);

    user->id = id;
    user->name = (char*) malloc((1 + strlen(username)) * sizeof(char));
    strcpy(user->name, username);
}
