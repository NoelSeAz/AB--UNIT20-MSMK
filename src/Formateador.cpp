#include "Formateador.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

// M�todos para imprimir encabezados
void Formateador::imprimirEncabezadoPacientes() {
    std::cout << std::left;
    std::cout << std::setw(10) << "ID"
        << std::setw(20) << "Nombre"
        << std::setw(20) << "Apellido"
        << std::setw(30) << "Direcci�n"
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
        << std::setw(15) << "M�dico ID"
        << std::setw(15) << "Fecha"
        << std::setw(15) << "Prioridad"
        << "\n";
    std::cout << std::string(100, '-') << "\n";
}

void Formateador::imprimirEncabezadoEspecialidades() {
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(20) << "Nombre"
        << std::setw(50) << "Descripci�n"
        << "\n";
    std::cout << std::string(75, '-') << "\n";
}

// M�todos para imprimir registros individuales
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

void Formateador::imprimirRegistro(const Especialidad& especialidad) {
    std::cout << std::left << std::setw(5) << especialidad.getID()
        << std::setw(20) << especialidad.getNombre()
        << std::setw(50) << especialidad.getDescripcion()
        << "\n";
}

// M�todos para imprimir tablas completas
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

void Formateador::imprimirTablaEspecialidades(const std::vector<Especialidad>& especialidades) {
    imprimirEncabezadoEspecialidades();
    for (const auto& especialidad : especialidades) {
        imprimirRegistro(especialidad);
    }
}

void Formateador::imprimirHistorialMedico(const HistorialMedico& historial) {
    size_t anchoFecha = 20;
    size_t anchoDiagnostico = 50;
    size_t anchoPrueba = 50;
    size_t anchoEnfermedad = 30;
    size_t anchoSeveridad = 10;  // Mant�n esto fijo
    size_t anchoTratamiento = 50;

    std::cout << std::left;
    std::cout << "\n--- Historial M�dico del Paciente ID: " << historial.getPacienteID() << " ---\n";

    // Diagn�sticos
    std::cout << "\n" << std::setw(anchoFecha) << "Fecha"
        << " " << std::setw(anchoDiagnostico) << "Diagn�stico" << "\n";
    std::cout << std::string(anchoFecha + 1 + anchoDiagnostico, '-') << "\n";
    for (const auto& [fecha, diagnostico] : historial.getDiagnosticos()) {
        auto lineas = dividirTexto(diagnostico, anchoDiagnostico);
        std::cout << std::setw(anchoFecha) << fecha
            << " " << lineas[0] << "\n";
        for (size_t i = 1; i < lineas.size(); ++i) {
            std::cout << std::setw(anchoFecha) << " "
                << " " << lineas[i] << "\n";
        }
    }

    // Pruebas
    std::cout << "\n" << std::setw(anchoFecha) << "Fecha"
        << " " << std::setw(anchoPrueba) << "Prueba Realizada" << "\n";
    std::cout << std::string(anchoFecha + 1 + anchoPrueba, '-') << "\n";
    for (const auto& [fecha, prueba] : historial.getPruebas()) {
        auto lineas = dividirTexto(prueba, anchoPrueba);
        std::cout << std::setw(anchoFecha) << fecha
            << " " << lineas[0] << "\n";
        for (size_t i = 1; i < lineas.size(); ++i) {
            std::cout << std::setw(anchoFecha) << " "
                << " " << lineas[i] << "\n";
        }
    }

    // Enfermedades
    std::cout << "\n" << std::setw(anchoFecha) << "Fecha Diagn�stico"
        << " " << std::setw(anchoEnfermedad) << "Enfermedad"
        << " " << std::setw(anchoSeveridad) << "Severidad"
        << " " << std::setw(anchoTratamiento) << "Tratamiento" << "\n";
    std::cout << std::string(anchoFecha + 1 + anchoEnfermedad + 1 + anchoSeveridad + 1 + anchoTratamiento, '-') << "\n";
    for (const auto& enfermedad : historial.getEnfermedadesCronicas()) {
        auto lineasEnfermedad = dividirTexto(enfermedad.getNombre(), anchoEnfermedad);
        auto lineasTratamiento = dividirTexto(enfermedad.getTratamiento(), anchoTratamiento);

        size_t maxLineas = std::max(lineasEnfermedad.size(), lineasTratamiento.size());
        for (size_t i = 0; i < maxLineas; ++i) {
            std::cout << std::setw(anchoFecha) << (i == 0 ? enfermedad.getFechaDiagnostico() : "")
                << " " << std::setw(anchoEnfermedad) << (i < lineasEnfermedad.size() ? lineasEnfermedad[i] : "")
                << " " << std::setw(anchoSeveridad) << (i == 0 ? "   " + std::to_string(enfermedad.getSeveridad()) : "")
                << " " << std::setw(anchoTratamiento) << (i < lineasTratamiento.size() ? lineasTratamiento[i] : "") << "\n";
        }
    }

    // Notas generales
    std::cout << "\nNotas Generales:\n";
    std::cout << historial.getNotas() << "\n";
    std::cout << std::string(80, '-') << "\n";
}

void Formateador::imprimirEnfermedadCronica(const EnfermedadCronica& enfermedad) {
    std::cout << std::left;
    std::cout << "\n--- Detalles de Enfermedad Cr�nica ---\n";
    std::cout << std::setw(20) << "Nombre"
        << std::setw(20) << "Fecha Diagn�stico"
        << std::setw(30) << "Tratamiento Actual" << "\n";
    std::cout << std::string(70, '-') << "\n";

    std::cout << std::setw(20) << enfermedad.getNombre()
        << std::setw(20) << enfermedad.getFechaDiagnostico()
        << std::setw(30) << enfermedad.getTratamiento() << "\n";
}

//M�todo para limpiar la pantalla
void Formateador::limpiarPantalla() {
    #if defined(_WIN32)
        std::system("cls");
    #elif defined(__linux__) || defined(__APPLE__)
        std::system("clear");
    #else
        std::cout << "\nLimpieza no soportada en este sistema operativo.\n";
    #endif
}

//M�todos para ajustar y ordenar el texto
std::vector<std::string> Formateador::dividirTexto(const std::string& texto, size_t ancho) {
    std::vector<std::string> lineas;
    size_t inicio = 0;

    while (inicio < texto.size()) {
        size_t longitud = std::min(ancho, texto.size() - inicio);
        lineas.push_back(texto.substr(inicio, longitud));
        inicio += longitud;
    }

    return lineas;
}