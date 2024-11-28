#include "Archivo.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


// Guardar datos de pacientes
void Archivo::guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& archivo) {
    std::ofstream out(archivo);
    if (!out) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return;
    }

    for (const auto& paciente : pacientes) {
        out << paciente.getID() << "," << paciente.getNombre() << "," << paciente.getApellido() << ","
            << paciente.getDireccion() << "," << paciente.getEdad() << "\n";
    }
    out.close();
}

// Guardar datos de médicos
void Archivo::guardarMedicos(const std::vector<Medico>& medicos, const std::string& archivo) {
    std::ofstream out(archivo);
    if (!out) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return;
    }

    for (const auto& medico : medicos) {
        out << medico.getID() << "," << medico.getNombre() << "," << medico.getApellido() << ","
            << medico.getEspecialidad() << "," << medico.obtenerDisponibilidad() << "\n";
    }
    out.close();
}

// Guardar datos de citas
void Archivo::guardarCitas(const std::vector<Cita>& citas, const std::string& archivo) {
    std::ofstream out(archivo);
    if (!out) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return;
    }

    for (const auto& cita : citas) {
        out << cita.getCitaID() << ","
            << cita.getPacienteID() << ","
            << cita.getMedicoID() << ","
            << cita.getFecha() << ","
            << cita.getPrioridad() << "\n";
    }
    out.close();
}

// Cargar datos de pacientes
std::vector<Paciente> Archivo::cargarPacientes(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<Paciente> pacientes;

    if (!in) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return pacientes;
    }

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int id, edad;
        std::string nombre, apellido, direccion;

        // Leer cada campo utilizando el delimitador '|'
        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');
        std::getline(ss, direccion, ',');

        std::getline(ss, token, ',');
        edad = std::stoi(token);

        // Crear objeto Paciente y añadir al vector
        pacientes.emplace_back(id, nombre, apellido, direccion, edad);
    }

    return pacientes;
}

std::vector<Medico> Archivo::cargarMedicos(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<Medico> medicos;

    if (!in) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return medicos;
    }

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int id;
        std::string nombre, apellido, especialidad;
        bool disponibilidad;

        // Leer cada campo utilizando el delimitador '|'
        std::getline(ss, token, ',');
        id = std::stoi(token);

        
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');

        std::getline(ss, especialidad, ',');

        std::getline(ss, token, ',');
        disponibilidad = (token == "1");

        // Crear objeto Medico y añadir al vector
        medicos.emplace_back(id, nombre, apellido, especialidad, disponibilidad);
    }

    return medicos;
}

std::vector<Cita> Archivo::cargarCitas(const std::string& archivo) {
    std::ifstream in(archivo);
    std::vector<Cita> citas;

    if (!in) {
        std::cerr << "Error al abrir el archivo: " << archivo << "\n";
        return citas;
    }

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int citaID, pacienteID, medicoID, prioridad;
        std::string fecha;

        // Leer cada campo utilizando el delimitador ','
        std::getline(ss, token, ',');
        citaID = std::stoi(token);

        std::getline(ss, token, ',');
        pacienteID = std::stoi(token);

        std::getline(ss, token, ',');
        medicoID = std::stoi(token);

        std::getline(ss, fecha, ',');

        std::getline(ss, token, ',');
        prioridad = std::stoi(token);

        // Crear objeto Cita y añadir al vector
        citas.emplace_back(citaID, pacienteID, medicoID, fecha, prioridad);
    }

    return citas;
}
