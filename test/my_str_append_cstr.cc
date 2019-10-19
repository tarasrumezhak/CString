#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_append_cstr){
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "what";
    my_str_from_cstr(&str, c, sizeof(c));

    int status = my_str_append_cstr(&str, "ever");

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "whatever");

    my_str_free(&str);
}
