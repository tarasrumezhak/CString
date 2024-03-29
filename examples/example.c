#include <stdio.h>
#include <stdlib.h>
#include <cstrings.h>
#include <ctype.h>

// Freestyle here
static inline int greater(const void* p1, const void* p2) {
    char c1 = *(char*) p1;
    char c2 = *(char*) p2;

    // Upper case is compared with lower case on equal terms
    char value1 = c1 + (isupper(c1) ? 'a' - 'A' : 0);
    char value2 = c2 + (isupper(c2) ? 'a' - 'A' : 0);

    return value1 > value2;
}

int sort_letters(FILE* source, FILE* dest) {
    my_str_t string;
    my_str_create(&string, 4096);

    int status = my_str_read_file(&string, source);
    if (status != 0) {
        fprintf(stderr, "sorry, apparently we can't read. (status): %d\n", status);

        return 1;
    }

    // Making sure the last word is not left out
    my_str_pushback(&string, '!');

    char* lidx;
    char* ridx;
    for (lidx = ridx = string.data; *ridx; ridx++) {
        // Threat anything non alpha as a word break
        if (!isalpha(*ridx)) {
            // Unless there were consecutive breaks -
            // sort the space from the last break until this break
            if (ridx != lidx) {
                qsort(lidx, ridx-lidx, sizeof(char), greater);
            }

            lidx = ridx;
        }
    }

    my_str_popback(&string);

    return my_str_write_file(&string, dest);
}
