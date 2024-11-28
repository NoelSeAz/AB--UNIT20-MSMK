#include "Medico.hpp"
#include <iostream>

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

// Imprimir los datos del médico
void Medico::imprimirDatos() const {
    std::cout << "Médico ID: " << ID << "\n"
        << "Nombre: " << nombre << " " << apellido << "\n"
        << "Especialidad: " << especialidad << "\n"
        << "Disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << "\n";
}
