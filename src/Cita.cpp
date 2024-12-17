#include "Cita.hpp"
#include "InputValidator.hpp"
#include <iostream>
#include <iomanip>

// Constructor
Cita::Cita(const std::string& citaIDHash, const std::string& citaID, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad, bool validar)
    : citaIDHash(citaIDHash), citaID(citaID), pacienteID(pacienteID), medicoID(medicoID), fecha(fecha), prioridad(prioridad) {
    if (validar && !InputValidator::esFechaFutura(fecha)) {
        throw std::invalid_argument("La fecha de la cita debe ser igual o posterior a la fecha actual.");
    }
    this->fecha = fecha; // Asignar la fecha validada
}

// Modificar los detalles de una cita
void Cita::modificarCita(const std::string& nuevaFecha, int nuevaPrioridad) {
    if (!InputValidator::validarFormatoFecha(nuevaFecha)) {
        throw std::invalid_argument("El formato de la nueva fecha es inválido.");
    }

    // Obtener la fecha actual para comparación
    std::string fechaActual = InputValidator::obtenerFechaActual(); 

    // Validar que la nueva fecha no sea anterior a hoy
    if (!InputValidator::esFechaPosterior(nuevaFecha, fechaActual)) {
        throw std::invalid_argument("La nueva fecha debe ser igual o posterior a la fecha actual.");
    }

    // Si la nueva fecha es anterior a la fecha original, se permite
    // mientras sea igual o posterior a hoy
    this->fecha = nuevaFecha;
    this->prioridad = nuevaPrioridad;

    std::cout << "Nueva fecha: " << nuevaFecha << ", Nueva prioridad: " << nuevaPrioridad << "\n";
}

// Función de comparación por fecha
bool Cita::compararPorFecha(const Cita& a, const Cita& b) {
    return a.fecha < b.fecha; // Orden ascendente
}

// Función de comparación por prioridad
bool Cita::compararPorPrioridad(const Cita& a, const Cita& b) {
    return a.prioridad > b.prioridad; // Orden descendente
}

// Ordenar citas por fecha
void Cita::ordenarCitasPorFecha(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), compararPorFecha);
}

// Ordenar citas por prioridad
void Cita::ordenarCitasPorPrioridad(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), compararPorPrioridad);
}

// Getters
std::string Cita::getCitaIDHash() const { return citaIDHash;  }
std::string Cita::getCitaID() const { return citaID; }
std::string Cita::getPacienteID() const { return pacienteID; }
std::string Cita::getMedicoID() const { return medicoID; }
int Cita::getPrioridad() const { return prioridad; }
std::string Cita::getFecha() const { return fecha; }
