#ifndef GESTORPACIENTES_HPP
#define GESTORPACIENTES_HPP

#include "Paciente.hpp"
#include "Archivo.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include <vector>
#include <string>

class GestorPacientes {
public:
    static void altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre, const std::string& apellido, const std::string& direccion, int edad);
    static void bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id);
    static Paciente* buscarPacientePorID(std::vector<Paciente>& pacientes, const std::string& id);
};

#endif
