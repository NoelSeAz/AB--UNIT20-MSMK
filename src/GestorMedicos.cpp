#include "GestorMedicos.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "Archivo.hpp"
#include "iostream"

void GestorMedicos::altaMedico(std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades) {
    std::string nombre, apellido;
    int disponibilidad;

    // Recolección de datos básicos
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

    // Selección de especialidad
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

    // Crear y registrar el médico
    std::string ID = IDGenerator::generarID("M", nombre, apellido, {});
    medicos.emplace_back(ID, nombre, apellido, especialidad->getNombre(), static_cast<bool>(disponibilidad));

    // Confirmación del registro
    std::cout << "Médico registrado exitosamente:\n";
    Formateador::imprimirRegistro(medicos.back());

    // Guardar los médicos en el archivo
    Archivo::guardarMedicos(medicos, "archivo_medicos.txt");
}

void GestorMedicos::bajaMedico(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [&id](const Medico& m) { return m.getID() == id; });
    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
        Archivo::guardarMedicos(medicos, "archivo_medicos.txt");
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