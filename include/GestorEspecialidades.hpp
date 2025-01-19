#ifndef GESTOR_ESPECIALIDADES_HPP
#define GESTOR_ESPECIALIDADES_HPP

#include "ArchivosActivos.hpp"

#include <string>
#include <vector>
#include <optional>

class Especialidad {
private:
    int id;
    std::string nombre;
    std::string descripcion;

public:
    Especialidad(int id, const std::string& nombre, const std::string& descripcion);

    int getID() const;
    std::string getNombre() const;
    std::string getDescripcion() const;

    void imprimir() const;
};

class GestorEspecialidades {
private:
    std::vector<Especialidad>& especialidades;
    int obtenerSiguienteID() const {
        if (especialidades.empty()) {
            return 1;
        }

        int maxID = 0;
        for (const auto& especialidad : especialidades) {
            if (especialidad.getID() > maxID) {
                maxID = especialidad.getID();
            }
        }
        return maxID + 1;
    }

public:
    explicit GestorEspecialidades(std::vector<Especialidad>& especialidadesIniciales);

    std::vector<Especialidad> obtenerListaEspecialidades() const;
    std::optional<Especialidad> buscarEspecialidadPorID(int id) const;
    void crearEspecialidad(const std::string& nombre, const std::string& descripcion, ArchivosActivos& archivos);
};

#endif