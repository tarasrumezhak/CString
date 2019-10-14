#include "gtest/gtest.h"

class CStringsTest : public testing::Test {
    void SetUp() {}
    void TearDown() {}
};

TEST(CStringsTest, ok) {
    ASSERT_EQ(42, 41);
}
