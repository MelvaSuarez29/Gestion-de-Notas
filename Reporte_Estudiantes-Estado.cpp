#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
//Función reporte de estudiantes: 
/*1. ver estudiantes registrados
2. Estudiantes estado activo o no
3. cantidadde estudiantesregistradospor semestre*/
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern vector<Estudiante> estudiantes;

void reporteEstudiantesPorEstado() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados" << endl;
        return;
    }
    
    int activos = 0, inactivos = 0;
    int totalEstudiantes = estudiantes.size();
    
    cout << "\n=== REPORTE DE ESTUDIANTES POR ESTADO ===" << endl;
    cout << "==================================================" << endl;
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.activo) activos++;
        else inactivos++;
    }
    
    cout << "TOTAL ESTUDIANTES: " << totalEstudiantes << endl;
    cout << "ESTUDIANTES ACTIVOS: " << activos << " (" << fixed << setprecision(1) << (activos * 100.0 / totalEstudiantes) << "%)" << endl;
    cout << "ESTUDIANTES INACTIVOS: " << inactivos << " (" << fixed << setprecision(1) << (inactivos * 100.0 / totalEstudiantes) << "%)" << endl;
    
    cout << "\nDISTRIBUCIÓN POR SEMESTRE:" << endl;
    cout << "--------------------------------------------------" << endl;
    
    vector<int> estudiantesPorSemestre(6, 0);
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.activo && estudiante.semestreActual >= 1 && estudiante.semestreActual <= 5) {
            estudiantesPorSemestre[estudiante.semestreActual]++;
        }
    }
    
    for (int i = 1; i <= 5; i++) {
        cout << "Semestre " << i << ": " << estudiantesPorSemestre[i] << " estudiantes" << endl;
    }
}