#pragma once
#include <iostream>
#include <string>
#include "registro.h"
#include "utilerias.h"


void mostrarBoleta(const std::string nombres[],
    const double espanol[],
    const double matematicas[],
    const double disenoProgramas[],
    int total) {
    if (total == 0) {
        std::cout << "No hay alumnos registrados.\n";
        return;
    }

    std::string nombreBuscado = leerCadena("Nombre a buscar: ");
    int indice = -1;

    for (int i = 0; i < total; ++i){
        if (nombres[i] == nombreBuscado){
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        std::cout << "No se encontro al alumno: " << nombreBuscado << ".\n";
        return;
    }

    double promedio = (espanol[indice] + matematicas[indice] + disenoProgramas[indice]) / 3.0;
    int materiasReprobadas = 0;
    if (espanol[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;
    if (matematicas[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;
    if (disenoProgramas[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;
    
    std::cout << "--- BOLETA ---\n";
    std::cout << "Alumno: " << nombres[indice] << ":\n";
    std::cout << "Espanol: " << espanol[indice] << "    Matematicas: " << matematicas[indice] << "  Diseno de Programas: " << disenoProgramas[indice] << "\n";
    std::cout << "Promedio: " << (promedio) << "    Materias Reprobadas: " << materiasReprobadas;
    std::cout << "  Estado: " << ((promedio >= CALIFICACION_APROBATORIA && materiasReprobadas == 0) ? "Aprobado" : "Reprobado") << "\n";
}