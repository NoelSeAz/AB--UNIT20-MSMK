#include "Cita.hpp"
#include "InputValidator.hpp"
#include "IDGenerator.hpp"
#include "Formateador.hpp"
#include <iostream>
#include <iomanip>
#include <optional>

// Constructor
Cita::Cita(const unsigned long citaIDHashParam, const std::string& citaIDParam, const std::string& pacienteIDParam,
    const std::string& medicoIDParam, const std::string& fechaParam, int prioridadParam, bool validar)
    : citaIDHash(citaIDHashParam), citaID(citaIDParam), pacienteID(pacienteIDParam),
    medicoID(medicoIDParam), fecha(fechaParam), prioridad(prioridadParam) {
    if (validar && !InputValidator::esFechaFutura(fecha)) {
        throw std::invalid_argument("La fecha de la cita debe ser igual o posterior a la fecha actual.");
    }
}

// Actualizar el hash de la cita
void Cita::setCitaIDHash(const unsigned long nuevoHash) {
    citaIDHash = nuevoHash;
}

// Modificar los detalles de una cita
void Cita::modificarCita(const std::string& nuevaFecha, int nuevaPrioridad,  const std::optional<std::string>& nuevoMedicoID) {
    // Validar formato de la nueva fecha
    if (!InputValidator::validarFormatoFecha(nuevaFecha)) {
        throw std::invalid_argument("El formato de la nueva fecha es inválido.");
    }

    // Validar que la nueva fecha no sea anterior a la actual
    if (!InputValidator::esFechaPosterior(nuevaFecha, InputValidator::obtenerFechaActual())) {
        throw std::invalid_argument("La nueva fecha debe ser igual o posterior a la fecha actual.");
    }

    // Validar prioridad
    if (nuevaPrioridad != 1 && nuevaPrioridad != 2) {
        throw std::invalid_argument("Prioridad inválida. Debe ser 1 (Urgente) o 2 (Normal).");
    }

    // Actualizar atributos
    if (nuevoMedicoID.has_value() && !nuevoMedicoID.value().empty()) {
        this->medicoID = nuevoMedicoID.value();
        std::cout << "Médico actualizado a: " << this->medicoID << "\n";
    }

    this->fecha = nuevaFecha;
    this->prioridad = nuevaPrioridad;

    // Regenerar citaID
    this->citaID = IDGenerator::generarIDCita(this->pacienteID, this->medicoID, this->fecha);
}

// Función de comparación por fecha
bool Cita::compararPorFecha(const Cita& a, const Cita& b) {
    return a.fecha < b.fecha; // Orden ascendente
}

// Función de comparación por prioridad
bool Cita::compararPorPrioridad(const Cita& a, const Cita& b) {
    return a.prioridad > b.prioridad; // Orden descendente
}

// Getters
unsigned long Cita::getCitaIDHash() const { return citaIDHash; }
std::string Cita::getCitaID() const { return citaID; }
std::string Cita::getPacienteID() const { return pacienteID; }
std::string Cita::getMedicoID() const { return medicoID; }
int Cita::getPrioridad() const { return prioridad; }
std::string Cita::getFecha() const { return fecha; }
