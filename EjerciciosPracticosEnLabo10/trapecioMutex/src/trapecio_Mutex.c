#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define a 0
#define b 10
#define n 10

int thread_count;
double global_result = 0.0;

void *Area(void* rank);
double f(double x);    /* Function we're integrating */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;

   thread_count = strtol(argv[1], NULL, 10);
   thread_handles = malloc (thread_count*sizeof(pthread_t));
   // pthread_mutex_init(&mutex, NULL);

   for (thread = 0; thread < thread_count; thread++){
	   pthread_create(&thread_handles[thread], NULL, Area, (void*) thread);
   }

   for (thread = 0; thread < thread_count; thread++){
	   pthread_join(thread_handles[thread], NULL);
   }


   free(thread_handles);
   return 0;
}

double f(double x) {
   double return_val;

   return_val = x*x;
   return return_val;
}

/*-------------------------------------------------------------------*/
void *Area(void* rank) {
   double h, x, my_result;
   double local_a, local_b;
   int  i, local_n;
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n;
   local_n = n/thread_count;
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   my_result = (f(local_a) + f(local_b))/2.0;
   for (i = 1; i <= local_n-1; i++) {
	   x = local_a + i*h;
	   my_result += f(x);
   }

   global_result += my_result;
   return NULL;
}
