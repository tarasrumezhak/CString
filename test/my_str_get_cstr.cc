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

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    const char* cstring = my_str_get_cstr(&str);

    ASSERT_STREQ(original, cstring);
}
