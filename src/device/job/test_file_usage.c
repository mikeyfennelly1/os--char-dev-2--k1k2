#include "./job.h"

// job to get CPU information from kernel space
static struct Job cpu = {
    // title of the job 
    "cpu",

    // head step of the job
    //
    // Initially I don't have one, so I will leave it as
    NULL
};

static key_value_pair* get_cpu_speed_hz(void)
{
    // malloc the key_value_pair
    key_value_pair* cpu_speed_step_kvp = (key_value_pair *) malloc(sizeof(key_value_pair));

    // set the fields of the key_value_pair you just malloc'd
    cpu_speed_step_kvp->key = "cpu_speed_hz";
    cpu_speed_step_kvp->value = "3000Hz";

    // return pointer to key_value_pair on heap
    return cpu_speed_step_kvp;
};

int main(void)
{
    add_step_to_job(&cpu, &get_cpu_speed_hz);
    run_job(&cpu);
}