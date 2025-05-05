#include "mod.h"
#include "../lib.h"

/***************************************************************/
/*         (i):=> check if a given year is a leap year         */
/***************************************************************/
//⏬
short isLeapYear(short year) {
    if(!(year % 100) && !(year % 400) || (year % 100) && !(year % 4))
        return 1;

    return 0;
}
