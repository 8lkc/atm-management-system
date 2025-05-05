#include "mod.h"
#include "../lib.h"

/*********************************************************************************************************************/
/*         (i):=> to 'ascize' a slice of characters (replace every character of the slice by its ascii code)         */
/*********************************************************************************************************************/
//⏬
char* asciize(char *password) {
    char *result, asciiSlice[637], value[5];
    int asciiCode;

    asciiCode = password[0];
    sprintf(asciiSlice, "%d", asciiCode);

    for(short i = 1; password[i] != '\0'; i++) {
        asciiCode = password[i];
        sprintf(value, "%d", asciiCode);
        strcat(asciiSlice, value);
    }

    result = (char*) malloc((1 + strlen(asciiSlice)) * sizeof(char));
    strcpy(result, asciiSlice);
    return result;
}
