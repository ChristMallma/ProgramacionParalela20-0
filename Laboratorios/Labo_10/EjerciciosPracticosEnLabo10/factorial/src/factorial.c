/*
 Autor: Christian
 Contenido: Cálculo del factorial de un número usando hilos
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int cantidad;
int factorial = 1;

void *Factorial(void* rank);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;
   printf("Ingresa un numero: ");
   scanf("%d",&cantidad);

   thread_count = strtol(argv[1], NULL, 10);
   thread_handles = malloc (thread_count*sizeof(pthread_t));

   for (thread = 0; thread < thread_count; thread++){
	   pthread_create(&thread_handles[thread], NULL, Factorial, (void*) thread);
   }

   for (thread = 0; thread < thread_count; thread++){
	   pthread_join(thread_handles[thread], NULL);
   }

   printf("Resultado: %d", factorial);

   free(thread_handles);
   return 0;
}

/*-------------------------------------------------------------------*/
void *Factorial(void* rank) {
   long my_rank = (long) rank;
   int local_m = cantidad/thread_count;

   int inicio = my_rank*local_m + 1;
   int fin = (my_rank+1)*local_m;

   if(cantidad % thread_count != 0){
	   int sobrante = cantidad % thread_count;
	   if(my_rank == thread_count-1) fin += sobrante;
   }

   for(int i = inicio; i <= fin; i++){
	   factorial = factorial*i;
   }
   return NULL;
}
