#ifndef GESTORCITAS_HPP
#define GESTORCITAS_HPP

#include "Cita.hpp"
#include "InputValidator.hpp"
#include "Archivo.hpp"
#include <vector>
#include <string>

class GestorCitas {
public:
    static void crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad);
    static void cancelarCita(std::vector<Cita>& citas, const std::string& citaID);
    static void modificarCita(std::vector<Cita>& citas, const std::string& citaID, const std::string& nuevaFecha, int nuevaPrioridad);
};

#endif
