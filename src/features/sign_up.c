#include "mod.h"
#include "../lib.h"

/**********************************************************************************/
/*         (i):=> for registration of users whose aren't be registred yet         */
/**********************************************************************************/
//⏬
void signUp(User user) {
    FILE *db = dbOpen(USERS, "a+");
    char username[255], tempUsername[255], tempPassword[637];
    short userId = -1;

    header();
    frameLabel("NEW USER");
    printf("\n\t\tGIVE AN USERNAME:  ");
    fgets(username, 255, stdin);
    username[strcspn(username, "\n")] = '\0';

    while(contentBlank(username) || !isConform(username) || isExistsUsername(username, db)) {
        header();
        frameLabel("NEW USER");

        if(contentBlank(username))
            printf("\n\t \033[1;38;5;208m PLEASE, NO BLANK !\033[0m\n");
        else if(!isConform(username))
            printf("\n\t \033[1;38;5;208m ONLY ALPH-NUMERICAL CHARACTERS ALLOWED !\033[0m\n");
        else
            printf("\n\t \033[1;38;5;208m USERNAME ALREADY TAKEN !\033[0m\n");

        printf("\n\t\tGIVE AN USERNAME:  ");
        fgets(username, 255, stdin);
        username[strcspn(username, "\n")] = '\0';

        // Move the file pointer to the beginning of the file
        fseek(db, 0, SEEK_SET);
    }

    // make an identifier for the new user
    while(getUserData(db, &userId, tempUsername, tempPassword));
    if(userId > -1)
        userId++;
    else
        userId = 0;

    saveUserData(db, userId, username, createPassword());
    setUser(&user, userId, username);
    fclose(db);

    initMenu(user, "\033[1;32mOPERATION SUCCEDED !\033[0m");
}
