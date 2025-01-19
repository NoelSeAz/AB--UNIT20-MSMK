#ifndef ARCHIVOS_ACTIVOS_HPP
#define ARCHIVOS_ACTIVOS_HPP

#include <string>

struct ArchivosActivos {
    std::string pacientes = "archivo_pacientes.txt";
    std::string medicos = "archivo_medicos.txt";
    std::string citas = "archivo_citas.txt";
    std::string especialidades = "especialidades.csv";
};

#endif // ARCHIVOS_ACTIVOS_HPP
