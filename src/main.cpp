#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

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
#include "GestorEspecialidades.hpp"
#include "ArchivosActivos.hpp"

// Funciones para los submenús
void mostrarMenuPrincipal(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, std::vector<Especialidad>& especialidades, ArchivosActivos& archivos, GestorEspecialidades& gestorEspecialidades);
void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, std::vector<Especialidad>& especialidades, ArchivosActivos& archivos, GestorEspecialidades& gestorEspecialidades);
void mostrarMenuMedico(std::vector<Paciente>& pacientes);
void mostrarMenuPaciente(std::vector<Paciente>& pacientes, ArchivosActivos& archivos);
void mostrarMenuGestionArchivos(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, std::vector<Especialidad>& especialidades, ArchivosActivos& archivos);
void mostrarMenuListados(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, std::vector<Cita>& citas);
void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos);
void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, ArchivosActivos& archivos);
void mostrarMenuGestionEspecialidades(GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos);

int main() {

    Formateador::limpiarPantalla();

#ifdef _WIN32
    // Configurar la consola para UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ArchivosActivos archivos;

    // Instanciar las estructuras principales
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;
    std::vector<Especialidad> especialidades;

    try {
        // Cargar los archivos predeterminados automáticamente
        Archivo::cargarDatos<Paciente>(
            pacientes,
            "Cargando archivo predeterminado de pacientes",
            archivos.pacientes,
            [](const std::string& ruta) {
                return Archivo::cargarPacientes(ruta);
            },
            false
        );

        Archivo::cargarDatos<Medico>(
            medicos,
            "Cargando archivo predeterminado de médicos",
            archivos.medicos,
            [](const std::string& ruta) {
                return Archivo::cargarMedicos(ruta);
            },
            false
        );

        Archivo::cargarDatos<Cita>(
            citas,
            "Cargando archivo predeterminado de citas",
            archivos.citas,
            [](const std::string& ruta) {
                return Archivo::cargarCitas(ruta);
            },
            false
        );

        Archivo::cargarDatos<Especialidad>(
            especialidades,
            "Cargando archivo predeterminado de especialidades",
            archivos.especialidades,
            [](const std::string& ruta) {
                return Archivo::cargarEspecialidades(ruta);
            },
            false
        );

        std::cout << "Archivos predeterminados cargados correctamente.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar archivos: " << e.what() << "\n";
        std::cerr << "Por favor, asegúrese de que los archivos existan en la carpeta 'data/'.\n";
        return 1;
    }

    GestorEspecialidades gestorEspecialidades(especialidades);

    mostrarMenuPrincipal(pacientes, medicos, citas, especialidades, archivos, gestorEspecialidades);

    return 0;
}

