#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define max_rows 1000
#define s_tag 1111
#define r_tag 2222

int array[max_rows];
int array_2[max_rows];

void main(int argc, char **argv){
	long int sum;
	long int partial_sum;
	MPI_Status status;
	int my_id, root_process, ierr, i, 
	num_rows, num_procs, an_id, num_rows_to_recv,
	avg_rows_per_proc, sender, num_rows_received,
	start_row, end_row, num_rows_to_snd;

	ierr = MPI_Init(&argc, &argv);
	root_process = 0;

	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	if (my_id == root_process){
		printf("enter amount of number to sum: ");
		scanf("%i", &num_rows);
		if (num_rows>max_rows){
			printf("Too many nums.\n");
			exit(1);
		}	

		avg_rows_per_proc = num_rows / 	num_procs;

		for (i = 0; i < num_rows; i++){
			array[i] = i + 1;
		}

		for (an_id = 1; an_id < num_procs; an_id++){
			start_row = an_id * avg_rows_per_proc + 1;
			end_row = (an_id + 1) * avg_rows_per_proc;

			if ((num_procs - end_row) < avg_rows_per_proc){
				end_row = num_rows - 1;
			}

			num_rows_to_snd = end_row - start_row + 1;
			ierr = MPI_Send(&num_rows_to_snd, 1, MPI_INT, an_id, s_tag, MPI_COMM_WORLD);
			ierr = MPI_Send(&array[start_row], num_rows_to_snd, MPI_INT, an_id, s_tag, MPI_COMM_WORLD);
			}

		sum = 0;
		for (i = 0; i < avg_rows_per_proc + 1; i++){
			sum += array[i];
		}
		printf("Sum calculated by root_process: %i\n", sum);

		for (an_id = 1; an_id < num_procs; an_id++){
			ierr = MPI_Recv(&partial_sum, 1, MPI_LONG, MPI_ANY_SOURCE,
				r_tag, MPI_COMM_WORLD, &status);
			sender = status.MPI_SOURCE;
			printf("partial_sum return from process %i: %i\n", partial_sum, sender);
			sum += partial_sum;
		}

		printf("Total sum: %i\n", sum);
	}
	else{
		ierr = MPI_Recv(&num_rows_to_recv, 1 , MPI_INT, 
			root_process, s_tag, MPI_COMM_WORLD, &status);

		ierr = MPI_Recv(&array_2, num_rows_to_recv, MPI_INT,
			root_process, s_tag, MPI_COMM_WORLD, &status);

		num_rows_received = num_rows_to_recv;

		partial_sum = 0;
		for (i = 0; i < num_rows_received; i++){
			partial_sum += array_2[i];
		}

		ierr = MPI_Send(&partial_sum, 1, MPI_LONG, root_process, 
			r_tag, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}