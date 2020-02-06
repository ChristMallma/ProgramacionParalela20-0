/*
 ============================================================================
 Name        : Pregunta7_PrimeraPráctica.c
 Author      : Christian
 Version     :
 Copyright   : Your copyright notice
 Description : Primera praćtica calificada de Programación Paralela
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
using namespace std;
//Para este ejemplo usaremos 2 procesadores
//El número a ingresar será un múltiplo de 3
 
int main(int argc, char *argv[]) {
	int cantProcesos, procActual;
	int A[6]={0};
	int b[2]={0};
	int producto,n,local_prod;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&cantProcesos);
	MPI_Comm_rank(MPI_COMM_WORLD,&procActual);

	if(procActual==0){
		//Ingresando valor para "n"
		cout<<"Ingrese número => ";cin>>n;

		//LLenando el vector con datos aleatorios
		for(int i=0;i<n;i++){
			A[i]=i+1;
		}
	}

	//Repartiendo los datos
	MPI_Scatter(&A,3,MPI_INT,&b,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int j=0;j<3;j++){
		cout<<b[j]<<" ";
	}

	//Hallando producto en cada procesador, para enviarlo al Reduce
	local_prod=b[0];
	for(int k=1;k<3;k++){
		local_prod*=b[k];
	}
	cout<<endl;
	cout<<"Producto parcial => "<<local_prod;
	cout<<endl;

	MPI_Reduce(&local_prod,&producto,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

	if(procActual==0){
		cout<<"El factorial de "<<n<<" es => "<<producto<<endl;
	}

	MPI_Finalize();
	return 0;
}

