#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../src/device/job/job.h"

// job to get CPU information from kernel space
static struct Job cpu = {
    // title of the job 
    "cpu",

    // head step of the job
    //
    // Initially I don't have one, so I will leave it as
    NULL
};

static key_value_pair* get_cpu_speed_hz(void)
{
    // malloc the key_value_pair
    key_value_pair* cpu_speed_step_kvp = (key_value_pair *) malloc(sizeof(key_value_pair));

    // set the fields of the key_value_pair you just malloc'd
    cpu_speed_step_kvp->key = "cpu_speed_hz";
    cpu_speed_step_kvp->value = "3000Hz";

    // return pointer to key_value_pair on heap
    return cpu_speed_step_kvp;
};

void test_job(void) {
    add_step_to_job(&cpu, &get_cpu_speed_hz);
    CU_ASSERT_EQUAL(job(), 1);
}

int main(void)
{
    // init CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS)
    {
        return CU_get_error();
    }

    // create test suite
    CU_pSuite suite = CU_add_suite("Test suite for test flow", NULL, NULL);
    if (!suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "test_job", test_job))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
