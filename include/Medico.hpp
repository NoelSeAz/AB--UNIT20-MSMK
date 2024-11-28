#ifndef MEDICO_HPP
#define MEDICO_HPP

#include <string>
#include <vector>

class Medico {
private:
    int ID;                           // Identificador �nico del m�dico
    std::string nombre;               // Nombre del m�dico
    std::string apellido;             // Apellido del m�dico
    std::string especialidad;         // Especialidad del m�dico
    bool disponibilidad;              // Disponibilidad del m�dico (true: disponible, false: ocupado)
    std::vector<int> listaCitas;      // IDs de las citas asignadas al m�dico

public:
    // Constructor
    Medico(int id, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    // M�todos para gestionar la especialidad
    void asignarEspecialidad(const std::string& nuevaEspecialidad);

    // M�todos para la disponibilidad
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    bool obtenerDisponibilidad() const;

    // M�todos relacionados con citas
    void agregarCita(int citaID);
    void mostrarCitas() const;

    // M�todos de depuraci�n
    void imprimirDatos() const;
};

#endif
