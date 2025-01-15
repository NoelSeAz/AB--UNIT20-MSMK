#include "GestorEspecialidades.hpp"
#include "Archivo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// --- Clase Especialidad ---

Especialidad::Especialidad(int idParam, const std::string& nombreParam, const std::string& descripcionParam)
    : id(idParam), nombre(nombreParam), descripcion(descripcionParam) {
}

int Especialidad::getID() const {
    return id;
}

std::string Especialidad::getNombre() const {
    return nombre;
}

std::string Especialidad::getDescripcion() const {
    return descripcion;
}

void Especialidad::imprimir() const {
    std::cout << "ID: " << id << " | Nombre: " << nombre << " | Descripci�n: " << descripcion << "\n";
}

// --- Clase GestorEspecialidades ---

GestorEspecialidades::GestorEspecialidades(const std::vector<Especialidad>& especialidadesIniciales)
    : especialidades(especialidadesIniciales) {
}

std::vector<Especialidad> GestorEspecialidades::obtenerListaEspecialidades() const {
    return especialidades;
}

std::optional<Especialidad> GestorEspecialidades::buscarEspecialidadPorID(int id) const {
    for (const auto& esp : especialidades) {
        if (esp.getID() == id) {
            return esp;
        }
    }
    return std::nullopt;
}

void GestorEspecialidades::crearEspecialidad(const std::string& nombre, const std::string& descripcion) {
    int id = obtenerSiguienteID(); // Generar el pr�ximo ID
    especialidades.emplace_back(id, nombre, descripcion); // Crear y agregar la especialidad
    std::cout << "Especialidad a�adida exitosamente con ID " << id << ".\n";

    // Guardar en el archivo
    Archivo::guardarEspecialidades(especialidades, "./data/especialidades.csv");
}