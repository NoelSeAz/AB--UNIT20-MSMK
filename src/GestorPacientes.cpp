#include "GestorPacientes.hpp"
#include "iostream"

void GestorPacientes::altaPaciente(std::vector<Paciente>& pacientes, ArchivosActivos& archivos) {
    std::string nombre, apellido, direccion;
    int edad;

    std::cout << "Ingrese Nombre: ";
    if (!(std::cin >> nombre)) {
        std::cerr << "Error: Entrada inválida para el nombre.\n";
        return;
    }

    std::cout << "Ingrese Apellido: ";
    if (!(std::cin >> apellido)) {
        std::cerr << "Error: Entrada inválida para el apellido.\n";
        return;
    }

    std::cin.ignore();
    std::cout << "Ingrese Dirección: ";
    std::getline(std::cin, direccion);

    std::cout << "Ingrese Edad: ";
    if (!(std::cin >> edad) || edad <= 0) {
        std::cerr << "Error: Edad inválida. Debe ser un número positivo.\n";
        return;
    }

    // Generar ID único para el paciente
    std::vector<std::string> idsExistentes;
    for (const auto& paciente : pacientes) {
        idsExistentes.push_back(paciente.getID());
    }

    std::string ID = IDGenerator::generarID("P", nombre, apellido, idsExistentes);
    pacientes.emplace_back(ID, nombre, apellido, direccion, edad);

    std::cout << "Paciente registrado exitosamente:\n";
    Formateador::imprimirRegistro(pacientes.back());

    // Guardar los pacientes en el archivo
    std::cout << "Archivo Pacientes:" << archivos.pacientes;
    Archivo::guardarPacientes(pacientes, archivos.pacientes);
}

void GestorPacientes::bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id, ArchivosActivos& archivos) {
    auto it = std::remove_if(pacientes.begin(), pacientes.end(), [&id](const Paciente& p) { 
        return p.getID() == id; 
        });

    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        std::cout << "Paciente con ID " << id << " dado de baja exitosamente.\n";
        try {
           Archivo::guardarPacientes(pacientes, archivos.pacientes);
            std::cout << "Archivo de pacientes actualizado correctamente.\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error al guardar el archivo de pacientes: " << e.what() << "\n";
        }
    }
    else {
        std::cerr << "Error: No se encontró un paciente con el ID " << id << ".\n";
    }
}

Paciente* GestorPacientes::buscarPacientePorID(std::vector<Paciente>& pacientes, const std::string& id) {
    auto it = std::find_if(pacientes.begin(), pacientes.end(), [&id](const Paciente& p) {
        return p.getID() == id;
        });
    return (it != pacientes.end()) ? &(*it) : nullptr;
}
