
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
using namespace std::chrono;

#include <stdio.h>
#include <cuda_runtime.h>

#define N 500

__global__ void gaussian_elimination(float* A, int pivot)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < N)
    {
        for (int i = pivot + 1; i < N; i++)
        {
            float factor = A[i * N + pivot] / A[pivot * N + pivot];
            for (int j = pivot; j < N; j++)
            {
                A[i * N + j] -= factor * A[pivot * N + j];
            }
        }
    }
}

int main()
{
    float *A = new float[N * N];
    float det = 1.0;

    for (int i = 0; i < N * N; i++)
    {
        A[i] = rand() % 100;
    }


    float* d_A;
    cudaMalloc((void**)&d_A, N * N * sizeof(float));

    // Copy data to device memory
    cudaMemcpy(d_A, A, N * N * sizeof(float), cudaMemcpyHostToDevice);

    auto start = high_resolution_clock::now();
    // Gaussian elimination
    for (int i = 0; i < N; i++)
    {
        gaussian_elimination << <1, N >> > (d_A, i);
    }

    // Copy data back to host memory
    cudaMemcpy(A, d_A, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Calculate determinant
    for (int i = 0; i < N; i++)
    {
        det *= A[i * N + i];
    }

    auto stop = high_resolution_clock::now();

    cudaFree(d_A);

    std::cout << "Determinant: " << det << std::endl;

   
    auto duration = duration_cast<seconds>(stop - start).count();

    std::cout << "Seconds: " << duration << std::endl;

    delete[] A;

    return 0;
}