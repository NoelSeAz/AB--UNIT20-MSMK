#include "Reporte.hpp"
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
    std::cout << "Pacientes con enfermedades cr�nicas:\n";

    for (const auto& paciente : pacientes) {
        const auto& historial = paciente.getHistorialClinico();
        bool encontrado = false;

        for (const auto& registro : historial) {
            auto pos = registro.find("cr�nica");
            if (pos != std::string::npos || registro.find("Cr�nica") != std::string::npos) {
                encontrado = true;
                break;
            }
        }

        if (encontrado) {
            std::cout << "- " << paciente.getNombre() << " " << paciente.getApellido()
                << " (ID: " << paciente.getID() << ")\n";
        }
    }
}
