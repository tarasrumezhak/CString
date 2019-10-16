#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_from_cstr_empty_without_buf_size) {
    my_str_t str;
    my_str_create(&str, 0);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(original, str.data);
    ASSERT_EQ(str.size_m, 8);
    ASSERT_EQ(str.capacity_m, 8);
}

TEST(CStringsTest, my_str_from_cstr_empty_with_actual_bufsize) {
    my_str_t str;
    my_str_create(&str, 0);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 100);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(original, str.data);
    ASSERT_EQ(str.size_m, 8);
    ASSERT_EQ(str.capacity_m, 100);
}

TEST(CStringsTest, my_str_from_cstr_prealloc) {
    my_str_t str;
    my_str_create(&str, 100);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(original, str.data);
    ASSERT_EQ(str.size_m, 8);
    ASSERT_EQ(str.capacity_m, 100);
}
