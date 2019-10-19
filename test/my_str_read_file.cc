#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_read_file_not_empty) {
    my_str_t str;
    my_str_create(&str, 100);

    FILE* fp = tmpfile();
    if (!fp) fprintf(stderr, "can't create tmpfile\n");

    fputs("sin²(θ) is odious to me \n sin²(θ) is odious to me", fp);
    rewind(fp);

    int status = my_str_read_file(&str, fp);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 53);
    ASSERT_STREQ(my_str_get_cstr(&str), "sin²(θ) is odious to me \n sin²(θ) is odious to me");

    fclose(fp);
    my_str_free(&str);
}


TEST(CStringsTest, my_str_read_file_starting_empty) {
    my_str_t str;
    my_str_create(&str, 0);

    FILE* fp = tmpfile();
    if (!fp) fprintf(stderr, "can't create tmpfile\n");

    fprintf(fp, "merry christmas!");
    rewind(fp);

    int status = my_str_read_file(&str, fp);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(my_str_get_cstr(&str), "merry christmas!");
    ASSERT_EQ(str.size_m, 16);

    fclose(fp);
    my_str_free(&str);
}
