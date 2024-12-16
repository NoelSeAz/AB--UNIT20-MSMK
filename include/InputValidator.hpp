#ifndef INPUTVALIDATOR_HPP
#define INPUTVALIDATOR_HPP

#include <string>
#include <optional>
#include <chrono>

class InputValidator {
public:
    // Validar entrada de números enteros
    static int solicitarNumero(const std::string& mensaje, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());

    // Validar entrada de cadenas (solo letras y espacios)
    // static std::string solicitarCadena(const std::string& mensaje, bool permitirEspacios = true);

    // Validar valores booleanos
    // static bool solicitarBooleano(const std::string& mensaje);

    // Obtener la fecha actual en formato "dd/mm/aaaa"
    static std::string obtenerFechaActual();

    // Valida el formato de fecha en "dd/mm/aaaa"
    static bool validarFormatoFecha(const std::string& fecha);

    //Solicitar una fecha con validación de formato y rango opcional
    static std::string solicitarFecha(const std::string& mensaje,
        const std::optional<std::string>& fechaInicio = std::nullopt,
        const std::optional<std::string>& fechaFin = std::nullopt);

    // Validar que un rango de fechas es lógico
    static bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin);

    //Validar que la fecha ingresada es futura (>= hoy)
    static bool InputValidator::esFechaFutura(const std::string& fecha);

    // Validar que la fecha ingresada es pasada o actual (<= hoy)
    static bool esFechaPasadaOActual(const std::string& fecha);

    // Validar que fechaComparada es igual o posterior a fechaReferencia
    static bool esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia);
};

#endif
