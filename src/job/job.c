/**
 * For creating a list of jobs to get sysinfo information.
 * 
 * @author Mikey Fennelly
 */

#define PROC_MODE 1
#define READ_MODE 2

typedef struct {
    // The first step of the job.
    Step* head_step;

    // the run method for a job, runs the job in the specified mode;
    void (*run) ();

    // the mode for a job defines where the output of that job will be
    // 
    // if the mode is PROC_MODE then the output of the job's data will
    // be written to the /proc file
    //    
    // if the mode is READ_MODE, this indicates that the device has gotten
    // a read call, and that the data should be written to a userspace
    // JSON file.
    int mode;

    // add a Step to the Job.
    void (*add_step)(Step step_to_add);
} Job;

/**
 * @brief A runnable portion of a job.
 */
typedef struct {
    // Title describing the information returned by the step.
    //
    // e.g for the job get_cpu_speed_hz(), title="cpu_speed_hz"
    char* title

    // the value returned from the step in char* format
    char* value

    // function to run the job
    // as all sysinfo jobs 'get' information, it is named as such
    char* (*get) ();

    // the next step to execute
    Step* next = NULL;

    // add a step to the list
    void* (*)
} Step;


// Execute all steps in a job.
void run_job(*Job job_to_run)
{
    if (job_to_run.mode == PROC_MODE)
    {
        while (job_to_run.head_step.next)
        {
            char* title = job_to_run.head_step.title;
            char* result = job_to_run.head_step.get();
            append_to_proc(title, result);
        }
    }
}