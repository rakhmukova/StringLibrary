#include "library.h"
#include <unity.h>

void setUp()
{

}

void tearDown()
{

}

void test_strlength_string_type()
{
    String string = init_string("fascinating");

    size_t result = strlength('s', string);
    TEST_ASSERT_EQUAL(11, result);

    deinit_string(&string);
}

void test_strlength_string_ptr_type()
{
    String *string_ptr = (String *)calloc(1, sizeof(String));
    *string_ptr = init_string("loop");

    size_t result = strlength('p', string_ptr);
    TEST_ASSERT_EQUAL(4, result);

    deinit_string(string_ptr);
    free(string_ptr);
}

void test_strlength_char_array_type()
{
    char *string = "";

    size_t result = strlength('c', string);
    TEST_ASSERT_EQUAL(0, result);
}

void test_strcompare_lengths_differ()
{
    char *f_string = "Polar";
    String s_string = init_string("bear");

    int result = strcompare('c', 's', f_string, s_string);
    TEST_ASSERT_EQUAL('r', result);

    deinit_string(&s_string);
}

void test_strcompare_same_lengths_chars_differ()
{
    String *f_string = (String *)calloc(1, sizeof(String));
    *f_string = init_string("wise");
    String s_string = init_string("wide");

    int result = strcompare('p', 's', f_string, s_string);
    TEST_ASSERT_EQUAL('s' - 'd', result);

    deinit_string(f_string);
    deinit_string(&s_string);
    free(f_string);
}

void test_strcompare_strings_coincide()
{
    char *f_string = "Rolling red wagons";
    String *s_string = (String *)calloc(1, sizeof(String));
    *s_string = init_string(f_string);

    int result = strcompare('c', 'p', f_string, s_string);
    TEST_ASSERT_EQUAL(0, result);

    deinit_string(s_string);
    free(s_string);
}

void test_substr()
{
    String *string_ptr = (String *)calloc(1, sizeof(String));
    *string_ptr = init_string("prefix_root_suffix");

    String substring = substr(0, 6, 'p', string_ptr);
    TEST_ASSERT_EQUAL_STRING("prefix", substring.str);
    deinit_string(&substring);

    substring = substr(7, 11, 'p', string_ptr);
    TEST_ASSERT_EQUAL_STRING("root", substring.str);

    deinit_string(string_ptr);
    deinit_string(&substring);
    free(string_ptr);
}

void test_concat()
{
    String string1 = init_string("How ");
    char *string2 = "are ";
    String *string3 = (String *)calloc(1, sizeof(String));
    *string3 = init_string("you");
    char *string4 = "? ";
    String *string5 = (String *)calloc(1, sizeof(String));
    *string5 = init_string(" okay");

    String result_string = concat("s c p c c p p c", string1, string2, string3, string4,
                                  string2, string3, string5, string4);
    TEST_ASSERT_EQUAL_STRING("How are you? are you okay? ", result_string.str);

    deinit_string(&result_string);
    deinit_string(&string1);
    deinit_string(string3);
    deinit_string(string5);
    free(string3);
    free(string5);
}

void test_strsplit_char_many_occurences()
{
    String **tokens = (String **)calloc(1, sizeof(String *));
    char *string = "What     a wonderful  day!";

    int tokens_num = strsplit(' ', tokens, 'c', string);
    TEST_ASSERT_EQUAL(4, tokens_num);
    TEST_ASSERT_EQUAL_STRING("What", (*tokens)[0].str);
    TEST_ASSERT_EQUAL_STRING("a", (*tokens)[1].str);
    TEST_ASSERT_EQUAL_STRING("wonderful", (*tokens)[2].str);
    TEST_ASSERT_EQUAL_STRING("day!", (*tokens)[3].str);

    for (size_t i = 0; i < tokens_num; ++i){
        deinit_string(&(*tokens)[i]);
    }
    free(*tokens);
    free(tokens);
}

void test_strsplit_no_tokens()
{
    String **tokens = (String **)calloc(1, sizeof(String *));
    String string = init_string("rrrrrrrr");

    int tokens_num = strsplit('r', tokens, 's', string);
    TEST_ASSERT_EQUAL(0, tokens_num);

    deinit_string(&string);
    for (size_t i = 0; i < tokens_num; ++i){
        deinit_string(tokens[i]);
    }
    free(tokens);
}

void test_first_char_occur()
{
    String *string_ptr = (String *)calloc(1, sizeof(String));
    *string_ptr = init_string("How can a clam cram in a clean cream can?");

    String substring = first_char_occur('c', 'p', string_ptr);
    TEST_ASSERT_EQUAL_STRING("can a clam cram in a clean cream can?", substring.str);
    deinit_string(&substring);

    substring = first_char_occur('i', 'p', string_ptr);
    TEST_ASSERT_EQUAL_STRING("in a clean cream can?", substring.str);

    deinit_string(&substring);
    deinit_string(string_ptr);
    free(string_ptr);
}

void test_last_char_occur()
{
    String string = init_string("Sheena leads, Sheila needs");

    String substring = last_char_occur('s', 's', string);
    TEST_ASSERT_EQUAL_STRING("s", substring.str);
    deinit_string(&substring);

    substring = last_char_occur('S', 's', string);
    TEST_ASSERT_EQUAL_STRING("Sheila needs", substring.str);

    deinit_string(&substring);
    deinit_string(&string);
}