#include "mod.h"
#include "../lib.h"

/********************************************************************/
/*         (i):=> juste to create a password for a new user         */
/********************************************************************/
//⏬
char* createPassword() {

    char password[255], confirmation[255], *result;

    header();
    frameLabel("PASSWORD CREATION");

    // disabling echo
    system("stty -echo");

    printf("\n\t\tMAKE A PASSWORD:  ");
    fgets(password, 255, stdin);
    printf("\n\n\t\tCONFIRM THE PASSWORD:  ");
    fgets(confirmation, 255, stdin);

    while(strcmp(password, confirmation)) {
        header();
        frameLabel("PASSWORD CREATION");
        printf("\n\t \033[1;38;5;208m THE PASSWORDS ENTERED ARE DIFFERENTS !\033[0m\n");
        printf("\n\t\tMAKE A PASSWORD:  ");
        fgets(password, 255, stdin);
        printf("\n\n\t\tCONFIRM THE PASSWORD:  ");
        fgets(confirmation, 255, stdin);
    }

    // restore terminal
    system("stty echo");

    password[strcspn(password, "\n")] = '\0';
    result = (char*) malloc((1 + strlen(password)) * sizeof(char));
    strcpy(result, password);
    return result;
}
