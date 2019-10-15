#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_reserve_empty) {
    // TODO Fixtures
    my_str_t str;
    my_str_create(&str, 100);

    int status = my_str_reserve(&str, 400);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    // Extra 1
    ASSERT_EQ(str.capacity_m, 401);
}

TEST(CStringsTest, my_str_reserve_not_empty) {
    my_str_t str;
    my_str_create(&str, 10);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 8);

    my_str_reserve(&str, 400);

    ASSERT_EQ(str.capacity_m, 401);
    ASSERT_EQ(str.size_m, 8);

    ASSERT_STREQ(my_str_get_cstr(&str), "whatever");
}
