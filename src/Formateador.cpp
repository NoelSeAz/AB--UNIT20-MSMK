#include "Formateador.hpp"
#include "HistorialMedico.hpp"
#include "EnfermedadCronica.hpp"
#include <iostream>
#include <iomanip>

// Métodos para imprimir encabezados
void Formateador::imprimirEncabezadoPacientes() {
    std::cout << std::left;
    std::cout << std::setw(10) << "ID"
        << std::setw(20) << "Nombre"
        << std::setw(20) << "Apellido"
        << std::setw(30) << "Dirección"
        << std::setw(5) << "Edad"
        << "\n";
    std::cout << std::string(100, '-') << "\n";
}

void Formateador::imprimirEncabezadoMedicos() {
    std::cout << std::left;
    std::cout << std::setw(10) << "ID"
        << std::setw(20) << "Nombre"
        << std::setw(20) << "Apellido"
        << std::setw(20) << "Especialidad"
        << std::setw(12) << "Disponibilidad"
        << "\n";
    std::cout << std::string(100, '-') << "\n";
}

void Formateador::imprimirEncabezadoCitas() {
    std::cout << std::left;
    std::cout << std::setw(15) << "Cita ID Hash"
        << std::setw(25) << "Cita ID"
        << std::setw(15) << "Paciente ID"
        << std::setw(15) << "Médico ID"
        << std::setw(15) << "Fecha"
        << std::setw(15) << "Prioridad"
        << "\n";
    std::cout << std::string(100, '-') << "\n";
}

// Métodos para imprimir registros individuales
void Formateador::imprimirRegistro(const Paciente& paciente) {
    std::cout << std::left;
    std::cout << std::setw(10) << paciente.getID()
        << std::setw(20) << paciente.getNombre()
        << std::setw(20) << paciente.getApellido()
        << std::setw(30) << paciente.getDireccion()
        << std::setw(5) << paciente.getEdad()
        << "\n";
}

void Formateador::imprimirRegistro(const Medico& medico) {
    std::cout << std::left;
    std::cout << std::setw(10) << medico.getID()
        << std::setw(20) << medico.getNombre()
        << std::setw(20) << medico.getApellido()
        << std::setw(20) << medico.getEspecialidad()
        << std::setw(12) << (medico.obtenerDisponibilidad() ? "Disponible" : "Ocupado")
        << "\n";
}

void Formateador::imprimirRegistro(const Cita& cita) {
    std::cout << std::left;
    std::cout << std::setw(15) << cita.getCitaIDHash()
        << std::setw(25) << cita.getCitaID()
        << std::setw(15) << cita.getPacienteID()
        << std::setw(15) << cita.getMedicoID()
        << std::setw(15) << cita.getFecha()
        << std::setw(15) << (cita.getPrioridad() == 1 ? "Urgente" : "Normal")
        << "\n";
}

// Métodos para imprimir tablas completas
void Formateador::imprimirTablaPacientes(const std::vector<Paciente>& pacientes) {
    imprimirEncabezadoPacientes();
    for (const auto& paciente : pacientes) {
        imprimirRegistro(paciente);
    }
}

void Formateador::imprimirTablaMedicos(const std::vector<Medico>& medicos) {
    imprimirEncabezadoMedicos();
    for (const auto& medico : medicos) {
        imprimirRegistro(medico);
    }
}

void Formateador::imprimirTablaCitas(const std::vector<Cita>& citas) {
    imprimirEncabezadoCitas();
    for (const auto& cita : citas) {
        imprimirRegistro(cita);
    }
}

void Formateador::imprimirHistorialMedico(const HistorialMedico& historial) {
    std::cout << std::left;
    std::cout << "\n--- Historial Médico del Paciente ID: " << historial.getPacienteID() << " ---\n";

    // Tabla de Diagnósticos
    std::cout << "\n" << std::setw(20) << "Fecha" << std::setw(30) << "Diagnóstico" << "\n";
    std::cout << std::string(50, '-') << "\n";
    for (const auto& [fecha, diagnostico] : historial.getDiagnosticos()) {
        std::cout << std::setw(20) << fecha << std::setw(30) << diagnostico << "\n";
    }

    // Tabla de Pruebas Realizadas
    std::cout << "\n" << std::setw(20) << "Fecha" << std::setw(30) << "Prueba Realizada" << "\n";
    std::cout << std::string(50, '-') << "\n";
    for (const auto& [fecha, prueba] : historial.getPruebas()) {
        std::cout << std::setw(20) << fecha << std::setw(30) << prueba << "\n";
    }

    // Tabla de Enfermedades Crónicas
    std::cout << "\n" << std::setw(20) << "Fecha Diagnóstico" << std::setw(25) << "Enfermedad"
        << std::setw(15) << "Severidad" << std::setw(30) << "Tratamiento" << "\n";
    std::cout << std::string(90, '-') << "\n";
    for (const auto& enfermedad : historial.getEnfermedadesCronicas()) {
        std::cout << std::setw(20) << enfermedad.getFechaDiagnostico()
            << std::setw(25) << enfermedad.getNombre()
            << std::setw(15) << enfermedad.getSeveridad()
            << std::setw(30) << enfermedad.getTratamiento() << "\n";
    }

    // Notas generales
    std::cout << "\nNotas Generales:\n";
    std::cout << historial.getNotas() << "\n";
    std::cout << std::string(90, '-') << "\n";
}

// Imprimir Enfermedad Crónica
void Formateador::imprimirEnfermedadCronica(const EnfermedadCronica& enfermedad) {
    std::cout << std::left;
    std::cout << "\n--- Detalles de Enfermedad Crónica ---\n";
    std::cout << std::setw(20) << "Nombre"
        << std::setw(20) << "Fecha Diagnóstico"
        << std::setw(30) << "Tratamiento Actual" << "\n";
    std::cout << std::string(70, '-') << "\n";

    std::cout << std::setw(20) << enfermedad.getNombre()
        << std::setw(20) << enfermedad.getFechaDiagnostico()
        << std::setw(30) << enfermedad.getTratamiento() << "\n";
}

void Formateador::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #elif __APPLE__
        system("clear");
    #else
        std::cout << "\nLimpieza no soportada en este sistema operativo.\n";
    #endif
}