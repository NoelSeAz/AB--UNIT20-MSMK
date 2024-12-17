#ifndef ARCHIVO_HPP
#define ARCHIVO_HPP

#include <string>
#include <vector>
#include "Paciente.hpp"
#include "Medico.hpp"
#include "Cita.hpp"
#include "HistorialMedico.hpp"

class Archivo {
public:
    // Guardar datos en archivos
    static void guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& archivo);
    static void guardarMedicos(const std::vector<Medico>& medicos, const std::string& archivo);
    static void guardarCitas(const std::vector<Cita>& citas, const std::string& archivo);
    static void guardarHistorialMedico(const HistorialMedico& historial);

    // Cargar datos desde archivos
    static std::vector<Paciente> cargarPacientes(const std::string& archivo);
    static std::vector<Medico> cargarMedicos(const std::string& archivo);
    static std::vector<Cita> cargarCitas(const std::string& archivo);
    static void cargarHistorialMedico(HistorialMedico& historial);

    // Realizar backup
    //static void realizarBackup(const std::string& directorioDestino);
};

#endif
