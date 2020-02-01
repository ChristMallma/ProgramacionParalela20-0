/*
 ============================================================================
 Name        : PruebaMapReduceSuma.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int cantProcesos,procActual;
	int local_x;
	int sum;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &cantProcesos);
	MPI_Comm_rank(MPI_COMM_WORLD, &procActual);

	local_x=rand()%10*procActual+3;
	if(local_x%2==0) local_x=1;
	else local_x=0;
	printf("El proceso %i ha generado el número: %i\n",procActual,local_x);
	MPI_Reduce(&local_x,&sum,1,MPI_INT,MPI_LAND,0,MPI_COMM_WORLD);

	if(procActual==0){
			printf("\nEl resultado de aplicar AND en los números generados es : %i \n", sum);
		}

	MPI_Finalize();
}

