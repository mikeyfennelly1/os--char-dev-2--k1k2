#ifndef TEST_DYNAMIC_JOB_BUFFER_H
#define TEST_DYNAMIC_JOB_BUFFER_H

#include <stdlib.h>

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
DynamicJobBuffer* init_job_buffer(void);
void resize_job_buffer(DynamicJobBuffer *b, size_t new_capacity);
void append_to_job_buffer(DynamicJobBuffer *b, const char* text);

#endif