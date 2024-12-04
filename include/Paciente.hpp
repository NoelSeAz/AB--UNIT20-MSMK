#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include <vector>

class Paciente {
private:
    int ID;                                 // Identificador �nico del paciente
    std::string nombre;                     // Nombre del paciente
    std::string apellido;                   // Apellido del paciente
    std::string direccion;                  // Direcci�n del paciente
    int edad;                               // Edad del paciente
    std::vector<std::string> historialClinico; // Historial cl�nico del paciente

public:
    // Constructor
    Paciente(int id, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    // M�todos para gestionar el historial cl�nico
    void registrarHistorial(const std::string& registro);
    void mostrarHistorial() const;

    // M�todos para acceder y modificar datos personales
    void modificarDatos(const std::string& nuevaDireccion, int nuevaEdad);

    // Getters
    int getID() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDireccion() const;
    int getEdad() const;
    const std::vector<std::string>& getHistorialClinico() const;
};

#endif
