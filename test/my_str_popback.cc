#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_popback_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    int status = my_str_popback(&str);

    EXPECT_EQ(status, -2);
    my_str_free(&str);
}

TEST(CStringsTest, my_str_popback) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas!", 0);

    int lastchar = my_str_popback(&str);

    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas");

    ASSERT_EQ(lastchar, '!');
    ASSERT_EQ(str.size_m, 15);
    ASSERT_EQ(str.capacity_m, 16);

    my_str_free(&str);
}

TEST(CStringsTest, my_str_pop_null) {
    int status = my_str_popback(NULL);
    ASSERT_EQ(status, -1);
}
