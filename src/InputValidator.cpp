#include "InputValidator.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <optional>

// Obtener la fecha actual en formato "dd/mm/aaaa"
std::string InputValidator::obtenerFechaActual() {
    auto t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

// Validar el formato de una fecha (dd/mm/aaaa)
bool InputValidator::validarFormatoFecha(const std::string& fecha) {
    static const std::regex formato("^\\d{2}/\\d{2}/\\d{4}$");
    return std::regex_match(fecha, formato);
}

// Comparar dos fechas: -1 si fecha1 < fecha2, 0 si fecha1 == fecha2, 1 si fecha1 > fecha2
int InputValidator::compararFechas(const std::string& fecha1, const std::string& fecha2) {
    if (!validarFormatoFecha(fecha1) || !validarFormatoFecha(fecha2)) {
        throw std::invalid_argument("Formato de fecha no válido.");
    }

    // Convertir ambas fechas a std::tm
    std::tm tm1 = {}, tm2 = {};
    std::istringstream ss1(fecha1), ss2(fecha2);
    ss1 >> std::get_time(&tm1, "%d/%m/%Y");
    ss2 >> std::get_time(&tm2, "%d/%m/%Y");

    // Comparar usando std::mktime
    auto time1 = std::mktime(&tm1);
    auto time2 = std::mktime(&tm2);

    if (time1 < time2) return -1;
    if (time1 > time2) return 1;
    return 0;
}

// Validar que la fecha ingresada es futura (>= hoy)
bool InputValidator::esFechaFutura(const std::string& fecha) {
    return compararFechas(fecha, obtenerFechaActual()) >= 0;
}

// Validar que la fecha ingresada es pasada o actual (<= hoy)
bool InputValidator::esFechaPasadaOActual(const std::string& fecha) {
    return compararFechas(fecha, obtenerFechaActual()) <= 0;
}

// Validar que fechaComparada es igual o posterior a fechaReferencia
bool InputValidator::esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia) {
    return compararFechas(fechaComparada, fechaReferencia) >= 0;
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
        try {
            if (fechaInicio && compararFechas(fecha, *fechaInicio) < 0) {
                std::cout << "La fecha no puede ser menor que " << *fechaInicio << ". Intente nuevamente.\n";
                continue;
            }
            if (fechaFin && compararFechas(fecha, *fechaFin) > 0) {
                std::cout << "La fecha no puede ser mayor que " << *fechaFin << ". Intente nuevamente.\n";
                continue;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
            continue;
        }

        return fecha;
    }
}

// Validar que un rango de fechas es lógico
bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) {
    return compararFechas(fechaInicio, fechaFin) <= 0;
}
