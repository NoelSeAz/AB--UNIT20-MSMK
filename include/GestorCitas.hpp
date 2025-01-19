#ifndef GESTORCITAS_HPP
#define GESTORCITAS_HPP

#include "Cita.hpp"
#include "GestorMedicos.hpp"
#include "GestorPacientes.hpp"
#include "ArchivosActivos.hpp"

#include <vector>
#include <string>
#include <algorithm>

class GestorCitas {
public:
    // Crear una nueva cita
    static void crearCita(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes,
        const std::vector<Medico>& medicos, ArchivosActivos& archivos);

    // Modificar una cita existente
    static bool modificarCita(std::vector<Cita>& citas, const std::string& citaID, 
        const std::vector<Medico>& medicos, ArchivosActivos& archivos);


    // Cancelar una cita
    static void cancelarCita(std::vector<Cita>& citas, const std::string& citaID, ArchivosActivos& archivos);

    // Ordenar citas
    static void ordenarCitasPorFecha(std::vector<Cita>& citas);
    static void ordenarCitasPorPrioridad(std::vector<Cita>& citas);

    // Filtrar citas
    static std::vector<Cita> filtrarCitasPorPaciente(const std::vector<Cita>& citas, const std::string& pacienteID);
    static std::vector<Cita> filtrarCitasPorMedico(const std::vector<Cita>& citas, const std::string& medicoID);
};

#endif
