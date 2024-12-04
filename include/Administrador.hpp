#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include <vector>

class Administrador {
public:
    // Métodos de alta y baja
    static void altaMedico(std::vector<Medico>& medicos, const std::string& id, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    static void bajaMedico(std::vector<Medico>& medicos, const std::string& id);

    static void altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    static void bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id);

    // Métodos de búsqueda
    static Paciente* buscarPacientePorID(const std::vector<Paciente>& pacientes, const std::string& id);
    static Medico* buscarMedicoPorID(const std::vector<Medico>& medicos, const std::string& id);
};

#endif
