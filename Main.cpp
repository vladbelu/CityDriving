#include "Main.h"
#include "Debugger.h"
#include "Master.h"
#include "Worker.h"

#include "Graph.h"
#include "mpi.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv);

	launchDebugger();

	if (argc > 1) {
		char* inputFile = argv[1];
		ifstream input(inputFile);
		freopen(inputFile, "r", stdin);
	}

	int rank, worldSize;
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		// Master

		Master master;
		master.ReadGraph();
		master.SetSearchPoints(0, 0, 0, 0);
		master.PrepareJobs(worldSize);

		cout << endl << "Master: " << rank;
	}
	else {
		// Slaves
		cout << endl << "Slave: " << rank;
	}
	MPI_Finalize();
	return 0;
}