#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_substr_cstr){
    my_str_t str;
    char c[10];
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "abcdwhateverwxyz", 0);
    int status = my_str_substr_cstr(&str, c, 4, 12);
    ASSERT_EQ(status, 0);
    ASSERT_STREQ(c, "whatever");
    my_str_free(&str);
}

TEST(CStringsTest, my_str_substr_cstr_out_of_bounds ){
    my_str_t str;
    char c[10];
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "abcdwhateverwxyz", 0);;
    int status = my_str_substr_cstr(&str, c, 10000, 10003);
    ASSERT_EQ(status, -1);
    ASSERT_STREQ(c, "");
    my_str_free(&str);
}
