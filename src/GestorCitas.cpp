#include "GestorCitas.hpp"
#include "IDGenerator.hpp"
#include "iostream"

void GestorCitas::crearCita(std::vector<Cita>& citas, const std::string& pacienteID,
    const std::string& medicoID, const std::string& fecha, int prioridad) {
    if (!InputValidator::esFechaFutura(fecha)) {
        throw std::invalid_argument("La fecha debe ser igual o posterior a la fecha actual.");
    }

    // Generar IDs únicos
    std::string citaID = IDGenerator::generarIDCita(pacienteID, medicoID, fecha);
    unsigned long hash = IDGenerator::generarHashCita(pacienteID, medicoID, fecha);

    // Crear y guardar la cita
    citas.emplace_back(hash, citaID, pacienteID, medicoID, fecha, prioridad, false);
    Archivo::guardarCitas(citas, "./data/archivo_citas.txt");
    std::cout << "Cita creada exitosamente con ID Hash: " << hash << "\n";
}

void GestorCitas::modificarCita(std::vector<Cita>& citas, const std::string& citaID,
    const std::string& nuevaFecha, int nuevaPrioridad) {
    auto it = std::find_if(citas.begin(), citas.end(), [&citaID](const Cita& c) {
        return c.getCitaID() == citaID;
        });

    if (it != citas.end()) {
        // Modificar los datos de la cita
        it->modificarCita(nuevaFecha, nuevaPrioridad);

        // Generar un nuevo hash para reflejar los cambios
        unsigned long nuevoHash = IDGenerator::generarHashCita(it->getPacienteID(), it->getMedicoID(), nuevaFecha);
        it->setCitaIDHash(nuevoHash);

        Archivo::guardarCitas(citas, "./data/archivo_citas.txt");
        std::cout << "Cita modificada exitosamente con nuevo ID Hash: " << nuevoHash << "\n";
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID " << citaID << ".\n";
    }
}

void GestorCitas::cancelarCita(std::vector<Cita>& citas, const std::string& citaID) {
    auto it = std::remove_if(citas.begin(), citas.end(), [&citaID](const Cita& c) { return c.getCitaID() == citaID; });
    if (it != citas.end()) {
        citas.erase(it, citas.end());
        Archivo::guardarCitas(citas, "./data/archivo_citas.txt");
        std::cout << "Cita cancelada exitosamente.\n";
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID " << citaID << ".\n";
    }
}