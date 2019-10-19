//
// Created by User on 19.10.2019.
//

#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_free_empty) {
my_str_t str;
my_str_create(&str, 0);
my_str_free(&str);
ASSERT_EQ(my_str_size(&str), 0);
}

TEST(CStringsTest, my_str_free_not_empty) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int status = my_str_from_cstr(&str, original, 8);
my_str_free(&str);
ASSERT_EQ(my_str_size(&str), 0);
}

