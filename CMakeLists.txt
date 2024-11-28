# CMakeList.txt: Proyecto de CMake para UNIT20-AB

# Versión mínima requerida
cmake_minimum_required(VERSION 3.12)

# Nombre del proyecto
project(UNIT20-AB)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configurar directorio de salida para ejecutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

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
 "src/Administrador.cpp")

# Configuración específica de MSVC
if (MSVC)
    # Configurar directorios para depuración
    set_target_properties(UNIT20-AB PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build
        PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build
        PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build
    )

    # Configurar depuración incremental
    if (POLICY CMP0141)
        cmake_policy(SET CMP0141 NEW)
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<CONFIG:Debug>:ProgramDatabase>")
    endif()
endif()
