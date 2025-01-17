#ifndef GESTORCITAS_HPP
#define GESTORCITAS_HPP

#include "Cita.hpp"
#include <vector>
#include <string>
#include <algorithm>

class GestorCitas {
public:
    // Crear una nueva cita
    static void crearCita(std::vector<Cita>& citas, const std::string& pacienteID,
        const std::string& medicoID, const std::string& fecha, int prioridad);

    // Modificar una cita existente
    static bool modificarCita(std::vector<Cita>& citas, const std::string& citaID,
        const std::string& nuevaFecha, int nuevaPrioridad);

    // Cancelar una cita
    static void cancelarCita(std::vector<Cita>& citas, const std::string& citaID);

    // Ordenar citas
    static void ordenarCitasPorFecha(std::vector<Cita>& citas);
    static void ordenarCitasPorPrioridad(std::vector<Cita>& citas);
};

#endif
