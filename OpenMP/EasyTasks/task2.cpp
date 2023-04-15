#include "tasks.hpp"
#include <omp.h>
#include <iostream>

/*
Написать программу, в которой объявлен массив из 16000 элементов и
инициализирован так, что значение элемента массива равно его порядковому номеру.
Затем создайте результирующий массив, в котором (за исключением крайних элементов)
будут средние значения исходного массива:
b[i] = (a[i-1] + a[i] + a[i+1])/3.0
Запустите программу с 8-ю процессами при различных типах распределения работ

вывод:
Static: 0.0007973
Dynamic: 0.0003979
Guided: 6.02e-05
Runtime: 6.53e-05
*/



double calculate(double prev, double next, double current) {
	return (prev + next + current) / 3.0;
}

int execute_task2() {
	int size = 16000;
	double* a = new double[size];
	double* b = new double[size];

	for (int i = 0; i < size; i++) {
		a[i] = i;
	}
	
	double start = omp_get_wtime();
#pragma omp parallel for schedule(static, 8), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = calculate(a[i - 1], a[i+1], a[i]);
	}
	double end = omp_get_wtime();

	std::cout << "Static: " << end - start << std::endl;

	start = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = calculate(a[i - 1], a[i + 1], a[i]);
	}

	end = omp_get_wtime();

	std::cout << "Dynamic: " << end - start << std::endl;

	start = omp_get_wtime();
#pragma omp parallel for schedule(guided, 10), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = calculate(a[i - 1], a[i + 1], a[i]);
	}

	end = omp_get_wtime();

	std::cout << "Guided: " << end - start << std::endl;


	start = omp_get_wtime();
#pragma omp parallel for schedule(runtime), num_threads(8)
	for (int i = 1; i < size - 1; i++) {
		b[i] = calculate(a[i - 1], a[i + 1], a[i]);
	}

	end = omp_get_wtime();

	std::cout << "Runtime: " << end - start << std::endl;

	delete[] a, b;
}