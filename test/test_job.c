#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/job.h"

#define TEST_KEY "test_key"
#define TEST_VALUE "test_value"
#define TEST_JOB_TITLE "test_job_title"

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
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}