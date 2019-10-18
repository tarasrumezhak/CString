#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_cmp_cstr_equal) {
    my_str_t str_1;
    my_str_create(&str_1, 0);
    char txt1[] = "hello";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    char txt2[] = "hello";

    int result = my_str_cmp_cstr(&str_1, txt2);

    ASSERT_EQ(result, 0);
    my_str_free(&str_1);
}

TEST(CStringsTest, my_str_cmp_cstr_less) {
    my_str_t str_1;
    my_str_create(&str_1, 0);
    char txt1[] = "abcd";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    char txt2[] = "abce";

    int result = my_str_cmp_cstr(&str_1, txt2);

    ASSERT_EQ(result, -1);
    my_str_free(&str_1);
}

TEST(CStringsTest, my_str_cmp_cstr_greater) {
    my_str_t str_1;
    my_str_create(&str_1, 0);
    char txt1[] = "abcz";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    char txt2[] = "abcf";

    int result = my_str_cmp_cstr(&str_1, txt2);

    ASSERT_EQ(result, 1);
    my_str_free(&str_1);
}

TEST(CStringsTest, my_str_cmp_cstr_less_size) {
    my_str_t str_1;
    my_str_create(&str_1, 0);
    char txt1[] = "hello";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    char txt2[] = "goodmorning";

    int result = my_str_cmp_cstr(&str_1,txt2);

    ASSERT_EQ(result, -1);
    my_str_free(&str_1);
}

TEST(CStringsTest, my_str_cmp_cstr_greater_size) {
    my_str_t str_1;
    my_str_create(&str_1, 0);
    char txt1[] = "ILovePOC";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    char txt2[] = "OOP";

    int result = my_str_cmp_cstr(&str_1, txt2);

    ASSERT_EQ(result, 1);
    my_str_free(&str_1);
}
