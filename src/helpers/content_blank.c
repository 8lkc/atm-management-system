#include "mod.h"
#include "../lib.h"

/*****************************************************************************/
/*         (i):=> check if a string contains blank (space character)         */
/*****************************************************************************/
//⏬
short contentBlank(char *password) {
    for(short i = 0; password[i] != '\0'; i++)
        if(password[i] == ' ')
            return 1;

    return 0;
}
