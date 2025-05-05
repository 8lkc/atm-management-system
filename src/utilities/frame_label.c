#include "mod.h"
#include "../lib.h"

/***************************************************************************************************/
/*         (i):=> create a label with a given banner (to make sure the form doesn't spoil)         */
/***************************************************************************************************/
//⏬
void frameLabel(char *banner) {
    short bloc, side, rest, nbr = strlen(banner);
    bloc = 72 - (nbr + 4);
    side = bloc / 2;
    rest = bloc % 2;

    printf("\n\n\t|");
    for(short i = 0; i < side; i++) {
        printf("█");
    }

    printf("  \033[1m%s\033[0m  ", banner);
    for(short i = 0; i < side + rest; i++) {
        printf("█");
    }

    printf("|\n");
}
