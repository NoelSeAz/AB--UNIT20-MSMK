#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Medico.hpp"
#include "Paciente.hpp" // Asegúrate de incluir también la clase Paciente
#include <vector>

/// Clase que gestiona operaciones relacionadas con médicos y pacientes.
class Administrador {
public:
    // Métodos para gestionar médicos
    static void altaMedico(std::vector<Medico>& medicos, int id, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    static void bajaMedico(std::vector<Medico>& medicos, int id);

    // Métodos para gestionar pacientes
    static void altaPaciente(std::vector<Paciente>& pacientes, int id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    static void bajaPaciente(std::vector<Paciente>& pacientes, int id);
};

#endif
