#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "memory.h"

#define zerofyArray(array, size) (memset(array, 0, size))

//http://math.stackexchange.com/questions/69544/create-polynomial-coefficients-from-its-roots
//http://stackoverflow.com/questions/21236788/efficient-calculation-of-polynomial-coefficients-from-its-roots
double * findCoefficients(double* roots, size_t size) {
	size_t sizeBytes = sizeof(double) * (size + 1);
	double * coefficients = malloc(sizeBytes);
	zerofyArray(coefficients, sizeBytes);

	//first iteration
	*coefficients = -*roots;
	*(coefficients + 1) = 1.;

	double * oldCoefficients = malloc(sizeBytes);
	int i;
	int j;
	for (i = 1; i < size; i++) {
		memcpy(oldCoefficients, coefficients, sizeof(double) * (i + 1));
		for (j = i; j >= 0; j--) {
			*(coefficients + j + 1) = *(coefficients + j);
		}
		*coefficients = 0.;
		for (j = 0; j <= i; j++) {
			*(oldCoefficients + j) = *(oldCoefficients + j) * *(roots + i);
		}
		for (j = 0; j <= i; j++) {
			*(coefficients + j) = *(coefficients + j) - *(oldCoefficients + j);
		}
	}
	free(oldCoefficients);
	return coefficients;
}


#define N 4
#define printDecimal(number) (printf("%f, ", number))
#define scanDecimal(number) (scanf("%lf", number))


int main(void) {
	double roots[N] = {3., 2., 1., -3.};
	double * coefficients = findCoefficients(roots, N);
	int i;
	for (i = 0; i < N + 1; i++) {
		printDecimal(coefficients[i]);
	}
	printf("\n");
	return 0;
}
