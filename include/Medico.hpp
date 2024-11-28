#ifndef MEDICO_HPP
#define MEDICO_HPP

#include <string>
#include <vector>

class Medico {
private:
    int ID;                           // Identificador único del médico
    std::string nombre;               // Nombre del médico
    std::string apellido;             // Apellido del médico
    std::string especialidad;         // Especialidad del médico
    bool disponibilidad;              // Disponibilidad del médico (true: disponible, false: ocupado)
    std::vector<int> listaCitas;      // IDs de las citas asignadas al médico

public:
    // Constructor
    Medico(int id, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    // Métodos para gestionar la especialidad
    void asignarEspecialidad(const std::string& nuevaEspecialidad);

    // Métodos para la disponibilidad
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    bool obtenerDisponibilidad() const;

    // Métodos relacionados con citas
    void agregarCita(int citaID);
    void mostrarCitas() const;

    // Métodos de depuración
    void imprimirDatos() const;

    // Getters
    int getID() const;
    std::string getNombreCompleto() const;
};

#endif
