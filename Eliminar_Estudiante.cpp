#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;
//Función eliminar estudiante 
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern void crear(string ruta, string informacion);

const string ruta_archivo = "/storage/emulated/0/Download/CodingC++/datos_estudiantes.txt";
extern vector<Estudiante> estudiantes;

void eliminarEstudiante() {
    cout << "\n=== ELIMINAR ESTUDIANTE ===" << endl;
    
    string cedula;
    cout << "Cedula del estudiante a eliminar: ";
    getline(cin, cedula);
    
    auto it = find_if(estudiantes.begin(), estudiantes.end(),
        [&cedula](const Estudiante& e) { return e.cedula == cedula; });
    
    if (it != estudiantes.end()) {
        cout << "\nEstudiante encontrado:" << endl;
        cout << "Nombre: " << it->nombre << endl;
        cout << "Semestre: " << it->semestreActual << endl;
        cout << "Créditos aprobados: " << it->creditosAprobados << endl;
        
        char confirmar;
        cout << "\n¿Está seguro de eliminar este estudiante? (S/N): ";
        cin >> confirmar;
        cin.ignore();
        
        if (toupper(confirmar) == 'S') {
            crear(ruta_archivo, "ELIMINADO: " + cedula + " - " + it->nombre);
            
            estudiantes.erase(it);
            cout << "Estudiante eliminado exitosamente" << endl;
        } else {
            cout << "Eliminación cancelada" << endl;
        }
    } else {
        cout << "Estudiante no encontrado" << endl;
    }
}