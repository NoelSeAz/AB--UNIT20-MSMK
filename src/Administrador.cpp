#include "Administrador.hpp"
#include "Formateador.hpp"
#include <iostream>

// Alta de m�dicos
void Administrador::altaMedico(std::vector<Medico>& medicos, int id, const std::string& nombre, const std::string& apellido,
    const std::string& especialidad, bool disponibilidad) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        std::cerr << "Error: Ya existe un m�dico con el ID " << id << ".\n";
        return;
    }

    auto& nuevoMedico = medicos.emplace_back(id, nombre, apellido, especialidad, disponibilidad);
    Formateador::imprimirEncabezadoMedicos();
    Formateador::imprimirRegistro(nuevoMedico);
    std::cout << "\nM�dico dado de alta exitosamente.\n";
}

// Baja de m�dicos
void Administrador::bajaMedico(std::vector<Medico>& medicos, int id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it == medicos.end()) {
        std::cerr << "Error: No se encontr� un m�dico con el ID " << id << ".\n";
        return;
    }

    medicos.erase(it, medicos.end());
    std::cout << "M�dico con ID " << id << " dado de baja exitosamente.\n";
}

// Alta de pacientes
void Administrador::altaPaciente(std::vector<Paciente>& pacientes, int id, const std::string& nombre, const std::string& apellido,
    const std::string& direccion, int edad) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        std::cerr << "\nError: Ya existe un paciente con el ID " << id << ".\n";
        return;
    }

    auto& nuevoPaciente = pacientes.emplace_back(id, nombre, apellido, direccion, edad);
    Formateador::imprimirEncabezadoPacientes();
    Formateador::imprimirRegistro(nuevoPaciente);
    std::cout << "\nPaciente dado de alta exitosamente.\n";
}

// Baja de pacientes
void Administrador::bajaPaciente(std::vector<Paciente>& pacientes, int id) {
    auto it = std::remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it == pacientes.end()) {
        std::cerr << "Error: No se encontr� un paciente con el ID " << id << ".\n";
        return;
    }

    pacientes.erase(it, pacientes.end());
    std::cout << "Paciente con ID " << id << " dado de baja exitosamente.\n";
}

// Buscar paciente por ID
Paciente* Administrador::buscarPacientePorID(const std::vector<Paciente>& pacientes, int id) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        return const_cast<Paciente*>(&(*it)); // Devuelve un puntero al paciente encontrado
    }
    else {
        std::cerr << "Error: No se encontr� un paciente con el ID " << id << ".\n";
        return nullptr;
    }
}

// Buscar m�dico por ID
Medico* Administrador::buscarMedicoPorID(const std::vector<Medico>& medicos, int id) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        return const_cast<Medico*>(&(*it)); // Devuelve un puntero al m�dico encontrado
    }
    else {
        std::cerr << "Error: No se encontr� un m�dico con el ID " << id << ".\n";
        return nullptr;
    }
}
