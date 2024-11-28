#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include <vector>

class Paciente {
private:
    int ID;                                 // Identificador único del paciente
    std::string nombre;                     // Nombre del paciente
    std::string apellido;                   // Apellido del paciente
    std::string direccion;                  // Dirección del paciente
    int edad;                               // Edad del paciente
    std::vector<std::string> historialClinico; // Historial clínico del paciente

public:
    // Constructor
    Paciente(int id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    // Métodos para gestionar el historial clínico
    void registrarHistorial(const std::string& registro);
    void mostrarHistorial() const;

    // Métodos para acceder y modificar datos personales
    void modificarDatos(const std::string& nuevaDireccion, int nuevaEdad);

    // Métodos de depuración
    void imprimirDatos() const;
};

#endif
