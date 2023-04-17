#include <mpi.h>
#include <iostream>

/*
Определить максимально допустимую длину посылаемого сообщения

вывод:
mpiexec -n 2 .\EasyTasks.exe
...
Send: 1672938532
Send: 1672939532

job aborted:
[ranks] message

[0] terminated

[1] process exited without calling finalize

Пояснение:
Размер сообщения в MPI ограничен двумя вещами:
- сигнатурой функций, который используют int
- доступной памятью машины (или максимально разрешенной для конкретного процесса)

например, моей машине поцессы крашились после достижения размера в 1672939532 байта
в тоже время, сам запуск стал работать нестабильно после превышения запрашиваемой памяти в 1.5 Гб на процесс (процесса запускается два).

*/

void execute_task4(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size, max_len;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (max_len = INT_MAX / 2; max_len < INT_MAX; max_len += 10000) {
        char* message = new char[max_len];
        if (rank == 0) {
            std::cout << "Send: " << max_len << std::endl;
            MPI_Send(message, max_len, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }
        else if (rank == 1) {
            MPI_Status status;
            MPI_Recv(message, max_len, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
            int received_len;
            MPI_Get_count(&status, MPI_CHAR, &received_len);
            if (received_len != max_len) {
                std::cout << "Message was truncated to length: " << received_len << std::endl;
                break;
            }
        }
    }
    delete[] message;

    if (rank == 0) {
        std::cout << "Max message length: " << max_len << std::endl;
    }

    MPI_Finalize();
}
