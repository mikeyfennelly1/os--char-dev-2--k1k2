#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include "job.h"

static key_value_pair get_total_ram(void);
static key_value_pair get_free_ram(void);
static key_value_pair get_buffer_ram(void);
static key_value_pair get_total_swap(void);
static key_value_pair get_free_swap(void);
Job* get_memory_job(void);

static key_value_pair get_total_ram(void)
{
    struct sysinfo si;
    si_meminfo(&si);
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "Total RAM";
    kvp->value = kasprintf(GFP_KERNEL, "%lu kB", si.totalram * (si.mem_unit / 1024));
    return *kvp;
}

static key_value_pair get_free_ram(void)
{
    struct sysinfo si;
    si_meminfo(&si);
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "Free RAM";
    kvp->value = kasprintf(GFP_KERNEL, "%lu kB", si.freeram * (si.mem_unit / 1024));
    return *kvp;
}

static key_value_pair get_buffer_ram(void)
{
    struct sysinfo si;
    si_meminfo(&si);
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "Buffered RAM";
    kvp->value = kasprintf(GFP_KERNEL, "%lu kB", si.bufferram * (si.mem_unit / 1024));
    return *kvp;
}

static key_value_pair get_total_swap(void)
{
    struct sysinfo si;
    si_swapinfo(&si);
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "Total Swap";
    kvp->value = kasprintf(GFP_KERNEL, "%lu kB", si.totalswap * (si.mem_unit / 1024));
    return *kvp;
}

static key_value_pair get_free_swap(void)
{
    struct sysinfo si;
    si_swapinfo(&si);
    key_value_pair* kvp = (key_value_pair *) kmalloc(sizeof(key_value_pair), GFP_KERNEL);
    kvp->key = "Free Swap";
    kvp->value = kasprintf(GFP_KERNEL, "%lu kB", si.freeswap * (si.mem_unit / 1024));
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
