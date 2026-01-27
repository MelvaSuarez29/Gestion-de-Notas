##  Estructura del Código

El sistema está desarrollado en **C++** bajo un enfoque **modular y estructurado**, utilizando funciones, estructuras (`struct`) y contenedores dinámicos (`vector`) para organizar la información académica.

---

##  Bibliotecas Utilizadas

- `<iostream>`: Entrada y salida de datos por consola.
- `<vector>`: Almacenamiento dinámico de estudiantes y materias.
- `<string>`: Manejo de cadenas de texto.
- `<fstream>`: Lectura y escritura de archivos para persistencia de datos.
- `<algorithm>`: Búsqueda y manipulación de colecciones (ej. `find_if`).
- `<iomanip>`: Formato de salida en tablas y números decimales.
- `<cctype>`: Validación de caracteres (letras, mayúsculas, etc.).

---

##  Estructuras de Datos Principales

- **MateriaSemestre**  
  Representa las materias del pénsum académico, incluyendo código, nombre, créditos, horas y semestre.

- **MateriaCursada**  
  Almacena el historial académico del estudiante: nota, estado (aprobado/reprobado), intentos y período.

- **Estudiante**  
  Contiene la información principal del estudiante: cédula, nombre, carrera, semestre actual, materias cursadas, promedio acumulado, créditos aprobados y estado (activo/inactivo).

---

## Persistencia de Datos

- Los datos se almacenan en un archivo de texto (`datos_estudiantes.txt`).
- Se utilizan funciones de lectura y escritura para mantener la información entre ejecuciones del sistema.
- El formato de almacenamiento emplea separadores (`|` y `,`) para organizar los datos.

---

## Función de Autenticación

- **login()**  
  Controla el acceso al sistema mediante usuario y contraseña.
  - Usuario: `admin`
  - Clave: `1234`
  - Máximo de 3 intentos permitidos.

---

##  Funciones Principales del Sistema

### Gestión de Estudiantes (CRUD)
- **crearEstudiante()**: Registra un nuevo estudiante validando cédula y nombre.
- **verEstudiantes()**: Muestra una lista tabulada de todos los estudiantes.
- **actualizarEstudiante()**: Permite modificar semestre o estado del estudiante.
- **eliminarEstudiante()**: Elimina un estudiante con confirmación previa.

### Gestión Académica
- **registrarNota()**: Registra o actualiza la nota de una materia considerando intentos y aprobación.
- **verHistorialAcademico()**: Muestra el historial completo de materias, créditos y promedio.
- **verMateriasPendientes()**: Lista las materias no aprobadas por semestre.

### Consultas y Reportes
- **reporteEstudiantesPorEstado()**: Genera estadísticas de estudiantes activos e inactivos.
- **reporteRendimientoAcademico()**: Clasifica a los estudiantes según su promedio académico.

### Manejo de Archivos
- **guardarEstudiantes()**: Guarda toda la información en el archivo.
- **cargarEstudiantes()**: Carga los datos desde el archivo al iniciar el sistema.

---

##  Menú del Sistema

El sistema funciona mediante un **menú interactivo en consola**, organizado en:
1. Gestión de Estudiantes  
2. Gestión Académica  
3. Consultas y Reportes  
4. Archivos  
5. Salida segura con opción de guardar cambios  

---

##  Enfoque del Desarrollo 

- Uso de **programación estructurada y orientada a objetos**.
- Validación de datos para evitar errores de ingreso.
- Diseño escalable para futuras mejoras (interfaz gráfica en Qt, base de datos, múltiples carreras).
