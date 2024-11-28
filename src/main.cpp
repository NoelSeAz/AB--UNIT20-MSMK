#include "Paciente.hpp"
#include "Cita.hpp"
#include "Medico.hpp"
#include "Reporte.hpp"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Crear pacientes
    Paciente paciente1(1, "Juan", "Pérez", "Calle 123", 30);
    Paciente paciente2(2, "Ana", "Gómez", "Avenida 456", 40);

    paciente1.registrarHistorial("Consulta inicial - Sin observaciones.");
    paciente2.registrarHistorial("Diagnóstico de hipertensión crónica.");

    // Crear médicos
    Medico medico1(1, "Luis", "Fernández", "Cardiología", true);
    Medico medico2(2, "María", "López", "Neurología", true);

    // Crear citas
    Cita cita1(1, 1, 1, "2024-11-25", 0);
    Cita cita2(2, 2, 2, "2024-11-27", 1);
    std::vector<Cita> listaCitas = { cita1, cita2 };

    // Generar reportes
    Reporte::generarListadoPacientes({ paciente1, paciente2 }, listaCitas, "2024-11-24", "2024-11-26");
    Reporte::generarCitasPendientes(listaCitas, { medico1, medico2 });
    Reporte::generarReporteEnfermedadesCronicas({ paciente1, paciente2 });

    return 0;
}
