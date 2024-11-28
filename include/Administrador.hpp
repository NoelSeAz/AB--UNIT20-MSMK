#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include <vector>

class Administrador {
public:
    // Métodos de alta y baja (ya implementados)
    static void altaMedico(std::vector<Medico>& medicos, int id, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    static void bajaMedico(std::vector<Medico>& medicos, int id);

    static void altaPaciente(std::vector<Paciente>& pacientes, int id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    static void bajaPaciente(std::vector<Paciente>& pacientes, int id);

    // Métodos de búsqueda
    static Paciente* buscarPacientePorID(const std::vector<Paciente>& pacientes, int id);
    static Medico* buscarMedicoPorID(const std::vector<Medico>& medicos, int id);
};

#endif
