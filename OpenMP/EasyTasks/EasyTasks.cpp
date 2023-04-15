// EasyTasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tasks.hpp"

int main()
{
    int task_number = 0;
    std::cout << "Enter task number (1-4)" << std::endl;
    std::cin >> task_number;

    if (task_number == 1)
    {
        execute_task1();
    }

    if (task_number == 2)
    {
        execute_task2();
    }
}
