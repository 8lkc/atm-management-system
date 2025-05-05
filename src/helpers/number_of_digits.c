#include "mod.h"
#include "../lib.h"

/*******************************************************************/
/*         (i):=> count the number of digits in an integer         */
/*******************************************************************/
//⏬
short numberOfDigits(int number) {
    short counter = 1;

    while(number > 0) {
        number /= 10;
        counter++;
    }

    return counter > 1 ? --counter : counter;
}
