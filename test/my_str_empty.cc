//
// Created by User on 19.10.2019.
//

#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_empty) {
my_str_t str;
my_str_create(&str, 0);
ASSERT_EQ(my_str_empty(&str), 1);
}

TEST(CStringsTest, my_str_not_empty) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int status = my_str_from_cstr(&str, original, 8);
ASSERT_EQ(my_str_empty(&str), 0);
}
