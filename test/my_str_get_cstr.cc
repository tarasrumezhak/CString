#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_get_cstr_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    const char* cstring = my_str_get_cstr(&str);

    ASSERT_STREQ(cstring, "");
}

TEST(CStringsTest, my_str_get_cstr) {
    my_str_t str;
    my_str_create(&str, 100);

    int status = my_str_from_cstr(&str, "over there \n over here", 0);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 22);
    ASSERT_STREQ(my_str_get_cstr(&str), "over there \n over here");
}
