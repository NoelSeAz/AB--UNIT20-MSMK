#include "GestorMedicos.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include "Archivo.hpp"
#include "iostream"

void GestorMedicos::altaMedico(std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades) {
    std::string nombre, apellido;
    bool disponibilidad;

    // Recolección de datos básicos
    std::cout << "Ingrese Nombre: ";
    std::cin >> nombre;
    std::cout << "Ingrese Apellido: ";
    std::cin >> apellido;
    std::cout << "Disponibilidad (1 = Disponible, 0 = Ocupado): ";
    std::cin >> disponibilidad;

    // Selección de especialidad
    auto listaEspecialidades = gestorEspecialidades.obtenerListaEspecialidades();
    if (listaEspecialidades.empty()) {
        std::cerr << "Error: No hay especialidades registradas. No se puede dar de alta al médico.\n";
        return;
    }

    Formateador::imprimirTablaEspecialidades(listaEspecialidades);
    std::cout << "Seleccione el ID de la especialidad para el médico: ";
    int idEspecialidad;
    std::cin >> idEspecialidad;

    auto especialidad = gestorEspecialidades.buscarEspecialidadPorID(idEspecialidad);
    if (!especialidad) {
        std::cerr << "Error: Especialidad no encontrada. Intente nuevamente.\n";
        return;
    }

    // Crear y registrar el médico
    std::string ID = IDGenerator::generarID("M", nombre, apellido, {});
    medicos.emplace_back(ID, nombre, apellido, especialidad->getNombre(), disponibilidad);

    std::cout << "Médico registrado exitosamente:\n";
    Formateador::imprimirRegistro(medicos.back());
}

void GestorMedicos::bajaMedico(std::vector<Medico>& medicos, const std::string& id) {
    auto it = std::remove_if(medicos.begin(), medicos.end(), [&id](const Medico& m) { return m.getID() == id; });
    if (it != medicos.end()) {
        medicos.erase(it, medicos.end());
        std::cout << "Médico con ID " << id << " dado de baja exitosamente.\n";
        Archivo::guardarMedicos(medicos, "./data/archivo_medicos.txt");
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