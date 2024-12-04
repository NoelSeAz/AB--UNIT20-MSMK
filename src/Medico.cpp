#include "Medico.hpp"
#include <iostream>
#include <iomanip>

// Constructor
Medico::Medico(int id, const std::string& nombre, const std::string& apellido, 
               const std::string& especialidad, bool disponibilidad)
    : ID(id), nombre(nombre), apellido(apellido), especialidad(especialidad), disponibilidad(disponibilidad) {}

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

// Agregar una cita al médico
void Medico::agregarCita(int citaID) {
    listaCitas.push_back(citaID);
}

// Mostrar todas las citas asignadas al médico
void Medico::mostrarCitas() const {
    std::cout << "Citas del médico " << nombre << " " << apellido << ":\n";
    for (const auto& cita : listaCitas) {
        std::cout << "- ID de la cita: " << cita << "\n";
    }
}

int Medico::getID() const {
    return ID;
}

std::string Medico::getNombre() const {
    return nombre;
}

std::string Medico::getApellido() const {
    return apellido;
}

std::string Medico::getEspecialidad() const {
    return especialidad;
}