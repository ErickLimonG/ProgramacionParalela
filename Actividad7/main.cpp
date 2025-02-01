#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

class OperacionesMatriciales {
public:
    std::vector<std::vector<int>> crearMatrizAleatoriaOpenMP(int filas, int columnas) {
        std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas));
        #pragma omp parallel for
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                matriz[i][j] = rand();
            }
        }
        return matriz;
    }

    std::vector<std::vector<int>> sumarMatricesOpenMP(const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB) {
        int filas = matrizA.size();
        int columnas = matrizA[0].size();
        std::vector<std::vector<int>> resultado(filas, std::vector<int>(columnas));
        #pragma omp parallel for
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                resultado[i][j] = matrizA[i][j] + matrizB[i][j];
            }
        }
        return resultado;
    }

    std::vector<std::vector<int>> restarMatricesOpenMP(const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB) {
        int filas = matrizA.size();
        int columnas = matrizA[0].size();
        std::vector<std::vector<int>> resultado(filas, std::vector<int>(columnas));
        #pragma omp parallel for
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                resultado[i][j] = matrizA[i][j] - matrizB[i][j];
            }
        }
        return resultado;
    }

    std::vector<std::vector<int>> multiplicarMatricesOpenMP(const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB) {
        int filasA = matrizA.size();
        int columnasA = matrizA[0].size();
        int filasB = matrizB.size();
        int columnasB = matrizB[0].size();


        std::vector<std::vector<int>> resultado(filasA, std::vector<int>(columnasB, 0));

        #pragma omp parallel for
        for (int i = 0; i < filasA; ++i) {
            for (int j = 0; j < columnasB; ++j) {
                for (int k = 0; k < columnasA; ++k) {
                    resultado[i][j] += matrizA[i][k] * matrizB[k][j];
                }
            }
        }

        return resultado;
    }

    std::vector<std::vector<int>> transponerMatrizOpenMP(const std::vector<std::vector<int>>& matriz) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        std::vector<std::vector<int>> transpuesta(columnas, std::vector<int>(filas));
        #pragma omp parallel for
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                transpuesta[j][i] = matriz[i][j];
            }
        }
        return transpuesta;
    }

    void imprimirMatriz(const std::vector<std::vector<int>>& matriz) {
        for (const auto& fila : matriz) {
            for (int elemento : fila) {
                std::cout << elemento << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    srand(time(0));
    OperacionesMatriciales operacionesMatrices;
    std::vector<std::vector<int>> matrizA, matrizB, matrizSeleccionada,resultado;
    int filas, columnas;
    int opcion;
    int matrizSelector;

    do {
        std::cout << "Operaciones"<< std::endl;;
        std::cout << "1. Crear Matrices aleatorias"<< std::endl;
        std::cout << "2. Sumar matrices"<< std::endl;
        std::cout << "3. Restar matrices"<< std::endl;
        std::cout << "4. Multiplicar matrices"<< std::endl;
        std::cout << "5. Transponer matriz"<< std::endl;
        std::cout << "6. Salir"<< std::endl;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese la dimensiond de la matriz ej: 3"<< std::endl;
                std::cin>>filas;
                columnas = filas;
                matrizA = operacionesMatrices.crearMatrizAleatoriaOpenMP(filas, columnas);
                matrizB = operacionesMatrices.crearMatrizAleatoriaOpenMP(filas, columnas);
                std::cout << "Generando matrices ... "<< std::endl;
                std::cout << "Matriz A"<< std::endl;
                operacionesMatrices.imprimirMatriz(matrizA);
                std::cout << "Matriz B"<< std::endl;
                operacionesMatrices.imprimirMatriz(matrizB);
                break;

            case 2:
                if (matrizA.empty() || matrizB.empty()) {
                    std::cout << "Cree primero las matrices" << std::endl;
                } else {
                    double tiempoInicio = omp_get_wtime();
                    resultado = operacionesMatrices.sumarMatricesOpenMP(matrizA, matrizB);
                    double tiempoFin = omp_get_wtime();
                    std::cout << "Resultado de la suma:"<< std::endl;
                    operacionesMatrices.imprimirMatriz(resultado);
                    std::cout << "Tiempo de ejecución=" << tiempoFin - tiempoInicio << " segundos"<< std::endl;
                }
                break;

            case 3:
                if (matrizA.empty() || matrizB.empty()) {
                    std::cout << "Cree primero las matrices" << std::endl;
                } else {
                    double tiempoInicio = omp_get_wtime();
                    resultado = operacionesMatrices.restarMatricesOpenMP(matrizA, matrizB);
                    double tiempoFin = omp_get_wtime();
                    std::cout << "Resultado de la resta:"<< std::endl;;
                    operacionesMatrices.imprimirMatriz(resultado);
                    std::cout << "Tiempo de ejecución=" << tiempoFin - tiempoInicio << " segundos"<< std::endl;
                }
                break;

            case 4:
                if (matrizA.empty() || matrizB.empty()) {
                    std::cout << "Cree primero las matrices" << std::endl;
                } else {
                    double tiempoInicio = omp_get_wtime();
                    resultado = operacionesMatrices.multiplicarMatricesOpenMP(matrizA, matrizB);
                    double tiempoFin = omp_get_wtime();
                    std::cout << "Resultado de la multiplicación:"<< std::endl;;
                    operacionesMatrices.imprimirMatriz(resultado);
                    std::cout << "Tiempo de ejecución=" << tiempoFin - tiempoInicio << " segundos"<< std::endl;
                }
                break;

            case 5:
                if (matrizA.empty() ) {
                    std::cout << "Cree primero las matrices" << std::endl;
                } else {
                    std::cout << "Elija cual matriz transponer"<<std::endl;
                    std::cout << "1. Matriz A \n2. Matriz B"<<std::endl;
                    std::cin>>matrizSelector;
                    if(matrizSelector == 1 || matrizSelector == 2){
                    double tiempoInicio = omp_get_wtime();
                        if (matrizSelector == 1) {
                            resultado = operacionesMatrices.transponerMatrizOpenMP(matrizA);
                        } else {
                            resultado = operacionesMatrices.transponerMatrizOpenMP(matrizB);
                        }
                        double tiempoFin = omp_get_wtime();
                        std::cout << "Matriz transpuesta:"<< std::endl;;
                        operacionesMatrices.imprimirMatriz(resultado);
                        std::cout << "Tiempo de ejecución=" << tiempoFin - tiempoInicio << " segundos"<< std::endl;
                    }else{
                        std::cout << "Opcion no valida" << std::endl;
                        break;
                    }

                }
                break;

            case 6:
                std::cout << "Terminando programa" << std::endl;;
                break;

            default:
                std::cout << "Opcion no valida" << std::endl;;
                break;
        }
    } while (opcion != 6);

    return 0;
}
