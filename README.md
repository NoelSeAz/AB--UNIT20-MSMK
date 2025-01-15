# AB-UNIT20-MSMK: Simulador de Gesti�n Hospitalaria

Este proyecto es un simulador de gesti�n hospitalaria desarrollado en C++. El sistema permite la gesti�n eficiente de informaci�n relacionada con pacientes, m�dicos, citas m�dicas, historiales cl�nicos y especialidades.

## Funcionalidades Principales

### Gesti�n de Pacientes
- Alta, baja y modificaci�n de datos personales.
- B�squeda de pacientes por nombre, identificaci�n o fecha de ingreso.
- Registro y consulta de historial cl�nico.

### Gesti�n de M�dicos
- Alta y baja de m�dicos.
- Asignaci�n y consulta de especialidades.
- Listado de m�dicos por especialidad o disponibilidad.

### Gesti�n de Citas
- Asignaci�n de citas a pacientes y m�dicos.
- Modificaci�n y cancelaci�n de citas.
- Ordenaci�n de citas por fecha o prioridad (urgencia).

### Generaci�n de Reportes
- Listado de pacientes atendidos en un rango de fechas.
- Reporte de citas pendientes por m�dico o especialidad.
- Informe sobre pacientes con enfermedades cr�nicas.

### Manejo de Archivos
- Guardar y cargar datos de pacientes, m�dicos, citas y especialidades.
- Funci�n de respaldo autom�tico de la base de datos.

---

## Requisitos T�cnicos

### **Compilador**
- C++17 o superior.
- Sistema operativo compatible con compiladores como `g++` o `MSVC`.

### **Librer�as Utilizadas**
- `<iostream>`: Entrada y salida est�ndar.
- `<fstream>`: Manejo de archivos.
- `<string>`: Manipulaci�n de cadenas.
- `<vector>`: Uso de arreglos din�micos.
- `<map>`: Estructura de datos para pares clave-valor.
- `<algorithm>`: Algoritmos de b�squeda y ordenaci�n.
- `<sstream>`: Manipulaci�n de flujos de datos.
- `<regex>`: Validaci�n y procesamiento de cadenas con expresiones regulares.
- `<ctime>` y `<iomanip>`: Manejo de fechas y formatos de salida.
- `<optional>`: Gesti�n de valores opcionales (C++17).
- `<filesystem>`: Operaciones en el sistema de archivos (C++17).

---

## Instrucciones de Uso

### **1. Configuraci�n Inicial**
1. Clona este repositorio:
```
git clone https://github.com/NoelSeAz/AB--UNIT20-MSMK.git
```

2. Aseg�rate de tener los archivos de datos necesarios en la carpeta data/:
	- archivo_pacientes.txt
	- archivo_medicos.txt
	- archivo_citas.txt
	- especialidades.csv

### **2. Compilaci�n**

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
	


### **3. Ejecuci�n**
Despu�s de compilar, puedes ejecutar el programa:

### Linux/macOS:
```
./UNIT20-AB
```

### Windows:
```
cd .\Debug\
.\UNIT20-AB.exe
```

> Nota Importante: Aseg�rate de ejecutar el programa desde el 
> directorio donde se gener� el ejecutable (build/Debug o build/Release).
> Si ejecutas desde otro directorio, el programa podr�a no encontrar 
> los archivos necesarios en la carpeta data/.

## Estructura del Proyecto

	- main.cpp: Punto de entrada del programa.

	- Clases Principales:
		- Paciente: Gesti�n de pacientes.
		- Medico: Gesti�n de m�dicos y especialidades.
		- Cita: Gesti�n de citas m�dicas.
		- HistorialMedico: Gesti�n del historial cl�nico.

	- Gestores:
		- GestorCitas: Administraci�n de las citas.
		- GestorPacientes: Administraci�n de los pacientes.
		- GestorMedicos: Administraci�n de los m�dicos y especialidades.

	- Persistencia:
		- Archivo: Carga y guarda datos en archivos.

	- Utilidades:
		- InputValidator: Validaci�n de entradas.
		- Formateador: Imprime datos de forma tabular y organizada.
		- IDGenerator: Generaci�n de IDs �nicos.

## Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o un pull request si deseas mejorar el proyecto.

## Licencia
Este proyecto est� bajo la licencia MIT.
