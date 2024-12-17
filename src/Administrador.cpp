#include "Administrador.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "InputValidator.hpp"
#include "Archivo.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Alta de médicos
void GestorAdministrativo::altaMedico(std::vector<Medico>& medicos, const std::string& nombre, const std::string& apellido,
    const std::string& especialidad, bool disponibilidad) {
    std::vector<std::string> idsExistentes;
    for (const auto& medico : medicos) {
        idsExistentes.push_back(medico.getID());
    }

    std::string ID = IDGenerator::generarID("M", nombre, apellido, idsExistentes);
    auto& nuevoMedico = medicos.emplace_back(ID, nombre, apellido, especialidad, disponibilidad);
    Formateador::imprimirEncabezadoMedicos();
    Formateador::imprimirRegistro(nuevoMedico);
    std::cout << "\nMédico dado de alta exitosamente.\n";

    Archivo archivo;
    archivo.guardarMedicos(medicos, "./data/archivo_medicos.txt");
}

// Baja de médicos
void GestorAdministrativo::bajaMedico(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        Archivo archivo;
        archivo.guardarMedicos(medicos, "./data/archivo_medicos.txt");
        std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
    }
    else {
        std::cout << "Error: No se encontró un médico con el ID " << id << ".\n";
    }
}

// Alta de pacientes
void GestorAdministrativo::altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre,
    const std::string& apellido, const std::string& direccion, int edad) {
    std::vector<std::string> idsExistentes;
    for (const auto& paciente : pacientes) {
        idsExistentes.push_back(paciente.getID());
    }

    std::string ID = IDGenerator::generarID("P", nombre, apellido, idsExistentes);
    auto& nuevoPaciente = pacientes.emplace_back(ID, nombre, apellido, direccion, edad);
    Formateador::imprimirEncabezadoPacientes();
    Formateador::imprimirRegistro(nuevoPaciente);
    std::cout << "\nPaciente dado de alta exitosamente.\n";

    Archivo archivo;
    archivo.guardarPacientes(pacientes, "./data/archivo_pacientes.txt");
}

// Baja de pacientes
void GestorAdministrativo::bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        Archivo archivo;
        archivo.guardarPacientes(pacientes, "./data/archivo_pacientes.txt");
        std::cout << "Paciente con ID " << id << " dado de baja exitosamente.\n";
    }
    else {
        std::cout << "Error: No se encontró un paciente con el ID " << id << ".\n";
    }
}

// Buscar paciente por ID
Paciente* GestorAdministrativo::buscarPacientePorID(const std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [id](const Paciente& paciente) {
        return paciente.getID() == id;
        });

    if (it != pacientes.end()) {
        return const_cast<Paciente*>(&(*it)); // Devuelve un puntero al paciente encontrado
    }
    else {
        std::cerr << "Error: No se encontró un paciente con el ID " << id << ".\n";
        return nullptr;
    }
}

// Buscar médico por ID
Medico* GestorAdministrativo::buscarMedicoPorID(const std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [id](const Medico& medico) {
        return medico.getID() == id;
        });

    if (it != medicos.end()) {
        return const_cast<Medico*>(&(*it)); // Devuelve un puntero al médico encontrado
    }
    else {
        std::cerr << "Error: No se encontró un médico con el ID " << id << ".\n";
        return nullptr;
    }
}

void GestorAdministrativo::cargarPacientes(std::vector<Paciente>& pacientes, const std::string& archivo) {
    pacientes = Archivo::cargarPacientes(archivo);
    std::cout << "Pacientes cargados desde " << archivo << "\n";
}

void GestorAdministrativo::cargarMedicos(std::vector<Medico>& medicos, const std::string& archivo) {
    medicos = Archivo::cargarMedicos(archivo);
    std::cout << "Médicos cargados desde " << archivo << "\n";
}

void GestorAdministrativo::cargarCitas(std::vector<Cita>& citas, const std::string& archivo) {
    citas = Archivo::cargarCitas(archivo);
    std::cout << "Citas cargadas desde " << archivo << "\n";
}

void AdministradorCitas::crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad) {
    // Validar que la fecha sea futura
    if (!InputValidator::esFechaFutura(fecha)) {
        throw std::invalid_argument("La fecha debe ser igual o posterior a la fecha actual.");
    }

    // Generar un ID único para la cita
    unsigned long citaIDHash = IDGenerator::generarIDCitaHash(pacienteID, medicoID, fecha);
    std::string citaID = IDGenerator::generarIDCita(pacienteID, medicoID, fecha);

    // Convertir citaID a string (si es necesario para la clase Cita)
    std::ostringstream oss;
    oss << citaIDHash;
    std::string citaIDStr = oss.str();

    // Crear la cita
    Cita nuevaCita(citaIDStr, citaID, pacienteID, medicoID, fecha, prioridad);
    citas.push_back(nuevaCita);

    // Guardar la cita en archivo
    Archivo archivo;
    archivo.guardarCitas(citas, "./data/archivo_citas.txt");

    std::cout << "Cita creada exitosamente con ID Hash: " << citaIDStr << std::endl;
    Formateador::imprimirEncabezadoCitas();
    Formateador::imprimirRegistro(nuevaCita);
}
void AdministradorCitas::modificarCita(std::vector<Cita>& citas, const std::string& citaID, const std::string& nuevaFecha, int nuevaPrioridad) {
    auto it = std::find_if(citas.begin(), citas.end(), [citaID](Cita& cita) {
        return cita.getCitaID() == citaID;
        });

    if (it != citas.end()) {
        try {
            it->modificarCita(nuevaFecha, nuevaPrioridad);
            Archivo archivo;
            archivo.guardarCitas(citas, "./data/archivo_citas.txt");
            std::cout << "Cita con ID " << citaID << " modificada exitosamente.\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error al modificar la cita: " << e.what() << "\n";
        }
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID " << citaID << ".\n";
    }
}

void AdministradorCitas::cancelarCita(std::vector<Cita>& citas, const std::string& citaID) {
    auto it = std::find_if(citas.begin(), citas.end(), [citaID](const Cita& cita) {
        return cita.getCitaID() == citaID; // Cambiar int por std::string
        });

    if (it != citas.end()) {
        citas.erase(it);

        Archivo archivo;
        archivo.guardarCitas(citas, "./data/archivo_citas.txt");

        std::cout << "Cita con ID " << citaID << " cancelada exitosamente.\n";
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID " << citaID << ".\n";
    }
}