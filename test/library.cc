#include "gtest/gtest.h"

extern "C" {
#include "library.h"
}

#define TESTING

class CStringsTest : public testing::Test {
    void SetUp() {}
    void TearDown() {}
};

TEST(CStringsTest, my_str_create) {
    my_str_t str;

    int status = my_str_create(&str, 0);

    EXPECT_NE(status, -1);
    ASSERT_EQ(str.size_m, 0);
    ASSERT_EQ(str.capacity_m, 1);
    EXPECT_EQ(*str.data, NULL);
}
