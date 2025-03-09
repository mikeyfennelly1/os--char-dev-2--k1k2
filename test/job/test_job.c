#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../src/job/job.h"

void test_job(void) {
    CU_ASSERT_EQUAL(job(), 1);
}