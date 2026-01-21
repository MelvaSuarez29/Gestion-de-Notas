#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Función crear estudiantes 
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<struct MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern bool cedulaValida(string cedula);
extern bool validarNombre(string nombre);
extern int validarSemestre();
extern Estudiante* buscarEstudiante(string cedula);
extern void crear(string ruta, string informacion);

const string ruta_archivo = "/storage/emulated/0/Download/CodingC++/datos_estudiantes.txt";
extern vector<Estudiante> estudiantes;

void crearEstudiante() {
    cout << "\n=== CREAR NUEVO ESTUDIANTE ===" << endl;
    
    Estudiante nuevo;
    
    while (true) {
        cout << "Cedula: ";
        getline(cin, nuevo.cedula);
        
        if (!cedulaValida(nuevo.cedula)) {
            continue;
        }
        
        if (buscarEstudiante(nuevo.cedula) != nullptr) {
            cout << "Error: Ya existe un estudiante con esta cedula" << endl;
        } else {
            break;
        }
    }
    
    while (true) {
        cout << "Nombre completo: ";
        getline(cin, nuevo.nombre);
        
        if (validarNombre(nuevo.nombre)) break;
    }
    
    nuevo.carrera = "Desarrollo de Software";
    
    cout << "\nSemestre de ingreso:" << endl;
    nuevo.semestreActual = validarSemestre();
    
    nuevo.promedioAcumulado = 0.0;
    nuevo.creditosAprobados = 0;
    nuevo.activo = true;
    
    estudiantes.push_back(nuevo);
    
    string info = "NUEVO ESTUDIANTE: " + nuevo.cedula + " - " + nuevo.nombre + 
                  " - Semestre: " + to_string(nuevo.semestreActual);
    crear(ruta_archivo, info);
    
    cout << "\n¡Estudiante creado exitosamente!" << endl;
    cout << "Carrera: Desarrollo de Software" << endl;
    cout << "Semestre: " << nuevo.semestreActual << endl;
    cout << "Cédula: " << nuevo.cedula << endl;
}