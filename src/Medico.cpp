#include "Medico.hpp"
#include "Cita.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Constructor
Medico::Medico(const std::string& idParam, const std::string& nombreParam, const std::string& apellidoParam,
    const std::string& especialidadParam, bool disponibilidadParam)
    : id(idParam), nombre(nombreParam), apellido(apellidoParam),
    especialidad(especialidadParam), disponibilidad(disponibilidadParam) {
}

// Asignar una nueva especialidad
void Medico::asignarEspecialidad(const std::string& nuevaEspecialidad) {
    especialidad = nuevaEspecialidad;
}

// Cambiar la disponibilidad del médico
void Medico::cambiarDisponibilidad(bool nuevaDisponibilidad) {
    disponibilidad = nuevaDisponibilidad;
}

// Obtener la disponibilidad actual del médico
bool Medico::obtenerDisponibilidad() const {
    return disponibilidad;
}

// Mostrar todas las citas asignadas al médico
void Medico::mostrarCitas() const {
    std::cout << "Citas del médico " << nombre << " " << apellido << ":\n";
    for (const auto& cita : listaCitas) {
        std::cout << "- ID de la cita: " << cita << "\n";
    }
}

// Getters
std::string Medico::getID() const { return id; }
std::string Medico::getNombre() const { return nombre; }
std::string Medico::getApellido() const { return apellido; }
std::string Medico::getEspecialidad() const { return especialidad; }
bool Medico::getDisponibilidad() const { return disponibilidad; }