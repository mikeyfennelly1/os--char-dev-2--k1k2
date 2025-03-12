#include <stdlib.h>
#include <stdio.h>
#include "./job_buffer.h"

#define JSON_MODE 1
#define KVP_MODE 2

// return type for a step function
typedef struct key_value_pair {
    char* key;
    char* value;
} key_value_pair;

typedef key_value_pair* (*GetKVPFuncPtr)(void);

typedef struct Step {
    // function to run the step
    GetKVPFuncPtr get_kvp;
    struct Step* next;
} Step;

typedef struct Job {
    char* job_title;
    Step* head;
} Job;

// add a Step to a Job
void add_step_to_job(Job* job, GetKVPFuncPtr get_kvp_func)
{
    // create Step object
    Step* new_step_ptr = (Step*)malloc(sizeof(Step));
    new_step_ptr->get_kvp = get_kvp_func;
    new_step_ptr->next = NULL;

    // if job has no steps, make new node the head
    if (job->head == NULL)
    {
        job->head = new_step_ptr;
        return;
    }
    else
    {
        Step* last = job->head;
        while (last->next)
        {
            // traverse the list until end is reached
            last = last->next;
        }
        // add point first item in list to new_step
        last->next = new_step_ptr;
    }

    return;
}

/**
 * Get the data of the job in string format.
 * 
 */
char* get_job_data_as_str(int mode)
{
    
}

/**
 * Runs the job (gets the key-value information for each step)
 * and writes the contents to a buffer on the heap.
 *
 * @return string buffer that contains job data in key-value form.
 */
char** run_job(Job* )
{
    // initialize the buffer
    DynamicJobBuffer* b;
    init_job_buffer(b);

    Step* cur = j->head;
    while (cur)
    {
        key_value_pair* kvp = cur->get_kvp();
        
        append_to_job_buffer("%s:%s\n", kvp->key, kvp->value);
        cur = cur->next; // walk the list until end
    }
}