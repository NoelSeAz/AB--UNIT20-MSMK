#include "Administrador.hpp"
#include <iostream>

// Alta de médicos
void Administrador::altaMedico(std::vector<Medico>& medicos, int id, const std::string& nombre, const std::string& apellido,
    const std::string& especialidad, bool disponibilidad) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        std::cerr << "Error: Ya existe un médico con el ID " << id << ".\n";
        return;
    }

    medicos.emplace_back(id, nombre, apellido, especialidad, disponibilidad);
    std::cout << "Médico dado de alta exitosamente.\n";
}

// Baja de médicos
void Administrador::bajaMedico(std::vector<Medico>& medicos, int id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it == medicos.end()) {
        std::cerr << "Error: No se encontró un médico con el ID " << id << ".\n";
        return;
    }

    medicos.erase(it, medicos.end());
    std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
}

// Alta de pacientes
void Administrador::altaPaciente(std::vector<Paciente>& pacientes, int id, const std::string& nombre, const std::string& apellido,
    const std::string& direccion, int edad) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        std::cerr << "Error: Ya existe un paciente con el ID " << id << ".\n";
        return;
    }

    pacientes.emplace_back(id, nombre, apellido, direccion, edad);
    std::cout << "Paciente dado de alta exitosamente.\n";
}

// Baja de pacientes
void Administrador::bajaPaciente(std::vector<Paciente>& pacientes, int id) {
    auto it = std::remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it == pacientes.end()) {
        std::cerr << "Error: No se encontró un paciente con el ID " << id << ".\n";
        return;
    }

    pacientes.erase(it, pacientes.end());
    std::cout << "Paciente con ID " << id << " dado de baja exitosamente.\n";
}
