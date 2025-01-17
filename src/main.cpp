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
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

// Funciones para los submenús
void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas, GestorEspecialidades& gestorEspecialidades);
void mostrarMenuMedico(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
void mostrarMenuPaciente(std::vector<Paciente>& pacientes);
void mostrarMenuGestionArchivos(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, std::vector<Cita>& citas);
void mostrarMenuListados(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos, const std::vector<Cita>& citas);
void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades);
void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos);
void mostrarMenuGestionEspecialidades(GestorEspecialidades& gestorEspecialidades);

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

    Formateador::limpiarPantalla();

    #ifdef _WIN32
        // Configurar la consola para UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    // Detectar el directorio raíz del proyecto
    std::filesystem::path rutaBase = std::filesystem::current_path();

    // Verificar si estamos en un subdirectorio como x64-debug y ajustar la ruta
    if (rutaBase.filename() == "x64-debug" || rutaBase.filename() == "Release" || rutaBase.filename() == "Debug") {
        rutaBase = rutaBase.parent_path().parent_path();
    }
    else {
        rutaBase = rutaBase.parent_path();
    }
    rutaBase /= "data";

    // Instanciar las estructuras principales
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;
    std::vector<Especialidad> especialidades;

    try {
        // Cargar los archivos predeterminados
        pacientes = Archivo::cargarPacientes((rutaBase / "archivo_pacientes.txt").string());
        medicos = Archivo::cargarMedicos((rutaBase / "archivo_medicos.txt").string());
        citas = Archivo::cargarCitas((rutaBase / "archivo_citas.txt").string());
        especialidades = Archivo::cargarEspecialidades((rutaBase / "especialidades.csv").string());
        std::cout << "Archivos predeterminados cargados correctamente.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar archivos: " << e.what() << "\n";
        std::cerr << "Por favor, asegúrese de que los archivos existan en la carpeta 'data/'.\n";
        return 1;
    }

    GestorEspecialidades gestorEspecialidades(especialidades);

    // Menú principal
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
            mostrarMenuAdministrador(pacientes, medicos, citas, gestorEspecialidades);
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

void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos,
    std::vector<Cita>& citas, GestorEspecialidades& gestorEspecialidades) {
    int opcion;
    do {
        std::cout << "\n--- Menú Administrador ---\n";
        std::cout << "1. Gestión de Archivos\n";
        std::cout << "2. Ver Listados\n";
        std::cout << "3. Alta y Baja de Registros\n";
        std::cout << "4. Gestión de Citas\n";
        std::cout << "5. Gestionar Especialidades\n";
        std::cout << "0. Volver al Menú Principal\n";
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
            mostrarMenuAltaBaja(pacientes, medicos, gestorEspecialidades);
            break;
        case 4:
            mostrarMenuGestionCitas(citas, pacientes, medicos);
            break;
        case 5:
            mostrarMenuGestionEspecialidades(gestorEspecialidades);
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

void mostrarMenuAltaBaja(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades) {
    int opcion;
    do {
        std::cout << "\n--- Alta y Baja de Registros ---\n";
        std::cout << "1. Dar de Alta a un Paciente\n";
        std::cout << "2. Dar de Alta a un Médico\n";
        std::cout << "3. Dar de Baja a un Paciente\n";
        std::cout << "4. Dar de Baja a un Médico\n";
        std::cout << "5. Cambiar Disponibilidad de un Médico\n";
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
            GestorMedicos::altaMedico(medicos, gestorEspecialidades);
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
        case 5: {
            // Solicitar el ID del médico
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

void mostrarMenuGestionCitas(std::vector<Cita>& citas, const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos) {
    int opcion;

    do {
        std::cout << "\n--- Gestión de Citas ---\n";
        std::cout << "1. Crear Cita\n";
        std::cout << "2. Cancelar Cita\n";
        std::cout << "3. Modificar Cita\n";
        std::cout << "4. Ver Citas por Paciente\n";
        std::cout << "5. Ver Citas por Médico\n";
        std::cout << "0. Volver al Menú Administrador\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cerr << "Error: Entrada inválida. Intente nuevamente.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1: {
            try {
                GestorCitas::crearCita(citas, pacientes, medicos);
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

            citaID = InputValidator::convertirAMayusculas(citaID);

            try {
                GestorCitas::cancelarCita(citas, citaID);
            }
            catch (const std::exception& e) {
                std::cerr << "Error al cancelar la cita: " << e.what() << "\n";
            }

            break;
        }

        case 3: {
            std::string citaID;

            // Solicitar ID de la cita
            std::cout << "Ingrese el ID de la cita a modificar: ";
            std::cin >> citaID;

            // Modificar la cita
            if (!GestorCitas::modificarCita(citas, citaID, medicos)) {
                std::cerr << "No se pudo modificar la cita. Verifique los datos ingresados.\n";
            }

            break;
        }

        case 4: {
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

void mostrarMenuGestionEspecialidades(GestorEspecialidades& gestorEspecialidades) {
    int opcion;
    do {
        std::cout << "\n--- Gestión de Especialidades ---\n";
        std::cout << "1. Listar Especialidades\n";
        std::cout << "2. Buscar Especialidad por ID\n";
        std::cout << "3. Añadir Nueva Especialidad\n";
        std::cout << "0. Volver al Menú Administrador\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
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
                std::cout << "Especialidad no encontrada.\n";
            }
            break;
        }

        case 3: { // Añadir una nueva especialidad
            std::string nombre, descripcion;

            std::cin.ignore();

            std::cout << "Ingrese el nombre de la especialidad: ";
            std::getline(std::cin, nombre);

            std::cout << "Ingrese una descripción para la especialidad: ";
            std::getline(std::cin, descripcion);

            gestorEspecialidades.crearEspecialidad(nombre, descripcion);
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

void mostrarMenuMedico(std::vector<Paciente>& pacientes, std::vector<Medico>& /*medicos*/) {
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
        std::cout << "3. Modificar datos personales\n";
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

        case 3: {
            std::string nuevaDireccion;
            int nuevaEdad;

            std::cin.ignore();
            std::cout << "Ingrese nueva dirección: ";
            std::getline(std::cin, nuevaDireccion);

            std::cout << "Ingrese nueva edad: ";
            std::cin >> nuevaEdad;

            paciente->modificarDatos(nuevaDireccion, nuevaEdad);
            Archivo::guardarPacientes(pacientes, "./data/archivo_pacientes.txt");
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