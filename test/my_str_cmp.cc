#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_cmp_equal) {
    my_str_t str_1;
    char txt1[] = "hello";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    my_str_t str_2;
    char txt2[] = "hello";
    my_str_from_cstr(&str_2, txt2, sizeof(txt2));

    int result = my_str_cmp(&str_1, &str_2)

    ASSERT_EQ(result, 0);
    my_str_free(&str1);
    my_str_free(&str2);
}

TEST(CStringsTest, my_str_cmp_less) {
    my_str_t str_1;
    char txt1[] = "abcd";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    my_str_t str_2;
    char txt2[] = "abce";
    my_str_from_cstr(&str_2, txt2, sizeof(txt2));

    int result = my_str_cmp(&str_1, &str_2)

    ASSERT_EQ(result, -1);
    my_str_free(&str1);
    my_str_free(&str2);
}

TEST(CStringsTest, my_str_cmp_greater) {
    my_str_t str_1;
    char txt1[] = "abcz";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    my_str_t str_2;
    char txt2[] = "abcf";
    my_str_from_cstr(&str_2, txt2, sizeof(txt2));

    int result = my_str_cmp(&str_1, &str_2)

    ASSERT_EQ(result, 1);
    my_str_free(&str1);
    my_str_free(&str2);
}

TEST(CStringsTest, my_str_cmp_greater) {
    my_str_t str_1;
    char txt1[] = "hello";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    my_str_t str_2;
    char txt2[] = "goodmorning";
    my_str_from_cstr(&str_2, txt2, sizeof(txt2));

    int result = my_str_cmp(&str_1, &str_2)

    ASSERT_EQ(result, -1);
    my_str_free(&str1);
    my_str_free(&str2);
}

TEST(CStringsTest, my_str_cmp_greater) {
    my_str_t str_1;
    char txt1[] = "ILovePOC";
    my_str_from_cstr(&str_1, txt1, sizeof(txt1));

    my_str_t str_2;
    char txt2[] = "OOP";
    my_str_from_cstr(&str_2, txt2, sizeof(txt2));

    int result = my_str_cmp(&str_1, &str_2)

    ASSERT_EQ(result, 1);
    my_str_free(&str1);
    my_str_free(&str2);
}
