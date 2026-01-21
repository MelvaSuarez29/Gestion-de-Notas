#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
// Función ver Estudiante registrado
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern vector<Estudiante> estudiantes;

void verEstudiantes() {
    if (estudiantes.empty()) {
        cout << "\nNo hay estudiantes registrados" << endl;
        return;
    }
    
    cout << "\n=== LISTA DE ESTUDIANTES ===" << endl;
    cout << "================================================================================" << endl;
    cout << left << setw(12) << "CEDULA" 
         << setw(25) << "NOMBRE" 
         << setw(8) << "SEM." 
         << setw(12) << "PROMEDIO" 
         << setw(10) << "CRED. APROB" 
         << setw(8) << "ESTADO" << endl;
    cout << "================================================================================" << endl;
    
    for (const auto& estudiante : estudiantes) {
        cout << left << setw(12) << estudiante.cedula
             << setw(25) << (estudiante.nombre.length() > 24 ? estudiante.nombre.substr(0, 24) + "." : estudiante.nombre)
             << setw(8) << estudiante.semestreActual
             << setw(12) << fixed << setprecision(2) << estudiante.promedioAcumulado
             << setw(10) << estudiante.creditosAprobados
             << setw(8) << (estudiante.activo ? "ACTIVO" : "INACTIVO") << endl;
    }
}