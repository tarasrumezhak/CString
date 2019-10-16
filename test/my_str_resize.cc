#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_resize_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    my_str_resize(&str, 10, '*');

    ASSERT_STREQ(my_str_get_cstr(&str), "**********");
    ASSERT_EQ(str.capacity_m, 20);
}

TEST(CStringsTest, my_str_resize_lessen) {
    my_str_t str;
    my_str_create(&str, 100);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    my_str_resize(&str, 4, '*');

    ASSERT_STREQ(my_str_get_cstr(&str), "what");
}

TEST(CStringsTest, my_str_resize_increase) {
    my_str_t str;
    my_str_create(&str, 0);

    char original[] = "whatever";
    my_str_from_cstr(&str, original, 0);

    int status = my_str_resize(&str, 9, '!');

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.capacity_m, 18);
    ASSERT_STREQ(my_str_get_cstr(&str), "whatever!");
}
