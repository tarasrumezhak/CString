#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_substr){
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 0);
    my_str_create(&str2, 0);
    my_str_from_cstr(&str1, "abcdwhateverwxyz", 0);
    int status = my_str_substr(&str1, &str2, 4, 12);
    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str2), "whatever");
    my_str_free(&str1);
    my_str_free(&str2);
}

TEST(CStringsTest, my_str_substr_out_of_bounds ){
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 0);
    my_str_create(&str2, 0);
    my_str_from_cstr(&str1, "abcdwhateverwxyz", 0);
    int status = my_str_substr(&str1, &str2, 10000, 10003);
    ASSERT_EQ(status, -1);
    ASSERT_STREQ(my_str_get_cstr(&str2), "");
    my_str_free(&str1);
    my_str_free(&str2);
}
