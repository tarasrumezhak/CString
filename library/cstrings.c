#include <stdlib.h>
#include <string.h>
#include <cstrings.h>

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
int my_str_from_cstr(my_str_t* str, const char* original, size_t buf_size){
    size_t original_size;

    // Measure size of the original string ourselves
    const char* idx;
    for (idx = original; *idx; ++idx);
    original_size = idx - original;

    //! [buf_size] менший за її [c-string] розмір -- вважати помилкою, не змінювати стрічку.
    if (original_size > buf_size && buf_size != 0) {
        return -1;
    }

    // They decided to not give us the size of the original string
    if (buf_size == 0) {
        buf_size = original_size;
        printf("(from_cstr): 0 buf_size, now it's %zu\n", buf_size);
    }

    // Satiate buf_size
    if (buf_size > str->capacity_m) {
        printf("(from_cstr): allocate some mem?, now it's %zu\n", buf_size);
        int status = my_str_reserve(str, buf_size);

        if (status == -1) {
            printf("(my_str_from_cstr) allocation failed");
            return -2;
        }
    }

    // Copy passed string
    memcpy(str->data, original, original_size);
    str->size_m = original_size;

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

const char* my_str_get_cstr(my_str_t* str) {
    *(str->data + str->size_m * sizeof(char)) = '\0';

    return str->data;
}

// Enlarge my_str buffer to buf_size+1
int my_str_reserve(my_str_t *str, size_t buf_size) {
    buf_size++;

    if (buf_size <= str->capacity_m) return 0;

    char* allocation = (char*) malloc(buf_size);
    if (allocation == NULL) return -1;

    // Copy old string
    memcpy(allocation, str->data, str->size_m);
    free(str->data);

    // Update old pointer
    str->data = allocation;
    str->capacity_m = buf_size;

    return 0;
}


int my_str_resize(my_str_t* str, size_t new_size, char sym) {
    if (new_size < str->size_m) {
        str->size_m = new_size;
        return 0;
    }

    // new_size > size_m
    int status = my_str_reserve(&str, new_size*2);
    if (status == -1) {
        printf("(resize): can't reserve more space");
        return -1;
    }

    // Setting extra space to "sym"
    for (size_t idx = str->size_m; idx < new_size; idx++) {
        *(str->data + idx) = sym;
    }

    str->size_m = new_size;

    return 0;
}
