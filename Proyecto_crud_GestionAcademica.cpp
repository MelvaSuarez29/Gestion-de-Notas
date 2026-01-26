#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cctype>

using namespace std;

const string ruta_archivo= "C:/Users/Patricio/Downloads/Proyecto/Gestion_Academica.txt" ;

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

vector<string> carreras = {"Desarrollo de Software"};

vector<MateriaSemestre> mallaCurricular = {
    // 1er Semestre 
    {"CSHD111", "Comunicación Oral y Escrita", 1, 48, 1},
    {"MATD143", "Cálculo Diferencial e Integral", 3, 144, 1},
    {"ICOD142", "Introducción a las TICS", 2, 96, 1},
    {"FISD113", "Física", 3, 144, 1},
    {"MATD153", "Estadística y Probabilidad Básica", 3, 144, 1},
    {"ADMD163", "Administración Financiera", 3, 144, 1},
    // 2do semestre
    {"TDSD214", "Programación", 4, 192, 2},
    {"TDSD222", "Algoritmos y Estructuras de Datos", 2, 96, 2},
    {"TDSD232", "Arquitectura de Computadores", 2, 96, 2},
    {"TDSD243", "Redes de Computadores", 3, 144, 2},
    {"AMBD261", "Ecología y Ambiente", 1, 48, 2},
    {"TDSD253", "Sistemas Operativos", 3, 144, 2},
    // 3er semestre
    {"TDSD314", "Programación Orientada a Objetos", 4, 192, 3},
    {"TDSD343", "Bases de Datos", 3, 144, 3},
    {"TDSD322", "Diseño de Interfaces", 2, 96, 3},
    {"TDSD333", "Gestión de Proyectos de Software", 3, 144, 3},
    {"TDSD353", "Análisis de Datos", 3, 144, 3},
    //4to semestre 
    {"TDSD422", "Desarrollo de IoT", 2, 96, 4},
    {"TDSD431", "Fundamentos de Inteligencia Artificial", 1, 48, 4},
    {"ADMD421", "Metodología de la Investigación", 1, 48, 4},
    {"TDSD414", "Desarrollo de Aplicaciones Web", 4, 192, 4},
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

vector<string> periodos = {"2024-A", "2024-B", "2025-A", "2025-B", "2026-A", "2026-B"};

vector<Estudiante> estudiantes;

bool login() {
    string usuario, clave;
    int intentos = 3;
    
    while (intentos > 0) {
        cout << "\n=== SISTEMA DE GESTIÓN ACADÉMICA ===" << endl;
        cout << "=== LOGIN ===" << endl;
        cout << "Usuario: ";
        getline(cin, usuario);
        cout << "Clave: ";
        getline(cin, clave);
        
        if (usuario == "admin" && clave == "1234") {
            cout << "\n¡Login exitoso!" << endl;
            return true;
        } else {
            intentos--;
            cout << "\nUsuario o clave incorrectos. Intentos restantes: " << intentos << endl;
            if (intentos == 0) {
                cout << "\nAcceso denegado. El sistema se cerrará." << endl;
                return false;
            }
        }
    }
    return false;
}

void crear(string ruta, string informacion) {
    ofstream archivo(ruta, ios::app);
    if (archivo.is_open()) {
        archivo << informacion << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo" << endl;
    }
}

void guardarEstudiantes() {
    ofstream archivo(ruta_archivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo para guardar en: " << ruta_archivo << endl;
        return;
    }
    
    for (const auto& estudiante : estudiantes) {
        string linea = estudiante.cedula + "|" + 
                      estudiante.nombre + "|" + 
                      estudiante.carrera + "|" + 
                      to_string(estudiante.semestreActual) + "|" +
                      to_string(estudiante.promedioAcumulado) + "|" +
                      to_string(estudiante.creditosAprobados) + "|" +
                      (estudiante.activo ? "1" : "0") + "|" +
                      to_string(estudiante.materiasCursadas.size());
        
        for (const auto& materia : estudiante.materiasCursadas) {
            linea += "|" + materia.codigo + "," + 
                    materia.nombre + "," + 
                    to_string(materia.creditos) + "," + 
                    to_string(materia.nota) + "," + 
                    materia.periodo + "," + 
                    materia.estado + "," + 
                    to_string(materia.intentos) + "," + 
                    (materia.aprobada ? "1" : "0");
        }
        
        archivo << linea << endl;
    }
    
    archivo.close();
    cout << "Datos guardados en '" << ruta_archivo << "'" << endl;
}

void cargarEstudiantes() {
    ifstream archivo(ruta_archivo);
    if (!archivo.is_open()) {
        cout << "No se encontró archivo previo. Iniciando sistema nuevo." << endl;
        return;
    }
    
    estudiantes.clear();
    string linea;
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        Estudiante estudiante;
        vector<string> partes;
        string token;
        size_t pos = 0;
        
        while ((pos = linea.find('|')) != string::npos) {
            token = linea.substr(0, pos);
            partes.push_back(token);
            linea.erase(0, pos + 1);
        }
        partes.push_back(linea);
        
        if (partes.size() >= 8) {
            estudiante.cedula = partes[0];
            estudiante.nombre = partes[1];
            estudiante.carrera = partes[2];
            estudiante.semestreActual = stoi(partes[3]);
            estudiante.promedioAcumulado = stod(partes[4]);
            estudiante.creditosAprobados = stoi(partes[5]);
            estudiante.activo = (partes[6] == "1");
            
            int numMaterias = stoi(partes[7]);
            
            for (int i = 0; i < numMaterias && (8 + i) < partes.size(); i++) {
                string materiaStr = partes[8 + i];
                vector<string> datosMateria;
                size_t posM = 0;
                
                while ((posM = materiaStr.find(',')) != string::npos) {
                    token = materiaStr.substr(0, posM);
                    datosMateria.push_back(token);
                    materiaStr.erase(0, posM + 1);
                }
                datosMateria.push_back(materiaStr);
                
                if (datosMateria.size() >= 8) {
                    MateriaCursada materia;
                    materia.codigo = datosMateria[0];
                    materia.nombre = datosMateria[1];
                    materia.creditos = stoi(datosMateria[2]);
                    materia.nota = stod(datosMateria[3]);
                    materia.periodo = datosMateria[4];
                    materia.estado = datosMateria[5];
                    materia.intentos = stoi(datosMateria[6]);
                    materia.aprobada = (datosMateria[7] == "1");
                    
                    estudiante.materiasCursadas.push_back(materia);
                }
            }
            
            estudiantes.push_back(estudiante);
        }
    }
    
    archivo.close();
    cout << "Datos cargados exitosamente. Estudiantes cargados: " << estudiantes.size() << endl;
}

