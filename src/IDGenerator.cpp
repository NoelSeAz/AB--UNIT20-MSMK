#include "IDGenerator.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>

std::string IDGenerator::generarID(const std::string& tipo, const std::string& nombre, const std::string& apellido,
    const std::vector<std::string>& idsExistentes) {
    std::string iniciales = extraerIniciales(nombre, apellido);
    int sufijo = 0;
    std::string nuevoID;

    // Generar ID único
    do {
        std::ostringstream oss;
        oss << tipo << iniciales << sufijo;
        nuevoID = oss.str();
        sufijo++;
    } while (std::find(idsExistentes.begin(), idsExistentes.end(), nuevoID) != idsExistentes.end());

    return nuevoID;
}

std::string IDGenerator::extraerIniciales(const std::string& nombre, const std::string& apellido) {
    std::string iniciales;
    if (!nombre.empty()) iniciales += std::toupper(nombre[0]);
    if (!apellido.empty()) iniciales += std::toupper(apellido[0]);
    return iniciales;
}