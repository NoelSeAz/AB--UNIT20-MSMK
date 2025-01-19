#ifndef ARCHIVO_HPP
#define ARCHIVO_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include "Cita.hpp"
#include "HistorialMedico.hpp"
#include "GestorEspecialidades.hpp"
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <filesystem>

class Archivo {
public:
    // Guardar datos en archivos
    static void guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& archivo);
    static void guardarMedicos(const std::vector<Medico>& medicos, const std::string& archivo);
    static void guardarCitas(const std::vector<Cita>& citas, const std::string& archivo);
    static void guardarEspecialidades(const std::vector<Especialidad>& especialidades, const std::string& archivo);
    static void guardarHistorialMedico(const HistorialMedico& historial);

    //Cargar datos de archivos
    static std::vector<Paciente> cargarPacientes(const std::string& archivo);
    static std::vector<Medico> cargarMedicos(const std::string& archivo);
    static std::vector<Cita> cargarCitas(const std::string& archivo);
    static std::vector<Especialidad> cargarEspecialidades(const std::string& archivo);
    static void cargarHistorialMedico(HistorialMedico& historial);

    //Obtener ruta base
    static std::filesystem::path obtenerRutaBase(const std::string& nombreArchivo);

    template <typename T>
    static void cargarDatos(
        std::vector<T>& contenedor,
        const std::string& mensaje,
        std::string& archivo,
        std::function<std::vector<T>(const std::string&)> parser,
        bool interactivo = true
    )
    {
        // -- Parte 1: Determinar la ruta del archivo (interactivo o por defecto)
        std::string ruta = archivo;
        if (interactivo) {
            std::cout << mensaje <<": ";
            std::string inputUsuario;
            std::getline(std::cin, inputUsuario);

            if (!inputUsuario.empty()) {
                ruta = inputUsuario;
            }
        }

        // -- Parte 2: Intentar parsear el archivo con la función específica
        try {
            std::vector<T> datos = parser(ruta);
            contenedor = std::move(datos);
            archivo = ruta;

            std::cout << "Datos cargados exitosamente desde: " << ruta << "\n";
        }
        catch (const std::exception& e) {
            // Manejo de la excepción: mostramos error y conservamos los datos anteriores
            std::cerr << "Error al cargar el archivo: " << ruta << "\n";
            std::cerr << e.what() << "\n";
            std::cout << "No se realizaron cambios en los datos actuales.\n";
        }
    }

};

#endif
