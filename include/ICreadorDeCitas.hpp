#ifndef ICREADORDECITAS_HPP
#define ICREADORDECITAS_HPP

#include <vector>
#include <string>
#include "Cita.hpp"

class ICreadorDeCitas {
public:
    virtual ~ICreadorDeCitas() = default;

    // Método para crear una cita
    virtual void crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad) = 0;
};

#endif
