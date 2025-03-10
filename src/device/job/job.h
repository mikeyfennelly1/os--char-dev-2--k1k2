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

void add_step_to_job(Job* job, GetKVPFuncPtr get_kvp_func);
void run_job(Job* j);