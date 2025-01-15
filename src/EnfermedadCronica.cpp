#include "EnfermedadCronica.hpp"
#include <iostream>

// Constructor
EnfermedadCronica::EnfermedadCronica(const std::string& nombreParam, int severidadParam, const std::string& tratamientoParam, const std::string& fechaDiagnosticoParam)
    : nombre(nombreParam), severidad(severidadParam), tratamiento(tratamientoParam), fechaDiagnostico(fechaDiagnosticoParam) {
}

// Getters
std::string EnfermedadCronica::getNombre() const { return nombre; }
int EnfermedadCronica::getSeveridad() const { return severidad;  }
std::string EnfermedadCronica::getFechaDiagnostico() const { return fechaDiagnostico; }
std::string EnfermedadCronica::getTratamiento() const { return tratamiento; }

// Setters
void EnfermedadCronica::setTratamiento(const std::string& nuevoTratamiento) {
    tratamiento = nuevoTratamiento;
}