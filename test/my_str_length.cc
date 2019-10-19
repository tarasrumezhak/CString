#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}


TEST(CStringsTest, my_str_length) {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "merry christmas!\nand happy new year!", 0);

    size_t length = my_str_length(&str);

    ASSERT_EQ(length, str.size_m);

    my_str_free(&str);
}
