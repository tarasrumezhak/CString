#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_resize_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    my_str_resize(&str, 10, '&');

    ASSERT_STREQ(my_str_get_cstr(&str), "&&&&&&&&&&");
    // Resizing twice as needed + 1
    ASSERT_EQ(str.capacity_m, 21);
}

TEST(CStringsTest, my_str_resize_not_empty) {
    my_str_t str;
    my_str_create(&str, 100);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    my_str_resize(&str, 4, '&');

    ASSERT_STREQ(my_str_get_cstr(&str), "what");
}
