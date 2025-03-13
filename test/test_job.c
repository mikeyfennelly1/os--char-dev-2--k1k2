#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/job.h"
#include <stdio.h>
#include "./test_dynamic_job_buffer.h"

#define TEST_KEY "test_key"
#define TEST_VALUE "test_value"
#define TEST_JOB_TITLE "test_job_title"

#define TEST_TEXT "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

void test_init_job_buffer(void)
{
    DynamicJobBuffer* b = init_job_buffer();
    CU_ASSERT_PTR_NOT_NULL(b);
    CU_ASSERT_EQUAL(b->capacity, INITIAL_CAPACITY);
    CU_ASSERT_EQUAL(b->size, 0);
    CU_ASSERT_EQUAL(b->data[0], '\0');
}

void test_resize_job_buffer(void)
{
    DynamicJobBuffer* b = init_job_buffer();
    CU_ASSERT_EQUAL(b->capacity, 16);
    resize_job_buffer(b, 200);
    CU_ASSERT_EQUAL(b->capacity, 200);
}

void test_append_to_job_buffer(void)
{
    DynamicJobBuffer* b = init_job_buffer();
    append_to_job_buffer(b, TEST_TEXT);
    CU_ASSERT_STRING_EQUAL(b->data, TEST_TEXT);
}

key_value_pair return_kvp(void)
{
  key_value_pair kvp;
  kvp.key = TEST_KEY;
  kvp.value = TEST_VALUE;
  return kvp;
}

void test_return_kvp(void)
{
  key_value_pair kvp = return_kvp();
  CU_ASSERT_EQUAL(TEST_KEY, kvp.key);
  CU_ASSERT_EQUAL(TEST_VALUE, kvp.value);
}

void test_step_init(void)
{
  Step* step = step_init(&return_kvp);
  CU_ASSERT_EQUAL(TEST_KEY, step->get_kvp().key);
  CU_ASSERT_EQUAL(TEST_VALUE, step->get_kvp().value);
}

void test_job_init(void)
{
  Job* my_job = job_init(TEST_JOB_TITLE, &return_kvp);
  CU_ASSERT_EQUAL(TEST_JOB_TITLE, my_job->job_title);
  CU_ASSERT_EQUAL(TEST_KEY, my_job->head->get_kvp().key);
  CU_ASSERT_EQUAL(TEST_VALUE, my_job->head->get_kvp().value);
}

/**
 * Test if job_init returns a job with the pointer
 * job->head is NULL
 */
void test_if_job_head_is_not_null(void)
{
    Job* my_job = job_init(TEST_JOB_TITLE, &return_kvp);
    CU_ASSERT_PTR_NOT_NULL(my_job->head);
}

/**
 * Tests if after job_init, the job->head->get_kvp
 * pointer is not null.
 */
void test_job_head_get_kvp_is_non_null_pointer(void)
{
    Job* my_job = job_init(TEST_JOB_TITLE, &return_kvp);
    CU_ASSERT_PTR_NOT_NULL(my_job->head->get_kvp);
}

void test_append_step_to_job(void)
{
    Job* my_job = job_init(TEST_JOB_TITLE, &return_kvp);
    CU_ASSERT_EQUAL(TEST_JOB_TITLE, my_job->job_title);

    for (int i = 0; i<3; i++)
    {
      // append 3 steps to the job.
      append_step_to_job(my_job, &return_kvp);
    }

    // walk the steps in the job. At each step
    // assert all values are as expected
    Step cur = (*my_job->head);
    while (cur.next)
    {
      CU_ASSERT_EQUAL(TEST_KEY, cur.get_kvp().key);
      CU_ASSERT_EQUAL(TEST_VALUE, cur.get_kvp().value);
      cur = (*cur.next);
    }
}

void test_run_job_json()
{
    Job* my_job = job_init(TEST_JOB_TITLE, &return_kvp);

    char* expected = "{test_key:test_value}";
    char* actual = run_job(my_job);

    printf("\n\n\n%s\n\n\n", actual);

    CU_ASSERT_EQUAL(expected, actual);
}

int main(void)
{
    // init CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }
    
    // create test suite
    CU_pSuite suite = CU_add_suite("Job", NULL, NULL);
    if (!suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (!CU_add_test(suite, "test_init_job_buffer", test_init_job_buffer))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_resize_job_buffer", test_resize_job_buffer))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_append_to_job_buffer", test_append_to_job_buffer))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_return_kvp", test_return_kvp))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_step_init", test_step_init))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_job_init", test_job_init))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_append_step_to_job", test_append_step_to_job))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_if_job_head_is_not_null", test_if_job_head_is_not_null))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_job_head_get_kvp_is_non_null_pointer", test_job_head_get_kvp_is_non_null_pointer))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}