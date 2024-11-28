#include "Paciente.hpp"
#include <iostream>

// Constructor
Paciente::Paciente(int id, const std::string& nombre, const std::string& apellido,
    const std::string& direccion, int edad)
    : ID(id), nombre(nombre), apellido(apellido), direccion(direccion), edad(edad) {}

// Registrar un nuevo historial cl�nico
void Paciente::registrarHistorial(const std::string& registro) {
    historialClinico.push_back(registro);
}

// Mostrar el historial cl�nico completo
void Paciente::mostrarHistorial() const {
    std::cout << "Historial cl�nico de " << nombre << " " << apellido << ":\n";
    for (const auto& registro : historialClinico) {
        std::cout << "- " << registro << "\n";
    }
}

// Modificar datos personales del paciente
void Paciente::modificarDatos(const std::string& nuevaDireccion, int nuevaEdad) {
    direccion = nuevaDireccion;
    edad = nuevaEdad;
}

// Imprimir los datos del paciente
void Paciente::imprimirDatos() const {
    std::cout << "Paciente ID: " << ID << "\n"
        << "Nombre: " << nombre << " " << apellido << "\n"
        << "Direcci�n: " << direccion << "\n"
        << "Edad: " << edad << "\n";
}
