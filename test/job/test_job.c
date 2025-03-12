#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../src/device/job/job.h"

#define TEST_KEY "cpu_speed_hz"
#define TEST_VALUE "3000Hz"

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
    // malloc the key_value_pair
    key_value_pair* cpu_speed_step_kvp = (key_value_pair *) malloc(sizeof(key_value_pair));

    // set the fields of the key_value_pair you just malloc'd
    //
    // NOTE: Yours will be retrieving data from kernel space,
    //       I just put in some dummy data for this example.
    cpu_speed_step_kvp->key = TEST_KEY;
    cpu_speed_step_kvp->value = TEST_VALUE;

    // return pointer to key_value_pair on heap
    return cpu_speed_step_kvp;
};

// assert that the JSON string returned from 
// the above CPU job is as expected 
void test_cpu_job_output(void)
{
    char* cpu_json = run_job(&cpu);
    printf("%d\n", cpu_json);

    char* actual = run_job(&cpu);
    char* expected = "{\n\tcpu_speed_hz:3000Hz\n}";

    CU_ASSERT_STRING_EQUAL(
        actual,
        expected
    );
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

    if (!CU_add_test(suite, "test_job", test_cpu_job_output))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
