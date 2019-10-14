//
// Created by User on 14.10.2019.
//

#include "library.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "Taras";
    my_str_from_cstr(&str, c, sizeof(c));
    printf("%zu\n", str.capacity_m);
    printf("CString: %s\n", c);
    printf("%s %zu %zu\n", str.data, str.capacity_m, str.size_m);
    printf("%zu\n", my_str_size(&str));
    printf("%i\n", my_str_getc(&str, 2));
    my_str_putc(&str, 2, 'p');
    printf("%s\n", str.data);
    printf("%zu\n", str.size_m);

}
