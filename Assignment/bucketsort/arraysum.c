#include <stdio.h>
#include <stdlib.h>
// #include <mpi.h>
#define max_rows 1000
int array[max_rows];

int main(int argc, char **argv){
	int i, num_rows;
	long int sum;
	printf("enter the amount of numbers: \n");
	scanf("%d", &num_rows);
	if (num_rows > max_rows){
		printf("Too many numbers.\n");
		exit(1);
	}
	for (i = 0; i < num_rows; i++){
		array[i] = i;
	}

	sum = 0;
	for (i = 0; i < num_rows; i++){
		sum += array[i];
	}
	printf("Sum: %i\n", sum);
}