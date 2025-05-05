#include "mod.h"
#include "../lib.h"

/***************************************************************************************/
/*         (i):=> check if an string (username) contains any special character         */
/***************************************************************************************/
//⏬
short isConform(char *username) {
    for(short i = 0; username[i] != '\0'; i++)
        if((username[i] < '0' || '9' < username[i]) && (username[i] < 'A' || 'Z' < username[i]) && (username[i] < 'a' || 'z' < username[i]))
            return 0;

    return 1;
}
