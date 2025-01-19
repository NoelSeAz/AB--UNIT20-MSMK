#ifndef GESTORMEDICOS_HPP
#define GESTORMEDICOS_HPP

#include "Medico.hpp"
#include "GestorEspecialidades.hpp"
#include "ArchivosActivos.hpp"

#include <vector>
#include <string>

class GestorMedicos {
public:
    static void altaMedico(std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades, ArchivosActivos& archivos);
    static void bajaMedico(std::vector<Medico>& medicos, const std::string& id, ArchivosActivos& archivos);
    static Medico* buscarMedicoPorID(std::vector<Medico>& medicos, const std::string& id);
    static void cambiarDisponibilidad(std::vector<Medico>& medicos, const std::string& medicoID);

};

#endif
