#ifndef GESTORMEDICOS_HPP
#define GESTORMEDICOS_HPP

#include "Medico.hpp"
#include "Archivo.hpp"
#include "Formateador.hpp"
#include "IDGenerator.hpp"
#include <vector>
#include <string>

class GestorMedicos {
public:
    static void altaMedico(std::vector<Medico>& medicos, const std::string& nombre, const std::string& apellido, const std::string& especialidad, bool disponibilidad);
    static void bajaMedico(std::vector<Medico>& medicos, const std::string& id);
    static Medico* buscarMedicoPorID(std::vector<Medico>& medicos, const std::string& id);
};

#endif
