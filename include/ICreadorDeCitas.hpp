#ifndef ICREADORDECITAS_HPP
#define ICREADORDECITAS_HPP

#include "Cita.hpp"
#include <vector>
#include <string>

// Interfaz para la gestión de citas
class ICreadorDeCitas {
public:
    virtual ~ICreadorDeCitas() = default;

    // Crear una nueva cita
    virtual void crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad) = 0;

    // Cancelar una cita existente
    virtual void cancelarCita(std::vector<Cita>& citas, const std::string& citaID) = 0;

    // Modificar una cita existente
    virtual void modificarCita(std::vector<Cita>& citas, const std::string& citaID, const std::string& nuevaFecha, int nuevaPrioridad) = 0;
};

#endif