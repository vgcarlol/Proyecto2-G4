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

//void atencion_efectivo();
void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo);

int main (){

    //Pedimos los datos que necesitamos. 
    cout << "Ingrese el numero de carros que usan compass: ";
    cin >> carros_compass;
    cout << "Ingrese el numero de carros que usan efectivo: ";
    cin >> carros_efectivo;

    // procedemos a declararlos.
    compass = new int[carros_compass];
    efectivo = new int[carros_efectivo];
    tiempos_efectivo = new int[3];
    tiempos_compass = new int[3];
    
    // llenando de los punteros. 
    for (int i =0;i<carros_compass;i++){
        compass[i] = i;
    }

    for (int i =0;i<carros_efectivo;i++){
        efectivo[i] = i;
    }

    
    //Realizaremos 2 tareas que llevan a cabo esto. 
    //
    atencion(carros_compass,compass,"compass",tiempos_compass,tiempo_compass);
}

void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo){
    int n = carros-1;
    for (int i = 0; i <= n; i+=3)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                tiempoTotal += tipo_tiempo;
                tiempos[0]+=tipo_tiempo;
                cout << "El carro: " << array[i]<< " es atendido en el kisko 1 de tipo "<<tipo<< endl;
                
            }
            #pragma omp section
            {
                if(i < n)
                {
                    tiempoTotal += tipo_tiempo;
                    tiempos[1]+=tipo_tiempo;
                    cout << "El carro: " << array[i+1]<< " es atendido en el kisko 2 de tipo "<<tipo<< endl;
                }
            }
            #pragma omp section
            {
                if(i < n-1)
                {
                    tiempoTotal += tipo_tiempo;
                    tiempos[2]+=tipo_tiempo;
                    cout << "El carro: " << array[i+2]<< " es atendido en el kisko 3 de tipo "<<tipo<< endl;
                }
            }
        }

        
    }
    
}