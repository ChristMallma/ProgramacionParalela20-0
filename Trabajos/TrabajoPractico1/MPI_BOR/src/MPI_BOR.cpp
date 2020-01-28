/*
 ============================================================================
 Name        : MPI_BOR.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_BOR
 ============================================================================
 */

#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int resBOR = 0;
	int nroBit;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Before to MPI Reduce %d\n", resBOR);

	}

	switch (rank) {
	case 0:
		nroBit = 0;
		break;
	case 1:
		nroBit = 1;
		break;
	case 2:
		nroBit = 0;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBOR, 1, MPI_INT, MPI_BOR, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("After to MPI Reduce BOR %d\n", resBOR);

	}
	MPI_Finalize();

	return 0;

}