bool cedulaValida(string cedula) {
    if (cedula.length() != 10) {
        cout << "Error: La cedula debe tener 10 digitos" << endl;
        return false;
    }
    
    for (int i = 0; i < 10; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            cout << "Error: La cedula solo debe contener numeros" << endl;
            return false;
        }
    }
    
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (!((provincia >= 1 && provincia <= 24) || provincia == 30)) {
        cout << "Error: Codigo de provincia invalido" << endl;
        return false;
    }
    
    return true;
}

bool esLetraValida(char c) {
    if (isalpha(static_cast<unsigned char>(c))) {
        return true;
    }
    
    if (c == ' ') {
        return true;
    }
    
    unsigned char uc = static_cast<unsigned char>(c);
    
    return (uc == 241 || uc == 209);
}

bool validarNombre(string nombre) {
    if (nombre.empty()) {
        cout << "Error: El nombre no puede estar vacio" << endl;
        return false;
    }
    
    for (char letra : nombre) {
        if (!esLetraValida(letra)) {
            cout << "Error: El nombre solo puede contener letras y espacios" << endl;
            cout << "Caracter invalido encontrado: " << letra << endl;
            return false;
        }
    }
    return true;
}

double validarNota() {
    double nota;
    while (true) {
        cout << "Ingrese la nota (0.0 - 10.0): ";
        cin >> nota;
        
        if (cin.fail() || nota < 0.0 || nota > 10.0) {
            cout << "Nota invalida. Debe ser entre 0.0 y 10.0" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore();
            return nota;
        }
    }
}

int validarSemestre() {
    int semestre;
    while (true) {
        cout << "Ingrese el semestre (1-5): ";
        cin >> semestre;
        
        if (cin.fail() || semestre < 1 || semestre > 5) {
            cout << "Semestre invalido. La carrera tiene 5 semestres" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            cin.ignore();
            return semestre;
        }
    }
}

