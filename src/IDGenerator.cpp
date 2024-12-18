#include "IDGenerator.hpp"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <numeric>

// M�todo para generar IDs �nicos para m�dicos y pacientes
std::string IDGenerator::generarID(const std::string& tipo, const std::string& nombre, const std::string& apellido,
    const std::vector<std::string>& idsExistentes) {
    std::string iniciales = extraerIniciales(nombre, apellido);
    int sufijo = 0;
    std::string nuevoID;

    // Generar ID �nico
    do {
        std::ostringstream oss;
        oss << tipo << iniciales << sufijo;
        nuevoID = oss.str();
        sufijo++;
    } while (std::find(idsExistentes.begin(), idsExistentes.end(), nuevoID) != idsExistentes.end());

    return nuevoID;
}

unsigned long IDGenerator::generarHashCita(const std::string& pacienteID, const std::string& medicoID, const std::string& fecha) {
    // Concatenar todos los valores en una cadena alfanum�rica
    std::string entrada = "C" + pacienteID + medicoID + fecha;

    // Generar hash simplificado (DJB2) y convertir a n�mero
    unsigned long hash = 5381;
    for (char c : entrada) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Retornar el hash
    return hash;
}

// M�todo para generar el ID �nico de una cita
std::string IDGenerator::generarIDCita(const std::string& pacienteID, const std::string& medicoID, const std::string& fecha) {
    // Crear una copia de la fecha y eliminar las barras "/"
    std::string fechaFormateada = fecha;
    fechaFormateada.erase(std::remove(fechaFormateada.begin(), fechaFormateada.end(), '/'), fechaFormateada.end());

    // Concatenar todos los valores en una cadena alfanum�rica
    std::string entrada = "C" + pacienteID + medicoID + fechaFormateada;

    return entrada;
}

// M�todo para extraer iniciales del nombre y apellido
std::string IDGenerator::extraerIniciales(const std::string& nombre, const std::string& apellido) {
    std::string iniciales;
    if (!nombre.empty()) iniciales += std::toupper(nombre[0]);
    if (!apellido.empty()) iniciales += std::toupper(apellido[0]);
    return iniciales;
}
