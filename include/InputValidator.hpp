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

    //
    static std::string obtenerFecha();

    // Valida el formato de fecha en "dd/mm/aaaa"
    static bool validarFormatoFecha(const std::string& fecha);

    //
    static std::string InputValidator::solicitarFecha(const std::string& mensaje, const std::optional<std::string>& fechaInicio, const std::optional<std::string>& fechaFin);

    //
    static bool InputValidator::validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin);

    //
    static bool InputValidator::esFechaFutura(const std::string& fecha);

    //
    static bool InputValidator::esFechaPasadaOActual(const std::string& fecha);
};

#endif
