#include <asm/cpu.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <asm/msr.h>
#include "job.h"

key_value_pair cpu_idle_time(void);
key_value_pair cpu_load(void);
key_value_pair cpu_cores(void);
key_value_pair cpu_frequency(void);
key_value_pair cpu_vendor(void);
key_value_pair cpu_model(void);
Job* get_cpu_job(void);

key_value_pair cpu_model(void)
{ 
    key_value_pair keyVal;
    keyVal.key = "cpu_model";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair cpu_vendor(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_vendor";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair cpu_frequency(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_frequency";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair cpu_cores(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_cores";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair cpu_load(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_load";
    keyVal.value = "dummy_value";
    return keyVal;
}
 
key_value_pair cpu_idle_time(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_idle_time";
    keyVal.value = "dummy_value";
    return keyVal;
}

Job* get_cpu_job(void)
{
    Job* cpu_info = job_init("cpu", &cpu_model);
    append_step_to_job(cpu_info, &cpu_vendor);
    append_step_to_job(cpu_info, &cpu_frequency);
    append_step_to_job(cpu_info, &cpu_cores);
    append_step_to_job(cpu_info, &cpu_load);
    append_step_to_job(cpu_info, &cpu_idle_time);

    return cpu_info;
}