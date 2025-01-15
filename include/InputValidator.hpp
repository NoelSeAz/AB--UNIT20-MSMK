#ifndef INPUT_VALIDATOR_HPP
#define INPUT_VALIDATOR_HPP

#include <string>
#include <optional>

class InputValidator {
public:
    // Obtener la fecha actual en formato "dd/mm/aaaa"
    static std::string obtenerFechaActual();

    // Validar el formato de una fecha (dd/mm/aaaa)
    static bool validarFormatoFecha(const std::string& fecha);

    // Comparar dos fechas: -1 si fecha1 < fecha2, 0 si fecha1 == fecha2, 1 si fecha1 > fecha2
    static int compararFechas(const std::string& fecha1, const std::string& fecha2);

    // Validar que la fecha ingresada es futura (>= hoy)
    static bool esFechaFutura(const std::string& fecha);

    // Validar que la fecha ingresada es pasada o actual (<= hoy)
    static bool esFechaPasadaOActual(const std::string& fecha);

    // Validar que una fecha es igual o posterior a otra
    static bool esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia);

    // Validar que un rango de fechas es lógico (inicio <= fin)
    static bool validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin);

    // Solicitar una fecha con validación de formato y rango opcional
    static std::string solicitarFecha(const std::string& mensaje, const std::optional<std::string>& fechaInicio = std::nullopt, const std::optional<std::string>& fechaFin = std::nullopt);
};

#endif