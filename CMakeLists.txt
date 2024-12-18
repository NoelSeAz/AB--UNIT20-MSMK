# CMakeList.txt: Proyecto de CMake para UNIT20-AB

# Versión mínima requerida
cmake_minimum_required(VERSION 3.8)

# Nombre del proyecto
project(UNIT20-AB)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configurar directorio de salida para ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Añadir el ejecutable
add_executable(UNIT20-AB)

# Directorios de encabezados
target_include_directories(UNIT20-AB PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Archivos fuente
target_sources(UNIT20-AB PRIVATE 
    "src/main.cpp" 
    "src/Paciente.cpp" 
    "src/Medico.cpp" 
    "src/Cita.cpp" 
    "src/Reporte.cpp" 
    "src/Archivo.cpp"
     
    "src/Formateador.cpp" 
    "src/IDGenerator.cpp" 
    "src/InputValidator.cpp" "src/HistorialMedico.cpp" "src/EnfermedadCronica.cpp" "src/GestorPacientes.cpp" "src/GestorMedicos.cpp" "src/GestorCitas.cpp" "src/GestorEspecialidades.cpp")
