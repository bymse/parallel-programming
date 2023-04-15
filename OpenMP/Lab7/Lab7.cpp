#include <iostream>
#include <omp.h>

int main()
{
    std::cout << "Enter matrix size" << std::endl;
    int size;

    std::cin >> size;
	double** A = new double* [size];

    for (int i = 0; i < size; i++)
    {
        A[i] = new double [size];
        for (int j = 0; j < size; j++)
        {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }
    double start_time = omp_get_wtime();
    double det = 1;
#pragma omp parallel for shared(A,det)
    for (int i = 0; i < size - 1; i++)
    {
        int max_row = i;
        for (int j = i + 1; j < size; j++)
        {
            if (fabs(A[j][i]) > fabs(A[max_row][i]))
            {
                max_row = j;
            }
        }
        if (max_row != i)
        {
            std::swap(A[i], A[max_row]);
            det *= -1;
        }

#pragma omp parallel for shared(A,det)
        for (int j = i + 1; j < size; j++)
        {
            double factor = A[j][i] / A[i][i];
            for (int k = i + 1; k < size; k++)
            {
                A[j][k] -= factor * A[i][k];
            }
            A[j][i] = 0;
        }
    }

    double det_diag = 1.0;
#pragma omp parallel for shared(A) reduction(*:det_diag)
    for (int i = 0; i < size; i++)
    {
        det_diag *= A[i][i];
    }
    det *= det_diag;
    double end_time = omp_get_wtime();

    std::cout << "Determinant of the matrix: " << det << std::endl;
    std::cout << "Time: " << end_time - start_time << std::endl;

    for (int i = 0; i < size; i++) {
        delete[] A[i];
    }

    delete[] A;
}


