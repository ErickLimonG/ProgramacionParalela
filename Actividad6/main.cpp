#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

void printHomiesNames() {
    std::cout << "De La Torre Arias Rafael" << std::endl;
    std::cout << "Limon Guevara Erick Antonio" << std::endl;
    std::cout << "Navarro Camacho Francisco Yahir" << std::endl;
}

void printArray(int* values, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;
}

bool isUnique(int num, int* values, int count) {
    for (int i = 0; i < count; i++) {
        if (values[i] == num) {
            return false;
        }
    }
    return true;
}

int main() {
    printHomiesNames();
    std::cout << "Programa hace arrays de 10 posiciones con cada hilo, lo llena de numeros que no se repiten y los imprime " << std::endl;
    int size = 10;

    srand((time(0)));

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int* values = new int[size];
        int count = 0;

        int seed = (time(0)) + thread_num;
        srand(seed);

        while (count < size) {
            int randNum = rand() + 1;
            if (isUnique(randNum, values, count)) {
                values[count] = randNum;
                count++;

                #pragma omp critical
                {
                    std::cout << "Hilo " << thread_num << ": " << (count * 100 / size) << "% completado" << std::endl;
                }
            }
        }

        #pragma omp critical
        {
            std::cout << "Array del hilo " << thread_num << ": ";
            printArray(values, size);
        }

        delete[] values;
    }

    return 0;
}
