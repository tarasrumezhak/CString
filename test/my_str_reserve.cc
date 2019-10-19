#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_reserve_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    int status = my_str_reserve(&str, 400);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 400);
}

TEST(CStringsTest, my_str_reserve_not_empty) {
    my_str_t str;
    my_str_create(&str, 10);

    int status = my_str_from_cstr(&str, "merry christmas!", 0);

    my_str_reserve(&str, 400);

    ASSERT_EQ(str.capacity_m, 400);
    ASSERT_EQ(str.size_m, 16);

    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas!");
}
