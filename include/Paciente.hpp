#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "HistorialMedico.hpp"
#include <string>

class Paciente {
private:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string direccion;
    int edad;

public:
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
    
    // Método para cargar el historial bajo demanda
    HistorialMedico cargarHistorial() const;
    //const HistorialMedico& getHistorialMedico() const;
};

#endif