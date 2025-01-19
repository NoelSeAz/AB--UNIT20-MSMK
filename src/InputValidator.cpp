#include "InputValidator.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <functional>

// Obtener la fecha actual en formato "dd/mm/aaaa"
std::string InputValidator::obtenerFechaActual() {
    auto t = std::time(nullptr);
    std::tm tm;

#if defined(_WIN32)
    localtime_s(&tm, &t);  // Windows
#else
    localtime_r(&t, &tm);  // Linux/Unix
#endif

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
        return -2;
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
    int resultado = compararFechas(fecha, obtenerFechaActual());
    if (resultado == -2) {
        std::cerr << "Error: Formato de fecha no válido en esFechaFutura.\n";
        return false;
    }
    return resultado >= 0;
}

// Validar que la fecha ingresada es pasada o actual (<= hoy)
bool InputValidator::esFechaPasadaOActual(const std::string& fecha) {
    int resultado = compararFechas(fecha, obtenerFechaActual());
    if (resultado == -2) {
        return false;
    }
    return resultado <= 0;
}

// Validar que fechaComparada es igual o posterior a fechaReferencia
bool InputValidator::esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia) {
    int resultado = compararFechas(fechaComparada, fechaReferencia);
    if (resultado == -2) {
        std::cerr << "Error: Formato de fecha no válido en esFechaPosterior.\n";
        return false;
    }
    return resultado >= 0;
}

// Validar que un rango de fechas es lógico
bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin) {
    return compararFechas(fechaInicio, fechaFin) <= 0;
}

//Validar entrada consola
int InputValidator::leerEnteroConsola(const std::string& mensaje){
    while (true) {
        std::cout << mensaje;
        std::string linea;
        if (!std::getline(std::cin, linea)) {
            std::cout << "\nNo se pudo leer la entrada (EOF o error). Saliendo...\n";
            return 0;
        }

        try {
            int valor = std::stoi(linea);
            return valor;
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error: Entrada inválida (no numérico). Intente nuevamente.\n";
        }
        catch (const std::out_of_range&) {
            std::cerr << "Error: Número fuera de rango. Intente nuevamente.\n";
        }
    }
}

// Solicitar una fecha con validación de formato y rango opcional
std::string InputValidator::solicitarFecha(const std::string& mensaje,
    const std::optional<std::string>& fechaInicio,
    const std::optional<std::string>& fechaFin) {
    std::string fecha;

    while (true) {
        try {
            std::cout << mensaje << " (DD/MM/AAAA): ";
            std::cin >> fecha;

            if (!validarFormatoFecha(fecha)) {
                throw std::invalid_argument("Formato de fecha no válido.");
            }

            // Validar rango de fechas si se especifica
            if (fechaInicio || fechaFin) {
                int resultadoInicio = fechaInicio ? compararFechas(fecha, *fechaInicio) : 0;
                int resultadoFin = fechaFin ? compararFechas(fecha, *fechaFin) : 0;

                if (resultadoInicio < 0) {
                    throw std::out_of_range("La fecha no puede ser anterior que " + *fechaInicio + ".");
                }
                if (resultadoFin > 0) {
                    throw std::out_of_range("La fecha no puede ser posterior que " + *fechaFin + ".");
                }
            }

            return fecha;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\nIntente nuevamente.\n";
        }
    }
}

std::string InputValidator::solicitarFechaPasadaOActual(const std::string& mensaje) {
    while (true) {
        std::string fecha = solicitarFecha(mensaje);

        if (!esFechaPasadaOActual(fecha)) {
            std::cerr << "Error: la fecha no puede ser futura. Intente nuevamente.\n";
            continue;
        }

        return fecha;
    }
}


//Convertir minúsculas a mayúsculas
std::string InputValidator::convertirAMayusculas(const std::string& input) {
    std::string resultado = input;
    for (char& c : resultado) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return resultado;
}

//Validar valor prioridad
int InputValidator::solicitarPrioridad() {
    int prioridad;

    while (true) {
        std::cout << "Ingrese la prioridad de la cita (1 = Urgente, 2 = Normal): ";
        std::cin >> prioridad;

        if (std::cin.fail() || (prioridad != 1 && prioridad != 2)) {
            std::cerr << "Error: Prioridad inválida. Debe ser 1 (Urgente) o 2 (Normal).\n";
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(1000, '\n'); // Descarta la entrada inválida
        }
        else {
            return prioridad; // Valor válido
        }
    }
}

bool InputValidator::validarDisponibilidad(int disponibilidad) {
    return disponibilidad == 0 || disponibilidad == 1;
}
