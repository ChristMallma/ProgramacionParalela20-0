/*
 ============================================================================
 Name        : MPI_MIN.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_MIN
 ============================================================================
 */

#include <math.h> 
#include <stdio.h>
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int Data = 0;
	int minData = 0;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Data = (rank + 1) * 4;

	if (rank == 0) {
		cout << "Before to MPI_Reduce" << endl;
		cout << "Min: " << minData << endl;
	}

	MPI_Reduce(&Data, &minData, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "After to MPI_Reduce" << endl;
		cout << "Min number to process is: " << minData << endl;
	}
	MPI_Finalize();

	return 0;
}

