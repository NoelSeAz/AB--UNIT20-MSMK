#include "Paciente.hpp"
#include <Formateador.hpp>
#include <iostream>
#include <iomanip>

// Constructor
Paciente::Paciente(const std::string& id, const std::string& nombre, const std::string& apellido,
    const std::string& direccion, int edad)
    : ID(id), nombre(nombre), apellido(apellido), direccion(direccion), edad(edad) {}

// Registrar un nuevo historial clínico
void Paciente::registrarHistorial(const std::string& registro) {
    historialClinico.push_back(registro);
}

// Mostrar el historial clínico completo
void Paciente::mostrarHistorial() const {
    std::cout << "Historial clínico de " << nombre << " " << apellido << ":\n";
    for (const auto& registro : historialClinico) {
        std::cout << "- " << registro << "\n";
    }
}

// Modificar datos personales del paciente
void Paciente::modificarDatos(const std::string& nuevaDireccion, int nuevaEdad) {
    direccion = nuevaDireccion;
    edad = nuevaEdad;
}

// Getters
std::string Paciente::getID() const {
    return ID;
}

std::string Paciente::getNombre() const {
    return nombre;
}

std::string Paciente::getApellido() const {
    return apellido;
}

std::string Paciente::getDireccion() const {
    return direccion;
}

int Paciente::getEdad() const {
    return edad;
}

const std::vector<std::string>& Paciente::getHistorialClinico() const {
    return historialClinico;
}
