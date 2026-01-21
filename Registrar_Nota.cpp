#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Función registrar nota del Estudiante 
//Para registrar nota se pregunta la cédula del estudiante 

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
extern MateriaCursada* buscarMateriaCursada(Estudiante* estudiante, string codigo);
extern vector<MateriaSemestre> obtenerMateriasSemestre(int semestre);
extern double validarNota();
extern void crear(string ruta, string informacion);

const string ruta_archivo = "/storage/emulated/0/Download/CodingC++/datos_estudiantes.txt";
extern vector<Estudiante> estudiantes;
extern vector<MateriaSemestre> mallaCurricular;
extern vector<string> periodos;

void registrarNota() {
    cout << "\n=== REGISTRAR NOTA ===" << endl;
    
    string cedula;
    cout << "Cedula del estudiante: ";
    getline(cin, cedula);
    
    Estudiante* estudiante = buscarEstudiante(cedula);
    if (!estudiante) {
        cout << "Estudiante no encontrado" << endl;
        return;
    }
    
    if (!estudiante->activo) {
        cout << "El estudiante no está activo en la carrera" << endl;
        return;
    }
    
    vector<MateriaSemestre> materiasDisponibles = obtenerMateriasSemestre(estudiante->semestreActual);
    
    if (materiasDisponibles.empty()) {
        cout << "No hay materias disponibles para este semestre" << endl;
        return;
    }
    
    cout << "\nMaterias del semestre " << estudiante->semestreActual << ":" << endl;
    cout << "==================================================" << endl;
    for (int i = 0; i < materiasDisponibles.size(); i++) {
        cout << i+1 << ". " << materiasDisponibles[i].codigo << " - " 
             << materiasDisponibles[i].nombre 
             << " (" << materiasDisponibles[i].creditos << " créditos)" << endl;
    }
    
    cout << "\nSeleccione la materia (1-" << materiasDisponibles.size() << "): ";
    int opcionMateria;
    cin >> opcionMateria;
    cin.ignore();
    
    if (opcionMateria < 1 || opcionMateria > materiasDisponibles.size()) {
        cout << "Opción inválida" << endl;
        return;
    }
    
    MateriaSemestre materiaSel = materiasDisponibles[opcionMateria-1];
    
    MateriaCursada* materiaCursada = buscarMateriaCursada(estudiante, materiaSel.codigo);
    if (materiaCursada && materiaCursada->aprobada) {
        cout << "\nEl estudiante ya aprobó esta materia" << endl;
        cout << "Nota anterior: " << materiaCursada->nota << endl;
        cout << "No puede cursarla nuevamente" << endl;
        return;
    }
    
    if (materiaCursada && materiaCursada->intentos >= 3) {
        cout << "\nEl estudiante ha agotado los 3 intentos para esta materia" << endl;
        cout << "Debe solicitar permiso especial para un nuevo intento" << endl;
        return;
    }
    
    cout << "\nPeriodos disponibles:" << endl;
    for (int i = 0; i < periodos.size(); i++) {
        cout << i+1 << ". " << periodos[i] << endl;
    }
    
    int opcionPeriodo;
    while (true) {
        cout << "Seleccione el periodo (1-" << periodos.size() << "): ";
        cin >> opcionPeriodo;
        cin.ignore();
        
        if (opcionPeriodo >= 1 && opcionPeriodo <= periodos.size()) {
            break;
        }
        cout << "Opción inválida" << endl;
    }
    
    string periodoSeleccionado = periodos[opcionPeriodo-1];
    
    cout << "\nREGISTRO DE NOTA" << endl;
    cout << "Materia: " << materiaSel.nombre << endl;
    cout << "Créditos: " << materiaSel.creditos << endl;
    
    double nota = validarNota();
    
    string estado = (nota >= 7.0) ? "Aprobado" : "Reprobado";
    bool aprobada = (nota >= 7.0);
    
    if (materiaCursada) {
        materiaCursada->intentos++;
        materiaCursada->nota = nota;
        materiaCursada->estado = estado;
        materiaCursada->aprobada = aprobada;
        materiaCursada->periodo = periodoSeleccionado;
        
        cout << "\n¡Nota actualizada! Intento #" << materiaCursada->intentos << endl;
    } else {
        MateriaCursada nuevaMateria;
        nuevaMateria.codigo = materiaSel.codigo;
        nuevaMateria.nombre = materiaSel.nombre;
        nuevaMateria.creditos = materiaSel.creditos;
        nuevaMateria.nota = nota;
        nuevaMateria.periodo = periodoSeleccionado;
        nuevaMateria.estado = estado;
        nuevaMateria.intentos = 1;
        nuevaMateria.aprobada = aprobada;
        
        estudiante->materiasCursadas.push_back(nuevaMateria);
        
        cout << "\n¡Nota registrada exitosamente! Intento #1" << endl;
    }
    
    if (aprobada) {
        estudiante->creditosAprobados += materiaSel.creditos;
        
        double sumaNotas = 0.0;
        int totalCreditos = 0;
        
        for (const auto& materia : estudiante->materiasCursadas) {
            if (materia.aprobada) {
                sumaNotas += materia.nota * materia.creditos;
                totalCreditos += materia.creditos;
            }
        }
        
        if (totalCreditos > 0) {
            estudiante->promedioAcumulado = sumaNotas / totalCreditos;
        }
    }
    
    string info = "NOTA REGISTRADA: " + cedula + " - " + materiaSel.codigo + 
                  " - Nota: " + to_string(nota) + " - " + estado;
    crear(ruta_archivo, info);
    
    cout << "Estado: " << estado << endl;
}