#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstrings.h>

//!===========================================================================
//! Створення та знищення стрічки.
//!===========================================================================

//! Створити стрічку із буфером вказаного розміру. Пам'ять виділяється динамічно.
//! Варто виділяти buf_size+1 для спрощення роботи my_str_get_cstr().
//! УВАГА! Ця функція -- аналог конструктора інших мов.
//! Всі решта функцій можуть вважати, що їм не буде передано жодної змінної,
//! до якої не застосували рівно один раз цю функцію.
//! Тобто, до того, як викликати будь-яку іншу функцію, до змінної типу
//! my_str_t слід рівно один раз за час її існування викликати  my_str_create().
//! (З біллю в серці згадуються закони Мерфі -- кожне твердження
//! обов'язково зрозуміють неправильно. Розказавши 20-30 раз, вирішив
//! записати. Тепер очікую збільшення кількості скарг на довжину опису...)
//! Після використання -- викличте my_str_free().
//! Зауважте -- за такого підходу, повторний виклик my_str_create до тієї ж
//! змінної, без виклику my_str_free, вестиме до memory leak.
//! Повертає 0, якщо все ОК, від'ємні числа, якщо сталася помилка.
int my_str_create(my_str_t* str, size_t buf_size) {
    str->capacity_m = buf_size;
    str->size_m = 0;

    str->data = (char*) malloc(buf_size + 1);

    // Failed allocation
    if (str->data == NULL) {
        return -1;
    }

    return 0;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір, buf_size == 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою, не змінювати стрічку.
//! Пам'ять виділяється динамічно. Не слід викликати my_str_create(),
//! більше підійде my_str_resize() або my_str_reserve().
//! Коди завершення:
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
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
    }

    // Satiate buf_size
    if (buf_size > str->capacity_m) {
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

//! Звільняє пам'ять, знищуючи стрічку.
//! Аналог деструктора інших мов.
//! Ремарка: free() нормально працює із NULL.
void my_str_free(my_str_t* str) {
    free(str->data);
}
//!============================================================================
//! Інформація про стрічку
//!============================================================================

//! Повертає розмір стрічки.
//! Для нульового вказівника -- 0.
size_t my_str_size(const my_str_t* str) {
    return str == NULL ? 0 : str->size_m;
}

//! Повертає розмір буфера.
//! Для нульового вказівника -- 0.
size_t my_str_capacity(const my_str_t* str) {
    if (str == NULL) {
        return -1;
    }

    return str->capacity_m;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str) {
    return str->size_m == 0;
}

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки,
//! включаючи переданий нульовий вказівник.
//! Тому, власне, int а не char
int my_str_getc(const my_str_t* str, size_t index) {
    if ((str == NULL) || (index < 0) || index > str->size_m){
        return -1;
    }

    return *(str->data + sizeof(char)*index);
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
int my_str_putc(my_str_t* str, size_t index, char c) {
    if ((str == NULL) || (index < 0) || index > str->size_m){
        return -1;
    }

    *(str->data + sizeof(char)*index) = c;
    return 0;
}

//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Вважатимемо, що як тільки my_str_t змінено, цей вказівник
//! може стати некоректним.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str) {
    *(str->data + str->size_m * sizeof(char)) = '\0';

    return str->data;
}

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================
//! Якщо буфер недостатній -- ці функції збільшують його,
//! викликом my_str_reserve().
//! Розумним є буфер кожного разу збільшувати в 1.8-2 рази.
//! ==========================================================================

//! Додає символ в кінець.
//! Повертає 0, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- помилка виділення додаткової пам'яті.
int my_str_pushback(my_str_t* str, char c) {
    if (str == NULL)
        return -1;

    if (str->size_m >= str->capacity_m) {
        int status = my_str_reserve(str, 2 * str->capacity_m);

        if (status != 0) {
            fprintf(stderr, "(my_str_pushback): failed to reserve more space");
            return -2;
        }
    }

    *(str->data + str->size_m++) = c;

    return 0;
}


//! Викидає символ з кінця.
//! Повертає його, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- якщо стрічка порожня.
int my_str_popback(my_str_t* str) {
    if (!str) return -1;
    if (my_str_empty(str)) return -2;

    // Or do we insert null byte?
    return *(str->data + --str->size_m);
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! (Старий вміст стрічки перед тим звільняє, за потреби).
//! Повертає 0, якщо успішно, різні від'ємні числа для діагностики
//! проблеми некоректних аргументів.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve) {
    int status = reserve ?
        my_str_reserve(to, from->capacity_m) :
        my_str_reserve(to, from->size_m);

    if (status != 0) {
        printf("(my_str_copy): can't reserve memory\n");
    }

    memcpy(to->data, from->data, from->size_m);
    to->size_m = from->size_m;

    return 0;
}
//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
//! Уточнення (чомусь ця ф-ція викликала багато непорозумінь):
//! стрічка продовжує існувати, буфер той самий, того ж розміру, що був,
//! лише містить 0 символів -- єдине, що вона робить, це size_m = 0.
void my_str_clear(my_str_t* str) {
    str->size_m = 0;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert_c(my_str_t* str, char c, size_t pos) {
    if (!str) return -1;

    if (pos > str->size_m) {
        fprintf(stderr, "(my_str_insert_c): out-of-bounds pos\n");
        return -1;
    }

    if (str->size_m >= str->capacity_m) {
        int status = my_str_reserve(str, 2 * str->capacity_m);

        if (status != 0) {
            fprintf(stderr, "(my_str_insert_c): can't reserve more space\n");
            return -2;
        }
    }

    memmove(str->data + pos + 1, str->data + pos, str->size_m - pos);

    *(str->data + pos) = c;
    str->size_m++;

    return 0;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos) {
    if (!from) return -1;
    int status;
    for (int i = 0; i < from->size_m; i++) {
        status = my_str_insert_c(str, *(from->data + i), pos);
        pos++;
    }
    return status;
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos){
    my_str_t new_my_str;
    my_str_create(&new_my_str, 0);
    my_str_from_cstr(&new_my_str, from, 0);
    int status = my_str_insert(str, &new_my_str, pos);
    my_str_free(&new_my_str);
    return status;
}

//! Додати стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_append(my_str_t* str, const my_str_t* from){
    return my_str_insert(str, from, str->size_m);
}

//! Додати С-стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_append_cstr(my_str_t* str, const char* from){
    return my_str_insert_cstr(str, from, str->size_m);
}

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end за межами початкової стрічки -- це не помилка, копіювати всі
//! символи до кінця. beg має бути в її межах -- якщо beg>size, це помилка.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_substr(const my_str_t* from, my_str_t* to, size_t beg, size_t end){
    if (beg > from->size_m){
        return -1;
    }
    if (end > from->size_m){
        end = from->size_m;
    }
    if (to->size_m >= to->capacity_m){
        int status = my_str_reserve(to, end - beg);
        if (status != 0){
            return -2;
        }
    }

    memcpy(to->data + to->size_m, from->data + beg, end - beg);
    to->size_m += end - beg;
    return 0;
}

