#include <stdlib.h>
#include <string.h>
#include <library.h>

#ifdef __WIN32
#include <mem.h>
#endif

// Create my_str given starting size
int my_str_create(my_str_t* str, size_t buf_size) {
    str->capacity_m = buf_size + 1;
    str->size_m = 0;

    str->data = (char*) malloc(str->capacity_m);

    // Failed allocation
    if (str->data == NULL) {
        return -1;
    }

    return 0;
}

void my_str_free(my_str_t* str){
    free(str->data);
}

// Створити стрічку із буфером вказаного розміру із переданої С-стрічки
// buf_size is actually a capacity
int my_str_from_cstr(my_str_t* str, const char* original, size_t original_size){
    size_t real_original_size;

    // Measure size of the original string ourselves
    const char* idx;
    for (idx = original; *idx; ++idx);
    real_original_size = idx - original;

    //! [buf_size] менший за її [c-string] розмір -- вважати помилкою, не змінювати стрічку.
    if (real_original_size > original_size && original_size != 0) {
        return -1;
    }

    // They decided to not give us the size of the original string
    if (original_size == 0) {
        original_size = real_original_size;
    }

    // Not enough memory
    if (original_size > str->capacity_m) {
        // TODO Realloc
        return -2;
    }

    memcpy(str->data, original, original_size);

    str->size_m = original_size;
    str->capacity_m = original_size * 2 + 1;

    return 0;
}


// Returns length of my_str
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

//const char* my_str_get_cstr(my_str_t* str){
//    *(str->data + sizeof(char)*(str->size_m + 1)) = '\0';
//    return str->data;
//}

// Enlarge my_str
int my_str_reserve(my_str_t *str, size_t buf_size){
    if (buf_size < str->capacity_m) return 0;

    char* temp = (char*) malloc(buf_size * 2);

    if (temp == NULL) return -1;

    memcpy(temp, str, buf_size);
    free(str->data);

    str->data = temp;
    str->capacity_m = buf_size;

    return 0;
}
