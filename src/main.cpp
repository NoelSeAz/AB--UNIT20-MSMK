#include "Paciente.hpp"
#include "Cita.hpp"
#include "Medico.hpp"
#include <windows.h>
#include "Archivo.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

        // Crear datos de prueba
        std::vector<Paciente> pacientes = { Paciente(1, "Juan", "Perez", "Calle 123", 30) };
        std::vector<Medico> medicos = { Medico(1, "Ana", "Gomez", "Cardiología", true) };
        std::vector<Cita> citas = { Cita(1, 1, 1, "2024-11-27", 1) };

        // Guardar datos
        Archivo::guardarPacientes(pacientes, "pacientes.txt");
        Archivo::guardarMedicos(medicos, "medicos.txt");
        Archivo::guardarCitas(citas, "citas.txt");

        // Cargar datos
        auto pacientesCargados = Archivo::cargarPacientes("pacientes.txt");
        for (const auto& paciente : pacientesCargados) {
            paciente.imprimirDatos();
        }

        auto medicosCargados = Archivo::cargarMedicos("medicos.txt");
        for (const auto& medico : medicosCargados) {
            medico.imprimirDatos();
        }

        return 0;
    }

