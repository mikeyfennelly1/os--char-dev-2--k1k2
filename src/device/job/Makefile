all: job
	rm job_buffer.o

job: job_buffer
	gcc -Wall -Wextra -c job.c -o job.o

job_buffer:
	gcc -Wall -Wextra -c job_buffer.c -o job_buffer.o

final: job job_buffer
	gcc -Wall -Wextra job.o job_buffer.o -o final

clean:
	rm -f job.o job_buffer.o final
