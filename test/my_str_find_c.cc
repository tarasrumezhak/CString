#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_find_c1) {
    my_str_t str_main;
    my_str_create(&str_main, 0);
    char txt[] = "regabcff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    char c = 'a';

    size_t index = 0;
    size_t result = my_str_find_c(&str_main, c, index);

    ASSERT_EQ(result, 3);
}

TEST(CStringsTest, my_str_find_c2) {
    my_str_t str_main;
    my_str_create(&str_main, 0);
    char txt[] = "regabff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    char c = 'k';

    size_t index = 0;
    size_t result = my_str_find_c(&str_main, c, index);

    ASSERT_EQ(result, -1);
}

TEST(CStringsTest, my_str_find_c3) {
    my_str_t str_main;
    my_str_create(&str_main, 0);
    char txt[] = "regabff";
    my_str_from_cstr(&str_main, txt, sizeof(txt));

    char c = 'a';

    size_t index = 10;
    size_t result = my_str_find_c(&str_main, c, index);

    ASSERT_EQ(result, -1);
}
