#include "GestorMedicos.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "InputValidator.hpp"
#include "Archivo.hpp"
#include "iostream"

void GestorMedicos::altaMedico(std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos) {
    std::string nombre, apellido;
    int disponibilidad;

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

    std::cout << "Disponibilidad (1 = Disponible, 0 = Ocupado): ";
    if (!(std::cin >> disponibilidad) || (disponibilidad != 0 && disponibilidad != 1)) {
        std::cerr << "Error: Entrada inválida para disponibilidad. Debe ser 0 o 1.\n";
        return;
    }

    auto listaEspecialidades = gestorEspecialidades.obtenerListaEspecialidades();
    if (listaEspecialidades.empty()) {
        std::cerr << "Error: No hay especialidades registradas. No se puede dar de alta al médico.\n";
        return;
    }

    Formateador::imprimirTablaEspecialidades(listaEspecialidades);
    std::cout << "Seleccione el ID de la especialidad para el médico: ";
    int idEspecialidad;
    if (!(std::cin >> idEspecialidad)) {
        std::cerr << "Error: Entrada inválida para el ID de especialidad.\n";
        return;
    }

    auto especialidad = gestorEspecialidades.buscarEspecialidadPorID(idEspecialidad);
    if (!especialidad) {
        std::cerr << "Error: Especialidad no encontrada. Intente nuevamente.\n";
        return;
    }

    std::vector<std::string> idsExistentes;
    for (const auto& medico : medicos) {
        idsExistentes.push_back(medico.getID());
    }

    std::string ID = IDGenerator::generarID("M", nombre, apellido, idsExistentes);
    medicos.emplace_back(ID, nombre, apellido, especialidad->getNombre(), static_cast<bool>(disponibilidad));
    std::cout << "Médico registrado exitosamente:\n";
    Formateador::imprimirRegistro(medicos.back());
    Archivo::guardarMedicos(medicos, archivos.medicos);
}

void GestorMedicos::bajaMedico(std::vector<Medico>& medicos, const std::string& id, ArchivosActivos& archivos) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [&id](const Medico& m) { 
        return m.getID() == id; 
        });

    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
        try {
            Archivo::guardarMedicos(medicos, archivos.medicos);
            std::cout << "Archivo de médicos actualizado correctamente.";
        }
        catch (const std::exception& e) {
            std::cerr << "Error al guardar el archivo de médicos: " << e.what() << "\n";
        }
    }
    else {
        std::cerr << "Error: No se encontró un médico con el ID " << id << ".\n";
    }
}

Medico* GestorMedicos::buscarMedicoPorID(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::find_if(medicos.begin(), medicos.end(), [&id](const Medico& m) {
        return m.getID() == id;
        });
    return (it != medicos.end()) ? &(*it) : nullptr;
}

void GestorMedicos::cambiarDisponibilidad(std::vector<Medico>& medicos, const std::string& medicoID) {
    auto itMedico = std::find_if(medicos.begin(), medicos.end(), [&medicoID](const Medico& medico) {
        return medico.getID() == medicoID;
        });

    if (itMedico == medicos.end()) {
        std::cerr << "Error: Médico no encontrado con el ID proporcionado.\n";
        return;
    }

    std::cout << "Disponibilidad actual del médico: "
        << (itMedico->obtenerDisponibilidad() ? "Disponible" : "Ocupado") << ".\n";


    int nuevaDisponibilidad;
    while (true) {
        std::cout << "Ingrese la nueva disponibilidad (1 = Disponible, 0 = Ocupado): ";
        std::cin >> nuevaDisponibilidad;

        if (std::cin.fail() || !InputValidator::validarDisponibilidad(nuevaDisponibilidad)) {
            std::cerr << "Error: Disponibilidad inválida. Debe ser 1 (Disponible) o 0 (Ocupado).\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else {
            break;
        }
    }

    itMedico->cambiarDisponibilidad(nuevaDisponibilidad);
    std::cout << "Disponibilidad del médico con ID " << medicoID << " actualizada a "
        << (nuevaDisponibilidad ? "Disponible" : "Ocupado");
}

