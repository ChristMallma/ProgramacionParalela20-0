/*
 ============================================================================
 Name        : SumaVectoresSendRecv.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void f1(int result[], int recibido[], int rango_ini, int rango_fin){
	int i;
	for(i = rango_ini; i <= rango_fin; i++){
		result[i] = recibido[i];
	}
}
 
int main(int argc, char *argv[]) {
	int rank, i;
	int arr1[100], arr2[100], arrResult[100];

	for(int i = 0; i < 100; i++){
		arr1[i] =  rand() % 100;
		arr2[i] =  rand() % 100;
	}

	MPI::Init(argc, argv);
	rank = MPI::COMM_WORLD.Get_rank();
	MPI_Status estado;

	int rango_ini = (rank)*10;
	int rango_fin = (rank+1)*10-1;
	for(i = rango_ini; i <= rango_fin; i++){
		arrResult[i] = arr1[i] + arr2[i];
	}

	if(rank != 0){
		MPI_Send(&arrResult, 10, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}else{
		int arrRecibido[10];
		MPI_Recv(&arrRecibido, 100, MPI_INT, 1, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 10, 19);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 2, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 20, 29);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 3, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 30, 39);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 4, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 40, 49);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 5, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 50, 59);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 6, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 60, 69);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 7, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 70, 79);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 8, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 80, 89);
		MPI_Recv(&arrRecibido, 100, MPI_INT, 9, 0, MPI_COMM_WORLD, &estado);
		f1(arrResult, arrRecibido, 90, 99);

		for(int i = 0; i < 100; i++){
			cout << "Indice " << i << " \t" << arrResult[i] << endl;
		}
	}

	MPI::Finalize();
	return 0;
}

