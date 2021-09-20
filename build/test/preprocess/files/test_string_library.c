#include "/home/just_user/.local/share/gem/ruby/2.7.0/gems/ceedling-0.31.0/vendor/unity/src/unity.h"
#include "src/library.h"


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

    UnityAssertEqualNumber((UNITY_INT)((11)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT);



    deinit_string(&string);

}



void test_strlength_string_ptr_type()

{

    String *string_ptr = (String *)calloc(1, sizeof(String));

    *string_ptr = init_string("loop");



    size_t result = strlength('p', string_ptr);

    UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);



    deinit_string(string_ptr);

    free(string_ptr);

}



void test_strlength_char_array_type()

{

    char *string = "";



    size_t result = strlength('c', string);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

}



void test_strcompare_lengths_differ()

{

    char *f_string = "Polar";

    String s_string = init_string("bear");



    int result = strcompare('c', 's', f_string, s_string);

    UnityAssertEqualNumber((UNITY_INT)(('r')), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);



    deinit_string(&s_string);

}



void test_strcompare_same_lengths_chars_differ()

{

    String *f_string = (String *)calloc(1, sizeof(String));

    *f_string = init_string("wise");

    String s_string = init_string("wide");



    int result = strcompare('p', 's', f_string, s_string);

    UnityAssertEqualNumber((UNITY_INT)(('s' - 'd')), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);



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

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);



    deinit_string(s_string);

    free(s_string);

}



void test_substr()

{

    String *string_ptr = (String *)calloc(1, sizeof(String));

    *string_ptr = init_string("prefix_root_suffix");



    String substring = substr(0, 6, 'p', string_ptr);

    UnityAssertEqualString((const char*)(("prefix")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(88));

    deinit_string(&substring);



    substring = substr(7, 11, 'p', string_ptr);

    UnityAssertEqualString((const char*)(("root")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(92));



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

    UnityAssertEqualString((const char*)(("How are you? are you okay? ")), (const char*)((result_string.str)), (

   ((void *)0)

   ), (UNITY_UINT)(111));



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

    UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((tokens_num)), (

   ((void *)0)

   ), (UNITY_UINT)(127), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("What")), (const char*)(((*tokens)[0].str)), (

   ((void *)0)

   ), (UNITY_UINT)(128));

    UnityAssertEqualString((const char*)(("a")), (const char*)(((*tokens)[1].str)), (

   ((void *)0)

   ), (UNITY_UINT)(129));

    UnityAssertEqualString((const char*)(("wonderful")), (const char*)(((*tokens)[2].str)), (

   ((void *)0)

   ), (UNITY_UINT)(130));

    UnityAssertEqualString((const char*)(("day!")), (const char*)(((*tokens)[3].str)), (

   ((void *)0)

   ), (UNITY_UINT)(131));



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

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((tokens_num)), (

   ((void *)0)

   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_INT);



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

    UnityAssertEqualString((const char*)(("can a clam cram in a clean cream can?")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(161));

    deinit_string(&substring);



    substring = first_char_occur('i', 'p', string_ptr);

    UnityAssertEqualString((const char*)(("in a clean cream can?")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(165));



    deinit_string(&substring);

    deinit_string(string_ptr);

    free(string_ptr);

}



void test_last_char_occur()

{

    String string = init_string("Sheena leads, Sheila needs");



    String substring = last_char_occur('s', 's', string);

    UnityAssertEqualString((const char*)(("s")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(177));

    deinit_string(&substring);



    substring = last_char_occur('S', 's', string);

    UnityAssertEqualString((const char*)(("Sheila needs")), (const char*)((substring.str)), (

   ((void *)0)

   ), (UNITY_UINT)(181));



    deinit_string(&substring);

    deinit_string(&string);

}
