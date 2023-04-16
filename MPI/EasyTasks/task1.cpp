#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include "tasks.hpp"
#include <iostream>

/*
Реализовать программу, в которой каждый процесс печатает число процессов в группе и свой номер в ней
вывод:
mpiexec -n 5 .\EasyTasks.exe
Count: 5
Count: 5
Count: 5
Count: 5
Count: 5
Current number: 1
Current number: 0
Current number: 4
Current number: 3
Current number: 2
*/

void execute_task1(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << "Count: " << size << std::endl;
    std::cout << "Current number: " << rank << std::endl;
    MPI_Finalize();
}