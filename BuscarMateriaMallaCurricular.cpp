#include <vector>
#include <string>
using namespace std;

struct MateriaSemestre {
    string codigo, nombre;
    int creditos, horas;
    int semestre;
};

extern vector<MateriaSemestre> mallaCurricular;

MateriaSemestre* buscarMateriaMalla(string codigo) {
    for (auto& materia : mallaCurricular) {
        if (materia.codigo == codigo) {
            return &materia;
        }
    }
    return nullptr;
}