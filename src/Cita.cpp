#include "Cita.hpp"
#include <iostream>
#include <iomanip>

// Constructor
Cita::Cita(int citaID, int pacienteID, int medicoID, const std::string& fecha, int prioridad)
    : citaID(citaID), pacienteID(pacienteID), medicoID(medicoID), fecha(fecha), prioridad(prioridad) {}

// Modificar los detalles de una cita
void Cita::modificarCita(const std::string& nuevaFecha, int nuevaPrioridad) {
    fecha = nuevaFecha;
    prioridad = nuevaPrioridad;
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

// Imprimir detalles de una cita
void Cita::imprimirCita() const {
    std::cout << std::left;
    std::cout << std::setw(5) << citaID
        << std::setw(10) << pacienteID
        << std::setw(10) << medicoID
        << std::setw(20) << fecha
        << std::setw(10) << (prioridad == 1 ? "Urgente" : "Normal")
        << "\n";
}

// Getters
int Cita::getCitaID() const { return citaID; }
int Cita::getPacienteID() const { return pacienteID; }
int Cita::getMedicoID() const { return medicoID; }
int Cita::getPrioridad() const { return prioridad; }
std::string Cita::getFecha() const { return fecha; }
