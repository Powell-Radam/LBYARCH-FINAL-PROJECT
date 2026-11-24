/*
* Multiplies X[i] with A then add Y[i] then store it in Z[i]
*/
void cdaxpy(int n, double A, double* X, double* Y, double* Z){
	int i;
	for (i = 0; i < n; i++)
	{
		Z[i] = A * X[i] + Y[i];
	}

}