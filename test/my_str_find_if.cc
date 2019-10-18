#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

int is_a(int letter) {
    if (letter == 97) {
        return 1;
    }
    return 0;
}

TEST(CStringsTest, my_str_find_if) {
    my_str_t str_sub;
    my_str_create(&str_sub, 0);
    char sub[] = "taras";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));

    size_t result = my_str_find_if(&str_sub, is_a);
    ASSERT_EQ(result, 1);
}

TEST(CStringsTest, my_str_find_if_not_found) {
    my_str_t str_sub;
    my_str_create(&str_sub, 0);
    char sub[] = "POCLover";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));


    size_t result = my_str_find_if(&str_sub, is_a);
    ASSERT_EQ(result, (size_t)(-1));
}
