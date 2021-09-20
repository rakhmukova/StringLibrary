#ifndef LIBRARY_H
#define LIBRARY_H

#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct String{
    size_t size;
    char *str;
} String;

String init_string(const char *str);
int deinit_string(String *string);
size_t strlength(int type, ...);
String concat(const char *format, ...);
String substr(size_t start, size_t end, int type, ...);
String first_char_occur(int c, int type, ...);
String last_char_occur(int c, int type, ...);
int strcompare(int f_type, int s_type, ...);
int strsplit(int c, String **tokens, int type, ...);

#endif