//! C-string варіант my_str_substr().
//! Вважати, що в цільовій С-стрічці достатньо місц.
int my_str_substr_cstr(const my_str_t* from, char* to, size_t beg, size_t end){
    if (beg > from->size_m){
        return -1;
    }
    if (end > from->size_m){
        end = from->size_m;
    }
    memcpy(to, from->data + beg, end - beg);
    to[end - beg] = '\0';
    return 0;
}

//!===========================================================================
//! Маніпуляції розміром стрічки
//!===========================================================================

//! Збільшує буфер стрічки, із збереженням вмісту,
//! якщо новий розмір більший за попередній,
//! не робить нічого, якщо менший або рівний.
//! (Як показує практика, це -- корисний підхід).
//! Для збільшення виділяє новий буфер, копіює вміст
//! стрічки (size_m символів -- немає сенсу копіювати
//! решту буфера) із старого буфера та звільняє його.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_reserve(my_str_t* str, size_t buf_size) {
    if (!str) return -3;
    if (buf_size <= str->capacity_m) return 0;

    char* allocation = (char*) malloc(buf_size + 1);
    if (!allocation) return -2;

    // Copy old string
    memcpy(allocation, str->data, str->size_m);
    free(str->data);

    // Update old pointer
    str->data = allocation;
    str->capacity_m = buf_size;

    return 0;
}

//! Робить буфер розміром, рівний необхідному:
//! так, щоб capacity_m == size_t. Єдиний "офіційний"
//! спосіб зменшити фактичний розмір буфера.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_shrink_to_fit(my_str_t* str) {
    if (!str) return -3;

    char* allocation = (char*) malloc(str->size_m + 1);
    if (!allocation) return -2;

    // Copy old string
    memcpy(allocation, str->data, str->size_m);
    free(str->data);

    // Update old pointer
    str->data = allocation;
    str->capacity_m = str->size_m;

    return 0;
}

