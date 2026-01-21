#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
/*Función visualizar el historialacadémico: 
1. visualizardatos registrados, promedio,tipo de estado
2. Historial de materias con calificaciónregistrada y limite de notas permitidas
3. Resumen del semestre cantidaddematerias registradas,  con y sin calificación*/
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
extern MateriaSemestre* buscarMateriaMalla(string codigo);
extern vector<MateriaSemestre> mallaCurricular;

void verHistorialAcademico() {
    cout << "\n=== HISTORIAL ACADÉMICO ===" << endl;
    
    string cedula;
    cout << "Cedula del estudiante: ";
    getline(cin, cedula);
    
    Estudiante* estudiante = buscarEstudiante(cedula);
    if (!estudiante) {
        cout << "Estudiante no encontrado" << endl;
        return;
    }
    
    cout << "\n==================================================" << endl;
    cout << "ESTUDIANTE: " << estudiante->nombre << endl;
    cout << "CEDULA: " << estudiante->cedula << endl;
    cout << "CARRERA: " << estudiante->carrera << endl;
    cout << "SEMESTRE ACTUAL: " << estudiante->semestreActual << endl;
    cout << "PROMEDIO ACUMULADO: " << fixed << setprecision(2) << estudiante->promedioAcumulado << endl;
    cout << "CRÉDITOS APROBADOS: " << estudiante->creditosAprobados << "/75" << endl;
    cout << "ESTADO: " << (estudiante->activo ? "ACTIVO" : "INACTIVO") << endl;
    cout << "==================================================" << endl;
    
    if (estudiante->materiasCursadas.empty()) {
        cout << "\nNo hay materias cursadas registradas" << endl;
        return;
    }
    
    cout << "\nHISTORIAL DE MATERIAS:" << endl;
    cout << "================================================================================" << endl;
    cout << left << setw(10) << "CODIGO" 
         << setw(30) << "MATERIA" 
         << setw(8) << "NOTA" 
         << setw(12) << "ESTADO" 
         << setw(8) << "INTENTOS" 
         << setw(10) << "PERIODO" 
         << setw(8) << "CREDITOS" << endl;
    cout << "================================================================================" << endl;
    
    for (int semestre = 1; semestre <= 5; semestre++) {
        bool tieneMaterias = false;
        
        for (const auto& materia : estudiante->materiasCursadas) {
            MateriaSemestre* materiaMalla = buscarMateriaMalla(materia.codigo);
            if (materiaMalla && materiaMalla->semestre == semestre) {
                if (!tieneMaterias) {
                    cout << "\nSEMESTRE " << semestre << ":" << endl;
                    tieneMaterias = true;
                }
                
                cout << left << setw(10) << materia.codigo
                     << setw(30) << (materia.nombre.length() > 29 ? materia.nombre.substr(0, 29) + "." : materia.nombre)
                     << setw(8) << fixed << setprecision(1) << materia.nota
                     << setw(12) << materia.estado
                     << setw(8) << materia.intentos
                     << setw(10) << materia.periodo
                     << setw(8) << materia.creditos << endl;
            }
        }
    }
    
    cout << "\nRESUMEN POR SEMESTRE:" << endl;
    cout << "==================================================" << endl;
    
    int totalCreditosCarrera = 0;
    for (int semestre = 1; semestre <= 5; semestre++) {
        int creditosSemestre = 0;
        int creditosAprobadosSemestre = 0;
        double promedioSemestre = 0.0;
        int materiasCursadasSemestre = 0;
        
        for (const auto& materia : mallaCurricular) {
            if (materia.semestre == semestre) {
                creditosSemestre += materia.creditos;
                totalCreditosCarrera += materia.creditos;
            }
        }
        
        double sumaNotas = 0.0;
        int creditosCursados = 0;
        
        for (const auto& materia : estudiante->materiasCursadas) {
            MateriaSemestre* materiaMalla = buscarMateriaMalla(materia.codigo);
            if (materiaMalla && materiaMalla->semestre == semestre) {
                materiasCursadasSemestre++;
                creditosCursados += materia.creditos;
                
                if (materia.aprobada) {
                    creditosAprobadosSemestre += materia.creditos;
                    sumaNotas += materia.nota * materia.creditos;
                }
            }
        }
        
        if (creditosCursados > 0) {
            promedioSemestre = sumaNotas / creditosCursados;
        }
        
        cout << "Semestre " << semestre << ": " 
             << creditosAprobadosSemestre << "/" << creditosSemestre 
             << " créditos - Promedio: " << fixed << setprecision(2) << promedioSemestre
             << " - " << materiasCursadasSemestre << " materias cursadas" << endl;
    }
    
    cout << "==================================================" << endl;
    cout << "TOTAL CARRERA: " << estudiante->creditosAprobados << "/75 créditos" << endl;
    
    double progreso = (estudiante->creditosAprobados * 100.0) / 75;
    cout << "PROGRESO: " << fixed << setprecision(1) << progreso << "%" << endl;
    
    if (estudiante->creditosAprobados >= 75) {
        cout << "\n¡EL ESTUDIANTE CUMPLE CON LOS REQUISITOS PARA GRADUARSE!" << endl;
    }
}