#include <stdlib.h>
#include <stdio.h>

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

void run_job(Job* j)
{
    Step* cur = j->head;
    while (cur)
    {
        key_value_pair* kvp = cur->get_kvp();
        printf("%s:%s\n", kvp->key, kvp->value);
        // traverse the list until end is reached
        cur = cur->next;
    }
}