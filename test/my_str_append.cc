#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_append){
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 0);
    my_str_create(&str2, 0);
    my_str_from_cstr(&str1, "what", 0);
    my_str_from_cstr(&str2, "ever", 0);
    int status = my_str_append(&str1, &str2);
    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str1), "whatever");
    my_str_free(&str1);
    my_str_free(&str2);
}
