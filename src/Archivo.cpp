#include "Archivo.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


// Guardar datos de pacientes
void Archivo::guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar pacientes.");
    }

    for (const auto& paciente : pacientes) {
        archivo << paciente.getID() << ',' << paciente.getNombre() << ',' << paciente.getApellido() << ','
            << paciente.getDireccion() << ',' << paciente.getEdad() << '\n';
    }

    archivo.close();
}

// Guardar datos de médicos
void Archivo::guardarMedicos(const std::vector<Medico>& medicos, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar médicos.");
    }

    for (const auto& medico : medicos) {
        archivo << medico.getID() << ',' << medico.getNombre() << ',' << medico.getApellido() << ','
            << medico.getEspecialidad() << ',' << medico.obtenerDisponibilidad() << '\n';
    }

    archivo.close();
}

// Guardar datos de citas
void Archivo::guardarCitas(const std::vector<Cita>& citas, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar citas.");
    }

    for (const auto& cita : citas) {
        archivo << cita.getCitaIDHash() << ',' << cita.getCitaID() << ',' << cita.getPacienteID() << ',' << cita.getMedicoID() << ','
            << cita.getFecha() << ',' << cita.getPrioridad() << '\n';
    }

    archivo.close();
}

void Archivo::guardarHistorialMedico(const HistorialMedico& historial) {
    std::ofstream archivo("data/historial_" + historial.getPacienteID() + ".csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para guardar historial médico.\n";
        return;
    }

    archivo << "Diagnosticos\n";
    for (const auto& [fecha, detalle] : historial.getDiagnosticos()) {
        archivo << fecha << "," << detalle << "\n";
    }

    archivo << "Pruebas\n";
    for (const auto& [fecha, prueba] : historial.getPruebas()) {
        archivo << fecha << "," << prueba << "\n";
    }

    archivo << "Enfermedades\n";
    for (const auto& enfermedad : historial.getEnfermedadesCronicas()) {
        archivo << enfermedad.getFechaDiagnostico() << ","
            << enfermedad.getNombre() << ","
            << enfermedad.getSeveridad() << ","
            << enfermedad.getTratamiento() << "\n";
    }

    archivo << "Notas\n" << historial.getNotas();
    archivo.close();
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

        int edad;
        std::string id, nombre, apellido, direccion;

        // Leer cada campo utilizando el delimitador '|'
        std::getline(ss, id, ',');
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

// Cargar datos de médicos
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

        std::string id, nombre, apellido, especialidad;
        bool disponibilidad;

        // Leer cada campo utilizando el delimitador '|'
        std::getline(ss, id, ',');
        
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

//Cargar datos de citas
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

        std::string citaIDHash, citaID, pacienteID, medicoID, fecha;
        int prioridad;

        // Leer cada campo usando ',' como delimitador
        std::getline(ss, citaIDHash, ',');   // 1. Hash ID
        std::getline(ss, citaID, ',');       // 2. Cita ID
        std::getline(ss, pacienteID, ',');   // 3. Paciente ID
        std::getline(ss, medicoID, ',');     // 4. Medico ID
        std::getline(ss, fecha, ',');        // 5. Fecha
        std::getline(ss, token, ',');        // 6. Prioridad

        try {
            prioridad = std::stoi(token); 
        }
        catch (...) {
            std::cerr << "Error: La prioridad no es válida.\n";
            continue;
        }

        // Crear y agregar la cita al vector
        citas.emplace_back(citaIDHash, citaID, pacienteID, medicoID, fecha, prioridad, false);
    }

    return citas;
}

void Archivo::cargarHistorialMedico(HistorialMedico& historial) {
    std::ifstream archivo("data/historial_" + historial.getPacienteID() + ".csv");
    if (!archivo) return;

    std::string linea, seccion;

    while (std::getline(archivo, linea)) {
        if (linea == "Diagnosticos") {
            seccion = "Diagnosticos";
            continue;
        }
        if (linea == "Pruebas") {
            seccion = "Pruebas";
            continue;
        }
        if (linea == "Enfermedades") {
            seccion = "Enfermedades";
            continue;
        }
        if (linea == "Notas") {
            std::string notas;
            std::getline(archivo, notas, '\0');
            historial.agregarNota(notas);
            break;
        }

        std::istringstream ss(linea);
        std::string fecha, detalle;

        if (seccion == "Diagnosticos" || seccion == "Pruebas") {
            std::getline(ss, fecha, ',');
            std::getline(ss, detalle);

            if (seccion == "Diagnosticos") historial.agregarDiagnostico(fecha, detalle);
            else historial.agregarPrueba(fecha, detalle);
        }
        else if (seccion == "Enfermedades") {
            std::string nombre, tratamiento;
            int severidad;

            std::getline(ss, fecha, ',');
            std::getline(ss, nombre, ',');
            ss >> severidad;
            ss.ignore(); // Saltar la coma
            std::getline(ss, tratamiento);

            historial.agregarEnfermedadCronica(EnfermedadCronica(nombre, severidad, tratamiento, fecha));
        }
    }
}