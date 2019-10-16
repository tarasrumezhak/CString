#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_shrink_to_fit) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas!", 100);

    ASSERT_EQ(str.capacity_m, 100);

    int status = my_str_shrink_to_fit(&str);

    EXPECT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 16);
    ASSERT_EQ(str.capacity_m, 16);

    my_str_free(&str);
}

TEST(CStringsTest, my_str_shrink_to_fit_null) {
    int status = my_str_shrink_to_fit(NULL);
    ASSERT_EQ(status, -3);
}
