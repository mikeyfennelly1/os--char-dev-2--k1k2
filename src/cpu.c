#include <asm/cpu.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <asm/msr.h>
#include "job.h"

static key_value_pair cpu_model(void) { 
    key_value_pair* keyVal = (key_value_pair*) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal -> key = "cpu_model";
    keyVal->value = "dummy_value";
    return *keyVal;
}

static key_value_pair cpu_vendor(void) {
    key_value_pair* keyVal = (key_value_pair*) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal->key = "cpu_vendor";
    keyVal->value = "dummy_value";
    return *keyVal;
}

static key_value_pair cpu_frequency(void) {
    key_value_pair* keyVal = (key_value_pair*) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal -> key = "dummy_key";
    keyVal->value = "dummy_value";
    return *keyVal;
}

static key_value_pair cpu_cores(void) {
    key_value_pair* keyVal = (key_value_pair*) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal -> key = "dummy_key";
    keyVal->value = "dummy_value";
    return *keyVal;
}

static key_value_pair cpu_load(void) {
    key_value_pair* keyVal = (key_value_pair*) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal -> key = "dummy_key";
    keyVal->value = "dummy_value";
    return *keyVal;
}
 
static key_value_pair cpu_idle_time(void) { // nanoseconds
    key_value_pair* keyVal = (key_value_pair* ) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    keyVal -> key = "dummy_key";
    keyVal->value = "dummy_value";
    return *keyVal;
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