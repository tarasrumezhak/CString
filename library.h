#include <stddef.h>
#ifndef CSTRING_LIBRARY_H
#define CSTRING_LIBRARY_H

typedef struct {
    // Total memory allocated
    size_t capacity_m; // Розмір блока
    // Useful space occupied
    size_t size_m;	   // Фактичний розмір стрічки

    char*  data;	   // Вказівник на блок пам'яті
} my_str_t;


int my_str_create(my_str_t *str, size_t buf_size);

void my_str_free(my_str_t* str);

int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size);

size_t my_str_size(const my_str_t* str);

size_t my_str_capacity(const my_str_t* str);

int my_str_empty(const my_str_t* str);

int my_str_getc(const my_str_t* str, size_t index);

int my_str_putc(my_str_t* str, size_t index, char c);

#endif //CSTRING_LIBRARY_H
