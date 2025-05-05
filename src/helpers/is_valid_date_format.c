#include "mod.h"
#include "../lib.h"

/******************************************************************************************/
/*         (i):=> check if a date format matches the expected format (dd/mm/yyyy)         */
/******************************************************************************************/
//⏬
short isValidDateFormat(char *date, short *day, short *month, short *year) {
    if(sscanf(date, "%hd/%hd/%hd", day, month, year) != 3)
        return 0;

    return 1;
}
