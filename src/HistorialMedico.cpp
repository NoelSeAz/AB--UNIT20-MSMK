#include "HistorialMedico.hpp"
#include "Paciente.hpp"
#include "Archivo.hpp"
#include <iostream>
#include <iomanip>

// Constructor
HistorialMedico::HistorialMedico(const std::string& pacienteID) : pacienteID(pacienteID), notas("") {
    Archivo::cargarHistorialMedico(*this);
}

// Agregar diagnóstico
void HistorialMedico::agregarDiagnostico(const std::string& fecha, const std::string& detalle) {
    diagnosticos[fecha] = detalle;
    Archivo::guardarHistorialMedico(*this);
}

// Agregar prueba
void HistorialMedico::agregarPrueba(const std::string& fecha, const std::string& detalle) {
    pruebas[fecha] = detalle;
    Archivo::guardarHistorialMedico(*this);
}

// Agregar nota
void HistorialMedico::agregarNota(const std::string& nota) {
    notas += nota + "\n";
    Archivo::guardarHistorialMedico(*this);
}

//Agregar enfermedad crónica
void HistorialMedico::agregarEnfermedadCronica(const EnfermedadCronica& enfermedad) {
    enfermedadesCronicas.push_back(enfermedad);
    Archivo::guardarHistorialMedico(*this);
}

void HistorialMedico::asignarTratamiento(const std::string& tratamiento) {
    notas += "Tratamiento asignado: " + tratamiento + "\n";
    Archivo::guardarHistorialMedico(*this);
}

// Getters
const std::string& HistorialMedico::getPacienteID() const { return pacienteID; }
const std::map<std::string, std::string>& HistorialMedico::getDiagnosticos() const { return diagnosticos; }
const std::map<std::string, std::string>& HistorialMedico::getPruebas() const { return pruebas; }
const std::map<std::string, std::string>& HistorialMedico::getCitas() const { return citas; }
const std::string& HistorialMedico::getNotas() const { return notas; }
const std::vector<EnfermedadCronica>& HistorialMedico::getEnfermedadesCronicas() const {
    return enfermedadesCronicas;
}
