#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

extern void asmdaxpy(int n, double A, double* X, double* Y, double* Z);
extern void cdaxpy(int n, double A, double* X, double* Y, double* Z);

int main() {
	int i, s;
	double A = 5.0;
	
	int size[3] = { pow(2, 20), pow(2, 24), pow(2,28)};
	clock_t start, end;

	for(s = 0; s < 3; s++)
	{
		int n = size[s];
		double* X = (double*) malloc(n * sizeof(double));
		double* Y = (double*)malloc(n * sizeof(double));
		double* Z_c = (double*)malloc(n * sizeof(double));
		double* Z_asm = (double*)malloc(n * sizeof(double));
		double time_c = 0.0;
		double time_asm = 0.0;

		if (X == NULL || Y == NULL || Z_c == NULL || Z_asm == NULL)
		{
			printf("Memory allocation failed!\n");

			free(X);
			free(Y);
			free(Z_c);
			free(Z_asm);

			continue;
		}

		// fill the array with 0 to n-1
		for(i = 0; i < n; i++)
		{
			X[i] = i;
			Y[i] = i;
		}

		//run 30 times
		for (i = 0; i < 30; i++)
		{
			start = clock();
			cdaxpy(n, A, X, Y, Z_c);
			end = clock();
			time_c += ((double)(end - start)) / CLOCKS_PER_SEC;

			start = clock();
			asmdaxpy(n, A, X, Y, Z_asm);
			end = clock();
			time_asm += ((double)(end - start)) / CLOCKS_PER_SEC;
		}
		int correct = 1;

		for (int i = 0; i < n; i++)
		{
			if (Z_c[i] != Z_asm[i])
				correct = 0;
		}

		// will not be necessary if the 3 sizes are the only possible sizes
		int count = min(n, 10);

		for (int i = 0; i < count; i++)
		{
			printf("C: %lf", Z_c[i]);
			printf("\n");
			printf("ASM: %lf", Z_asm[i]);
			printf("\n");
		}
		if(correct == 1)
			printf("The kernel matches, the x86-64 kernel is correct.\n");
		else
			printf("The kernel does not match, the x86-64 kernel is incorrect.\n");
		printf("Average time C: %lf\n", time_c / 30);
		printf("Average time ASM: %lf\n", time_asm / 30);

		free(X);
		free(Y);
		free(Z_c);
		free(Z_asm);
	}

	return 0;
}

