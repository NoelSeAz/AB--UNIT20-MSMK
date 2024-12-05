#include "Administrador.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "InputValidator.hpp"
#include <iostream>
#include <stdexcept>

// Alta de médicos
void GestorAdministrativo::altaMedico(std::vector<Medico>& medicos, const std::string& nombre, const std::string& apellido,
    const std::string& especialidad, bool disponibilidad) {
    std::vector<std::string> idsExistentes;
    for (const auto& medico : medicos) {
        idsExistentes.push_back(medico.getID());
    }

    std::string ID = IDGenerator::generarID("M", nombre, apellido, idsExistentes);
    auto& nuevoMedico = medicos.emplace_back(ID, nombre, apellido, especialidad, disponibilidad);
    Formateador::imprimirEncabezadoMedicos();
    Formateador::imprimirRegistro(nuevoMedico);
    std::cout << "\nMédico dado de alta exitosamente.\n";
}

// Baja de médicos
void GestorAdministrativo::bajaMedico(std::vector<Medico>& medicos, const std::string& id) {
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
void GestorAdministrativo::altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre,
    const std::string& apellido, const std::string& direccion, int edad) {
    std::vector<std::string> idsExistentes;
    for (const auto& paciente : pacientes) {
        idsExistentes.push_back(paciente.getID());
    }

    std::string ID = IDGenerator::generarID("P", nombre, apellido, idsExistentes);
    auto& nuevoPaciente = pacientes.emplace_back(ID, nombre, apellido, direccion, edad);
    Formateador::imprimirEncabezadoPacientes();
    Formateador::imprimirRegistro(nuevoPaciente);
    std::cout << "\nPaciente dado de alta exitosamente.\n";
}

// Baja de pacientes
void GestorAdministrativo::bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id) {
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

// Buscar paciente por ID
Paciente* GestorAdministrativo::buscarPacientePorID(const std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        return const_cast<Paciente*>(&(*it)); // Devuelve un puntero al paciente encontrado
    }
    else {
        std::cerr << "Error: No se encontró un paciente con el ID " << id << ".\n";
        return nullptr;
    }
}

// Buscar médico por ID
Medico* GestorAdministrativo::buscarMedicoPorID(const std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        return const_cast<Medico*>(&(*it)); // Devuelve un puntero al médico encontrado
    }
    else {
        std::cerr << "Error: No se encontró un médico con el ID " << id << ".\n";
        return nullptr;
    }
}


void AdministradorCitas::crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad) {
    // Validar que la fecha sea futura
    if (!InputValidator::esFechaFutura(fecha)) {
        throw std::invalid_argument("La fecha debe ser igual o posterior a la fecha actual.");
    }

    // Crear una nueva cita
    int citaID = citas.size() + 1;
    Cita nuevaCita(citaID, pacienteID, medicoID, fecha, prioridad);

    // Añadir la cita al vector
    citas.push_back(nuevaCita);

    // Mostrar confirmación
    std::cout << "Cita creada exitosamente:\n";
    nuevaCita.imprimirCita();
}