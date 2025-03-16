#include <linux/kernel.h>
#include <linux/slab.h>
#include "job.h"

static key_value_pair get_total_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "dummy_key";
    kvp->value = "dummy_value";
    return *kvp;
}

static key_value_pair get_free_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "dummy_key";
    kvp->value = "dummy_value";
    return *kvp;
}

static key_value_pair get_buffer_ram(void)
{
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "dummy_key";
    kvp->value = "dummy_value";
    return *kvp;
}

static key_value_pair get_total_swap(void)
{
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "dummy_key";
    kvp->value = "dummy_value";
    return *kvp;
}

static key_value_pair get_free_swap(void)
{
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "dummy_key";
    kvp->value = "dummy_value";
    return *kvp;
}

Job* get_memory_job(void)
{
    Job* memory = job_init("memory", get_total_ram);
    append_step_to_job(memory, get_free_ram);
    append_step_to_job(memory, get_total_swap);
    append_step_to_job(memory, get_buffer_ram);
    append_step_to_job(memory, get_free_swap);
    return memory;
}