#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_write_file) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "sin²(θ) is odious to me", 0);

    FILE* fp = tmpfile();
    if (!fp) fprintf(stderr, "can't create tmpfile\n");
    rewind(fp);

    int status = my_str_write_file(&str, fp);
    rewind(fp);

    char data[1024];
    fgets(data, sizeof(data), fp);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(data, my_str_get_cstr(&str));

    fclose(fp);
    my_str_free(&str);
}
