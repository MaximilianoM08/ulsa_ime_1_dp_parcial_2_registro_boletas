#pragma once
#include <iostream>
#include <string>
#include "registro.h"
#include "utilerias.h"


const int CAPTURA_NUM_MATERIAS = 3;


inline std::string capturaNombreMateria(int materia) {
    switch (materia) {
        case 0:  return "Espanol";
        case 1:  return "Matematicas";
        default: return "Diseno de Programas";
    }
}


inline int capturarAlumno(std::string nombres[], double espanol[],
                          double matematicas[], double disenoProgramas[],
                          int total) {
    if (total >= MAX_ALUMNOS) {
        std::cout << "La lista esta llena (" << MAX_ALUMNOS
                  << " alumnos)." << std::endl;
        return total;
    }

    std::string nombre = leerCadena("Nombre: ");
    
    while (nombre.empty()) {
        std::cout << "El nombre no puede quedar vacio." << std::endl;
        nombre = leerCadena("Nombre: ");
    }

    double cal[CAPTURA_NUM_MATERIAS];
    for (int i = 0; i < CAPTURA_NUM_MATERIAS; i++) {
        std::string materia = capturaNombreMateria(i);
        cal[i] = leerDecimal(materia + ": ");
        while (!calificacionValida(cal[i])) {
            std::cout << "Calificacion invalida. Debe estar entre 0 y 10." << std::endl;
            cal[i] = leerDecimal(materia + ": ");
        }
    }

    int nuevoTotal = agregarAlumno(nombres, espanol, matematicas,
                                   disenoProgramas, total, nombre,
                                   cal[0], cal[1], cal[2]);
    std::cout << "Alumno " << nuevoTotal << " registrado." << std::endl;
    return nuevoTotal;
}

