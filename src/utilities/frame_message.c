#include "mod.h"
#include "../lib.h"

/**********************************************************************************************************/
/*         (i):=> align a message at the center of the bloc (to make sure the form doesn't spoil)         */
/**********************************************************************************************************/
//⏬
void frameMessage(char *message, char *color) {
    short bloc, side, rest, nbr = strlen(message);
    bloc = 72 - nbr;
    side = bloc / 2;
    rest = bloc % 2;

    printf("\t|");
    for(short i = 0; i < side; i++) {
        printf(" ");
    }

    printf("%s%s\033[0m", color, message);
    for(short i = 0; i < side + rest; i++) {
        printf(" ");
    }

    printf("|\n\t| \t\t\t\t\t\t\t\t\t |\n");
}
