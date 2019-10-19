#include "gtest/gtest.h"


extern "C" {
#include "cstrings.h"
#include "example.h"
}

TEST(CStringsTest, example_small_lowercase) {
    FILE* source = tmpfile();
    if (source == NULL) {
        fprintf(stderr, "can't create tmpfile\n");
        return;
    }

    fputs("merry christmas everybody!", source);
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
    ASSERT_STRCASEEQ(data, "emrry achimrsst bdeeorvyy!");

    fclose(source);
    fclose(dest);
}

TEST(CStringsTest, example_small_mixedcase) {
    FILE* source = tmpfile();
    if (source == NULL) {
        fprintf(stderr, "can't create tmpfile\n");
        return;
    }

    fputs("Merry Christmas Everybody!", source);
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
    ASSERT_STRCASEEQ(data, "eMrry aChimrsst bdEeorvyy!");

    fclose(source);
    fclose(dest);
}

TEST(CStringsTest, example_large_mixedcase) {
    FILE* source = tmpfile();
    if (source == NULL) {
        fprintf(stderr, "can't create tmpfile\n");
        return;
    }

    fputs("Merry Christmas Everybody!", source);
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
    ASSERT_STRCASEEQ(data, "eMrry aChimrsst bdEeorvyy!");

    fclose(source);
    fclose(dest);
}
