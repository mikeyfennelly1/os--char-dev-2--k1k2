#include <stdlib.h>
#include <stdio.h>
#include <json-c/json.h>
#include <string.h>

#define JSON_MODE 1
#define KVP_MODE 2

#define INITIAL_CAPACITY 16
#define GROWTH_FACTOR 2

typedef struct {
    char *data;         // The buffer
    ssize_t size;       // the current size of the buffer
    ssize_t capacity;   // allocated capacity of the buffer
} DynamicJobBuffer;

/**
 * Initialize a DynamicJobBuffer.
 */
DynamicJobBuffer* init_job_buffer(void)
{
    DynamicJobBuffer *b = malloc(sizeof(DynamicJobBuffer));
    b->capacity = INITIAL_CAPACITY;
    b->size = 0;
    b->data = (char *)malloc(b->capacity);
    if (!b->data)
    {
        printf("Could not increase size of backing array in job buffer\n");
        exit(1);
    }
    b->data[0] = '\0';
    return b;
}

void resize_job_buffer(DynamicJobBuffer *b, size_t new_capacity)
{
    char *new_data = (char *)realloc(b->data, new_capacity);
    if (!new_data)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    b->data = new_data;
    b-> capacity = new_capacity;
}

void append_to_job_buffer(DynamicJobBuffer *b, const char* text)
{
    size_t text_len = strlen(text);
    long int* buffer_size = (long int*)b->size;
    if (*buffer_size + text_len + 1 > (unsigned long)b->capacity)
    {
        size_t new_capacity = b->capacity * GROWTH_FACTOR;
        while (new_capacity < b->size + text_len + 1)
        {
            new_capacity *= GROWTH_FACTOR;
        }
        resize_job_buffer(b, new_capacity);
    }

    strcpy(b->data + b->size, text);
    b->size += text_len;
}

void free_job_buffer(DynamicJobBuffer *b)
{
    free(b->data);
    b->data = NULL;
    b->size = 0;
    b-> capacity = 0;
}

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
 * Runs the job (gets the key-value information for each step)
 * and writes the contents to a buffer 'target_buf'.
 *
 * @arg target_buf - the buffer the caller wants data to be written to.
 * @return string buffer that contains job data in key-value form.
 */
char* run_job(Job* j)
{
    if (j->head->next == NULL)
    {
        return NULL;
    }
    DynamicJobBuffer* target_buf = init_job_buffer();
    
    struct json_object *root = json_object_new_object();
    Step *cur = j->head->next;
    while (cur)
    {
        key_value_pair* cur_kvp = cur->get_kvp();
        json_object_object_add(root, cur_kvp->key, json_object_new_string(cur_kvp->value));
        cur = cur->next;
    }

    append_to_job_buffer(target_buf, json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

    return target_buf->data;
}