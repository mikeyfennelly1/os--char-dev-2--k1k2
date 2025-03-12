#ifndef JOB_H
#define JOB_H

#include <stdlib.h>
#include <stdio.h>
#include <json-c/json.h>

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

/**
 * A job is a sequence of functions that get system information
 * in key_value_pair format
 */
typedef struct Job {
    // title for the job
    char* job_title;
    
    // The 'head' step is the first step to 
    // run in the job
    Step* head;
} Job;

/**
 * Add a step to the job.
 * 
 * @arg job - the job to add the function pointer to.
 * @arg get_kvp_func - The pointer to the GetKVPFuncPtr
 * 
 */
void add_step_to_job(Job* job, GetKVPFuncPtr get_kvp_func);

/**
 * Runs the job (gets the key-value information for each step)
 * and writes the contents to a buffer 'target_buf'.
 *
 * @arg target_buf - the buffer the caller wants data to be written to.
 * @return string buffer that contains job data in key-value form.
 */
char* run_job(Job* j);

#endif