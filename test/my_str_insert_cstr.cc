#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_insert_cstr) {
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "merrymas";
    my_str_from_cstr(&str, c, sizeof(c));

    int status = my_str_insert_cstr(&str, " christ", 5);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_insert_cstr_sample_text) {
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "sample text";
    my_str_from_cstr(&str, c, sizeof(c));

    int status = my_str_insert_cstr(&str, "some ", 0);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "some sample text");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_insert_cstr_out_of_bounds) {
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "sample text";
    my_str_from_cstr(&str, c, sizeof(c));

    int status = my_str_insert_cstr(&str, "some ", 10000);

    ASSERT_EQ(status, -1);
    ASSERT_STREQ(my_str_get_cstr(&str), "sample text");

    my_str_free(&str);
}
