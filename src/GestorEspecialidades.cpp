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
    std::cout << "ID: " << id << " | Nombre: " << nombre << " | Descripción: " << descripcion << "\n";
}

// --- Clase GestorEspecialidades ---

GestorEspecialidades::GestorEspecialidades(std::vector<Especialidad>& especialidadesIniciales)
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

void GestorEspecialidades::crearEspecialidad(const std::string& nombre, const std::string& descripcion, ArchivosActivos& archivos) {
    int id = obtenerSiguienteID();
    especialidades.emplace_back(id, nombre, descripcion);
    std::cout << "Especialidad creada exitosamente con ID " << id << ".\n";

    Archivo::guardarEspecialidades(especialidades, archivos.especialidades);
}