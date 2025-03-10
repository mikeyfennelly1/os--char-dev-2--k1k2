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
    Step head;
} Job;

// add a Step to a Job
void add_step_to_job(Job* job, Step* step_to_add)
{
    Step* new_step = (Step*)malloc(sizeof(Step));
    new_step->get_kvp = step_to_add->get_kvp;
    new_step->next = &job->head; 
    job->head = *new_step;
}

void run_job(Job* j)
{
    Step cur = j->head;
    while (cur.next)
    {
        key_value_pair* kvp = cur.get_kvp();
        printf("%s:%s\n", kvp->key, kvp->value);
    }
}