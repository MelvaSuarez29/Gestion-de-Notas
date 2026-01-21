#include <iostream>
using namespace std;

//Función Menú principal 
void mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "  SISTEMA DE GESTIÓN ACADÉMICA" << endl;
    cout << "  Carrera: Desarrollo de Software" << endl;
    cout << "  Pénsum: 2020 - 75 Créditos" << endl;
    cout << "========================================" << endl;
}
// Función Menú principal 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cctype>
using namespace std;

extern void mostrarMenuPrincipal();
extern void cargarEstudiantes();
extern void guardarEstudiantes();
extern void crearEstudiante();
extern void verEstudiantes();
extern void actualizarEstudiante();
extern void eliminarEstudiante();
extern void registrarNota();
extern void verHistorialAcademico();
extern void verMateriasPendientes();
extern void reporteEstudiantesPorEstado();
extern void reporteRendimientoAcademico();

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