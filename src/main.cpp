#include "Paciente.hpp"
#include "Medico.hpp"
#include "Cita.hpp"
#include "HistorialMedico.hpp"
#include "EnfermedadCronica.hpp"
#include "Formateador.hpp"
#include "InputValidator.hpp"
#include "Archivo.hpp"
#include "GestorCitas.hpp"
#include "GestorMedicos.hpp"
#include "GestorPacientes.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <memory>
#include <filesystem>
#include <fstream>

// Funciones para los submenús
void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas);
void mostrarMenuMedico(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
void mostrarMenuPaciente(std::vector<Paciente>& pacientes);
void mostrarMenuGestionArchivos(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas);
void mostrarMenuListados(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, const std::vector<Cita>& citas);
void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos);

// Función auxiliar para operar sobre el historial de un paciente
template <typename Funcion>
void operarHistorialPaciente(std::vector<Paciente>& pacientes, const std::string& id, Funcion operacion) {
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

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Establecer la raíz del proyecto como directorio actual
    std::filesystem::path raizProyecto = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::current_path(raizProyecto);

    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;

    try {
        // Cargar los archivos predeterminados
        pacientes = Archivo::cargarPacientes("./data/archivo_pacientes.txt");
        medicos = Archivo::cargarMedicos("./data/archivo_medicos.txt");
        citas = Archivo::cargarCitas("./data/archivo_citas.txt");
        std::cout << "Archivos predeterminados cargados correctamente.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar archivos: " << e.what() << "\n";
        std::cerr << "Por favor, asegúrese de que los archivos existan en la carpeta 'data/'.\n";
        return 1; // Salir del programa con código de error
    }

    // Continuar con el flujo normal del programa
    std::cout << "Sistema de Gestión Hospitalaria iniciado.\n";

    int opcion;
    do {
        std::cout << "\n--- Sistema de Gestión Hospitalaria ---\n";
        std::cout << "1. Entrar como Administrador\n";
        std::cout << "2. Entrar como Médico\n";
        std::cout << "3. Entrar como Paciente\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            mostrarMenuAdministrador(pacientes, medicos, citas);
            break;
        case 2:
            mostrarMenuMedico(pacientes, medicos);
            break;
        case 3:
            mostrarMenuPaciente(pacientes);
            break;
        case 0:
            std::cout << "Saliendo del sistema...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}

void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas) {
    int opcion;
    do {
        std::cout << "\n--- Menú Administrador ---\n";
        std::cout << "1. Gestión de Archivos\n";
        std::cout << "2. Ver Listados\n";
        std::cout << "3. Alta y Baja de Registros\n";
        std::cout << "4. Gestión de Citas\n";
        std::cout << "0. Volver al Menú Principal\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            mostrarMenuGestionArchivos(pacientes, medicos, citas);
            break;
        case 2:
            mostrarMenuListados(pacientes, medicos, citas);
            break;
        case 3:
            mostrarMenuAltaBaja(pacientes, medicos);
            break;
        case 4:
            mostrarMenuGestionCitas(citas, pacientes, medicos);
            break;
        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuGestionArchivos(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Archivos ---\n";
        std::cout << "1. Cargar Pacientes\n";
        std::cout << "2. Cargar Médicos\n";
        std::cout << "3. Cargar Citas\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            Archivo::cargarDatos(pacientes, "Ingrese el archivo de pacientes",
                "./data/archivo_pacientes.txt", Archivo::cargarPacientes);
            break;
        case 2:
            Archivo::cargarDatos(medicos, "Ingrese el archivo de médicos",
                "./data/archivo_medicos.txt", Archivo::cargarMedicos);
            break;
        case 3:
            Archivo::cargarDatos(citas, "Ingrese el archivo de citas",
                "./data/archivo_citas.txt", Archivo::cargarCitas);
            break;
        case 0:
            std::cout << "Volviendo al menú administrador...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuListados(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, const std::vector<Cita>& citas) {
    int opcion;
    do {
        std::cout << "\n--- Ver Listados ---\n";
        std::cout << "1. Lista de Pacientes\n";
        std::cout << "2. Lista de Médicos\n";
        std::cout << "3. Lista de Citas\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            Formateador::imprimirTablaPacientes(pacientes);
            break;
        case 2:
            Formateador::imprimirTablaMedicos(medicos);
            break;
        case 3:
            Formateador::imprimirTablaCitas(citas);
            break;
        case 0:
            std::cout << "Volviendo al menú administrador...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos) {
    int opcion;
    do {
        std::cout << "\n--- Alta y Baja de Registros ---\n";
        std::cout << "1. Dar de Alta un Paciente\n";
        std::cout << "2. Dar de Alta un Médico\n";
        std::cout << "3. Dar de Baja un Paciente\n";
        std::cout << "4. Dar de Baja un Médico\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: {
            int edad;
            std::string nombre, apellido, direccion;
            std::cout << "Ingrese Nombre: "; std::cin >> nombre;
            std::cout << "Ingrese Apellido: "; std::cin >> apellido;
            std::cout << "Ingrese Dirección: "; std::cin.ignore(); std::getline(std::cin, direccion);
            std::cout << "Ingrese Edad: "; std::cin >> edad;
            GestorPacientes::altaPaciente(pacientes, nombre, apellido, direccion, edad);
            break;
        }
        case 2: {
            std::string nombre, apellido, especialidad;
            bool disponibilidad;
            std::cout << "Ingrese Nombre: "; std::cin >> nombre;
            std::cout << "Ingrese Apellido: "; std::cin >> apellido;
            std::cout << "Ingrese Especialidad: "; std::cin.ignore(); std::getline(std::cin, especialidad);
            std::cout << "Disponibilidad (1 = Disponible, 0 = Ocupado): "; std::cin >> disponibilidad;
            GestorMedicos::altaMedico(medicos, nombre, apellido, especialidad, disponibilidad);
            break;
        }
        case 3: {
            std::string idPaciente;
            std::cout << "Ingrese ID del paciente a eliminar: "; std::cin >> idPaciente;
            GestorPacientes::bajaPaciente(pacientes, idPaciente);
            break;
        }
        case 4: {
            std::string idMedico;
            std::cout << "Ingrese ID del médico a eliminar: "; std::cin >> idMedico;
            GestorMedicos::bajaMedico(medicos, idMedico);
            break;
        }
        case 0:
            std::cout << "Volviendo al menú administrador...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Citas ---\n";
        std::cout << "1. Crear Cita\n";
        std::cout << "2. Cancelar Cita\n";
        std::cout << "3. Modificar Cita\n";
        std::cout << "4. Ver Citas por Paciente\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: {
            // Solicitar ID del médico
            std::string medicoID;
            std::cout << "Ingrese el ID del médico: ";
            std::cin >> medicoID;

            // Buscar el médico
            auto itMedico = std::find_if(medicos.begin(), medicos.end(), [&medicoID](const Medico& medico) {
                return medico.getID() == medicoID;
                });

            if (itMedico == medicos.end()) {
                std::cout << "Médico no encontrado.\n";
                break;
            }

            // Solicitar ID del paciente
            std::string pacienteID;
            std::cout << "Ingrese el ID del paciente: ";
            std::cin >> pacienteID;

            auto itPaciente = std::find_if(pacientes.begin(), pacientes.end(), [&pacienteID](const Paciente& paciente) {
                return paciente.getID() == pacienteID;
                });

            if (itPaciente == pacientes.end()) {
                std::cout << "Paciente no encontrado.\n";
                break;
            }

            // Solicitar fecha
            std::string fecha = InputValidator::solicitarFecha("Ingrese la fecha de la cita", {}, {});
            if (!InputValidator::esFechaFutura(fecha)) {
                std::cout << "La fecha debe ser igual o posterior a la fecha actual.\n";
                break;
            }

            // Solicitar prioridad
            int prioridad;
            std::cout << "Ingrese la prioridad de la cita (1 = Urgente, 2 = Normal): ";
            std::cin >> prioridad;
            if (prioridad != 1 && prioridad != 2) {
                std::cout << "Prioridad inválida. Debe ser 1 (Urgente) o 2 (Normal).\n";
                break;
            }

            // Crear cita usando el Administrador
            try {
                GestorCitas::crearCita(citas, pacienteID, medicoID, fecha, prioridad);
            }
            catch (const std::exception& e) {
                std::cerr << "Error al crear la cita: " << e.what() << "\n";
            }

            break;
        }

        case 2: {
            std::string citaID;
            std::cout << "Ingrese el ID de la cita a cancelar: ";
            std::cin >> citaID;

            GestorCitas::cancelarCita(citas, citaID);
            
            break;
        }
        case 3: {
            std::string citaID, nuevaFecha;
            int nuevaPrioridad;

            std::cout << "Ingrese el ID de la cita a modificar: ";
            std::cin >> citaID;
            nuevaFecha = InputValidator::solicitarFecha("Ingrese la nueva fecha de la cita", {}, {});
            std::cout << "Ingrese la nueva prioridad (1 = Urgente, 2 = Normal): ";
            std::cin >> nuevaPrioridad;

            GestorCitas::modificarCita(citas, citaID, nuevaFecha, nuevaPrioridad);
            break;
        }
        case 4: {
            std::string pacienteID;
            std::cout << "Ingrese el ID del paciente: ";
            std::cin >> pacienteID;

            Formateador::imprimirEncabezadoCitas();
            for (const auto& cita : citas) {
                if (cita.getPacienteID() == pacienteID) {
                    Formateador::imprimirRegistro(cita);
                }
            }
            break;
        }
        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuMedico(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos) {
    int opcion;
    do {
        std::cout << "\n--- Menú Médico ---\n";
        std::cout << "1. Ver lista de pacientes\n";
        std::cout << "2. Buscar paciente por ID\n";
        std::cout << "3. Agregar diagnóstico a un paciente\n";
        std::cout << "4. Agregar prueba médica a un paciente\n";
        std::cout << "5. Agregar nota general al historial de un paciente\n";
        std::cout << "6. Ver historial médico de un paciente\n";
        std::cout << "7. Agregar enfermedad crónica a un paciente\n";
        std::cout << "8. Asignar tratamiento a un paciente\n";
        std::cout << "0. Volver al menú principal\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: // Ver lista de pacientes
            Formateador::imprimirTablaPacientes(pacientes);
            break;

        case 2: { // Buscar paciente por ID
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;
            auto paciente = GestorPacientes::buscarPacientePorID(pacientes, id);
            if (paciente) {
                Formateador::imprimirEncabezadoPacientes();
                Formateador::imprimirRegistro(*paciente);
            }
            else {
                std::cout << "Paciente no encontrado.\n";
            }
            break;
        }

        case 3: { // Agregar diagnóstico
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            operarHistorialPaciente(pacientes, id, [](HistorialMedico& historial) {
                std::string diagnostico, fecha;
                std::cout << "Ingrese diagnóstico: ";
                std::cin.ignore();
                std::getline(std::cin, diagnostico);
                fecha = InputValidator::solicitarFecha("Ingrese fecha del diagnóstico: ");
                historial.agregarDiagnostico(fecha, diagnostico);
                });
            break;
        }

        case 4: { // Agregar prueba médica
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            operarHistorialPaciente(pacientes, id, [](HistorialMedico& historial) {
                std::string prueba, fecha;
                std::cout << "Ingrese prueba médica: ";
                std::cin.ignore();
                std::getline(std::cin, prueba);
                fecha = InputValidator::solicitarFecha("Ingrese fecha de la prueba: ");
                historial.agregarPrueba(fecha, prueba);
                });
            break;
        }

        case 5: { // Agregar nota general
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            operarHistorialPaciente(pacientes, id, [](HistorialMedico& historial) {
                std::string nota;
                std::cout << "Ingrese nota general: ";
                std::cin.ignore();
                std::getline(std::cin, nota);
                historial.agregarNota(nota);
                });
            break;
        }

        case 6: { // Ver historial médico
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            auto paciente = GestorPacientes::buscarPacientePorID(pacientes, id);
            if (paciente) {
                HistorialMedico historial = paciente->cargarHistorial();
                Formateador::imprimirHistorialMedico(historial);
            }
            else {
                std::cout << "Paciente no encontrado.\n";
            }
            break;
        }

        case 7: { // Agregar enfermedad crónica
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            operarHistorialPaciente(pacientes, id, [](HistorialMedico& historial) {
                std::string nombre, tratamiento, fechaDiagnostico;
                int severidad;

                std::cout << "Ingrese nombre de la enfermedad: ";
                std::cin.ignore();
                std::getline(std::cin, nombre);

                std::cout << "Ingrese severidad (1-10): ";
                std::cin >> severidad;

                std::cout << "Ingrese tratamiento recomendado: ";
                std::cin.ignore();
                std::getline(std::cin, tratamiento);

                fechaDiagnostico = InputValidator::solicitarFecha("Ingrese fecha de diagnóstico: ");
                EnfermedadCronica enfermedad(nombre, severidad, tratamiento, fechaDiagnostico);
                historial.agregarEnfermedadCronica(enfermedad);
                });
            break;
        }

        case 8: { // Asignar tratamiento
            std::string id;
            std::cout << "Ingrese ID del paciente: ";
            std::cin >> id;

            operarHistorialPaciente(pacientes, id, [](HistorialMedico& historial) {
                std::string tratamiento;
                std::cout << "Ingrese tratamiento a asignar: ";
                std::cin.ignore();
                std::getline(std::cin, tratamiento);
                historial.agregarNota("Tratamiento asignado: " + tratamiento);
                });
            break;
        }


        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;

        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuPaciente(std::vector<Paciente>& pacientes) {
    std::string id;
    std::cout << "Ingrese su ID para acceder al sistema: ";
    std::cin >> id;

    auto paciente = GestorPacientes::buscarPacientePorID(pacientes, id);
    if (!paciente) {
        std::cout << "Paciente no encontrado.\n";
        return;
    }

    int opcion;
    do {
        std::cout << "\n--- Menú Paciente ---\n";
        std::cout << "1. Ver información personal\n";
        std::cout << "2. Consultar historial clínico\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            Formateador::imprimirEncabezadoPacientes();
            Formateador::imprimirRegistro(*paciente);
            break;
        case 2:
            Formateador::imprimirHistorialMedico(paciente->cargarHistorial());
            break;
        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0); 
}
