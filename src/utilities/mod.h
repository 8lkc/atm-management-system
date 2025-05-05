#if !defined(HEADER_UTILITIES_MOD_FILE_H)
#define HEADER_UTILITIES_MOD_FILE_H

    #include "../data.h"

    short stayOrNot(char *banner, char *message, void (*func)(User, char*), User user);
    short stayOrReturn(char *banner, char *message, void (*func)(User), User user);

    void conditionalMenu(short boolean);
    void frameLabel(char *banner);
    void frameMessage(char *message, char *color);
    void header();
    void initMenu(User user, char *status);
    void mainMenu(User user, char *status);
    void success(User user);

#endif // HEADER_UTILITIES_MOD_FILE_H
