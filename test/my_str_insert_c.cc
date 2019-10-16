#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_insert_c) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merrychristmas!", 100);

    int status = my_str_insert_c(&str, ' ', 5);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas!");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_insert_c_sample_text) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, " sample text", 100);

    int status = my_str_insert_c(&str, 'a', 0);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "a sample text");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_insert_c_out_of_bounds) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, " sample text", 100);

    int status = my_str_insert_c(&str, 'a', 10000);

    ASSERT_EQ(status, -1);
    ASSERT_STREQ(my_str_get_cstr(&str), " sample text");

    my_str_free(&str);
}
