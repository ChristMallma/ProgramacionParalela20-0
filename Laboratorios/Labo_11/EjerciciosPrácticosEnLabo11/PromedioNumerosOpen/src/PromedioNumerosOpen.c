/*
 ============================================================================
 Name        : PromedioNumerosOpen.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C

 Compilación: gcc -o promedioNumeros -fopenmp  PromedioNumerosOpen.c
 Ejecución:./promedioNumeros
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int numeroHilos, id,n;
	int *numeros;
	float promedio=0;
	float suma=0;
	double local_n;

	printf("Ingrese cantidad de hilos =>");
	scanf("%d",&numeroHilos);
	omp_set_num_threads(numeroHilos);

	printf("Ingrese un valor para n =>");
	scanf("%d",&n);

	local_n=n/numeroHilos;
	numeros=malloc(n*sizeof(int));

	srand(time(NULL));
	for(int i=0;i<n;i++){
		numeros[i]=rand()%5;
	}
	printf("\n");
	for(int i=0;i<n;i++){
			printf("%d ",numeros[i]);
	}
	printf("\n");

	//Función paralela
	#pragma omp parallel private(id)
	{
		 id = omp_get_thread_num();
		 int posicion=0;
		 for(int i=0;i<local_n;i++){
			 posicion=id+i*numeroHilos;
			 suma=suma+numeros[posicion];
		 }
	}
	printf("\n");
	promedio=suma/n;
	printf("La suma es %.2f\n",suma);
	printf("\nEl promedio es %.2f\n",promedio);

 return 0;
}


