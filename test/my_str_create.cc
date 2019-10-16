#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_create) {
    my_str_t str;

    int status = my_str_create(&str, 0);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 0);
    ASSERT_STREQ(str.data, "");
}

TEST(CStringsTest, my_str_create_more) {
    my_str_t str;

    int status = my_str_create(&str, 100);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 100);
    ASSERT_STREQ(str.data, "");
}
