#include "gtest/gtest.h"


extern "C" {
#include "cstrings.h"
#include "example.h"
}

TEST(CStringsTest, example) {
    FILE* source = tmpfile();
    if (source == NULL) {
        fprintf(stderr, "can't create tmpfile\n");
        return;
    }

    fputs("zxyabc", source);
    rewind(source);

    FILE* dest = tmpfile();
    if (dest == NULL) {
        fprintf(stderr, "can't create tmpfile\n");
        return;
    }

    int status = sort_letters(source, dest);
    rewind(dest);

    char data[1024];
    fgets(data, sizeof(data), dest);

    ASSERT_EQ(status, 0);
    ASSERT_STRCASEEQ(data, "abcxyz");

    fclose(source);
    fclose(dest);
}
