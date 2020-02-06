/*
 ============================================================================
 Name        : Pregunta6_PrimeraPráctica.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Primera praćtica calificada de Programación Paralela
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
#define n 15
using namespace std;
//Ejemplo para 3 procesadores
//El número a buscar para este ejemplo será el 5
 
int main(int argc, char *argv[]) {
	int cantProcesos, procActual;
	int A[n]={0};
	int b[5]={0};
	int cont,coincidencias;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&cantProcesos);
	MPI_Comm_rank(MPI_COMM_WORLD,&procActual);

	if(procActual==0){
	//LLenando el vector con datos aleatorios
	for(int i=0;i<n;i++){
		A[i]=rand()%10;
	}

	}

	//Repartiendo los datos
	MPI_Scatter(&A,5,MPI_INT,&b,5,MPI_INT,0,MPI_COMM_WORLD);

	cout<<"Proceso "<<procActual<<endl;
	for(int j=0;j<5;j++) cout<<b[j]<<" ";
	cout<<endl;

	cont=0;
	for(int k=0;k<5;k++){
		if(b[k]==5) cont++;
	}
	cout<<cont<<" coincidencia"<<endl;
	MPI_Reduce(&cont,&coincidencias,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(procActual==0){
	//Mostrando coincidencias
	cout<<"La cantidad total de coincidencias es: "<<coincidencias<<endl;
	}

	MPI_Finalize();

	return 0;
}

