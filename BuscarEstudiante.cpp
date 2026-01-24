#include <vector>
#include <string>
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

Estudiante* buscarEstudiante(string cedula) {
    for (auto& estudiante : estudiantes) {
        if (estudiante.cedula == cedula) {
            return &estudiante;
        }
    }
    return nullptr;
}