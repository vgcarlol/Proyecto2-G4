/*
*----------------------------------------
* PROYECTO 2 GRUPO 4
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programacion de Microprocesadores
* Temario: 4 - Estudio de tiempos y movimientos de ventanillas de LA VAS
* ---------------------------------------
*
* Mathew Cordero 22982
* Josue Say 22801
* Abby Donis 22440
* Carlos Valladares 221164
*----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
using namespace std;
#define tiempo_compass 5 //5 mintuos compass.
#define tiempo_efectivo 10 //10 minutos efectivo. 
int *compass, *efectivo;
int carros_compass;
int carros_efectivo;
int *tiempos_efectivo, *tiempos_compass;
int tiempoTotal;
int Ttiempo;

//void atencion_efectivo();
void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo);
void sumaTiempos();
void llenartiempos();
// Validación de entrada para el número de carros
int getValidIntInput(string prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cout << "Entrada inválida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    return value;
}


int main (){
    // Validación de entrada
    carros_compass = getValidIntInput("Ingrese el número de carros que usan compass: ");
    carros_efectivo = getValidIntInput("Ingrese el número de carros que usan efectivo: ");

    // Procedemos a declararlos.
    compass = new int[carros_compass];
    efectivo = new int[carros_efectivo];
    tiempos_efectivo = new int[3];
    tiempos_compass = new int[3];

    llenartiempos();
    atencion(carros_compass, compass, "compass", tiempos_compass, tiempo_compass);
    atencion(carros_efectivo, efectivo, "efectivo", tiempos_efectivo, tiempo_efectivo);
    sumaTiempos();

}

/// @brief funcion que atiende a los carros. 
/// @param carros 
/// @param array 
/// @param tipo 
/// @param tiempos 
/// @param tipo_tiempo 
void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo){
    int n = carros-1;
    tiempos[0]=0;
    tiempos[1]=0;
    tiempos[2]=0;

    for (int i = 0; i <= n; i+=3)
    {
        #pragma omp sections
        {
            #pragma omp section
            { 
                #pragma omp atomic
                tiempos[0]+=tipo_tiempo;
                cout << "\nEl carro: " << array[i]<< " es atendido en el kisko 1 de tipo "<<tipo<<endl; 
            }
            #pragma omp section
            {
                if(i < n)
                {
                    #pragma omp atomic
                    tiempos[1]+=tipo_tiempo;
                    cout << "\nEl carro: " << array[i+1]<< " es atendido en el kisko 2 de tipo "<<tipo<<endl;
                  
                }
            }
            #pragma omp section
            {
                if(i < n-1)
                {   
                    #pragma omp atomic
                    tiempos[2]+=tipo_tiempo;
                    cout << "\nEl carro: " << array[i+2]<< " es atendido en el kisko 3 de tipo "<<tipo<<endl;
                    
                }
            }
        }

        
    }
    
}

/// @brief funcion que suma todos los tiempos e imprime el tiempo total 
// Suma de tiempos con paralelización
void sumaTiempos() {
    int suma = 0;
    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < 3; i++) {
        suma += tiempos_efectivo[i] + tiempos_compass[i];
    }
    cout << "\nEl tiempo total para atender a " << carros_compass << " carros compass y " << carros_efectivo << " carros efectivo es de: " << suma << " minutos.\n";
}

void llenartiempos(){
    // llenando de los punteros.
    #pragma omp parallel for 
    for (int i =0;i<carros_compass;i++){
        compass[i] = i;
    }

    #pragma omp parallel for
    for (int i =0;i<carros_efectivo;i++){
        efectivo[i] = i;
    }
}