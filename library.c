#include <stdlib.h>
#include <mem.h>

typedef struct
{
    size_t capacity_m; // Розмір блока
    size_t size_m;	   // Фактичний розмір стрічки
    char*  data;	   // Вказівник на блок пам'яті
} my_str_t;

int my_str_create(my_str_t *str, size_t buf_size) {
    str ->capacity_m = buf_size + 1;
    str ->size_m = 0;
    str->data = (char *) calloc(str->capacity_m, sizeof(char));
    if (str->data == NULL) {
        return -1;
    }
    return 0;
}


void my_str_free(my_str_t* str){
    free(str ->data);
}


int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    if (buf_size == 0) {
        str ->capacity_m = buf_size + 1;
    }
    else if (buf_size < sizeof(str)){
        return -1;
    }
    size_t real_cstring_size = 0;
    while (*(cstr + real_cstring_size) != '\0') {
        real_cstring_size += 1;
    }
    memcpy(str->data, cstr, real_cstring_size);
    str->size_m = real_cstring_size;
    str->capacity_m = real_cstring_size * 2 + 1;
}


size_t my_str_size(const my_str_t* str){
    if (str == NULL) {
        return -1;
    }
//    return sizeof(str) / sizeof(char);
    return str->size_m;
}


size_t my_str_capacity(const my_str_t* str){
    if (str == NULL) {
        return -1;
    }
    return str->capacity_m;
}

int my_str_empty(const my_str_t* str){
    if (str->size_m > 0){
        return 1;
    }
    return 0;
}

int my_str_getc(const my_str_t* str, size_t index){
    if ((str == NULL) || (index < 0) || index > str->size_m){
        return -1;
    }
    return *(str->data + sizeof(char)*index);
}

int my_str_putc(my_str_t* str, size_t index, char c){
    if ((str == NULL) || (index < 0) || index > str->size_m){
        return -1;
    }
    *(str->data + sizeof(char)*index) = c;
    return 0;
}
