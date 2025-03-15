#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <asm/processor.h>
#include <linux/time.h>
#include "../job.h/job.h"
#include "newCpu.h"

static struct Job cpu_info = {
    "cpu",
    NULL
};

static key_value_pair* cpu_model(void) { 
    key_value_pair* keyVal = (key_value_pair*) malloc(sizeof(key_value_pair));
    keyVal -> key = "cpu_model";
    asprintf(&keyVal -> value, "%s", boot_cpu_data.x86_model_id);
    return keyVal;
}

static key_value_pair* cpu_vendor(void) {
    key_value_pair* keyVal = (key_value_pair*) malloc(sizeof(key_value_pair));
    keyVal -> key = "cpu_vendor";
    asprintf(&keyVal -> value, "%s", boot_cpu_data.x86_vendor_id);
    return keyVal;
}

static key_value_pair* cpu_frequency(void) {
    key_value_pair* keyVal = (key_value_pair*) malloc(sizeof(key_value_pair));
    unsigned int frequency = cpufreq_get(0); // 1-minute average
    keyVal -> key = "cpu_frequency";
    asprintf(&keyVal -> value, "%u", frequency);
    return keyVal;
}

static key_value_pair* cpu_cores(void) {
    key_value_pair* keyVal = (key_value_pair*) malloc(sizeof(key_value_pair));
    keyVal -> key = "cpu_cores";
    aspritf(&keyVal -> value, "%d", num_online_cpus());
    return keyVal;
}

static key_value_pair* cpu_load(void) {
    key_value_pair* keyVal = (key_value_pair*) malloc(sizeof(key_value_pair));
    extern unsigned long avenrun[];
    keyVal -> key = "cpu_load_avg";
    asprintf(&keyVal -> value, "%lu", avenrun[0] / FIXED_1);
    return keyVal;
}

static key_value_pair* cpu_idle_time(void) { // nanoseconds
    key_value_pair* keyVal = (key_value_pair* ) malloc(sizeof(key_value_pair));
    if (!keyVal) {
        return NULL;
    }

    u64 wall_time;
    u64 idel_time = get_cpu_idle_time(0, &walltime, 0);

    keyVal -> key = "cpu_idle_time";
    asprintf(&keyVal -> value, "%lu", idle_time);

    return keyVal;
}

Job* cpu_job(void) {
    add_step_to_job(&cpu_info, &cpu_model);
    add_step_to_job(&cpu_info, &cpu_vendor);
    add_step_to_job(&cpu_info, &cpu_frequency);
    add_step_to_job(&cpu_info, &cpu_cores);
    add_step_to_job(&cpu_info, &cpu_load);
    ad_step_to_job(&cpu_info, &cpu_idle_time);
    return &cpu_info;
}