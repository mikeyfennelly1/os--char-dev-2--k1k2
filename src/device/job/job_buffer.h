#ifndef JOB_BUFFER_H
#define JOB_BUFFER_H

#define INITIAL_CAPACITY 16
#define GROWTH_FACTOR 2

typedef struct {
    char *data;         // The buffer
    ssize_t size;       // the current size of the buffer
    ssize_t capacity;   // allocated capacity of the buffer
} DynamicJobBuffer;

void init_job_buffer(DynamicJobBuffer *b);
void resize_job_buffer(DynamicJobBuffer *b, size_t new_capactiy);

#endif