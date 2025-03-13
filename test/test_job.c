#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/job.h"

#define TEST_KEY "test_key"
#define TEST_VALUE "test_value"

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
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}