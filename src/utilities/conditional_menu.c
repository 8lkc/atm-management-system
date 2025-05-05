#include "mod.h"
#include "../lib.h"

/************************************************************************************************************************************************/
/*         (i):=> displays a part of the main menu according to the fact that an user own, or not, at least one account in the db         */
/************************************************************************************************************************************************/
//⏬
void conditionalMenu(short boolean) {
    if(boolean) {
        printf("\t|\t[2]— UPDATE ACCOUNT INFORMATION                                  |\n");
        printf("\t|\t[3]— CHECK ACCOUNT(S)                                            |\n");
        printf("\t|\t[4]— CHECK LIST OF OWNED ACCOUNT(S)                              |\n");
        printf("\t|\t[5]— MAKE TRANSACTION                                            |\n");
        printf("\t|\t[6]— REMOVE EXISTING ACCOUNT                                     |\n");
        printf("\t|\t[7]— TRANSFERT OWNERSHIP                                         |\n");
    } else {
        printf("\t|\t\033[90m[2]— UPDATE ACCOUNT INFORMATION\033[0m                                  |\n");
        printf("\t|\t\033[90m[3]— CHECK ACCOUNT(S)\033[0m                                            |\n");
        printf("\t|\t\033[90m[4]— CHECK LIST OF OWNED ACCOUNT(S)\033[0m                              |\n");
        printf("\t|\t\033[90m[5]— MAKE TRANSACTION\033[0m                                            |\n");
        printf("\t|\t\033[90m[6]— REMOVE EXISTING ACCOUNT\033[0m                                     |\n");
        printf("\t|\t\033[90m[7]— TRANSFERT OWNERSHIP\033[0m                                         |\n");
    }
}
