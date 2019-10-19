//
// Created by User on 19.10.2019.
//

#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_getc_empty) {
my_str_t str;
my_str_create(&str, 0);
ASSERT_EQ(my_str_getc(&str, 2), -1);
}

TEST(CStringsTest, my_str_getc_first) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int status = my_str_from_cstr(&str, original, 8);
ASSERT_EQ(my_str_getc(&str, 0), int('w'));
}

TEST(CStringsTest, my_str_getc_last) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int status = my_str_from_cstr(&str, original, 8);
ASSERT_EQ(my_str_getc(&str, 7), int('r'));
}

TEST(CStringsTest, my_str_getc_mid) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int status = my_str_from_cstr(&str, original, 8);
ASSERT_EQ(my_str_getc(&str, 2), int('a'));
}