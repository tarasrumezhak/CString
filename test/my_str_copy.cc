#include "gtest/gtest.h"

extern "C" {
#include "cstrings.h"
}

TEST(CStringsTest, my_str_copy_empty) {
    my_str_t source;
    my_str_create(&source, 0);

    my_str_t dest;
    my_str_create(&dest, 0);

    int status = my_str_copy(&source, &dest, 0);

    EXPECT_EQ(status, 0);
    ASSERT_EQ(dest.capacity_m, 1);

    my_str_free(&source);
    my_str_free(&dest);
}

TEST(CStringsTest, my_str_copy_dest_empty_dont_reserve) {
    my_str_t source;
    my_str_create(&source, 100);

    my_str_t dest;
    my_str_create(&dest, 0);

    my_str_from_cstr(&source, "anything", 0);

    int status = my_str_copy(&source, &dest, 0);

    EXPECT_EQ(status, 0);
    ASSERT_EQ(dest.capacity_m, 9);
    ASSERT_EQ(dest.size_m, 8);
    ASSERT_STREQ(my_str_get_cstr(&dest), my_str_get_cstr(&source));

    my_str_free(&source);
    my_str_free(&dest);
}

TEST(CStringsTest, my_str_copy_dest_empty_reserve_please) {
    my_str_t source;
    my_str_create(&source, 100);

    my_str_t dest;
    my_str_create(&dest, 0);

    my_str_from_cstr(&source, "anything", 0);

    int status = my_str_copy(&source, &dest, 1);

    EXPECT_EQ(status, 0);
    ASSERT_EQ(dest.capacity_m, 102);
    ASSERT_EQ(dest.size_m, 8);
    ASSERT_STREQ(my_str_get_cstr(&dest), my_str_get_cstr(&source));

    my_str_free(&source);
    my_str_free(&dest);
}

TEST(CStringsTest, my_str_copy_dest_not_empty_dont_reserve) {
    my_str_t source;
    my_str_create(&source, 100);

    my_str_t dest;
    my_str_create(&dest, 10);

    my_str_from_cstr(&source, "anything", 0);
    my_str_from_cstr(&dest, "something else", 0);

    int status = my_str_copy(&source, &dest, 0);

    EXPECT_EQ(status, 0);
    ASSERT_EQ(dest.capacity_m, 102);
    ASSERT_EQ(dest.size_m, 8);
    ASSERT_STREQ(my_str_get_cstr(&dest), my_str_get_cstr(&source));

    my_str_free(&source);
    my_str_free(&dest);
}
