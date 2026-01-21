#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Función para visualizar materias pendientes 
struct MateriaSemestre {
    string codigo, nombre;
    int creditos, horas;
    int semestre;
};

struct MateriaCursada {
    string codigo, nombre;
    int creditos;
    double nota;
    string periodo;
    string estado;
    int intentos;
    bool aprobada;
};

struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;
    vector<MateriaCursada> materiasCursadas;
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;
};

extern Estudiante* buscarEstudiante(string cedula);
extern vector<MateriaSemestre> obtenerMateriasSemestre(int semestre);

void verMateriasPendientes() {
    cout << "\n=== MATERIAS PENDIENTES ===" << endl;
    
    string cedula;
    cout << "Cedula del estudiante: ";
    getline(cin, cedula);
    
    Estudiante* estudiante = buscarEstudiante(cedula);
    if (!estudiante) {
        cout << "Estudiante no encontrado" << endl;
        return;
    }
    
    cout << "\nESTUDIANTE: " << estudiante->nombre << endl;
    cout << "SEMESTRE ACTUAL: " << estudiante->semestreActual << endl;
    cout << "==================================================" << endl;
    
    for (int semestre = 1; semestre <= estudiante->semestreActual; semestre++) {
        vector<MateriaSemestre> materiasSemestre = obtenerMateriasSemestre(semestre);
        
        cout << "\nSEMESTRE " << semestre << ":" << endl;
        cout << "--------------------------------------------------" << endl;
        
        bool tienePendientes = false;
        
        for (const auto& materia : materiasSemestre) {
            bool aprobada = false;
            
            for (const auto& materiaCursada : estudiante->materiasCursadas) {
                if (materiaCursada.codigo == materia.codigo && materiaCursada.aprobada) {
                    aprobada = true;
                    break;
                }
            }
            
            if (!aprobada) {
                tienePendientes = true;
                
                bool cursadaAntes = false;
                int intentos = 0;
                
                for (const auto& materiaCursada : estudiante->materiasCursadas) {
                    if (materiaCursada.codigo == materia.codigo) {
                        cursadaAntes = true;
                        intentos = materiaCursada.intentos;
                        break;
                    }
                }
                
                cout << materia.codigo << " - " << materia.nombre 
                     << " (" << materia.creditos << " créditos)";
                
                if (cursadaAntes) {
                    cout << " - Cursada " << intentos << " vez(es)";
                    if (intentos >= 3) {
                        cout << " - ¡AGOTÓ INTENTOS!";
                    }
                }
                cout << endl;
            }
        }
        
        if (!tienePendientes) {
            cout << "Todas las materias aprobadas ✓" << endl;
        }
    }
}