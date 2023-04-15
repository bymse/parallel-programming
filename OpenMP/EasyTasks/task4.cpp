#include <stdlib.h>
#include <omp.h>
#include <iostream>

/*
Напишите программу перемножения больших матриц. Сравните врем выполнения
последовательной и параллельной программы на 2,4, 8 потоках (процессорах)

вывод:
Single thread: 8.01255
2 threads: 3.67469
4 threads: 1.92849
8 threads: 1.42398

*/

int execute_task4() {
	int size = 1000;
	double** a = new double* [size];
	double** b = new double* [size];
	double** c = new double* [size];

	for (int i = 0; i < size; i++) {
		a[i] = new double[size];
		b[i] = new double[size];
		c[i] = new double[size];
		for (int j = 0; j < size; j++) {
			a[i][j] = (double)rand() / RAND_MAX;
			b[i][j] = (double)rand() / RAND_MAX;
			c[i][j] = 0.0;
		}
	}

	double start_time = omp_get_wtime();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	double end_time = omp_get_wtime();
	std::cout << "Single thread: " << end_time - start_time << std::endl;


	int num_thread = 8; //2, 4, 8
	omp_set_num_threads(num_thread);
	start_time = omp_get_wtime();
#pragma omp parallel for
	for (int j = 0; j < size; j++) {
		for (int k = 0; k < size; k++) {
			double sum = 0.0;
#pragma omp parallel for reduction(+:sum)
			for (int l = 0; l < size; l++) {
				sum += a[j][l] * b[l][k];
			}
			c[j][k] = sum;
		}
	}
	end_time = omp_get_wtime();
	std::cout << num_thread << " threads: " << end_time - start_time << std::endl;


	for (int i = 0; i < size; i++) {
		delete[] a[i], b[i], c[i];
	}

	delete[] a, b, c;
}