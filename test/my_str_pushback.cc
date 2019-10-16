#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_pushback_no_alloc) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas", 100);

    int status = my_str_pushback(&str, '!');

    EXPECT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 16);
    ASSERT_EQ(str.capacity_m, 100);
    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas!");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_pushback_with_alloc) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas", 15);

    int status = my_str_pushback(&str, '!');

    EXPECT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 16);
    // Twice the previous capacity
    ASSERT_EQ(str.capacity_m, 30);
    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas!");

    my_str_free(&str);
}

TEST(CStringsTest, my_str_pushback_null) {
    int status = my_str_pushback(NULL, '!');
    ASSERT_EQ(status, -1);
}
