#include "InputValidator.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <optional>

// Obtener la fecha actual en formato "dd/mm/aaaa"
std::string InputValidator::obtenerFechaActual(){
    auto t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

// Validar el formato de una fecha (dd/mm/aaaa)
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

// Solicitar una fecha con validación de formato y rango opcional
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

// Validar que un rango de fechas es lógico
bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) {
    if (!validarFormatoFecha(fechaInicio) || !validarFormatoFecha(fechaFin)) {
        return false; // Una o ambas fechas no son válidas
    }
    return fechaInicio <= fechaFin; // El rango debe ser lógico
}

// Validar que la fecha ingresada es futura (>= hoy)
bool InputValidator::esFechaFutura(const std::string& fecha) {
    if (!validarFormatoFecha(fecha)) {
        return false; // Formato inválido
    }

    // Convertir la fecha actual a std::tm
    std::string fechaActualStr = obtenerFechaActual();
    std::tm fechaActualTm = {};
    std::istringstream ssActual(fechaActualStr);
    ssActual >> std::get_time(&fechaActualTm, "%d/%m/%Y");
    if (ssActual.fail()) {
        throw std::runtime_error("Error al obtener la fecha actual."); // Esto no debería ocurrir
    }

    // Convertir la fecha ingresada a std::tm
    std::tm fechaIngresadaTm = {};
    std::istringstream ssIngresada(fecha);
    ssIngresada >> std::get_time(&fechaIngresadaTm, "%d/%m/%Y");
    if (ssIngresada.fail()) {
        return false; // Conversión fallida
    }

    // Comparar años
    if (fechaIngresadaTm.tm_year > fechaActualTm.tm_year) {
        return true; // Año futuro
    }
    else if (fechaIngresadaTm.tm_year == fechaActualTm.tm_year) {
        // Comparar meses dentro del mismo año
        if (fechaIngresadaTm.tm_mon > fechaActualTm.tm_mon) {
            return true; // Mes futuro
        }
        else if (fechaIngresadaTm.tm_mon == fechaActualTm.tm_mon) {
            // Comparar días dentro del mismo mes
            return fechaIngresadaTm.tm_mday > fechaActualTm.tm_mday;
        }
    }

    return false; // Fecha no futura
}


// Validar que la fecha ingresada es pasada o actual (<= hoy)
bool InputValidator::esFechaPasadaOActual(const std::string& fecha) {
    std::string fechaActual = obtenerFechaActual();
    return validarFormatoFecha(fecha) && fecha <= fechaActual;
}

// Validar que fechaComparada es igual o posterior a fechaReferencia
bool InputValidator::esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia) {
    // Validar el formato de ambas fechas
    if (!validarFormatoFecha(fechaComparada) || !validarFormatoFecha(fechaReferencia)) {
        return false; // Formato inválido
    }

    // Convertir fechaComparada a std::tm
    std::tm tmComparada = {};
    std::istringstream ssComparada(fechaComparada);
    ssComparada >> std::get_time(&tmComparada, "%d/%m/%Y");
    if (ssComparada.fail()) {
        return false; // Fallo en conversión
    }

    // Convertir fechaReferencia a std::tm
    std::tm tmReferencia = {};
    std::istringstream ssReferencia(fechaReferencia);
    ssReferencia >> std::get_time(&tmReferencia, "%d/%m/%Y");
    if (ssReferencia.fail()) {
        return false; // Fallo en conversión
    }

    // Comparar las fechas utilizando std::mktime
    return std::mktime(&tmComparada) >= std::mktime(&tmReferencia);
}
