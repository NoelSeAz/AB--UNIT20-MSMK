#include "GestorPacientes.hpp"
#include "iostream"

void GestorPacientes::altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre, const std::string& apellido, const std::string& direccion, int edad) {
    std::vector<std::string> idsExistentes;
    for (const auto& paciente : pacientes) {
        idsExistentes.push_back(paciente.getID());
    }

    std::string ID = IDGenerator::generarID("P", nombre, apellido, idsExistentes);
    pacientes.emplace_back(ID, nombre, apellido, direccion, edad);
    std::cout << "Paciente dado de alta exitosamente:\n";
    Formateador::imprimirRegistro(pacientes.back());
    Archivo::guardarPacientes(pacientes, "./data/archivo_pacientes.txt");
}

void GestorPacientes::bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::remove_if(pacientes.begin(), pacientes.end(), [&id](const Paciente& p) { return p.getID() == id; });
    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        std::cout << "Paciente con ID " << id << " dado de baja exitosamente.\n";
        Archivo::guardarPacientes(pacientes, "./data/archivo_pacientes.txt");
    }
    else {
        std::cerr << "Error: No se encontró un paciente con el ID " << id << ".\n";
    }
}

Paciente* GestorPacientes::buscarPacientePorID(std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [&id](const Paciente& p) {
        return p.getID() == id;
        });
    return (it != pacientes.end()) ? &(*it) : nullptr;
}
