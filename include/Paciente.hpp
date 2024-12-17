#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "HistorialMedico.hpp"
#include <string>

class Paciente {
private:
    std::string id;                // Identificador �nico del paciente
    std::string nombre;            // Nombre del paciente
    std::string apellido;          // Apellido del paciente
    std::string direccion;         // Direcci�n del paciente
    int edad;                      // Edad del paciente
    HistorialMedico historialMedico; // Historial cl�nico del paciente

public:
    // Constructor
    Paciente(const std::string& id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    // M�todo para modificar datos personales
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