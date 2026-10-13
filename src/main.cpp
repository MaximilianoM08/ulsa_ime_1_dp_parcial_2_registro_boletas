// Proyecto Parcial 2: Sistema de Registro y Boletas de un Grupo Escolar
// Programa principal (bloque de integracion, de todo el equipo).
//
// Compilar (desde la carpeta del proyecto):
//   g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o boletas
// Ejecutar:
//   ./boletas
//
// Lean PROYECTO.md antes de escribir codigo.

#include <iostream>
#include <iomanip>
#include <string>

#include "utilerias.h"
#include "registro.h"

void mostrarMenu() {
    std::cout << "\n1. Capturar alumno\n";
    std::cout << "2. Mostrar lista\n";
    std::cout << "3. Estadisticas por materia\n";
    std::cout << "4. Aprobados y reprobados\n";
    std::cout << "5. Boleta individual\n";
    std::cout << "6. Materias reprobadas por alumno\n";
    std::cout << "7. Salir\n";
}

void mostrarEstadisticas(const std::string nombres[],
    const double espanol[],
    const double matematicas[],
    const double disenoProgramas[],
    int total) {
    (void)nombres;

    if (total == 0) {
        std::cout << "No hay alumnos registrados.\n";
        return;
    }

    double sumaEspanol = 0.0;
    double sumaMatematicas = 0.0;
    double sumaDiseno = 0.0;
    double mayorEspanol = espanol[0];
    double menorEspanol = espanol[0];
    double mayorMatematicas = matematicas[0];
    double menorMatematicas = matematicas[0];
    double mayorDiseno = disenoProgramas[0];
    double menorDiseno = disenoProgramas[0];

    for (int i = 0; i < total; ++i) {
        sumaEspanol += espanol[i];
        sumaMatematicas += matematicas[i];
        sumaDiseno += disenoProgramas[i];

        if (espanol[i] > mayorEspanol) mayorEspanol = espanol[i];
        if (espanol[i] < menorEspanol) menorEspanol = espanol[i];
        if (matematicas[i] > mayorMatematicas) mayorMatematicas = matematicas[i];
        if (matematicas[i] < menorMatematicas) menorMatematicas = matematicas[i];
        if (disenoProgramas[i] > mayorDiseno) mayorDiseno = disenoProgramas[i];
        if (disenoProgramas[i] < menorDiseno) menorDiseno = disenoProgramas[i];
    }

    std::cout << "--- ESTADISTICAS POR MATERIA ---\n";
    std::cout << "Espanol: " << (sumaEspanol / total) << "\n";
    std::cout << "Matematicas: " << (sumaMatematicas / total) << "\n";
    std::cout << "Diseno de Programas: " << (sumaDiseno / total) << "\n";
    std::cout << "Mas alta: Diseno de Programas (" << mayorDiseno << ")\n";
    std::cout << "Mas baja: Matematicas (" << menorMatematicas << ")\n";
}

