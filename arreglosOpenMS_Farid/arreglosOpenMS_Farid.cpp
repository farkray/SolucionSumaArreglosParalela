// arreglosOpenMS_Farid.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
// Tarea Cloud Computing
// Alumno: Farid Krayem Pineda
// Matricula: A00506281

#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL)); // Inicializar la semilla del generador de números aleatorios (para cumplir requerimientos de la tarea)

    const int SIZE = 1000;
    vector<int> array1(SIZE), array2(SIZE), sumArray(SIZE);

    // Preguntar al usuario cuántos hilos desea usar
    int nHilos;
    cout << "Ingrese el numero de hilos a usar: ";
    cin >> nHilos;

    // Establecer el número de hilos para OpenMP
    omp_set_num_threads(nHilos);

    // Llenar los arreglos con valores aleatorios
    for (int i = 0; i < SIZE; ++i) {
        array1[i] = rand() % 100;
        array2[i] = rand() % 100;
    }

    // Sumar los arreglos usando OpenMP
#pragma omp parallel for
    for (int i = 0; i < SIZE; ++i) {
        int tid = omp_get_thread_num(); // Obtener el ID del hilo
#pragma omp critical
        {
            cout << "El hilo " << tid << " comienza a trabajar en la iteracion " << i << endl;
        }

        sumArray[i] = array1[i] + array2[i];

#pragma omp critical
        {
            cout << "El hilo " << tid << " termino de trabajar en la iteracion " << i << endl;
        }
    }

    // Imprimir parte de los arreglos para verificar
    for (int i = 0; i < 10; ++i) {
        cout << array1[i] << " + " << array2[i] << " = " << sumArray[i] << endl;
    }

    // Imprimir el número de hilos usados
    cout << "Este proceso se ejecuto usando " << nHilos << " hilos" << endl;

    return 0;
}
