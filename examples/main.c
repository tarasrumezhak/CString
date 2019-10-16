#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstrings.h>

#ifndef TESTING
int main(void) {

    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "whatever";
    my_str_from_cstr(&str, c, sizeof(c));

    printf("Capacity: %zu\n", str.capacity_m);
    printf("CString: %s\n", c);

    printf("Data: %s,  Capacity: %zu, Size: %zu\n", str.data, str.capacity_m, str.size_m);
    printf("my_str_size: %zu\n", my_str_size(&str));

    printf("Char @7 = %c\n", my_str_getc(&str, 7));
    my_str_putc(&str, 7, 'R');
    printf("str.data: %s\n", str.data);

    printf("Out of my_str_get_cstr: %s\n", my_str_get_cstr(&str));

    my_str_t str_main;
    char txt[] = "regabcff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    my_str_t str_sub;
    char sub[] = "abc";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));

    size_t index = 0;
    printf(my_str_find(&str_main, &str_sub, index));
}
#endif
