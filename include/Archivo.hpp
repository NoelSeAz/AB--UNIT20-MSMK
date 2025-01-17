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

    // Cargar datos desde archivos usando una función genérica
    template <typename T>
    static void cargarDatos(std::vector<T>& contenedor, const std::string& mensaje,
        const std::string& archivoPorDefecto,
        std::vector<T>(*cargarFuncion)(const std::string&)){
        std::string archivo;
        std::cout << mensaje << " (por defecto: " << archivoPorDefecto << "): ";
        std::cin.ignore();
        std::getline(std::cin, archivo);

        if (archivo.empty()) {
            archivo = archivoPorDefecto;
        }

        try {
            std::vector<T> datos = cargarFuncion(archivo);
            contenedor = std::move(datos);
            std::cout << "Datos cargados exitosamente desde: " << archivo << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error al cargar el archivo: " << archivo << "\n";
            std::cerr << e.what() << "\n";
            std::cout << "No se realizaron cambios en los datos actuales.\n";
        }
    }

    //Cargar datos de archivos
    static std::vector<Paciente> cargarPacientes(const std::string& archivo);
    static std::vector<Medico> cargarMedicos(const std::string& archivo);
    static std::vector<Cita> cargarCitas(const std::string& archivo);
    static std::vector<Especialidad> cargarEspecialidades(const std::string& archivo);
    static void cargarHistorialMedico(HistorialMedico& historial);

    //Obtener ruta base
    static std::filesystem::path obtenerRutaBase(const std::string& nombreArchivo);
};

#endif