void mostrarMenuPrincipal(std::vector<Paciente>&pacientes, std::vector<Medico>&medicos, 
                          std::vector<Cita>&citas, std::vector<Especialidad>& especialidades, ArchivosActivos& archivos, GestorEspecialidades & gestorEspecialidades){
    int opcion = -1;
    do {
        std::cout << "\n--- Sistema de Gestión Hospitalaria ---\n";
        std::cout << "1. Entrar como Administrador\n";
        std::cout << "2. Entrar como Médico\n";
        std::cout << "3. Entrar como Paciente\n";
        std::cout << "0. Salir\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            mostrarMenuAdministrador(pacientes, medicos, citas, especialidades, archivos, gestorEspecialidades);
            break;
        case 2:
            mostrarMenuMedico(pacientes);
            break;
        case 3:
            mostrarMenuPaciente(pacientes, archivos);
            break;
        case 0:
            std::cout << "Saliendo del sistema...\n";
            break;
        default:    
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas,
    std::vector<Especialidad>& especialidades, ArchivosActivos& archivos, GestorEspecialidades& gestorEspecialidades) {
    int opcion = -1;
    do {
        std::cout << "\n--- Menú Administrador ---\n";
        std::cout << "1. Gestión de Archivos\n";
        std::cout << "2. Ver Listados\n";
        std::cout << "3. Alta y Baja de Registros\n";
        std::cout << "4. Gestión de Citas\n";
        std::cout << "5. Gestionar Especialidades\n";
        std::cout << "0. Volver al Menú Principal\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            mostrarMenuGestionArchivos(pacientes, medicos, citas, especialidades, archivos);
            break;
        case 2:
            mostrarMenuListados(pacientes, medicos, citas);
            break;
        case 3:
            mostrarMenuAltaBaja(pacientes, medicos, gestorEspecialidades, archivos);
            break;
        case 4:
            mostrarMenuGestionCitas(citas, pacientes, medicos, archivos);
            break;
        case 5:
            mostrarMenuGestionEspecialidades(gestorEspecialidades, archivos);
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuGestionArchivos(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, 
    std::vector<Especialidad>& especialidades, ArchivosActivos& archivos){
    int opcion = -1;
    do {
        std::cout << "\n--- Gestión de Archivos ---\n";
        std::cout << "1. Cambiar archivo de Pacientes (y cargarlo)\n";
        std::cout << "2. Cambiar archivo de Médicos (y cargarlo)\n";
        std::cout << "3. Cambiar archivo de Citas (y cargarlo)\n";
        std::cout << "4. Cambiar archivo de Especialidades (y cargarlo)\n";
        std::cout << "5. Volver a archivos por defecto\n";
        std::cout << "0. Volver al Menú Administrador\n\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: { // Cambiar archivo de Pacientes
            std::cout << "Archivo actual: " << archivos.pacientes << "\n";
            Archivo::cargarDatos<Paciente>(
                pacientes,
                "Ingrese el archivo de pacientes",
                archivos.pacientes,
                [](const std::string& ruta) {
                    return Archivo::cargarPacientes(ruta);
                },
                true
            );
            break;
        }
        case 2: { // Cambiar archivo de Medicos
            std::cout << "Archivo actual: " << archivos.medicos << "\n";
            Archivo::cargarDatos<Medico>(
                medicos,
                "Ingrese el archivo de medicos",
                archivos.medicos,
                [](const std::string& ruta) {
                    return Archivo::cargarMedicos(ruta);
                },
                true
            );
            break;
        }
        case 3: { // Cambiar archivo de Citas
            std::cout << "Archivo actual: " << archivos.citas << "\n";
            Archivo::cargarDatos<Cita>(
                citas,
                "Ingrese el archivo de citas",
                archivos.citas,
                [](const std::string& ruta) {
                    return Archivo::cargarCitas(ruta);
                },
                true
            );
            break;
        }
        case 4: {
            std::cout << "Archivo actual: " << archivos.especialidades << "\n";
            Archivo::cargarDatos<Especialidad>(
                especialidades,
                "Ingrese el archivo de especialidades",
                archivos.especialidades,
                [](const std::string& ruta) {
                    return Archivo::cargarEspecialidades(ruta);
                },
                true
            );
            break;
        }

        case 5: {
            archivos.pacientes = "archivo_pacientes.txt";
            archivos.medicos = "archivo_medicos.txt";
            archivos.citas = "archivo_citas.txt";
            archivos.especialidades = "especialidades.csv";

            try {
                pacientes = Archivo::cargarPacientes(archivos.pacientes);
                medicos = Archivo::cargarMedicos(archivos.medicos);
                citas = Archivo::cargarCitas(archivos.citas);
                especialidades = Archivo::cargarEspecialidades(archivos.especialidades);
                std::cout << "Archivos por defecto cargados nuevamente.\n";
            }
            catch (...) {
                std::cerr << "Error al cargar archivos por defecto.\n";
            }
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

void mostrarMenuListados(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, std::vector<Cita>& citas){
    int opcion = -1;
    do {
        std::cout << "\n--- Ver Listados ---\n";
        std::cout << "1. Lista de Pacientes\n";
        std::cout << "2. Lista de Médicos\n";
        std::cout << "3. Lista de Citas\n";
        std::cout << "4. Ordenar citas por fecha\n";
        std::cout << "5. Ordenar citas por prioridad\n";
        std::cout << "0. Volver al Menú Administrador\n\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
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
        case 4: { // Ordenar citas por fecha
            GestorCitas::ordenarCitasPorFecha(citas);
            std::cout << "Citas ordenadas por fecha:\n";
            Formateador::imprimirTablaCitas(citas);
            break;
        }
        case 5: { // Ordenar citas por prioridad
            GestorCitas::ordenarCitasPorPrioridad(citas);
            std::cout << "Citas ordenadas por prioridad:\n";
            Formateador::imprimirTablaCitas(citas);
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

void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos) {
    int opcion = -1;
    do {
        std::cout << "\n--- Alta y Baja de Registros ---\n";
        std::cout << "1. Dar de Alta a un Paciente\n";
        std::cout << "2. Dar de Alta a un Médico\n";
        std::cout << "3. Dar de Baja a un Paciente\n";
        std::cout << "4. Dar de Baja a un Médico\n";
        std::cout << "5. Cambiar Disponibilidad de un Médico\n";
        std::cout << "0. Volver al Menú Administrador\n\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: {
            GestorPacientes::altaPaciente(pacientes, archivos);
            break;
        }

        case 2: {
            GestorMedicos::altaMedico(medicos, gestorEspecialidades, archivos);
            break;
        }

        case 3: {
            std::string idPaciente;
            std::cout << "Ingrese ID del paciente a eliminar: "; std::cin >> idPaciente;
            GestorPacientes::bajaPaciente(pacientes, idPaciente, archivos);
            break;
        }
        case 4: {
            std::string idMedico;
            std::cout << "Ingrese ID del médico a eliminar: "; std::cin >> idMedico;
            GestorMedicos::bajaMedico(medicos, idMedico, archivos);
            break;
        }
        case 5: {
            Formateador::imprimirTablaMedicos(medicos);
            std::string medicoID = InputValidator::solicitarID <Medico>(
                "Ingrese el ID del médico: ",
                medicos,
                [](const Medico& medico) {
                    return medico.getID();
                }
            );

            GestorMedicos::cambiarDisponibilidad(medicos, medicoID);

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

void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, ArchivosActivos& archivos) {
    int opcion = -1;

    do {
        std::cout << "\n--- Gestión de Citas ---\n";
        std::cout << "1. Crear Cita\n";
        std::cout << "2. Modificar Cita\n";
        std::cout << "3. Cancelar Cita\n";
        std::cout << "4. Ver Citas por Paciente\n";
        std::cout << "5. Ver Citas por Médico\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        
        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: {
            try {
                GestorCitas::crearCita(citas, pacientes, medicos, archivos);
            }
            catch (const std::exception& e) {
                std::cerr << "Error al crear la cita: " << e.what() << "\n";
            }
            break;
        }

        case 2: {
            std::string citaID;

            // Solicitar ID de la cita
            std::cout << "Ingrese el ID de la cita a modificar: ";
            std::cin >> citaID;

            // Modificar la cita
            if (!GestorCitas::modificarCita(citas, citaID, medicos, archivos)) {
                std::cerr << "No se pudo modificar la cita. Verifique los datos ingresados.";
            }

            break;
        }

        case 3: {
            std::string citaID;
            std::cout << "Ingrese el ID de la cita a cancelar: ";
            std::cin >> citaID;

            citaID = InputValidator::convertirAMayusculas(citaID);

            try {
                GestorCitas::cancelarCita(citas, citaID, archivos);
            }
            catch (const std::exception& e) {
                std::cerr << "Error al cancelar la cita: " << e.what() << "\n";
            }

            break;
        }

        case 4: {
            Formateador::imprimirTablaPacientes(pacientes);

            std::string pacienteID = InputValidator::solicitarID<Paciente>(
                "Ingrese el ID del paciente: ",
                pacientes,
                [](const Paciente& paciente) {
                    return paciente.getID();
                });

            auto citasPorPaciente = GestorCitas::filtrarCitasPorPaciente(citas, pacienteID);
            Formateador::imprimirEncabezadoCitas();
            for (const auto& cita : citasPorPaciente) {
                Formateador::imprimirRegistro(cita);
            }
            break;
        }
        case 5: { // Ver citas por médico
            Formateador::imprimirTablaMedicos(medicos);

            std::string medicoID = InputValidator::solicitarID<Medico>(
                "Ingrese el ID del médico: ",
                medicos,
                [](const Medico& medico) {
                    return medico.getID();
                });

            auto citasPorMedico = GestorCitas::filtrarCitasPorMedico(citas, medicoID);
            Formateador::imprimirEncabezadoCitas();
            for (const auto& cita : citasPorMedico) {
                Formateador::imprimirRegistro(cita);
            }
            break;
        }

        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;

        default:
            std::cerr << "Error: Opción no válida.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuGestionEspecialidades(GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos) {
    int opcion = -1;
    do {
        std::cout << "\n--- Gestión de Especialidades ---\n";
        std::cout << "1. Listar Especialidades\n";
        std::cout << "2. Buscar Especialidad por ID\n";
        std::cout << "3. Añadir Nueva Especialidad\n";
        std::cout << "0. Volver al Menú Administrador\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: { // Listar todas las especialidades
            auto listaEspecialidades = gestorEspecialidades.obtenerListaEspecialidades();
            if (listaEspecialidades.empty()) {
                std::cout << "No hay especialidades registradas.\n";
            }
            else {
                Formateador::imprimirTablaEspecialidades(listaEspecialidades);
            }
            break;
        }

        case 2: { // Buscar especialidad por ID
            int id;
            std::cout << "Ingrese el ID de la especialidad: ";
            std::cin >> id;
            auto especialidad = gestorEspecialidades.buscarEspecialidadPorID(id);
            if (especialidad) {
                Formateador::imprimirRegistro(*especialidad);
            }
            else {
                std::cout << "Especialidad no encontrada.";
            }
            break;
        }

        case 3: { // Añadir una nueva especialidad
            std::string nombre, descripcion;

            std::cout << "Ingrese el nombre de la especialidad: ";
            std::getline(std::cin, nombre);

            std::cout << "Ingrese una descripción para la especialidad: ";
            std::getline(std::cin, descripcion);

            gestorEspecialidades.crearEspecialidad(nombre, descripcion, archivos);
            break;
        }

        case 0:
            std::cout << "Volviendo al Menú Administrador...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 0);
}

void mostrarMenuMedico(std::vector<Paciente>& pacientes) {
    int opcion = -1;
    const Paciente* pacienteSeleccionado = nullptr;
    
    do {
        
        std::cout << "\n--- Menú Médico ---\n";

        if (pacienteSeleccionado) {
            Formateador::imprimirEncabezadoMenuMedico(*pacienteSeleccionado);
        }
        else {
            std::cout << "\n--- No hay paciente seleccionado ---\n\n";
        }

        // Mostrar el menú
        std::cout << "1. Seleccionar paciente por ID\n";
        std::cout << "2. Agregar diagnóstico a un paciente\n";
        std::cout << "3. Agregar prueba médica a un paciente\n";
        std::cout << "4. Asignar tratamiento a un paciente\n";
        std::cout << "5. Agregar enfermedad crónica a un paciente\n";
        std::cout << "6. Agregar nota general al historial de un paciente\n";
        std::cout << "7. Ver historial médico de un paciente\n";
        std::cout << "0. Salir\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: { // Seleccionar paciente por ID
            Formateador::imprimirTablaPacientes(pacientes);
            Paciente* p = InputValidator::solicitarObjeto<Paciente>(
                "Ingrese el ID del paciente a seleccionar: ",
                pacientes,
                [](const Paciente& pac) {
                    return pac.getID();
                }
            );
            pacienteSeleccionado = p;
            break;
        }

        case 2: { // Agregar diagnóstico
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            GestorPacientes::operarHistorialPaciente(pacientes, pacienteSeleccionado->getID(), [](HistorialMedico& historial) {
                std::string diagnostico, fecha;
                std::cout << "Ingrese diagnóstico: ";
                std::getline(std::cin, diagnostico);
                fecha = InputValidator::solicitarFechaPasadaOActual("Ingrese fecha del diagnóstico: ");
                historial.agregarDiagnostico(fecha, diagnostico);
                });
            break;
        }

        case 3: { // Agregar prueba médica
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            GestorPacientes::operarHistorialPaciente(pacientes, pacienteSeleccionado->getID(), [](HistorialMedico& historial) {
                std::string prueba, fecha;
                std::cout << "Ingrese prueba médica: ";
                std::getline(std::cin, prueba);
                fecha = InputValidator::solicitarFecha("Ingrese fecha de la prueba: ");
                historial.agregarPrueba(fecha, prueba);
                });
            break;
        }

        case 4: { // Asignar tratamiento
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            GestorPacientes::operarHistorialPaciente(pacientes, pacienteSeleccionado->getID(), [](HistorialMedico& historial) {
                std::string tratamiento;
                std::cout << "Ingrese tratamiento a asignar: ";
                std::getline(std::cin, tratamiento);
                historial.agregarNota("Tratamiento asignado: " + tratamiento);
                });
            break;
        }

        case 5: { // Agregar enfermedad crónica
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            GestorPacientes::operarHistorialPaciente(pacientes, pacienteSeleccionado->getID(),
                [](HistorialMedico& historial)
                {
                    std::string nombre, tratamiento, fechaDiagnostico;

                    std::cout << "Ingrese nombre de la enfermedad: ";
                    std::getline(std::cin, nombre);

                    int severidad;
                    while (true) {
                        severidad = InputValidator::leerEnteroConsola("Ingrese severidad (1-10): ");
                        if (severidad >= 1 && severidad <= 10) {
                            break;
                        }
                        std::cerr << "Error: La severidad debe estar entre 1 y 10. Intente nuevamente.\n";
                    }

                    std::cout << "Ingrese tratamiento recomendado: ";
                    std::getline(std::cin, tratamiento);

                    fechaDiagnostico = InputValidator::solicitarFechaPasadaOActual("Ingrese fecha del diagnóstico: ");

                    EnfermedadCronica enfermedad(nombre, severidad, tratamiento, fechaDiagnostico);
                    historial.agregarEnfermedadCronica(enfermedad);
                }
            );
            break;
        }

        case 6: { // Agregar nota general
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            GestorPacientes::operarHistorialPaciente(pacientes, pacienteSeleccionado->getID(), [](HistorialMedico& historial) {
                std::string nota;
                std::cout << "Ingrese nota general: ";
                std::getline(std::cin, nota);
                historial.agregarNota(nota);
                });
            break;
        }

        case 7: { // Ver historial médico
            if (!pacienteSeleccionado) {
                std::cerr << "Error: No hay ningún paciente seleccionado. Seleccione uno primero.\n";
                break;
            }

            auto paciente = GestorPacientes::buscarPacientePorID(pacientes, pacienteSeleccionado->getID());
            if (paciente) {
                HistorialMedico historial = paciente->cargarHistorial();
                Formateador::imprimirHistorialMedico(historial);
                std::cout << "\nPresione enter para continuar...";
                std::cin.get();
                Formateador::limpiarPantalla();
            }
            else {
                std::cout << "Paciente no encontrado.\n";
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

void mostrarMenuPaciente(std::vector<Paciente>& pacientes, ArchivosActivos& archivos) {
    Formateador::imprimirTablaPacientes(pacientes);
    Paciente* paciente = InputValidator::solicitarObjeto<Paciente>(
        "Ingrese el ID del paciente a seleccionar: ",
        pacientes,
        [](const Paciente& p) {
            return p.getID();
        }
    );

    int opcion = -1;
    do {
        std::cout << "\n--- Menú Paciente ---\n";
        std::cout << "1. Ver información personal\n";
        std::cout << "2. Consultar historial clínico\n";
        std::cout << "3. Modificar datos personales\n";
        std::cout << "0. Volver al menú principal\n";

        opcion = InputValidator::leerEnteroConsola("Seleccione una opción: ");
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            Formateador::imprimirEncabezadoPacientes();
            Formateador::imprimirRegistro(*paciente);
            break;

        case 2:
            Formateador::imprimirHistorialMedico(paciente->cargarHistorial());
            std::cout << "\nPresione enter para continuar...";
            std::cin.get();
            Formateador::limpiarPantalla();
            break;

        case 3: {
            std::string nuevaDireccion;
            std::cout << "Ingrese nueva dirección: ";
            std::getline(std::cin, nuevaDireccion);

            int nuevaEdad = InputValidator::leerEnteroConsola("Ingrese nueva edad: ");

            paciente->modificarDatos(nuevaDireccion, nuevaEdad);
            Archivo::guardarPacientes(pacientes, archivos.pacientes);
            std::cout << "Datos modificados exitosamente.\n";
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