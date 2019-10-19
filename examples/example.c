#include <stdio.h>
#include <stdlib.h>
#include <cstrings.h>

// Freestyle here
// TODO handle uppercase?
static int less(const void* p1, const void* p2) {
    return *(char*) p1 > *(char*) p2;
}

int sort_letters(FILE* source, FILE* dest) {
    my_str_t string;
    my_str_create(&string, 4096);

    int status = my_str_read_file(&string, source);
    if (status != 0) {
        fprintf(stderr, "sorry, apparently we can't read. (status): %d\n", status);

        return 1;
    }

    qsort(string.data, string.size_m, sizeof(char), less);

    return my_str_write_file(&string, dest);
}
