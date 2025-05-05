#include "mod.h"
#include "../lib.h"

/****************************************************/
/*         (i):=> to place the right border         */
/****************************************************/
//⏬
void borderRight(short blank) {
    for(short i = 0; i < blank; i++)
        printf(" ");
    printf("|\n");
}
