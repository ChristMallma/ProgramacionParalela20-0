/*
 ============================================================================
 Name        : pth_hello.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
int thread_count;

void Usage(char *prog_name);
void* Hello(void *rank); /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	long thread; /* Use long in case of a 64-bit system */
	pthread_t *thread_handles;

	/* Get number of threads from command line */
	if (argc != 2)
		Usage(argv[0]);
	printf("%s\n", argv[0]);
	thread_count = strtol(argv[1], NULL, 10);
	if (thread_count <= 0 || thread_count > MAX_THREADS)
		Usage(argv[0]);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);

	printf("Hello from the main thread\n");

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	free(thread_handles);
	return 0;
} /* main */

/*-------------------------------------------------------------------*/
void* Hello(void *rank) {
	long my_rank = (long) rank; /* Use long in case of 64-bit system */

	printf("Hello from thread %ld of %d\n", my_rank, thread_count);

	return NULL;
} /* Hello */

/*-------------------------------------------------------------------*/
void Usage(char *prog_name) {
	fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
	fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
	exit(0);
} /* Usage */
