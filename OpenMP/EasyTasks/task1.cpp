
#include <omp.h>
#include <iostream>
#include "tasks.hpp"

/*
Написать программу где каждый поток печатает свой идентификатор, количество
потоков всего и строчку «Hello World». Запустить программу с 8 потоками. Всегда ли
вывод идентичен? Почему?

Пример вывода: 
Hello world | thread id: 0 | threads: 8
Hello world | thread id: 1 | threads: 8
Hello world | thread id: 2 | threads: 8
Hello world | thread id: 3 | threads: 8
Hello world | thread id: 4 | threads: 8
Hello world | thread id: 5 | threads: 8
Hello world | thread id: 6 | threads: 8
Hello world | thread id: 7 | threads: 8

1. Вывод не идентичиен
2. Потому что потоки с разными идентифкаторами могут начать выполняться в разное время в зависмости от доступныъ ресурсов и фазы луны.

*/

int execute_task1() {
#pragma omp parallel num_threads(8)
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_num_threads();

        //cout приводит к перемешиванию частей разных строк
        printf("Hello world | thread id: %d | threads: %d\n", thread_id, thread_count);
    }
    return 0;
}