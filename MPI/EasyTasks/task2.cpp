#include <mpi.h>
#include <iostream>


/*
Cмоделировать последовательный обмен сообщениями между двумя процессами, замерить время на одну итерацию обмена.

Вывод:
mpiexec -n 2 .\EasyTasks.exe
Process 0 sent message. Seconds: 0.0002165
Process 1 received message. Seconds: 0.000522
*/

const int TAG = 7;

void execute_task2(int argc, char* argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int message = 0;

    if (rank == 0) {
        message = 111;
        double start_time = MPI_Wtime();
        MPI_Send(&message, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
        double end_time = MPI_Wtime();
        std::cout << "Process " << rank << " sent message." << " Seconds: " << end_time - start_time << std::endl;
    }
    else if (rank == 1) { // второй процесс принимает сообщение от первого процесса
        double start_time = MPI_Wtime();
        MPI_Recv(&message, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double end_time = MPI_Wtime();
        std::cout << "Process " << rank << " received message." << " Seconds: " << end_time - start_time << std::endl;
    }

    MPI_Finalize();
}