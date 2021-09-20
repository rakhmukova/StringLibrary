#include "library.h"

enum StringTypes {
    Str = 's',
    Str_ptr = 'p',
    Char_array = 'c'
};

static size_t char_ar_size(const char *str)
{
    size_t pos = 0;
    while (str[pos] != '\0')
    {
        ++pos;
    }
    return pos;
}

String init_string(const char *str)
{
    String result = {char_ar_size(str), 0};
    result.str = (char *)calloc(result.size + 1, sizeof (char));
    for (size_t i = 0; i < result.size; ++i){
        result.str[i] = str[i];
    }
    return result;
}

int deinit_string(String *string)
{
    if (!string)
        return -1;

    free(string->str);
    string->str = NULL;
    string->size = 0;
    return 0;
}

String get_string(enum StringTypes type, va_list *list_ptr)
{
    String string = {0, 0};
    char *str = NULL;
    switch(type){
        case Str:
            string = va_arg(*list_ptr, String);
            break;
        case Str_ptr:
            string = *va_arg(*list_ptr, String *);
            break;
        case Char_array:
            str = va_arg(*list_ptr, char *);
            string.size = char_ar_size(str);
            string.str = str;
    }
    return string;
}

size_t strlength(int type, ...)
{
    va_list args;
    va_start(args, type);
    String string = get_string(type, &args);
    va_end(args);

    return string.size;
}

static String substring(size_t start, size_t end, String initial_str)
{
    String result_str = {0, 0};
    if (start < 0 || end > initial_str.size || start >= end)
        return result_str;

    size_t new_size = end - start;
    result_str.str = (char *)calloc(new_size + 1, sizeof (char));
    for (size_t i = 0; i < new_size; ++i){
        result_str.str[i] = initial_str.str[i + start];
    }
    result_str.size = new_size;
    return result_str;
}

String substr(size_t start, size_t end, int type, ...)
{
    va_list args;
    va_start(args, type);
    String initial_str = get_string(type, &args);
    va_end(args);
    return substring(start, end, initial_str);
}

static int resize_string(String *string_ptr, size_t new_size)
{
    if (new_size == string_ptr->size)
        return 0;

    if (new_size < 0)
        return - 1;

    string_ptr->size = new_size;
    char *new_ptr = (char *)realloc(string_ptr->str, (new_size + 1) * sizeof (char));
    if (!new_ptr)
        return -1;

    string_ptr->str = new_ptr;
    (string_ptr->str)[new_size] = 0;
    return 0;
}

#define DEF_SIZE 50

String concat(const char *format, ...)
{
    int resize_success = 0;
    String result_string = {0, 0};
    if ((resize_success = resize_string(&result_string, DEF_SIZE)) == -1)
        return result_string;

    size_t cur_size = 0;
    size_t format_pos = 0;
    size_t result_size = 0;
    String cur_string = {0, 0};

    va_list args;
    va_start(args, format);
    while (format[format_pos] != '\0') {
        cur_string = get_string(format[format_pos], &args);
        cur_size = cur_string.size;
        if (result_size + cur_size > result_string.size){
            if ((resize_success = resize_string(&result_string, result_size + cur_size)) == -1)
                break;
        }
        for (size_t i = 0; i < cur_size; ++i) {
            result_string.str[result_size + i] = cur_string.str[i];
        }
        result_size += cur_size;
        while(format[++format_pos] == ' ');
    }
    va_end(args);

    if ((resize_success = resize_string(&result_string, result_size)) == -1){
        result_string.size = 0;
        result_string.str = NULL;
    }
    return result_string;
}

int strcompare(int f_type, int s_type, ...)
{
    String strings[2] = {{0, NULL}, {0, NULL}};

    va_list args;
    va_start(args, s_type);
    strings[0] = get_string(f_type, &args);
    strings[1] = get_string(s_type, &args);
    va_end(args);

    int result = 0;

    size_t f_size = strings[0].size;
    size_t s_size = strings[1].size;

    if (f_size < s_size)
        result = strings[1].str[f_size];
    else if (f_size > s_size)
        result = strings[0].str[s_size];
    else{
        size_t pos = 0;
        while(strings[0].str[pos] == strings[1].str[pos]){
            if (++pos == f_size)
                break;
        }
        if (pos != f_size)
            result = strings[0].str[pos] - strings[1].str[pos];
    }
    return result;
}

static long int find_first_occur(int c, char *substr, size_t left_size)
{
    size_t pos = 0;
    while(substr[pos] != c){
        if (++pos == left_size)
            break;
    }

    if (pos == left_size)
        return -1;

    return pos;
}

static long int find_last_occur(int c, char *substr, size_t left_size)
{
    size_t pos = left_size;
    while(substr[pos] != c){
        if (--pos == -1)
            break;
    }
    return pos;
}

String first_char_occur(int c, int type, ...)
{
    va_list args;
    va_start(args, type);
    String initial_string = get_string(type, &args);
    va_end(args);

    long int start_pos = find_first_occur(c, initial_string.str, initial_string.size);
    return substring(start_pos, initial_string.size, initial_string);
}

String last_char_occur(int c, int type, ...)
{
    va_list args;
    va_start(args, type);
    String initial_string = get_string(type, &args);
    va_end(args);

    long int start_pos = find_last_occur(c, initial_string.str, initial_string.size);
    return substring(start_pos, initial_string.size, initial_string);
}

int strsplit(int c, String **tokens, int type, ...)
{
    va_list args;
    va_start(args, type);
    String initial_str = get_string(type, &args);
    va_end(args);

    if (initial_str.size == 0)
        return -1;

    free(*tokens);
    *tokens = (String *)calloc(initial_str.size / 2 + 1, sizeof (String));

    long int cur_token_pos = 0;
    long int cur_f_not_c = 0;
    long int cur_next_c = 0;
    size_t str_size = initial_str.size;
    char *str = initial_str.str;
    while(cur_f_not_c < str_size){
        while(str[cur_f_not_c] == c){
            if (++cur_f_not_c == str_size)
                break;
        }

        if (cur_f_not_c == str_size)
            break;

        cur_next_c = cur_f_not_c + find_first_occur(c, &(str[cur_f_not_c]), str_size - cur_f_not_c);
        if (cur_next_c < cur_f_not_c)
            cur_next_c = str_size;
        (*tokens)[cur_token_pos++] = substring(cur_f_not_c, cur_next_c, initial_str);
        cur_f_not_c = cur_next_c;
    }
    if (cur_token_pos){
        String *new_ptr = (String *)realloc(*tokens, cur_token_pos * sizeof (String));
        if (!new_ptr)
	        return -1;
        *tokens = new_ptr;
    }
    else{
        free(*tokens);
        *tokens = NULL;
    }
    return cur_token_pos;
}
