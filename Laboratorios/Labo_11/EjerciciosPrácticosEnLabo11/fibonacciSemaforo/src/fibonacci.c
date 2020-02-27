#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int thread_count;
int cantidad;
int *f;
sem_t* semaphores;

void *Suma(void* rank);
void *fibo(void *rank);

/*--------------------------------------------------------------------*/
/*fibonacci={0,1,1,2,3,5,8,13,21,34,55,89}*/

int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;
   printf("Ingresa un numero: ");
   scanf("%d",&cantidad);

   f= malloc((cantidad)*sizeof(int));
   f[0]=0;
   f[1]=1;
   f[2]=1;

   thread_count = strtol(argv[1], NULL, 10);
   thread_handles = malloc (thread_count*sizeof(pthread_t));
   semaphores = malloc(thread_count * sizeof(sem_t));

   int s=0;
   for (thread = 0; thread < thread_count; thread++) {
	   if(thread==0)s=1;
	   sem_init(&semaphores[thread], 0, s);
	   s=0;
   	}

   for (thread = 0; thread < thread_count; thread++){
	   pthread_create(&thread_handles[thread], NULL, fibo, (void*) thread);
   }

   for (thread = 0; thread < thread_count; thread++){
	   pthread_join(thread_handles[thread], NULL);
   }

   for (thread = 0; thread < thread_count; thread++)
   	  	   sem_destroy(&semaphores[thread]);

   printf("Resultado: %d \n", f[cantidad]);

   free(semaphores);
   free(thread_handles);
   return 0;
}

/*-------------------------------------------------------------------*/
void *fibo(void *rank){
	long my_rank=(long)rank;
	int cont=my_rank+3;
	long dest = (my_rank + 1) % thread_count;

	sem_wait(&semaphores[my_rank]);

	f[cont]=f[cont-1]+f[cont-2];

	sem_post(&semaphores[dest]);
	return NULL;
}

