#include <stdio.h>
#include "cpu.h"

int main(void) {
    Job* my_cpu_job = cpu_job();

    if (!my_cpu_job) {
        fprintf(stderr, "Error: Could not create CPU job.\n");
        return 1;
    }

    run_job(my_cpu_job);

    return 0;
}