#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/job.h"

#define TEST_KEY "cpu_speed_hz"
#define TEST_VALUE "3000Hz"

void test_step_init(void)
{

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
    
    if (!CU_add_test(suite, "step_init", test_step_init))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}