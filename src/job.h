#ifndef JOB_H
#define JOB_H

// definitions for info types
#define CPU 1
#define MEMORY 2
#define DISK 3

Job* get_current_job(void);
int set_current_info_type(int value);

/**
 * Return type for job function in snake case.
 * key_value_pair.key - the name of the metric (e.g. cpu_speed_hz)
 * key_value_pair.value - the value of that metric
 */
typedef struct key_value_pair {
    char* key;
    char* value;
} key_value_pair;

/**
 * The smallest unit of a Job.
 * Consists of a get_kvp function pointer and a pointer to the
 * next Step in the Job.
 */
typedef struct Step {
    // function to run the step
    key_value_pair (*get_kvp)(void);

    // pointer to the next step in the job
    struct Step* next;
} Step;

/**
 * Initialize a step with Step.next==NULL
 *
 * @param get_kvp the get_kvp function to initialize the step.
 * @return Step* - pointer to the initialized step.
 * @return NULL if step init failed.
 */
Step* step_init(key_value_pair (*get_kvp)(void));

/**
 * A Job is composed of a title and a list steps.
 */
typedef struct Job {
    // title for the job
    char* job_title;
    
    // The 'head' step is the first step to 
    // run in the job
    Step* head;
} Job;

/**
 * Initialize a job, by title and first function
 * to run in the job.
 *
 * @param title The title of the Job to initialize.
 * @param head_func the function for the first step in the Job.
 * @return a pointer to the initialized Job,
 *         NULL if job_init failed
 */
Job* job_init(char* title, key_value_pair (*head_func)(void));

/**
 * Add a step to the job.
 * 
 * @param job - the job to add the function pointer to.
 * @param get_kvp_func - the function for the step to add
 */
void append_step_to_job(Job* job, key_value_pair (*get_kvp_func)(void));

/**
 * Runs the job (gets the key-value information for each step)
 * and writes the contents to a buffer 'target_buf'.
 *
 * @param j - pointer to the job to run.
 * @return string buffer that contains job data in key-value form.
 */
char* run_job(Job* j);

#endif