//! Якщо new_size менший за поточний розмір -- просто
//! відкидає зайві символи (зменшуючи size_m). Якщо
//! більший -- збільшує фактичний розмір стрічки,
//! встановлюючи нові символи рівними sym.
//! За потреби, збільшує буфер.
//! Сподіваюся, різниця між розміром буфера та фактичним
//! розміром стрічки зрозуміла?
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_resize(my_str_t* str, size_t new_size, char sym) {
    if (new_size < str->size_m) {
        str->size_m = new_size;
        return 0;
    }

    // new_size > size_m
    int status = my_str_reserve(str, 2 * new_size);
    if (status != 0) {
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

//!===========================================================================
//! Функції пошуку та порівняння
//!===========================================================================

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from) {
//    printf("In function");
    for (size_t i = from; i < str->size_m; ++i) {
//        printf("in for %zu", i);
        if (my_str_getc(str, i) == my_str_getc(tofind, 0)) {
//            printf("in if %i   %i", my_str_getc(str, i), my_str_getc(tofind, 0));
            size_t j = 0;
            while (my_str_getc(str, i + j) == my_str_getc(tofind, j)) {
//                printf("In while %i   %i\n", my_str_getc(str, i + j), my_str_getc(tofind, j));
//                printf("j and size %zu  %zu\n", j, tofind->size_m - 1);
                if (j == tofind->size_m - 1) {
                    return i;
                }
                j++;
            }
        }
    }
    return (size_t)(-1);
}


//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(const my_str_t* str1, const my_str_t* str2){
    if (str1->size_m == str2->size_m) {
        for (size_t i = 0; i < str1->size_m; ++i) {
            if (my_str_getc(str1, i) < my_str_getc(str2, i)) {
                return -1;
            } else if (my_str_getc(str1, i) > my_str_getc(str2, i)) {
                return 1;
            }
        }
        return 0;
    }
    if (str1->size_m < str2->size_m) { return -1;}
    return 1;
}

//! Порівняти стрічку із С-стрічкою, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
size_t len_const_char(const char* cstr) {
    size_t size = 0;
    while (cstr[size] != '\0') size++;
    return size;
}

int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2){
    if (str1->size_m == len_const_char(cstr2)) {
        for (size_t i = 0; i < str1->size_m; ++i) {
            if (my_str_getc(str1, i) < cstr2[i]) {
                return -1;
            } else if (my_str_getc(str1, i) > cstr2[i]) {
                return 1;
            }
        }
        return 0;
    }
    if (str1->size_m < len_const_char(cstr2)) { return -1;}
    return 1;
}

//! Знайти перший символ в стрічці, повернути його номер
//! або (size_t)(-1), якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from) {
    if (from > str->size_m) {
        return (size_t)(-1);
    }
    for (size_t i = from; i < str->size_m; ++i) {
        if (my_str_getc(str, i) == tofind) {
            return i;
        }
    }
    return (size_t)(-1);
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або (size_t)(-1), якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(int)) {
    for (size_t i = 0; i < str->size_m; ++i) {
        if (predicat(my_str_getc(str, i)) == 1) {
            return i;
        }
    }
    return (size_t)(-1);
}

//!===========================================================================
//! Ввід-вивід
//!===========================================================================

//! Прочитати стрічку із файлу. Читає цілий файл.
//! Не давайте читанню вийти за межі буфера! За потреби --
//! збільшуйте буфер.
//! Рекомендую скористатися fgets().
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file(my_str_t* str, FILE* file) {
    if (str == NULL || file == NULL)
        return -1;

    // buffering size, it's purposefully that small
    size_t reading_gap_size = 4;
    int idx = -reading_gap_size+1;

    do {
        idx += reading_gap_size - 1;

        if (str->size_m + reading_gap_size >= str->capacity_m) {
            int status = str->capacity_m < reading_gap_size ?
                my_str_reserve(str, 2 * reading_gap_size) :
                my_str_reserve(str, 2 * str->capacity_m);

            if (status != 0) {
                fprintf(stderr, "(my_str_read_file): can't reserve more space\n");
                return -1;
            }
        }
    } while (fgets(str->data + idx, reading_gap_size, file));

    // FIXME That's a very crude update of the actual size
    str->size_m = my_str_length(str);

    return 0;
}

//! Аналог my_str_read_file, із stdin.
int my_str_read(my_str_t* str) {
    return my_str_read_file(str, stdin) ? -1 : 0;
}

//! Записати стрічку в файл:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write_file(const my_str_t* str, FILE* file) {
    if (str->size_m == 0) return 0;

    // Very lazy :'(
    fputs(my_str_get_cstr(((my_str_t*) str)), file);

    return 0;
}

//! Записати стрічку на консоль:
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_write(const my_str_t* str) {
    return my_str_write_file(str, stdout) ? -1 : 0;
}

//! На відміну від my_str_read_file(), яка читає до кінця файлу,
//! читає по вказаний delimiter, за потреби
//! збільшує стрічку.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter) {
    if (str == NULL || file == NULL)
        return -1;

    int buf;
    while((buf = fgetc(file)) != EOF) {
        if (buf == delimiter)
            break;

        int status = my_str_pushback(str, buf);

        if (status != 0)
            return status;
    }

    return 0;
}

size_t my_str_length(my_str_t* str) {
    const char* idx;
    for (idx = str->data; *idx; ++idx);
    return idx - str->data;
}
