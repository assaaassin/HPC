#include <stdio.h>
#define max_rows 1000

int array[max_rows];

void main(int argc, char **argv){
	int i, num_rows;
	long int sum;

	printf("Enter the total of numbers to sum: ");
	scanf("%i", &num_rows);

	if (num_rows > max_rows){
		printf("Too many numbers.\n");
		// exit(1);
	}
	for (i = 0; i < num_rows; i++){
		array[i] = i;
	}

	sum = 0;
	for (i = 0; i < num_rows; i++){
		sum += array[i];
	}
	printf("Sum:%i\n");
}