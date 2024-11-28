#include "Paciente.hpp"
#include "Cita.hpp"
#include "Medico.hpp"
#include "Administrador.hpp"
#include <windows.h>
#include "Archivo.hpp"
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Crear datos de prueba
    std::vector<Paciente> pacientes = { Paciente(1, "Juan", "Perez", "Calle 123", 30) };
    std::vector<Medico> medicos = { Medico(1, "Ana", "Gomez", "Cardiología", true) };
    std::vector<Cita> citas = { Cita(1, 1, 1, "2024-11-27", 1) };

    // Guardar datos
    Archivo::guardarPacientes(pacientes, "pacientes.csv");
    Archivo::guardarMedicos(medicos, "medicos.txt");
    Archivo::guardarCitas(citas, "citas.txt");

    // Cargar y mostrar datos de pacientes
    auto pacientesCargados = Archivo::cargarPacientes("pacientes.txt");
    std::cout << "\nPacientes Cargados:\n";
    for (const auto& paciente : pacientesCargados) {
        paciente.imprimirDatos();
    }

    // Cargar y mostrar datos de médicos
    auto medicosCargados = Archivo::cargarMedicos("medicos.txt");
    std::cout << "\nMédicos Cargados:\n";
    for (const auto& medico : medicosCargados) {
        medico.imprimirDatos();
    }

    // Cargar y mostrar datos de citas
    auto citasCargadas = Archivo::cargarCitas("citas.txt");
    std::cout << "\nCitas Cargadas:\n";
    for (const auto& cita : citasCargadas) {
        std::cout << "Cita ID: " << cita.getCitaID()
            << ", Paciente ID: " << cita.getPacienteID()
            << ", Médico ID: " << cita.getMedicoID()
            << ", Fecha: " << cita.getFecha()
            << ", Prioridad: " << (cita.getPrioridad() == 1 ? "Urgente" : "Normal") << "\n";
    }

    // Alta de médicos
    Administrador::altaMedico(medicos, 1, "Luis", "Fernandez", "Cardiología", true);

    // Alta de pacientes
    Administrador::altaPaciente(pacientes, 3, "Anna", "Lopez", "Calle Falsa 123", 30);

    // Baja de médicos
    Administrador::bajaMedico(medicos, 1);

    // Baja de pacientes
    Administrador::bajaPaciente(pacientes, 1);
}
