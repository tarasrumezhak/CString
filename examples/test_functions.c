#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstrings.h>

#ifndef TESTING
int main(void) {

    // Створення та знищення стрічки.
    printf("// Створення та знищення стрічки.\n");
    my_str_t str;
    my_str_create(&str, 0);
    char c[] = "whatever";
    my_str_from_cstr(&str, c, sizeof(c));

    // Інформація про стрічку
    printf("\n// Інформація про стрічку\n");
    printf("Data: %s\n", my_str_get_cstr(&str));
    printf("Capacity: %zu\n", my_str_capacity(&str));
    printf("Size: %zu\n", my_str_size(&str));
    printf("Is string empty?: %s\n", my_str_empty(&str)?"true":"false");

    // Доступ до символів стрічки
    printf("\n// Доступ до символів стрічки\n");
    printf("Char №7 = %c\n", my_str_getc(&str, 7));
    my_str_putc(&str, 7, 'R');

    // Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
    printf("\n// Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.\n");
    printf("Data(7th symbol changed): %s\n", my_str_get_cstr(&str));
    my_str_pushback(&str, '.');
    printf("Data(new symbol added): %s\n", my_str_get_cstr(&str));
    my_str_popback(&str);
    printf("Data(new symbol removed): %s\n", my_str_get_cstr(&str));
    my_str_t str_dest;
    my_str_create(&str_dest, 0);
    my_str_copy(&str, &str_dest, 0);
    printf("Data(copied string): %s\n", my_str_get_cstr(&str_dest));
    my_str_clear(&str_dest);
    printf("Data(copied and cleared string): %s\n", my_str_get_cstr(&str_dest));
    my_str_free(&str_dest);
    my_str_insert_c(&str, '(', 4);
    printf("Data(inserted char): %s\n", my_str_get_cstr(&str));

    my_str_t temp_str1;
    my_str_create(&temp_str1, 0);
    char temp1[] = "inserted string) ";
    my_str_from_cstr(&temp_str1, temp1, sizeof(temp1));
    my_str_insert(&str, &temp_str1, 5);
    my_str_free(&temp_str1);
    printf("Data(inserted my_str): %s\n", my_str_get_cstr(&str));
    my_str_insert_cstr(&str, " and inserted cstring", 20);
    printf("Data(inserted cstr): %s\n", my_str_get_cstr(&str));

    my_str_t temp_str2;
    my_str_create(&temp_str2, 0);
    char temp2[] = " (appended string";
    my_str_from_cstr(&temp_str2, temp2, sizeof(temp2));
    my_str_append(&str, &temp_str2);
    my_str_free(&temp_str2);
    printf("Data(appended string: %s\n", my_str_get_cstr(&str));
    my_str_append_cstr(&str, " and appended cstring)");
    printf("Data(appended cstring): %s\n", my_str_get_cstr(&str));

    my_str_t new_str;
    my_str_create(&new_str, 0);
    my_str_substr(&str, &new_str, 0, 4);
    printf("Data(substring): %s\n", my_str_get_cstr(&new_str));
    char new_c_str[10];
    my_str_substr_cstr(&str, new_c_str, 43, 47);
    printf("Data(sub Cstring): %s\n", new_c_str);
    my_str_free(&str);

    // Маніпуляції розміром стрічки.
    printf("\n// Маніпуляції розміром стрічки.\n");
    my_str_append_cstr(&new_str, new_c_str); // new string is "whateveR"
    printf("Capacity(before increasing new string capacity): %zu\n", my_str_capacity(&new_str));
    my_str_reserve(&new_str, 10);
    printf("Capacity(after increasing new string capacity): %zu\n", my_str_capacity(&new_str));
    my_str_shrink_to_fit(&new_str);
    printf("Capacity(capacity = size): %zu\n", my_str_capacity(&new_str));
    my_str_resize(&new_str, 4, '_');
    my_str_resize(&new_str, 8, '_');
    printf("Capacity(resized): %s\n", my_str_get_cstr(&new_str));

    // Функції пошуку та порівняння.
    printf("\n// Функції пошуку та порівняння.\n");
    my_str_t str_sub;
    my_str_create(&str_sub, 0);
    char sub[] = "____";
    my_str_from_cstr(&str_sub, sub, sizeof(sub));
    printf("Substring \"____\" starts from index %ld\n", my_str_find(&new_str, &str_sub, 0));
    printf("Are new string and sub string equal?: %s\n", my_str_cmp(&new_str, &str_sub)?"false":"true");
    printf("Are new string and Cstring equal?: %s\n", my_str_cmp_cstr(&new_str, "what____")?"false":"true");
    printf("First appearance of char \'_\': %ld\n", my_str_find_c(&new_str, '_', 0));
    int is_a(int symbol) { if (symbol == '.') { return 1; }return 0; }
    printf("Is symbol \'.\' in string?: %ld\n", my_str_find_if(&new_str, is_a));
    my_str_free(&str_sub);

    // Ввід-вивід
    printf("\n// Ввід-вивід\n");
    my_str_t tmp_str1;
    my_str_create(&tmp_str1, 100);
    my_str_t tmp_str2;
    my_str_create(&tmp_str2, 100);
    FILE* tmp_file = tmpfile();
    rewind(tmp_file);
    my_str_write_file(&new_str, tmp_file);
    rewind(tmp_file);
    my_str_read_file(&tmp_str1, tmp_file);
    rewind(tmp_file);
    printf("String read from file: %s\n", my_str_get_cstr(&tmp_str1));
    my_str_read_file_delim(&tmp_str2, tmp_file, '_');
    printf("String read from file up to delimiter: %s\n", my_str_get_cstr(&tmp_str2));
    my_str_free(&new_str);
    my_str_free(&tmp_str1);
    my_str_free(&tmp_str2);
    printf("Done!\n");
}
#endif
