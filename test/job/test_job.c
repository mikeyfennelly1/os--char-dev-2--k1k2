#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../src/device/job/job.h"

// job data structure to get CPU 
// information from kernel space
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
    add_step_to_job(&cpu, &get_cpu_speed_hz);
    
    char** job_data = run_job(&cpu);

    free(data_buffer);
};

void test_cpu_job_output(void)
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
