#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h> 
#include "cpu.h"

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
    keyVal.value = kstrdup(current_cpu_data.x86_model_id, GFP_KERNEL);

    if (!keyVal.value) {
        keyVal.value = kstrdup("unknown", GFP_KERNEL);
    }

    return keyVal;
}

key_value_pair cpu_vendor(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_vendor";
    keyVal.value = kstrdup(current_cpu_data.x86_vendor_id, GFP_KERNEL);

    if (!keyVal.value) {
        keyVal.value = kstrdup("unknown", GFP_KERNEL);
    }

    return keyVal;
}

key_value_pair cpu_frequency(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_frequency";

    unsigned long freq = cpufreq_quick_get(0); 

    char *freq_str = kmalloc(20, GFP_KERNEL);
    if (!freq_str) {
        return keyVal;
    }

    scnprintf(freq_str, 20, "%lu", freq);
    keyVal.value = freq_str;

    return keyVal;
}

key_value_pair cpu_cores(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_cores";

    int num_cores = num_online_cpus();

    char *value = kmalloc(16, GFP_KERNEL);
    if (!value) {
        return keyVal;
    }

    scnprintf(value, 16, "%d", num_cores);
    keyVal.value = value;

    return keyVal;
}

key_value_pair cpu_load(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_load";

    unsigned long load;
    get_avenrun(&load, FIXED_1, 0);  

    char *load_str = kmalloc(20, GFP_KERNEL);
    if (!load_str) {
        return keyVal;
    }

    scnprintf(load_str, 20, "%lu", load);
    keyVal.value = load_str;

    return keyVal;
}
 
key_value_pair cpu_idle_time(void)
{
    key_value_pair keyVal;
    keyVal.key = "cpu_idle_time";

    unsigned long idle_time = get_cpu_idle_time(0, NULL, 0);

    char *idle_str = kmalloc(20, GFP_KERNEL);
    if (!idle_str) {
        return keyVal;
    }

    scnprintf(idle_str, 20, "%lu", idle_time);
    keyVal.value = idle_str;

    return keyVal;
}

Job* get_cpu_job(void) {
    Job* cpu_info = job_init("cpu", &cpu_model);
    append_step_to_job(cpu_info, &cpu_vendor);
    append_step_to_job(cpu_info, &cpu_frequency);
    append_step_to_job(cpu_info, &cpu_cores);
    append_step_to_job(cpu_info, &cpu_load);
    append_step_to_job(cpu_info, &cpu_idle_time);

    return cpu_info;
}
