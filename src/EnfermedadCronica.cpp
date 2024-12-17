#include "EnfermedadCronica.hpp"
#include <iostream>

// Constructor
EnfermedadCronica::EnfermedadCronica(const std::string& nombre, int severidad, const std::string& tratamiento, const std::string& fechaDiagnostico)
    : nombre(nombre), severidad(severidad), tratamiento(tratamiento), fechaDiagnostico(fechaDiagnostico) {
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