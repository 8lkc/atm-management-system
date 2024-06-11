#include "./library/header.h"

int main(int argc, char *argv[]) {

    User user;
    user.name = NULL;

    initMenu(user, "");

    return EXIT_SUCCESS;
}
