#include "GestorCitas.hpp"
#include "InputValidator.hpp"
#include "IDGenerator.hpp"
#include <iostream>
#include <algorithm> // Para std::sort

// Crear una nueva cita
void GestorCitas::crearCita(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes,
    const std::vector<Medico>& medicos) {
    // Solicitar ID del médico
    std::string medicoID = InputValidator::solicitarID<Medico>(
        "Ingrese el ID del médico: ",
        medicos,
        [](const Medico& medico) {
            return medico.getID();
        }
    );

    // Verificar disponibilidad del médico
    auto itMedico = std::find_if(medicos.begin(), medicos.end(), [&medicoID](const Medico& medico) {
        return medico.getID() == medicoID;
        });

    if (!itMedico->obtenerDisponibilidad()) {
        std::cerr << "Error: El médico seleccionado no está disponible para asignar citas.\n";
        return;
    }

    // Solicitar ID del paciente
    std::string pacienteID = InputValidator::solicitarID<Paciente>(
        "Ingrese el ID del paciente: ",
        pacientes,
        [](const Paciente& paciente) {
            return paciente.getID();
        }
    );

    // Solicitar fecha
    std::string fecha = InputValidator::solicitarFecha("Ingrese la fecha de la cita", InputValidator::obtenerFechaActual(), {});

    // Solicitar prioridad
    int prioridad = InputValidator::solicitarPrioridad();

    // Crear cita
    unsigned long hash = IDGenerator::generarHashCita(pacienteID, medicoID, fecha);
    std::string citaID = IDGenerator::generarIDCita(pacienteID, medicoID, fecha);

    citas.emplace_back(hash, citaID, pacienteID, medicoID, fecha, prioridad);
    std::cout << "Cita creada exitosamente con ID: " << citaID << "\n";

    // Guardar las citas en el archivo
    Archivo::guardarCitas(citas, "archivo_citas.txt");
}

// Modificar una cita existente
bool GestorCitas::modificarCita(std::vector<Cita>& citas, const std::string& citaID, const std::vector<Medico>& medicos) {
    // Buscar la cita
    auto itCita = std::find_if(citas.begin(), citas.end(), [&citaID](const Cita& cita) {
        return cita.getCitaID() == citaID;
        });

    if (itCita == citas.end()) {
        std::cerr << "Error: No se encontró una cita con el ID proporcionado.\n";
        return false;
    }

    // Mostrar los datos actuales de la cita
    std::cout << "\n--- Detalles Actuales de la Cita ---\n\n";
    Formateador::imprimirEncabezadoCitas();
    Formateador::imprimirRegistro(*itCita);
    std::cout << std::string(100, '-') << "\n\n";

    // Verificar disponibilidad del médico asociado
    auto itMedico = std::find_if(medicos.begin(), medicos.end(), [&itCita](const Medico& medico) {
        return medico.getID() == itCita->getMedicoID();
        });

    std::optional<std::string> nuevoMedicoID = std::nullopt;

    if (itMedico == medicos.end() || !itMedico->obtenerDisponibilidad()) {
        std::cerr << "\nAdvertencia: El médico asociado no está disponible.\n";

        // Mostrar lista de médicos disponibles
        std::cout << "\n--- Médicos Disponibles ---\n";
        Formateador::imprimirEncabezadoMedicos();
        for (const auto& medico : medicos) {
            if (medico.obtenerDisponibilidad()) {
                Formateador::imprimirRegistro(medico);
            }
        }

        // Solicitar un nuevo médico
        nuevoMedicoID = InputValidator::solicitarID<Medico>(
            "Ingrese el ID de un nuevo médico: ",
            medicos,
            [](const Medico& medico) {
                return medico.getID();
            });

        auto nuevoMedicoIt = std::find_if(medicos.begin(), medicos.end(), [&nuevoMedicoID](const Medico& medico) {
            return medico.getID() == nuevoMedicoID.value();
            });

        if (nuevoMedicoIt == medicos.end() || !nuevoMedicoIt->obtenerDisponibilidad()) {
            std::cerr << "Error: El nuevo médico no es válido o no está disponible.\n";
            return false;
        }
    }

    // Solicitar nueva fecha
    std::string nuevaFecha;
    while (true) {
        try {
            nuevaFecha = InputValidator::solicitarFecha("Ingrese la nueva fecha de la cita", InputValidator::obtenerFechaActual(), {});
            break;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << " Intente nuevamente.\n";
        }
    }

    // Solicitar nueva prioridad
    int nuevaPrioridad = InputValidator::solicitarPrioridad();

    // Modificar la cita
    try {
        itCita->modificarCita(nuevaFecha, nuevaPrioridad, nuevoMedicoID.value_or(""));
        std::cout << "\n--- Cita Modificada Exitosamente ---\n\n";
        Formateador::imprimirEncabezadoCitas();
        Formateador::imprimirRegistro(*itCita);
        std::cout << std::string(100, '-') << "\n\n";
        Archivo::guardarCitas(citas, "archivo_citas.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Error al modificar la cita: " << e.what() << "\n";
        return false;
    }

    return true;
}

// Cancelar una cita
void GestorCitas::cancelarCita(std::vector<Cita>& citas, const std::string& citaID) {
    auto it = std::remove_if(citas.begin(), citas.end(), [&citaID](const Cita& cita) {
        return cita.getCitaID() == citaID;
        });

    if (it != citas.end()) {
        citas.erase(it, citas.end());
        std::cout << "Cita cancelada exitosamente.\n";
    }
    else {
        std::cerr << "Error: No se encontró una cita con el ID proporcionado.\n";
    }
}

// Ordenar citas por fecha
void GestorCitas::ordenarCitasPorFecha(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), Cita::compararPorFecha);
}

// Ordenar citas por prioridad
void GestorCitas::ordenarCitasPorPrioridad(std::vector<Cita>& citas) {
    std::sort(citas.begin(), citas.end(), Cita::compararPorPrioridad);
}

std::vector<Cita> GestorCitas::filtrarCitasPorPaciente(const std::vector<Cita>& citas, const std::string& pacienteID) {
    std::vector<Cita> resultado;
    std::copy_if(citas.begin(), citas.end(), std::back_inserter(resultado),
        [&pacienteID](const Cita& cita) { return cita.getPacienteID() == pacienteID; });
    return resultado;
}

std::vector<Cita> GestorCitas::filtrarCitasPorMedico(const std::vector<Cita>& citas, const std::string& medicoID) {
    std::vector<Cita> resultado;
    std::copy_if(citas.begin(), citas.end(), std::back_inserter(resultado),
        [&medicoID](const Cita& cita) { return cita.getMedicoID() == medicoID; });
    return resultado;
}

