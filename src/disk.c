/**
 * disk.c
 * 
 * Create job, and getter for disk job.
 * 
 * @author Mikey Fennelly
 */

#include <asm/cpu.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <asm/msr.h>
#include "job.h"

Job* get_disk_job(void);
key_value_pair disk_model(void);
key_value_pair disk_vendor(void);
key_value_pair disk_frequency(void);
key_value_pair disk_cores(void);
key_value_pair disk_load(void);
key_value_pair disk_idle_time(void);

key_value_pair disk_model(void)
{ 
    key_value_pair keyVal;
    keyVal.key = "disk_model";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair disk_vendor(void)
{
    key_value_pair keyVal;
    keyVal.key = "disk_vendor";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair disk_frequency(void)
{
    key_value_pair keyVal;
    keyVal.key = "disk_frequency";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair disk_cores(void)
{
    key_value_pair keyVal;
    keyVal.key = "disk_cores";
    keyVal.value = "dummy_value";
    return keyVal;
}

key_value_pair disk_load(void)
{
    key_value_pair keyVal;
    keyVal.key = "disk_load";
    keyVal.value = "dummy_value";
    return keyVal;
}
 
key_value_pair disk_idle_time(void)
{
    key_value_pair keyVal;
    keyVal.key = "disk_idle_time";
    keyVal.value = "dummy_value";
    return keyVal;
}

Job* get_disk_job(void)
{
    Job* disk_info = job_init("disk", &disk_model);
    append_step_to_job(disk_info, &disk_vendor);
    append_step_to_job(disk_info, &disk_frequency);
    append_step_to_job(disk_info, &disk_cores);
    append_step_to_job(disk_info, &disk_load);
    append_step_to_job(disk_info, &disk_idle_time);

    return disk_info;
}