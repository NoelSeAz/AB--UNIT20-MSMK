# CMakeList.txt: Proyecto de CMake para UNIT20-AB

# Versión mínima requerida
cmake_minimum_required(VERSION 3.12)

# Nombre del proyecto
project(UNIT20-AB)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir el ejecutable
add_executable(UNIT20-AB)

# Directorios de encabezados y archivos fuente
target_include_directories(UNIT20-AB PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp")
target_sources(UNIT20-AB PRIVATE ${SOURCES} "src/main.cpp" "src/Paciente.cpp" "src/Medico.cpp" "src/Cita.cpp" "src/Reporte.cpp" )

# Configuración específica de MSVC (opcional)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
