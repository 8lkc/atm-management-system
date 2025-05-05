#include "mod.h"
#include "../lib.h"

/******************************************************************/
/*         (i):=> for authentification of registred users         */
/******************************************************************/
//⏬
void signIn(User user) {
    char username[255], password[255];

    header();
    frameLabel("BANK MANAGEMENT SYSTEM");
    printf("\n\t\tUSERNAME: ");
    fgets(username, 255, stdin);
    username[strcspn(username, "\n")] = '\0';

    // disabling echo
    system("stty -echo");

    printf("\n\t\tPASSWORD: ");
    fgets(password, 255, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    // restore terminal
    system("stty echo");

    switch(strcmp(asciize(password), getPassword(username))) {
        case 0:
            setUser(&user, getUserId(username), username);
            mainMenu(user, "\033[1;32mCONNECTION SUCCEDED !\033[0m");
            break;

        default:
            initMenu(user, "\033[1;38;5;208mWRONG PASSWORD OR USERNAME !!\033[0m");
    }
}
