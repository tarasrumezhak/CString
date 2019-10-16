#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_clear) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas!", 100);

    my_str_clear(&str);

    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 100);
    ASSERT_STREQ(my_str_get_cstr(&str), "");

    my_str_free(&str);
}