Estudiante* buscarEstudiante(string cedula) {
    for (auto& estudiante : estudiantes) {
        if (estudiante.cedula == cedula) {
            return &estudiante;
        }
    }
    return nullptr;
}

MateriaSemestre* buscarMateriaMalla(string codigo) {
    for (auto& materia : mallaCurricular) {
        if (materia.codigo == codigo) {
            return &materia;
        }
    }
    return nullptr;
}

MateriaCursada* buscarMateriaCursada(Estudiante* estudiante, string codigo) {
    for (auto& materia : estudiante->materiasCursadas) {
        if (materia.codigo == codigo) {
            return &materia;
        }
    }
    return nullptr;
}

vector<MateriaSemestre> obtenerMateriasSemestre(int semestre) {
    vector<MateriaSemestre> materiasSemestre;
    for (const auto& materia : mallaCurricular) {
        if (materia.semestre == semestre) {
            materiasSemestre.push_back(materia);
        }
    }
    return materiasSemestre;
}

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
            cout << "Todas las materias aprobadas ?" << endl;
        }
    }
}

void reporteEstudiantesPorEstado() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados" << endl;
        return;
    }
    
    int activos = 0, inactivos = 0;
    int totalEstudiantes = estudiantes.size();
    
    cout << "\n=== REPORTE DE ESTUDIANTES POR ESTADO ===" << endl;
    cout << "==================================================" << endl;
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.activo) activos++;
        else inactivos++;
    }
    
    cout << "TOTAL ESTUDIANTES: " << totalEstudiantes << endl;
    cout << "ESTUDIANTES ACTIVOS: " << activos << " (" << fixed << setprecision(1) << (activos * 100.0 / totalEstudiantes) << "%)" << endl;
    cout << "ESTUDIANTES INACTIVOS: " << inactivos << " (" << fixed << setprecision(1) << (inactivos * 100.0 / totalEstudiantes) << "%)" << endl;
    
    cout << "\nDISTRIBUCIÓN POR SEMESTRE:" << endl;
    cout << "--------------------------------------------------" << endl;
    
    vector<int> estudiantesPorSemestre(6, 0);
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.activo && estudiante.semestreActual >= 1 && estudiante.semestreActual <= 5) {
            estudiantesPorSemestre[estudiante.semestreActual]++;
        }
    }
    
    for (int i = 1; i <= 5; i++) {
        cout << "Semestre " << i << ": " << estudiantesPorSemestre[i] << " estudiantes" << endl;
    }
}

void reporteRendimientoAcademico() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados" << endl;
        return;
    }
    
    cout << "\n=== REPORTE DE RENDIMIENTO ACADÉMICO ===" << endl;
    cout << "================================================================================" << endl;
    
    int excelentes = 0;
    int buenos = 0;
    int regulares = 0;
    int deficientes = 0;
    int sinNotas = 0;
    
    double promedioGeneral = 0.0;
    int estudiantesConNotas = 0;
    
    for (const auto& estudiante : estudiantes) {
        if (estudiante.creditosAprobados > 0) {
            estudiantesConNotas++;
            promedioGeneral += estudiante.promedioAcumulado;
            
            if (estudiante.promedioAcumulado >= 9.0) excelentes++;
            else if (estudiante.promedioAcumulado >= 7.0) buenos++;
            else if (estudiante.promedioAcumulado >= 5.0) regulares++;
            else deficientes++;
        } else {
            sinNotas++;
        }
    }
    
    if (estudiantesConNotas > 0) {
        promedioGeneral /= estudiantesConNotas;
    }
    
    cout << "TOTAL ESTUDIANTES: " << estudiantes.size() << endl;
    cout << "ESTUDIANTES CON NOTAS: " << estudiantesConNotas << endl;
    cout << "PROMEDIO GENERAL: " << fixed << setprecision(2) << promedioGeneral << endl;
    
    cout << "\nDISTRIBUCIÓN POR RENDIMIENTO:" << endl;
    cout << "Excelente (>=9.0): " << excelentes << " estudiantes" << endl;
    cout << "Bueno (7.0-8.9): " << buenos << " estudiantes" << endl;
    cout << "Regular (5.0-6.9): " << regulares << " estudiantes" << endl;
    cout << "Deficiente (<5.0): " << deficientes << " estudiantes" << endl;
    cout << "Sin notas registradas: " << sinNotas << " estudiantes" << endl;
}

void mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "  SISTEMA DE GESTIÓN ACADÉMICA" << endl;
    cout << "  Carrera: Desarrollo de Software" << endl;
    cout << "  Pénsum: 2020 - 75 Créditos" << endl;
    cout << "========================================" << endl;
}

void menuPrincipal() {
    int opcion;
    
    cargarEstudiantes();
    
    do {
        mostrarMenuPrincipal();
        
        cout << "\nMENÚ PRINCIPAL:" << endl;
        cout << "1. Gestión de Estudiantes (CRUD)" << endl;
        cout << "2. Gestión Académica" << endl;
        cout << "3. Consultas y Reportes" << endl;
        cout << "4. Archivos" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        
        cin >> opcion;
        cin.ignore();
        
        switch(opcion) {
            case 1: {
                int subopcion;
                do {
                    cout << "\n=== GESTIÓN DE ESTUDIANTES ===" << endl;
                    cout << "1. Crear nuevo estudiante" << endl;
                    cout << "2. Ver todos los estudiantes" << endl;
                    cout << "3. Actualizar estudiante" << endl;
                    cout << "4. Eliminar estudiante" << endl;
                    cout << "5. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    
                    cin >> subopcion;
                    cin.ignore();
                    
                    switch(subopcion) {
                        case 1: crearEstudiante(); break;
                        case 2: verEstudiantes(); break;
                        case 3: actualizarEstudiante(); break;
                        case 4: eliminarEstudiante(); break;
                        case 5: cout << "Volviendo al menú principal..." << endl; break;
                        default: cout << "Opción inválida" << endl;
                    }
                } while(subopcion != 5);
                break;
            }
                
            case 2: {
                int subopcion;
                do {
                    cout << "\n=== GESTIÓN ACADÉMICA ===" << endl;
                    cout << "1. Registrar nota de materia" << endl;
                    cout << "2. Ver historial académico" << endl;
                    cout << "3. Ver materias pendientes" << endl;
                    cout << "4. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    
                    cin >> subopcion;
                    cin.ignore();
                    
                    switch(subopcion) {
                        case 1: registrarNota(); break;
                        case 2: verHistorialAcademico(); break;
                        case 3: verMateriasPendientes(); break;
                        case 4: cout << "Volviendo al menú principal..." << endl; break;
                        default: cout << "Opción inválida" << endl;
                    }
                } while(subopcion != 4);
                break;
            }
                
            case 3: {
                int subopcion;
                do {
                    cout << "\n=== CONSULTAS Y REPORTES ===" << endl;
                    cout << "1. Reporte de estudiantes por estado" << endl;
                    cout << "2. Reporte de rendimiento académico" << endl;
                    cout << "3. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    
                    cin >> subopcion;
                    cin.ignore();
                    
                    switch(subopcion) {
                        case 1: reporteEstudiantesPorEstado(); break;
                        case 2: reporteRendimientoAcademico(); break;
                        case 3: cout << "Volviendo al menú principal..." << endl; break;
                        default: cout << "Opción inválida" << endl;
                    }
                } while(subopcion != 3);
                break;
            }
                
            case 4: {
                int subopcion;
                do {
                    cout << "\n=== ARCHIVOS ===" << endl;
                    cout << "1. Guardar todos los estudiantes" << endl;
                    cout << "2. Cargar estudiantes desde archivo" << endl;
                    cout << "3. Volver al menú principal" << endl;
                    cout << "Opción: ";
                    
                    cin >> subopcion;
                    cin.ignore();
                    
                    switch(subopcion) {
                        case 1: guardarEstudiantes(); break;
                        case 2: cargarEstudiantes(); break;
                        case 3: cout << "Volviendo al menú principal..." << endl; break;
                        default: cout << "Opción inválida" << endl;
                    }
                } while(subopcion != 3);
                break;
            }
                
            case 5:
                cout << "\n¿Desea guardar los cambios antes de salir? (S/N): ";
                char respuesta;
                cin >> respuesta;
                cin.ignore();
                
                if (toupper(respuesta) == 'S') {
                    guardarEstudiantes();
                }
                
                cout << "\nSaliendo del sistema..." << endl;
                cout << "¡Gracias por usar el Sistema de Gestión Académica!" << endl;
                break;
                
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
        
    } while(opcion != 5);
}

int main() {
    if (!login()) {
        return 0;
    }
    
    menuPrincipal();
    return 0;
}