void mostrarAprobadosYReprobados(const std::string nombres[],
     const double espanol[],
    const double matematicas[],
    const double disenoProgramas[],
    int total) {
    (void)nombres;

    if (total == 0) {
        std::cout << "No hay alumnos registrados.\n";
        return;
    }

    double aprobadosEspanol = 7;
    double reprobadosEspanol = 6.9;
    double aprobadosMatematicas = 7;
    double reprobadosMatematicas = 6.9;
    double aprobadosDiseno = 7;
    double reprobadosDiseno = 6.9;

    for (int i = 0; i < total; ++i) {
        if (espanol[i] >= CALIFICACION_APROBATORIA) aprobadosEspanol++; else reprobadosEspanol++;
        if (matematicas[i] >= CALIFICACION_APROBATORIA) aprobadosMatematicas++; else reprobadosMatematicas++;
        if (disenoProgramas[i] >= CALIFICACION_APROBATORIA) aprobadosDiseno++; else reprobadosDiseno++;
    }

    std::cout << "--- APROBADOS Y REPROBADOS ---\n";
    std::cout << "Espanol: " << aprobadosEspanol << " aprobados, " << reprobadosEspanol << " reprobados\n";
    std::cout << "Matematicas: " << aprobadosMatematicas << " aprobados, " << reprobadosMatematicas << " reprobados\n";
    std::cout << "Diseno de Programas: " << aprobadosDiseno << " aprobados, " << reprobadosDiseno << " reprobado\n";

    for(int i = 0; i<total; i++) {
        if (espanol[i] > 6 && matematicas[i]>6 && disenoProgramas[i]>6) {
            std::cout << nombres[i] << " Espanol: " << espanol[i] << " Matematicas: " << matematicas[i] << " DP" << disenoProgramas[i] << " APROVADO\n";
        } else {
            std::cout << nombres[i]  << " Espanol: " << espanol[i] << " Matematicas: " << matematicas[i] << " DP" << disenoProgramas[i] << " REPROBADO\n";

        }
    }
}

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

    for (int i = 0; i < total; ++i) {
        if (nombres[i] == nombreBuscado) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        std::cout << "No se encontro al alumno " << nombreBuscado << ".\n";
        return;
    }

    double promedio = (espanol[indice] + matematicas[indice] + disenoProgramas[indice]) / 3.0;
    int materiasReprobadas = 0;
    if (espanol[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;
    if (matematicas[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;
    if (disenoProgramas[indice] < CALIFICACION_APROBATORIA) materiasReprobadas++;


    std::cout << "--- BOLETA ---\n";
    std::cout << "Alumno: " << nombres[indice] << "\n";
    std::cout << "Espanol: " <<  espanol[indice] << "   Matematicas: " << matematicas[indice]
              << "   Diseno de Programas: " <<  (disenoProgramas[indice]) << "\n";
    std::cout << "Promedio: " << (promedio) << "   Materias reprobadas: " << materiasReprobadas;
    std::cout << "   Estado: " << ((promedio >= CALIFICACION_APROBATORIA && materiasReprobadas == 0) ? "Aprobado" : "Reprobado") << "\n";
}

void mostrarMateriasReprobadas(const std::string nombres[],
    const double espanol[],
    const double matematicas[],
    const double disenoProgramas[],
    int total) {
    if (total == 0) {
        std::cout << "No hay alumnos registrados.\n";
        return;
    }

    int alumnosConReprobadas = 0;
    std::cout << "--- MATERIAS REPROBADAS POR ALUMNO ---\n";

    for (int i = 0; i < total; ++i) {
        int reprobadas = 0;
        if (espanol[i] < CALIFICACION_APROBATORIA) reprobadas++;
        if (matematicas[i] < CALIFICACION_APROBATORIA) reprobadas++;
        if (disenoProgramas[i] < CALIFICACION_APROBATORIA) reprobadas++;

        if (reprobadas > 0) {
            std::cout << nombres[i] << "   " << reprobadas << "\n";
            alumnosConReprobadas++;
        }
    }

    std::cout << "Alumnos con materias reprobadas: " << alumnosConReprobadas << "\n";
}

int main() {
    std::string nombres[MAX_ALUMNOS];
    double espanol[MAX_ALUMNOS];
    double matematicas[MAX_ALUMNOS];
    double disenoProgramas[MAX_ALUMNOS];
    int totalAlumnos = 0;

    while (true) {
        mostrarMenu();
        int opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: {
                if (totalAlumnos >= MAX_ALUMNOS) {
                    std::cout << "La lista esta llena (" << MAX_ALUMNOS << " alumnos).\n";
                    break;
                }

                std::string nombre = leerCadena("Nombre: ");
                double calEspanol, calMatematicas, calDiseno;

                while (true) {
                    calEspanol = leerDecimal("Espanol: ");
                    if (calificacionValida(calEspanol)) break;
                    std::cout << "Calificacion invalida. Debe estar entre 0 y 10.\n";
                }
                while (true) {
                    calMatematicas = leerDecimal("Matematicas: ");
                    if (calificacionValida(calMatematicas)) break;
                    std::cout << "Calificacion invalida. Debe estar entre 0 y 10.\n";
                }
                while (true) {
                    calDiseno = leerDecimal("Diseno de Programas: ");
                    if (calificacionValida(calDiseno)) break;
                    std::cout << "Calificacion invalida. Debe estar entre 0 y 10.\n";
                }

                totalAlumnos = agregarAlumno(nombres, espanol, matematicas, disenoProgramas,
                                            totalAlumnos, nombre, calEspanol,
                                            calMatematicas, calDiseno);
                std::cout << "Alumno " << totalAlumnos << " registrado.\n";
                break;
            }
            case 2:
                mostrarLista(nombres, espanol, matematicas, disenoProgramas, totalAlumnos);
                break;
            case 3:
                mostrarEstadisticas(nombres, espanol, matematicas, disenoProgramas, totalAlumnos);
                break;
            case 4:
                mostrarAprobadosYReprobados(nombres, espanol, matematicas, disenoProgramas, totalAlumnos);
                break;
            case 5:
                mostrarBoleta(nombres, espanol, matematicas, disenoProgramas, totalAlumnos);
                break;
            case 6:
                mostrarMateriasReprobadas(nombres, espanol, matematicas, disenoProgramas, totalAlumnos);
                break;
            case 7:
                std::cout << "Hasta luego.\n";
                return 0;
            default:
                std::cout << "Opcion invalida.\n";
                break;
        }
    }

    return 0;
}