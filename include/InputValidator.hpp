#ifndef INPUT_VALIDATOR_HPP
#define INPUT_VALIDATOR_HPP

#include <string>
#include <vector>
#include <functional>
#include <optional>
#include <algorithm>
#include <iostream>

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

    // Validar que fechaComparada es igual o posterior a fechaReferencia
    static bool esFechaPosterior(const std::string& fechaComparada, const std::string& fechaReferencia);

    static bool validarRangoFechas(const std::string& fechaInicio, const std::string& fechaFin);

    // Solicitar una fecha con validación de formato y rango opcional
    static std::string solicitarFecha(const std::string& mensaje,
        const std::optional<std::string>& fechaInicio = std::nullopt,
        const std::optional<std::string>& fechaFin = std::nullopt);

    // Función plantilla para solicitar un ID genérico
    template <typename T>
    static std::string solicitarID(const std::string& mensaje,
        const std::vector<T>& objetos,
        const std::function<std::string(const T&)>& obtenerID)
    {
        std::string id;

        while (true) {
            std::cout << mensaje;
            std::cin >> id;

            id = convertirAMayusculas(id);

            auto it = std::find_if(objetos.begin(), objetos.end(),
                [&id, &obtenerID](const T& objeto) {
                    return obtenerID(objeto) == id;
                }
            );

            if (it != objetos.end()) {
                return id;
            }
            else {
                std::cerr << "Error: ID no encontrado. Intente nuevamente.\n";
            }
        }
    }

    // Convertir minúsculas a mayúsculas
    static std::string convertirAMayusculas(const std::string& input);

    // Validar valor prioridad
    static int solicitarPrioridad();
};

#endif
