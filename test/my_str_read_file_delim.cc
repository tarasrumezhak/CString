#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_read_file_delim_empty_file) {
    my_str_t str;
    my_str_create(&str, 0);

    FILE* fp = tmpfile();
    if (fp == NULL) fprintf(stderr, "can't create tmpfile\n");

    int status = my_str_read_file_delim(&str, fp, '*');

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "");

    fclose(fp);
    my_str_free(&str);
}

TEST(CStringsTest, my_str_read_file_delim_with_delim) {
    my_str_t str;
    my_str_create(&str, 0);

    FILE* fp = tmpfile();
    if (fp == NULL) fprintf(stderr, "can't create tmpfile\n");
    fprintf(fp, "sin²(θ) is odious to me");
    rewind(fp);

    int status = my_str_read_file_delim(&str, fp, '(');

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "sin²");

    fclose(fp);
    my_str_free(&str);
}

TEST(CStringsTest, my_str_read_file_delim_without_delim) {
    my_str_t str;
    my_str_create(&str, 0);

    FILE* fp = tmpfile();
    if (fp == NULL) fprintf(stderr, "can't create tmpfile\n");
    fprintf(fp, "sin²(θ) is odious to me");
    rewind(fp);

    int status = my_str_read_file_delim(&str, fp, '*');

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "sin²(θ) is odious to me");

    // FIXME segfault at fclose?
    // fclose(fp);
    my_str_free(&str);
}
