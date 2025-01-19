#ifndef GESTORPACIENTES_HPP
#define GESTORPACIENTES_HPP

#include "Paciente.hpp"
#include "Archivo.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "ArchivosActivos.hpp"

#include <vector>
#include <string>

class GestorPacientes {
public:
    static void altaPaciente(std::vector<Paciente>& pacientes, ArchivosActivos& archivos);
    static void bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id, ArchivosActivos& archivos);
    static Paciente* buscarPacientePorID(std::vector<Paciente>& pacientes, const std::string& id);

    // Función auxiliar para operar sobre el historial de un paciente
    template <typename Funcion>
    static void operarHistorialPaciente(std::vector<Paciente>& pacientes, const std::string& id, Funcion operacion) {
        auto paciente = GestorPacientes::buscarPacientePorID(pacientes, id);
        if (paciente) {
            HistorialMedico historial = paciente->cargarHistorial();
            operacion(historial);

            try {
                Archivo::guardarHistorialMedico(historial);
                std::cout << "Operación completada exitosamente.\n";
            }
            catch (const std::exception& e) {
                std::cerr << "Error al guardar el historial médico: " << e.what() << "\n";
            }
        }
        else {
            std::cout << "Paciente no encontrado.\n";
        }
    }

};

#endif
