# AB-UNIT20-MSMK: Simulador de Gestión Hospitalaria

Este proyecto es un simulador de gestión hospitalaria desarrollado en C++. El sistema permite la gestión eficiente de información relacionada con pacientes, médicos, citas médicas, historiales clínicos y especialidades.

## Funcionalidades Principales

### Gestión de Pacientes
- Alta, baja y modificación de datos personales.
- Búsqueda de pacientes por nombre, identificación o fecha de ingreso.
- Registro y consulta de historial clínico.

### Gestión de Médicos
- Alta y baja de médicos.
- Asignación y consulta de especialidades.
- Listado de médicos por especialidad o disponibilidad.

### Gestión de Citas
- Asignación de citas a pacientes y médicos.
- Modificación y cancelación de citas.
- Ordenación de citas por fecha o prioridad (urgencia).

### Generación de Reportes
- Listado de pacientes atendidos en un rango de fechas.
- Reporte de citas pendientes por médico o especialidad.
- Informe sobre pacientes con enfermedades crónicas.

### Manejo de Archivos
- Guardar y cargar datos de pacientes, médicos, citas y especialidades.
- Función de respaldo automático de la base de datos.

---

## Requisitos Técnicos

### **Compilador**
- C++17 o superior.
- Sistema operativo compatible con compiladores como `g++` o `MSVC`.

### **Librerías Utilizadas**
- `<iostream>`: Entrada y salida estándar.
- `<fstream>`: Manejo de archivos.
- `<string>`: Manipulación de cadenas.
- `<vector>`: Uso de arreglos dinámicos.
- `<map>`: Estructura de datos para pares clave-valor.
- `<algorithm>`: Algoritmos de búsqueda y ordenación.
- `<sstream>`: Manipulación de flujos de datos.
- `<regex>`: Validación y procesamiento de cadenas con expresiones regulares.
- `<ctime>` y `<iomanip>`: Manejo de fechas y formatos de salida.
- `<optional>`: Gestión de valores opcionales (C++17).
- `<filesystem>`: Operaciones en el sistema de archivos (C++17).

---

## Instrucciones de Uso

### **1. Configuración Inicial**
1. Clona este repositorio:
```
git clone https://github.com/NoelSeAz/AB--UNIT20-MSMK.git
```

2. Asegúrate de tener los archivos de datos necesarios en la carpeta data/:
	- archivo_pacientes.txt
	- archivo_medicos.txt
	- archivo_citas.txt
	- especialidades.csv

### **2. Compilación**

### Linux/macOS:
```
mkdir build
cd build
cmake .. -G "Unix Makefiles"
cmake --build . --config Debug
```

### Windows (Ejemplo: Windows 10 con MSVS 2022):
```
New-Item -ItemType Directory -Path .\build\
Set-Location .\build\
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
```
	


### **3. Ejecución**
Después de compilar, puedes ejecutar el programa:

### Linux/macOS:
```
./UNIT20-AB
```

### Windows:
```
cd .\Debug\
.\UNIT20-AB.exe
```

> Nota Importante: Asegúrate de ejecutar el programa desde el 
> directorio donde se generó el ejecutable (build/Debug o build/Release).
> Si ejecutas desde otro directorio, el programa podría no encontrar 
> los archivos necesarios en la carpeta data/.

## Estructura del Proyecto

	- main.cpp: Punto de entrada del programa.

	- Clases Principales:
		- Paciente: Gestión de pacientes.
		- Medico: Gestión de médicos y especialidades.
		- Cita: Gestión de citas médicas.
		- HistorialMedico: Gestión del historial clínico.

	- Gestores:
		- GestorCitas: Administración de las citas.
		- GestorPacientes: Administración de los pacientes.
		- GestorMedicos: Administración de los médicos y especialidades.

	- Persistencia:
		- Archivo: Carga y guarda datos en archivos.

	- Utilidades:
		- InputValidator: Validación de entradas.
		- Formateador: Imprime datos de forma tabular y organizada.
		- IDGenerator: Generación de IDs únicos.

## Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o un pull request si deseas mejorar el proyecto.

## Licencia
Este proyecto está bajo la licencia MIT.
