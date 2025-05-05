#include "mod.h"
#include "../lib.h"

/*****************************************************/
/*         (i):=> check if a date is correct         */
/*****************************************************/
//⏬
short isValidDate(short day, short month, short year) {
    if(1967 <= year && year <= 2023 && 1 <= month && month <= 12 && 1 <= day && day <= 31) {
        if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30 || month == 2 && (isLeapYear(year) && day > 29 || !isLeapYear(year) && day > 28))
            return 0;

        return 1;
    }

    return 0;
}
