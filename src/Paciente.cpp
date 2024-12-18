#include "Paciente.hpp"
#include "Formateador.hpp"
#include <iostream>
#include <iomanip>
#include "Archivo.hpp"

// Constructor
Paciente::Paciente(const std::string& id, const std::string& nombre, const std::string& apellido,
    const std::string& direccion, int edad)
    : id(id), nombre(nombre), apellido(apellido), direccion(direccion), edad(edad) {
}

// Modificar datos personales del paciente
void Paciente::modificarDatos(const std::string& nuevaDireccion, int nuevaEdad) {
    if (nuevaEdad > 0) {
        edad = nuevaEdad;
    }
    direccion = nuevaDireccion;
}

// Getters
std::string Paciente::getID() const { return id; }
std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getApellido() const { return apellido; }
std::string Paciente::getDireccion() const { return direccion; }
int Paciente::getEdad() const { return edad; }

// Cargar historial clínico bajo demanda
HistorialMedico Paciente::cargarHistorial() const{
    HistorialMedico historial(id);
    Archivo::cargarHistorialMedico(historial);
    return historial;
}