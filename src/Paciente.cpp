#include "Paciente.hpp"
#include "Formateador.hpp"
#include <iostream>
#include <iomanip>
#include "Archivo.hpp"

// Constructor
Paciente::Paciente(const std::string& idParam, const std::string& nombreParam, const std::string& apellidoParam,
    const std::string& direccionParam, int edadParam) {
    id = idParam;
    nombre = nombreParam;
    apellido = apellidoParam;
    direccion = direccionParam;
    edad = edadParam;
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

// Cargar historial cl�nico bajo demanda
HistorialMedico Paciente::cargarHistorial() const{
    HistorialMedico historial(id);
    Archivo::cargarHistorialMedico(historial);
    return historial;
}