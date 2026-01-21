#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
//Función Actualizar estudiante 
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern Estudiante* buscarEstudiante(string cedula);
extern int validarSemestre();
extern void crear(string ruta, string informacion);

const string ruta_archivo = "/storage/emulated/0/Download/CodingC++/datos_estudiantes.txt";
extern vector<Estudiante> estudiantes;

void actualizarEstudiante() {
    cout << "\n=== ACTUALIZAR ESTUDIANTE ===" << endl;
    
    string cedula;
    cout << "Cedula del estudiante: ";
    getline(cin, cedula);
    
    Estudiante* estudiante = buscarEstudiante(cedula);
    if (!estudiante) {
        cout << "Estudiante no encontrado" << endl;
        return;
    }
    
    cout << "\nEstudiante: " << estudiante->nombre << endl;
    cout << "Semestre actual: " << estudiante->semestreActual << endl;
    cout << "Estado: " << (estudiante->activo ? "ACTIVO" : "INACTIVO") << endl;
    
    cout << "\n¿Qué desea actualizar?" << endl;
    cout << "1. Semestre actual" << endl;
    cout << "2. Estado (Activo/Inactivo)" << endl;
    cout << "3. Cancelar" << endl;
    cout << "Opción: ";
    
    int opcion;
    cin >> opcion;
    cin.ignore();
    
    switch(opcion) {
        case 1:
            cout << "\nNuevo semestre (1-5): ";
            estudiante->semestreActual = validarSemestre();
            
            crear(ruta_archivo, "ACTUALIZACION: " + cedula + " - Nuevo semestre: " + to_string(estudiante->semestreActual));
            
            cout << "Semestre actualizado correctamente" << endl;
            break;
            
        case 2: {
            char respuesta;
            cout << "\n¿Está activo en la carrera? (S/N): ";
            cin >> respuesta;
            cin.ignore();
            estudiante->activo = (toupper(respuesta) == 'S');
            
            string estado = estudiante->activo ? "ACTIVO" : "INACTIVO";
            crear(ruta_archivo, "ACTUALIZACION: " + cedula + " - Nuevo estado: " + estado);
            
            cout << "Estado actualizado correctamente" << endl;
            break;
        }
            
        case 3:
            cout << "Actualización cancelada" << endl;
            return;
            
        default:
            cout << "Opción inválida" << endl;
    }
}