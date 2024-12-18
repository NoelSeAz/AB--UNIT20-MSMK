#include "GestorMedicos.hpp"
#include "iostream"

void GestorMedicos::altaMedico(std::vector<Medico>& medicos, const std::string& nombre, const std::string& apellido, const std::string& especialidad, bool disponibilidad) {
    std::vector<std::string> idsExistentes;
    for (const auto& medico : medicos) {
        idsExistentes.push_back(medico.getID());
    }

    std::string ID = IDGenerator::generarID("M", nombre, apellido, idsExistentes);
    medicos.emplace_back(ID, nombre, apellido, especialidad, disponibilidad);
    std::cout << "Médico dado de alta exitosamente:\n";
    Formateador::imprimirRegistro(medicos.back());
    Archivo::guardarMedicos(medicos, "./data/archivo_medicos.txt");
}

void GestorMedicos::bajaMedico(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [&id](const Medico& m) { return m.getID() == id; });
    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
        Archivo::guardarMedicos(medicos, "./data/archivo_medicos.txt");
    }
    else {
        std::cerr << "Error: No se encontró un médico con el ID " << id << ".\n";
    }
}

Medico* GestorMedicos::buscarMedicoPorID(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [&id](const Medico& m) {
        return m.getID() == id;
        });
    return (it != medicos.end()) ? &(*it) : nullptr;
}