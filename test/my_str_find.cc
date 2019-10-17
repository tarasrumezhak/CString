#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_find) {
    my_str_t str_main;
    char txt[] = "regabcff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    my_str_t str_sub;
    char sub[] = "abc";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));

    size_t index = 0;
    size_t result = my_str_find(&str_main, &str_sub, index);

    ASSERT_EQ(result, 3);

    my_str_free(&str_main);
    my_str_free(&str_sub);
}

TEST(CStringsTest, my_str_find_not_found) {
    my_str_t str_main;
    char txt[] = "regabff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    my_str_t str_sub;
    char sub[] = "abc";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));

    size_t index = 0;
    size_t result = my_str_find(&str_main, &str_sub, index);

    ASSERT_EQ(result, -1);

my_str_free(&str_main);
my_str_free(&str_sub);
}


