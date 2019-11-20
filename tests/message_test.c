
#include "test.h"

// Represents the size of the Message struct (10/28/2019)
#define PREV_MSG_SIZE_BYTES     32

void test_message_alloc() {
    Message * msg = message_alloc();
    
    // Check if it's not NULL
    TEST_ASSERT_NOT_NULL(msg);
    
    // Check if allocated message size has increased.
    TEST_ASSERT_TRUE(sizeof(*msg) == PREV_MSG_SIZE_BYTES);
    
    // Check if the variables are initialized correctly.
    TEST_ASSERT_NULL(msg->data);
    TEST_ASSERT_NULL(msg->data_type);
    TEST_ASSERT_TRUE(msg->size == 0);
    TEST_ASSERT_TRUE(msg->time_stamp == -1);
    
    message_free(msg);
}

void test_message_reset() {
    
    Message * msg = message_alloc();
    
    // TODO
    
    message_free(msg);
}

void test_message_free() {
    int ret = 0;
    Message * msg = NULL;
    
    // Test if error message output
    ret = message_free(msg);
    TEST_ASSERT_TRUE(ERROR_TYPENULL == ret);
    
    // Allocate the message
    msg = message_alloc();
    
    // Check if function returns correct result
    ret = message_free(msg);
    TEST_ASSERT_TRUE(ret == 0);
}

void test_message_set_data_works() {
    
    int ret;
    Message * msg = message_alloc();
    
    char * test_str = strdup("test data string");
    
    ret = message_set_data(msg,test_str,strlen(test_str),"data type test");
    
    TEST_ASSERT_TRUE(ret == 0);
    TEST_ASSERT_NOT_NULL(msg->data);
    TEST_ASSERT_EQUAL_STRING (test_str, msg->data);
    TEST_ASSERT_EQUAL_STRING("data type test",msg->data_type);
    
    free(test_str);
    
    message_free(msg);
    
}

void test_message_set_data_null_msg() {
    
    int ret = 0;
    Message * msg = NULL;
    char * test_str = strdup("test data string");
    
    ret = message_set_data(msg,test_str,strlen(test_str),NULL);
    TEST_ASSERT_TRUE(ret == ERROR_TYPENULL);
    
    free(test_str);
    
    message_free(msg);
}

void test_message_set_data_null_data() {
    int ret;
    Message * msg = message_alloc();
    char * test_str = NULL;
    
    ret = message_set_data(msg,test_str,0,NULL);
    TEST_ASSERT_TRUE(ret == ERROR_TYPEDATA);
    
    message_free(msg);
}

void test_message_set_data_size_zero() {
    int ret;
    Message * msg = message_alloc();
    char * test_str = strdup("test data string");
    
    ret = message_set_data(msg,test_str,0,NULL);
    TEST_ASSERT_TRUE(ret == ERROR_SIZE);
    
    free(test_str);
    
    message_free(msg);
}

void test_message_set_data_diff_data() {
    int ret;
    Message * msg = message_alloc();
    
    char * test_str = strdup("test data string");
    // Sets the initial data
    ret = message_set_data(msg,test_str,strlen(test_str),"data type test");
    // Checks the inital data is correct
    TEST_ASSERT_TRUE(ret == 0);
    TEST_ASSERT_NOT_NULL(msg->data);
    TEST_ASSERT_EQUAL_STRING (test_str, msg->data);
    TEST_ASSERT_EQUAL_STRING("data type test",msg->data_type);
    
    char * test_str_2 = strdup("different test data string");
    
    ret = message_set_data(msg,test_str_2,strlen(test_str_2),"data type test");
    
    TEST_ASSERT_TRUE(ret == 0);
    TEST_ASSERT_NOT_NULL(msg->data);
    TEST_ASSERT_EQUAL_STRING (test_str_2, msg->data);
    
    free(test_str);
    free(test_str_2);
    message_free(msg);
}

void test_message_set_timestamp() {
    int ret;
    //TEST_FAIL_MESSAGE("Function and test function not yet implemented.");
    Message * msg = message_alloc();
    ret = message_set_timestamp(msg,100122);
    TEST_ASSERT_TRUE(100122 == msg->time_stamp);
    TEST_ASSERT_TRUE(ret == 0);
}

void test_unit_message_file() {
    RUN_TEST(test_message_alloc);
    RUN_TEST(test_message_reset);
    RUN_TEST(test_message_free);
    RUN_TEST(test_message_set_data_works);
    RUN_TEST(test_message_set_data_null_msg);
    RUN_TEST(test_message_set_data_null_data);
    RUN_TEST(test_message_set_data_size_zero);
    RUN_TEST(test_message_set_data_diff_data);
    RUN_TEST(test_message_set_timestamp);
}
