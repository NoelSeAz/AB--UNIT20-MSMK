#ifndef GESTOR_ESPECIALIDADES_HPP
#define GESTOR_ESPECIALIDADES_HPP

#include <string>
#include <vector>
#include <optional>

class Especialidad {
private:
    int id;
    std::string nombre;
    std::string descripcion;

public:
    // Constructor
    Especialidad(int id, const std::string& nombre, const std::string& descripcion);

    // Getters
    int getID() const;
    std::string getNombre() const;
    std::string getDescripcion() const;

    // Mostrar información de la especialidad
    void imprimir() const;
};

class GestorEspecialidades {
private:
    std::vector<Especialidad> especialidades;
    int obtenerSiguienteID() const {
        if (especialidades.empty()) {
            return 1; // Primer ID si no hay especialidades
        }

        // Buscar el ID más alto en la lista de especialidades
        int maxID = 0;
        for (const auto& especialidad : especialidades) {
            if (especialidad.getID() > maxID) {
                maxID = especialidad.getID();
            }
        }
        return maxID + 1;
    }

public:
    // Constructor: carga especialidades al iniciar
    GestorEspecialidades(const std::vector<Especialidad>& especialidadesIniciales);

    // Métodos principales
    std::vector<Especialidad> obtenerListaEspecialidades() const;
    std::optional<Especialidad> buscarEspecialidadPorID(int id) const;
    void añadirEspecialidad(const std::string& nombre, const std::string& descripcion);
};

#endif