#include "GestorCitas.hpp"
#include "InputValidator.hpp"
#include "IDGenerator.hpp"
#include <iostream>
#include <algorithm> // Para std::sort

// Crear una nueva cita
void GestorCitas::crearCita(std::vector<Cita>& citas, const std::string& pacienteID,
    const std::string& medicoID, const std::string& fecha, int prioridad) {
    if (!InputValidator::validarFormatoFecha(fecha) || !InputValidator::esFechaFutura(fecha)) {
        std::cerr << "Error: La fecha de la cita no es válida.\n";
        return;
    }

    unsigned long hash = IDGenerator::generarHashCita(pacienteID, medicoID, fecha);
    std::string citaID = IDGenerator::generarIDCita(pacienteID, medicoID, fecha);

    citas.emplace_back(hash, citaID, pacienteID, medicoID, fecha, prioridad);
    std::cout << "Cita creada exitosamente con ID: " << citaID << "\n";
}

// Cancelar una cita
void GestorCitas::cancelarCita(std::vector<Cita>& citas, const std::string& citaID) {
    auto it = std::remove_if(citas.begin(), citas.end(), [&citaID](const Cita& cita) {
        return cita.getCitaID() == citaID;
        });

    if (it != citas.end()) {
        citas.erase(it, citas.end());
        std::cout << "Cita cancelada exitosamente.\n";
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID proporcionado.\n";
    }
}

// Modificar una cita existente
bool GestorCitas::modificarCita(std::vector<Cita>& citas, const std::string& citaID,
    const std::string& nuevaFecha, int nuevaPrioridad) {
    auto it = std::find_if(citas.begin(), citas.end(), [&citaID](const Cita& cita) {
        return cita.getCitaID() == citaID;
        });

    if (it == citas.end()) {
        std::cerr << "Error: No se encontró una cita con el ID proporcionado.\n";
        return false;
    }

    try {
        it->modificarCita(nuevaFecha, nuevaPrioridad);
    }
    catch (const std::exception& e) {
        std::cerr << "Error al modificar la cita: " << e.what() << "\n";
        return false;
    }

    return true;
}

// Ordenar citas por fecha
void GestorCitas::ordenarCitasPorFecha(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), Cita::compararPorFecha);
}

// Ordenar citas por prioridad
void GestorCitas::ordenarCitasPorPrioridad(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), Cita::compararPorPrioridad);
}
