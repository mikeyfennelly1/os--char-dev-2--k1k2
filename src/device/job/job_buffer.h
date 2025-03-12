#ifndef JOB_BUFFER_H
#define JOB_BUFFER_H

typedef struct {
    char *data;         // The buffer
    ssize_t size;       // the current size of the buffer
    ssize_t capacity;   // allocated capacity of the buffer
} DynamicJobBuffer;     

DynamicJobBuffer* init_job_buffer(void);
void append_to_job_buffer(DynamicJobBuffer *b, const char* text);
void free_job_buffer(DynamicJobBuffer *b);

#endif