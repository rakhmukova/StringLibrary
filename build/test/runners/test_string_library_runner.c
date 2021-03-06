/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_strlength_string_type();
extern void test_strlength_string_ptr_type();
extern void test_strlength_char_array_type();
extern void test_strcompare_lengths_differ();
extern void test_strcompare_same_lengths_chars_differ();
extern void test_strcompare_strings_coincide();
extern void test_substr();
extern void test_concat();
extern void test_strsplit_char_many_occurences();
extern void test_strsplit_no_tokens();
extern void test_first_char_occur();
extern void test_last_char_occur();


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_string_library.c");
  run_test(test_strlength_string_type, "test_strlength_string_type", 14);
  run_test(test_strlength_string_ptr_type, "test_strlength_string_ptr_type", 24);
  run_test(test_strlength_char_array_type, "test_strlength_char_array_type", 36);
  run_test(test_strcompare_lengths_differ, "test_strcompare_lengths_differ", 44);
  run_test(test_strcompare_same_lengths_chars_differ, "test_strcompare_same_lengths_chars_differ", 55);
  run_test(test_strcompare_strings_coincide, "test_strcompare_strings_coincide", 69);
  run_test(test_substr, "test_substr", 82);
  run_test(test_concat, "test_concat", 99);
  run_test(test_strsplit_char_many_occurences, "test_strsplit_char_many_occurences", 121);
  run_test(test_strsplit_no_tokens, "test_strsplit_no_tokens", 140);
  run_test(test_first_char_occur, "test_first_char_occur", 155);
  run_test(test_last_char_occur, "test_last_char_occur", 172);

  return UnityEnd();
}
