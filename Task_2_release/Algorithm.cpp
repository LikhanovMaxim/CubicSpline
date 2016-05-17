#include"Algorithm.h"
double* solveMatrix(int sizeMatrix, double *belowDiagonal, double *mainDiagonal, double *aboveDiagonal, double *f){
	double m;
	double *result = new double[sizeMatrix];
	for (int i = 1; i < sizeMatrix; i++){
		m = belowDiagonal[i] / mainDiagonal[i - 1];
		mainDiagonal[i] = mainDiagonal[i] - m*aboveDiagonal[i - 1];
		f[i] = f[i] - m * f[i - 1];
	}
	result[sizeMatrix - 1] = f[sizeMatrix - 1] / mainDiagonal[sizeMatrix - 1];
	for (int i = sizeMatrix - 2; i >= 0; i--){
		result[i] = (f[i] - aboveDiagonal[i] * result[i + 1]) / mainDiagonal[i];
	}
	return result;
}