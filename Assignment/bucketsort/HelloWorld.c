#include <stdio.h>
#include <mpi.h>

void main(int argc, char **argv)
{
	int ierr, num_processes, id;
	// printf("Now entering MPI Block\n");
	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	printf("Hello World! Process %i out of %i processes\n",
		id, num_processes);
	ierr = MPI_Finalize();
}
