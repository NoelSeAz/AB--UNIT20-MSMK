#ifndef HISTORIALMEDICO_HPP
#define HISTORIALMEDICO_HPP

#include "EnfermedadCronica.hpp"
#include <string>
#include <vector>
#include <map>

class HistorialMedico {
private:
    std::string pacienteID;                          // ID del paciente
    std::map<std::string, std::string> diagnosticos; // Fecha -> Diagnóstico
    std::map<std::string, std::string> pruebas;      // Fecha -> Pruebas realizadas
    std::map<std::string, std::string> citas;        // Fecha -> Resumen de cita
    std::string notas;                               // Notas generales del historial médico
    std::vector<EnfermedadCronica> enfermedadesCronicas;

public:
    // Constructor
    HistorialMedico(const std::string& pacienteID);

    // Métodos para agregar datos al historial
    void agregarDiagnostico(const std::string& fecha, const std::string& detalle);
    void agregarPrueba(const std::string& fecha, const std::string& detalle);
    void agregarNota(const std::string& nota);
    void agregarEnfermedadCronica(const EnfermedadCronica& enfermedad);
    void asignarTratamiento(const std::string& tratamiento);

    // Getters
    const std::string& getPacienteID() const;
    const std::map<std::string, std::string>& getDiagnosticos() const;
    const std::map<std::string, std::string>& getPruebas() const;
    const std::map<std::string, std::string>& getCitas() const;
    const std::string& getNotas() const;
    const std::vector<EnfermedadCronica>& getEnfermedadesCronicas() const;
    HistorialMedico& getHistorialMedico();
};

#endif
