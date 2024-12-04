#include "Paciente.hpp"
#include "Medico.hpp"
#include "Administrador.hpp"
#include "Formateador.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

// Funciones para los submenús
void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
void mostrarMenuMedico(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos);
void mostrarMenuPaciente(const std::vector<Paciente>& pacientes);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Datos iniciales
    std::vector<Paciente> pacientes = {
        Paciente("PJP0", "Juan", "Perez", "Calle 123", 30),
        Paciente("PAL0", "Ana", "Lopez", "Avenida Real", 25)
    };

    std::vector<Medico> medicos = {
        Medico("MLF0", "Luis", "Fernandez", "Cardiología", true),
        Medico("MMG0", "Maria", "Gomez", "Pediatría", false)
    };

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
            mostrarMenuAdministrador(pacientes, medicos);
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

void mostrarMenuAdministrador(std::vector<Paciente>& pacientes, std::vector<Medico>& medicos) {
    int opcion;
    do {
        std::cout << "\n--- Menú Administrador ---\n";
        std::cout << "1. Ver lista de pacientes\n";
        std::cout << "2. Ver lista de médicos\n";
        std::cout << "3. Dar de alta un paciente\n";
        std::cout << "4. Dar de alta un médico\n";
        std::cout << "5. Dar de baja un paciente\n";
        std::cout << "6. Dar de baja un médico\n";
        std::cout << "0. Volver al menú principal\n\n";
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
        case 3: {
            int edad;
            std::string nombre, apellido, direccion;
            std::cout << "Ingrese Nombre: "; std::cin >> nombre;
            std::cout << "Ingrese Apellido: "; std::cin >> apellido;
            std::cout << "Ingrese Dirección: "; std::cin.ignore(); std::getline(std::cin, direccion);
            std::cout << "Ingrese Edad: "; std::cin >> edad;
            Administrador::altaPaciente(pacientes, nombre, apellido, direccion, edad);
            break;
        }
        case 4: {
            std::string id, nombre, apellido, especialidad;
            bool disponibilidad;
            std::cout << "Ingrese ID: "; std::cin >> id;
            std::cout << "Ingrese Nombre: "; std::cin >> nombre;
            std::cout << "Ingrese Apellido: "; std::cin >> apellido;
            std::cout << "Ingrese Especialidad: "; std::cin.ignore(); std::getline(std::cin, especialidad);
            std::cout << "Disponibilidad (1 = Disponible, 0 = Ocupado): "; std::cin >> disponibilidad;
            Administrador::altaMedico(medicos, id, nombre, apellido, especialidad, disponibilidad);
            break;
        }
        case 5: {
            std::string idPaciente;
            std::cout << "Ingrese ID del paciente a eliminar: "; std::cin >> idPaciente;
            Administrador::bajaPaciente(pacientes, idPaciente);
            break;
        }
        case 6: {
            std::string idMedico;
            std::cout << "Ingrese ID del médico a eliminar: "; std::cin >> idMedico;
            Administrador::bajaMedico(medicos, idMedico);
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

void mostrarMenuMedico(const std::vector<Paciente>& pacientes, const std::vector<Medico>& medicos) {
    int opcion;
    do {
        std::cout << "\n--- Menú Médico ---\n";
        std::cout << "1. Ver lista de pacientes\n";
        std::cout << "2. Buscar paciente por ID\n";
        std::cout << "0. Volver al menú principal\n\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        Formateador::limpiarPantalla();

        switch (opcion) {
        case 1:
            Formateador::imprimirTablaPacientes(pacientes);
            break;
        case 2: {
            std::string id;
            std::cout << "Ingrese ID del paciente: "; std::cin >> id;
            auto paciente = Administrador::buscarPacientePorID(pacientes, id);
            if (paciente) {
                Formateador::imprimirEncabezadoPacientes();
                Formateador::imprimirRegistro(*paciente);
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

void mostrarMenuPaciente(const std::vector<Paciente>& pacientes) {
    std::string id;
    std::cout << "Ingrese su ID para acceder al sistema: ";
    std::cin >> id;

    auto paciente = Administrador::buscarPacientePorID(pacientes, id);
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
            paciente->mostrarHistorial();
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
