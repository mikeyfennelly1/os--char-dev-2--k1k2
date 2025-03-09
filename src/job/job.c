#include <stdlib.h>
#include <stdio.h>

// write retrieved data to /proc directory
// default mode
#define WRITE_TO_PROC 1
// write job data to json file provided by
// user space calling process
#define WRITE_TO_USER_SPACE_JSON 2

typedef struct {
    // first step in the job
    Step head = NULL;

    // add a step to the job
    void (*add_job)();
    
    // mode of operation for the job
    int mode;
    
    // run the job
    void (*run)();

} Job;

typedef struct {
    title char*,
    result char*
} STEP_INFORMATION;

typedef struct {
    // function to run the step
    STEP_INFORMATION (*get_data)();
    
    Step next_step = NULL;
} Step;

int job(void)
{
    printf("test print");
    return 1;
}