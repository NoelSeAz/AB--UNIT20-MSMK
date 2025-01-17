cmake_minimum_required(VERSION 3.6)

# Nombre del proyecto
project(UNIT20-AB)

# Especificación de C++ estándar
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Evitar extensiones específicas del compilador

# Configuración de compilación (Debug/Release)
set(CMAKE_BUILD_TYPE Debug)

# Configuración específica del compilador
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        "$<$<CONFIG:Debug>:-Wpedantic;-Wall;-Wextra;-Wconversion;-Wshadow;-Wcast-qual;-Wwrite-strings;-DDEBUG>"
        "$<$<CONFIG:Release>:-pedantic;-Wall;-O3>"
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        "$<$<CONFIG:Debug>:-pedantic;-Wall;-Wextra;-Wconversion;-Wshadow;-Wcast-qual;-Wwrite-strings;-O0;-ggdb3;-DDEBUG>"
        "$<$<CONFIG:Release>:-pedantic;-Wall;-O3>"
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
        "$<$<CONFIG:Debug>:/W4;/DDEBUG;/Od;/Zi>" # /W4: Nivel de advertencias alto, /Od: Sin optimización, /Zi: Depuración
        "$<$<CONFIG:Release>:/W4;/O2>"          # /O2: Optimización, /W3: Advertencias moderadas
    )
endif()

# Verificar compilador activo
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

# Configuración del ejecutable
add_executable(UNIT20-AB
    src/main.cpp 
    src/Paciente.cpp 
    src/Medico.cpp 
    src/Cita.cpp 
    src/Reporte.cpp 
    src/Archivo.cpp 
    src/Formateador.cpp 
    src/IDGenerator.cpp 
    src/InputValidator.cpp 
    src/HistorialMedico.cpp 
    src/EnfermedadCronica.cpp 
    src/GestorPacientes.cpp 
    src/GestorMedicos.cpp 
    src/GestorCitas.cpp 
    src/GestorEspecialidades.cpp
)

# Directorios de encabezados
target_include_directories(UNIT20-AB PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Directorios de salida (separados por configuración)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# Instalación
install(TARGETS UNIT20-AB RUNTIME DESTINATION bin)

# Pruebas automáticas para verificar la configuración
enable_testing()

add_test(
    NAME CompiladorCorrecto
    COMMAND ${CMAKE_COMMAND} -E echo "Compilador: ${CMAKE_CXX_COMPILER_ID}, Versión: ${CMAKE_CXX_COMPILER_VERSION}"
)
