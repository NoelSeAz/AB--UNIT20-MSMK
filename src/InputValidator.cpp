#include "InputValidator.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <optional>

// Función auxiliar para obtener la fecha actual en formato "dd/mm/aaaa"
std::string obtenerFechaActual() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

// Validar formato de fecha
bool InputValidator::validarFormatoFecha(const std::string& fecha) {
    std::tm fechaTm = {};
    std::istringstream ss(fecha);

    // Intentamos parsear con el formato "dd/mm/aaaa"
    ss >> std::get_time(&fechaTm, "%d/%m/%Y");

    // Si el parseo falla, la fecha no es válida
    if (ss.fail()) {
        return false;
    }

    // Validar que no queden datos adicionales en el stream
    std::string resto;
    ss >> resto;
    return resto.empty();
}

// Solicitar fecha con validación
std::string InputValidator::solicitarFecha(const std::string& mensaje, const std::optional<std::string>& fechaInicio, const std::optional<std::string>& fechaFin) {
    std::string fecha;

    while (true) {
        std::cout << mensaje << " (dd/mm/aaaa): ";
        std::cin >> fecha;

        // Validar formato de fecha
        if (!validarFormatoFecha(fecha)) {
            std::cout << "Formato de fecha no válido. Intente nuevamente.\n";
            continue;
        }

        // Comparar con rango de fechas si es necesario
        if (fechaInicio && fecha < *fechaInicio) {
            std::cout << "La fecha no puede ser menor que " << *fechaInicio << ". Intente nuevamente.\n";
            continue;
        }
        if (fechaFin && fecha > *fechaFin) {
            std::cout << "La fecha no puede ser mayor que " << *fechaFin << ". Intente nuevamente.\n";
            continue;
        }

        return fecha;
    }
}

// Validar rango de fechas
bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) {
    if (!validarFormatoFecha(fechaInicio) || !validarFormatoFecha(fechaFin)) {
        return false; // Una o ambas fechas no son válidas
    }
    return fechaInicio <= fechaFin; // El rango debe ser lógico
}

// Validar fecha futura (para Cita)
bool InputValidator::esFechaFutura(const std::string& fecha) {
    std::string fechaActual = obtenerFechaActual();
    return validarFormatoFecha(fecha) && fecha >= fechaActual;
}

// Validar fecha en el pasado o actual (para Reporte)
bool InputValidator::esFechaPasadaOActual(const std::string& fecha) {
    std::string fechaActual = obtenerFechaActual();
    return validarFormatoFecha(fecha) && fecha <= fechaActual;
}
