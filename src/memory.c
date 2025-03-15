#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include "../job/job.h"



// Job to get memory information from kernel space
static struct Job memory = {
    
    "memory",

    NULL
};

// Create a function that returns a key_value_pair.

static key_value_pair* get_total_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) malloc(sizeof(key_value_pair));
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }
    kvp->key = "total_ram";
    asprintf(&kvp->value, "%ld", sys_info.totalram);
    return kvp;
}

static key_value_pair* get_free_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) malloc(sizeof(key_value_pair));
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }
    kvp->key = "free_ram";
    asprintf(&kvp->value, "%ld", sys_info.freeram);
    return kvp;
}

static key_value_pair* get_buffer_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) malloc(sizeof(key_value_pair));
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }
    kvp->key = "buffer_ram";
    asprintf(&kvp->value, "%ld", sys_info.bufferram);
    return kvp;
}

static key_value_pair* get_total_swap(void)
{
    key_value_pair* kvp = (key_value_pair *) malloc(sizeof(key_value_pair));
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }
    kvp->key = "total_swap";
    asprintf(&kvp->value, "%ld", sys_info.totalswap);
    return kvp;
}

static key_value_pair* get_free_swap(void)
{
    key_value_pair* kvp = (key_value_pair *) malloc(sizeof(key_value_pair));
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }
    kvp->key = "free_swap";
    asprintf(&kvp->value, "%ld", sys_info.freeswap);
    return kvp;
}


int main(void)
{
    add_step_to_job(&memory, &get_total_ram);
    add_step_to_job(&memory, &get_free_ram);
    add_step_to_job(&memory, &get_buffer_ram);
    add_step_to_job(&memory, &get_total_swap);
    add_step_to_job(&memory, &get_free_swap);
    run_job(&memory);
    return 0;
}
