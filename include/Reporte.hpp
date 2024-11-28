#ifndef REPORTE_HPP
#define REPORTE_HPP

#include <vector>
#include <string>
#include "Paciente.hpp"
#include "Cita.hpp"
#include "Medico.hpp"

class Reporte {
public:
    static void generarListadoPacientes(const std::vector<Paciente>& pacientes, const std::vector<Cita>& citas,
                                        const std::string& fechaInicio, const std::string& fechaFin);
    static void generarCitasPendientes(const std::vector<Cita>& citas, const std::vector<Medico>& medicos);
    static void generarReporteEnfermedadesCronicas(const std::vector<Paciente>& pacientes);
};

#endif
