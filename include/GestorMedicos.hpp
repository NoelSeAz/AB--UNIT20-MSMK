#ifndef GESTORMEDICOS_HPP
#define GESTORMEDICOS_HPP

#include "Medico.hpp"
#include "GestorEspecialidades.hpp"
#include <vector>
#include <string>

class GestorMedicos {
public:
    static void altaMedico(std::vector<Medico>& medicos, GestorEspecialidades& gestorEspecialidades);
    static void bajaMedico(std::vector<Medico>& medicos, const std::string& id);
    static Medico* buscarMedicoPorID(std::vector<Medico>& medicos, const std::string& id);
};

#endif
