#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern vector<Estudiante> estudiantes;

void reporteRendimientoAcademico() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados" << endl;
        return;
    }
    
    cout << "\n=== REPORTE DE RENDIMIENTO ACADÉMICO ===" << endl;
    cout << "================================================================================" << endl;
    
    int excelentes = 0;
    int buenos = 0;
    int regulares = 0;
    int deficientes = 0;
    int sinNotas = 0;
    
    double promedioGeneral = 0.0;
    int estudiantesConNotas = 0;
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.creditosAprobados > 0) {
            estudiantesConNotas++;
            promedioGeneral += estudiante.promedioAcumulado;
            
            if (estudiante.promedioAcumulado >= 9.0) excelentes++;
            else if (estudiante.promedioAcumulado >= 7.0) buenos++;
            else if (estudiante.promedioAcumulado >= 5.0) regulares++;
            else deficientes++;
        } else {
            sinNotas++;
        }
    }
    
    if (estudiantesConNotas > 0) {
        promedioGeneral /= estudiantesConNotas;
    }
    
    cout << "TOTAL ESTUDIANTES: " << estudiantes.size() << endl;
    cout << "ESTUDIANTES CON NOTAS: " << estudiantesConNotas << endl;
    cout << "PROMEDIO GENERAL: " << fixed << setprecision(2) << promedioGeneral << endl;
    
    cout << "\nDISTRIBUCIÓN POR RENDIMIENTO:" << endl;
    cout << "Excelente (>=9.0): " << excelentes << " estudiantes" << endl;
    cout << "Bueno (7.0-8.9): " << buenos << " estudiantes" << endl;
    cout << "Regular (5.0-6.9): " << regulares << " estudiantes" << endl;
    cout << "Deficiente (<5.0): " << deficientes << " estudiantes" << endl;
    cout << "Sin notas registradas: " << sinNotas << " estudiantes" << endl;
}