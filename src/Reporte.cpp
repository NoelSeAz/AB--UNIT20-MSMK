#include "Reporte.hpp"
#include "Paciente.hpp"
#include <iostream>
#include <algorithm>

// Generar listado de pacientes atendidos en un rango de fechas
void Reporte::generarListadoPacientes(const std::vector<Paciente>& pacientes, const std::vector<Cita>& citas,
    const std::string& fechaInicio, const std::string& fechaFin) {
    std::cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";

    for (const auto& cita : citas) {
        if (cita.getFecha() >= fechaInicio && cita.getFecha() <= fechaFin) {
            auto it = std::find_if(pacientes.begin(), pacientes.end(),
                [&cita](const Paciente& paciente) {
                    return paciente.getID() == cita.getPacienteID();
                });

            if (it != pacientes.end()) {
                std::cout << "- " << it->getNombre() << " " << it->getApellido()
                    << " (ID: " << it->getID() << ")\n";
            }
        }
    }
}

// Generar listado de citas pendientes por m�dico
void Reporte::generarCitasPendientes(const std::vector<Cita>& citas, const std::vector<Medico>& medicos) {
    std::cout << "Citas pendientes por m�dico:\n";

    for (const auto& medico : medicos) {
        std::cout << "\nM�dico: " << medico.getNombre() << " " << medico.getApellido()
            << " (ID: " << medico.getID() << ")\n";
        for (const auto& cita : citas) {
            if (cita.getMedicoID() == medico.getID() && cita.getFecha() >= "2024-11-26") {
                std::cout << "- Cita ID: " << cita.getCitaID()
                    << ", Fecha: " << cita.getFecha() << "\n";
            }
        }
    }
}

// Generar reporte de pacientes con enfermedades cr�nicas
void Reporte::generarReporteEnfermedadesCronicas(const std::vector<Paciente>& pacientes) {
    std::cout << "\n--- Reporte de Enfermedades Cr�nicas ---\n";
    for (const auto& paciente : pacientes) {
        const auto& historial = paciente.getHistorialMedico();
        std::cout << "Paciente: " << paciente.getNombre() << " " << paciente.getApellido() << "\n";

        const auto& enfermedades = historial.getEnfermedadesCronicas();
        if (enfermedades.empty()) {
            std::cout << "  No se registran enfermedades cr�nicas.\n";
        }
        else {
            for (const auto& enfermedad : enfermedades) {
                std::cout << "  Enfermedad: " << enfermedad.getNombre()
                    << ", Severidad: " << enfermedad.getSeveridad()
                    << ", Tratamiento: " << enfermedad.getTratamiento()
                    << ", Diagn�stico: " << enfermedad.getFechaDiagnostico() << "\n";
            }
        }
        std::cout << "----------------------------------------\n";
    }
}