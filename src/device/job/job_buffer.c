#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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