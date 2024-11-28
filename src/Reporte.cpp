#include "Reporte.hpp"
#include <iostream>
#include <algorithm>

// Generar listado de pacientes atendidos en un rango de fechas
void Reporte::generarListadoPacientes(const std::vector<Paciente>& pacientes, const std::vector<Cita>& citas,
    const std::string& fechaInicio, const std::string& fechaFin) {
    std::cout << "Pacientes atendidos entre " << fechaInicio << " y " << fechaFin << ":\n";

    for (const auto& cita : citas) {
        if (cita.getFecha() >= fechaInicio && cita.getFecha() <= fechaFin) {
            for (const auto& paciente : pacientes) {
                if (paciente.getID() == cita.getPacienteID()) {
                    std::cout << "- " << paciente.getNombreCompleto() << " (ID: " << paciente.getID() << ")\n";
                }
            }
        }
    }
}

// Generar listado de citas pendientes por médico
void Reporte::generarCitasPendientes(const std::vector<Cita>& citas, const std::vector<Medico>& medicos) {
    std::cout << "Citas pendientes por médico:\n";

    for (const auto& medico : medicos) {
        std::cout << "\nMédico: " << medico.getNombreCompleto() << " (ID: " << medico.getID() << ")\n";
        for (const auto& cita : citas) {
            if (cita.getMedicoID() == medico.getID() && cita.getFecha() >= "2024-11-26") {
                std::cout << "- Cita ID: " << cita.getCitaID() << ", Fecha: " << cita.getFecha() << "\n";
            }
        }
    }
}

// Generar reporte de pacientes con enfermedades crónicas
void Reporte::generarReporteEnfermedadesCronicas(const std::vector<Paciente>& pacientes) {
    std::cout << "Pacientes con enfermedades crónicas:\n";

    for (const auto& paciente : pacientes) {
        const auto& historial = paciente.getHistorialClinico();
        for (const auto& registro : historial) {
            if (registro.find("crónica") != std::string::npos) {
                std::cout << "- " << paciente.getNombreCompleto() << " (ID: " << paciente.getID() << ")\n";
                break; // Ya no necesitamos revisar más registros para este paciente
            }
        }
    }
}
