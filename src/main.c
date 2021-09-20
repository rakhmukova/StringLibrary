#include <stdio.h>
#include "library.h"

String *string_ptr;

int main()
{
    string_ptr = (struct String *)calloc(1, sizeof (struct String));
    *string_ptr = init_string("Hi.");
    printf("%s \n", string_ptr->str);
    deinit_string(string_ptr);
    free(string_ptr);
    return 0;
}