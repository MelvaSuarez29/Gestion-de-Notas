#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Estructura de materias por semestre
struct MateriaSemestre {
    string codigo, nombre;
    int creditos, horas;
    int semestre; // Semestre 1ero al 5to
};

/* Estructura materia cursada por estudiante */
struct MateriaCursada {
    string codigo, nombre;
    int creditos;
    double nota;            // Nota obtenida
    string periodo;         // Periodo académico (2025-A, 2025-B, etc.)
    string estado;          // Aprobado/Reprobado
    int intentos;           // Número de veces que ha cursado la materia (máximo 3)
    bool aprobada;          // aprobó la materia true o false
};

/*Estructura para almacenar información del estudiante*/ 
struct Estudiante {
    string cedula, nombre, carrera;
    int semestreActual;     // Semestre en el que está matriculado
    vector<MateriaCursada> materiasCursadas; // Historial académico
    double promedioAcumulado;
    int creditosAprobados;
    bool activo;            // Si está cursando la carrera o anuló
};

vector<string> carreras = {"Desarrollo de Software"};

/*Materias por semestre */ 
vector<MateriaSemestre> mallaCurricular = {
    // 1er Semestre 
    {"CSHD111", "Comunicación Oral y Escrita", 1, 48, 1},
    {"MATD143", "Cálculo Diferencial e Integral", 3, 144, 1},
    {"ICOD142", "Introducción a las TICS", 2, 96, 1},
    {"FISD113", "Física", 3, 144, 1},
    {"MATD153", "Estadística y Probabilidad Básica", 3, 144, 2},
    {"ADMD163", "Administración Financiera", 3, 144, 2},
    // 2do semestre
    {"TDSD214", "Programación", 4, 192, 1},
    {"TDSD222", "Algoritmos y Estructuras de Datos", 2, 96, 2},
    {"TDSD232", "Arquitectura de Computadores", 2, 96, 2},
    {"TDSD243", "Redes de Computadores", 3, 144, 2},
    {"AMBD261", "Ecología y Ambiente", 1, 48, 3},
    {"TDSD253", "Sistemas Operativos", 3, 144, 3},
    // 3er semestre
    {"TDSD314", "Programación Orientada a Objetos", 4, 192, 3},
    {"TDSD343", "Bases de Datos", 3, 144, 3},
    {"TDSD322", "Diseño de Interfaces", 2, 96, 4},
    {"TDSD333", "Gestión de Proyectos de Software", 3, 144, 4},
    {"TDSD353", "Análisis de Datos", 3, 144, 4},
    //4to semestre 
    {"TDSD422", "Desarrollo de IoT", 2, 96, 4},
    {"TDSD431", "Fundamentos de Inteligencia Artificial", 1, 48, 4},
    {"ADMD421", "Metodología de la Investigación", 1, 48, 3},
    {"TDSD414", "Desarrollo de Aplicaciones Web", 4, 192, 5},
    //5to semestre 
    
    {"TDSD514", "Desarrollo de Aplicaciones Móviles", 4, 192, 5},
    {"TDSD523", "Aplicaciones Distribuidas", 3, 144, 5},
    {"TDSD532", "Tecnologías de Seguridad", 2, 96, 5},
    
    // Requisitos Finales: practicas y trabajo final
    {"PSCD202", "Prácticas de Servicio Comunitario", 2, 96, 5},
    {"PRLD105", "Prácticas Laborales", 5, 240, 5},
    {"TITD103", "Diseño de Trabajo de Integración Curricular", 3, 144, 5},
    {"TITD201", "Trabajo de Integración Curricular/Examen Complexivo", 5, 240, 5}
};
// Periodos académicos 
vector<string> periodos = {"2024-A", "2024-B", "2025-A", "2025-B", "2026-A", "2026-B"};

vector<Estudiante> estudiantes; //crea lista de estudiantes se va a registrar