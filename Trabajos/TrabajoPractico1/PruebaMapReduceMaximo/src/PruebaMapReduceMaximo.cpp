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
	double local_x,sum;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &cantProcesos);
	MPI_Comm_rank(MPI_COMM_WORLD, &procActual);

	local_x=rand()%10*procActual;
	printf("El proceso %i ha generado el número: %lf\n",procActual,local_x);
	MPI_Reduce(&local_x,&sum,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

	if(procActual==0){
			printf("\nEl máximo de los números generados es : %lf \n", sum);
		}

	MPI_Finalize();
}

