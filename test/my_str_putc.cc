//
// Created by User on 19.10.2019.
//


#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_putc_empty) {
my_str_t str;
my_str_create(&str, 0);
int status = my_str_putc(&str, 0, 'c');
ASSERT_EQ(status, 0);
ASSERT_EQ(my_str_getc(&str, 0), int('c'));
}

TEST(CStringsTest, my_str_putc_first) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int stat = my_str_from_cstr(&str, original, 10);
int status = my_str_putc(&str, 0, 'a');
ASSERT_EQ(status, 0);
ASSERT_EQ(my_str_getc(&str, 0), int('a'));
}

TEST(CStringsTest, my_str_putc_last) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int stat = my_str_from_cstr(&str, original, 10);
int status = my_str_putc(&str, 7, 'a');
ASSERT_EQ(status, 0);
ASSERT_EQ(my_str_getc(&str, 7), int('a'));
}

TEST(CStringsTest, my_str_putc_beyond) {
my_str_t str;
my_str_create(&str, 0);
char original[] = "whatever";
int stat = my_str_from_cstr(&str, original, 10);
int status = my_str_putc(&str, 9, 'a');
ASSERT_EQ(status, -1);
}