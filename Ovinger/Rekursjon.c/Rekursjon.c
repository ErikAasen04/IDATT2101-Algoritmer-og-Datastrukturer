#include <stdio.h>
#include <time.h>
#include <math.h>


double method1(double x, int n) {
	if (n == 1) {
		return x;
	}
	else {
		return x * method1(x, n - 1);
	}
}

double method2(double x, int n) {
	if (n == 1) {
		return x;
	}
	else if (n & 1) {
		return x * method2(x * x, (n - 1) / 2);
	}
	else {
		return method2(x * x, n / 2);
	}
}

double method3(double x, int n) {
	return pow(x, n);
}

int main() {
	double x_value = 1.002;
	int n_value = 3000;
	int repetetisions = 1000000;

	double result1 = method1(x_value, n_value);
	double result2 = method2(x_value, n_value);
	double result3 = method3(x_value, n_value);

	clock_t start1 = clock();

	for (int i = 0; i < repetetisions; i++) {
		method1(x_value, n_value);
	}

	clock_t end1 = clock();

	clock_t start2 = clock();

	for (int i = 0; i < repetetisions; i++) {
		method2(x_value, n_value);
	}

	clock_t end2 = clock();

	clock_t start3 = clock();

	for (int i = 0; i < repetetisions; i++) {
		method3(x_value, n_value);
	}

	clock_t end3 = clock();

	double time_spent1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
	double time_spent2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	double time_spent3 = (double)(end3 - start3) / CLOCKS_PER_SEC;

	printf("%f opphoyd i %d er %f ved bruk av metode 1\n", x_value, n_value, result1);
	printf("Tid brukt paa %d repetisjoner: %f\n\n", repetetisions, time_spent1);

	printf("%f opphoyd i %d er %f ved bruk av metode 2\n", x_value, n_value, result2);
	printf("Tid brukt paa %d repetisjoner: %f\n\n", repetetisions, time_spent2);

	printf("%f opphoyd i %d er %f ved bruk av metode 3\n", x_value, n_value, result3);
	printf("Tid brukt paa %d repetisjoner: %f\n", repetetisions, time_spent3);

	return 0;

}