#ifndef REPORTE_HPP
#define REPORTE_HPP

#include <string>
#include <vector>
#include "Paciente.hpp"
#include "Cita.hpp"
#include "Medico.hpp"

class Reporte {
public:
    // Generar reportes de pacientes atendidos en un rango de fechas
    static void generarListadoPacientes(const std::vector<Paciente>& pacientes, const std::vector<Cita>& citas,
        const std::string& fechaInicio, const std::string& fechaFin);

    // Generar citas pendientes por m�dico
    static void generarCitasPendientes(const std::vector<Cita>& citas, const std::vector<Medico>& medicos);

    // Generar un reporte de pacientes con enfermedades cr�nicas
    static void generarReporteEnfermedadesCronicas(const std::vector<Paciente>& pacientes);

private:
    // M�todos auxiliares (si es necesario) podr�an declararse aqu�
};

#endif
