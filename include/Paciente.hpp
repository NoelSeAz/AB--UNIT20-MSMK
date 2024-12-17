#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "HistorialMedico.hpp"
#include <string>

class Paciente {
private:
    std::string id;                // Identificador único del paciente
    std::string nombre;            // Nombre del paciente
    std::string apellido;          // Apellido del paciente
    std::string direccion;         // Dirección del paciente
    int edad;                      // Edad del paciente
    HistorialMedico historialMedico; // Historial clínico del paciente

public:
    // Constructor
    Paciente(const std::string& id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    // Método para modificar datos personales
    void modificarDatos(const std::string& nuevaDireccion, int nuevaEdad);

    // Getters
    std::string getID() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDireccion() const;
    int getEdad() const;
    HistorialMedico& getHistorialMedico();
    const HistorialMedico& getHistorialMedico() const;
};

#endif