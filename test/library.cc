#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

#define TESTING

class CStringsTest : public testing::Test {
    void SetUp() {}

    void TearDown() {}
};

TEST(CStringsTest, my_str_create) {
    my_str_t str;

    int status = my_str_create(&str, 0);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 1);
    ASSERT_STREQ(str.data, "\0");
}

TEST(CStringsTest, my_str_create_more) {
    my_str_t str;

    int status = my_str_create(&str, 100);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 101);
    ASSERT_STREQ(str.data, "\0");
}

TEST(CStringsTest, my_str_from_cstr) {
    my_str_t str;
    my_str_create(&str, 100);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    ASSERT_EQ(status, 0);
    ASSERT_STREQ(original, str.data);
    ASSERT_EQ(str.size_m, 8);
    ASSERT_EQ(str.capacity_m, 17);
}

TEST(CStringsTest, my_str_reserve) {
    // TODO Fixtures
    my_str_t str;
    my_str_create(&str, 100);

    int status = my_str_reserve(&str, 400);

    ASSERT_EQ(status, 0);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 400);
}

TEST(CStringsTest, my_str_get_cstr_empty) {
    // TODO Fixtures
    my_str_t str;
    my_str_create(&str, 0);

    const char* cstring = my_str_get_cstr(&str);

    ASSERT_STREQ(cstring, "");
}

TEST(CStringsTest, my_str_get_cstr) {
    // TODO Fixtures
    my_str_t str;
    my_str_create(&str, 100);

    char original[] = "whatever";
    int status = my_str_from_cstr(&str, original, 0);

    const char* cstring = my_str_get_cstr(&str);

    ASSERT_STREQ(original, cstring);
}
