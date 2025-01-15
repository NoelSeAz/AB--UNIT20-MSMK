#include "Archivo.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


// Guardar datos de pacientes, medicos, citas, especialidades o historial médico
void Archivo::guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& nombreArchivo) {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Error al guardar pacientes: " << e.what() << "\n";
    }
}

void Archivo::guardarMedicos(const std::vector<Medico>& medicos, const std::string& nombreArchivo) {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Error al guardar medicos: " << e.what() << "\n";
    }
}

void Archivo::guardarCitas(const std::vector<Cita>& citas, const std::string& nombreArchivo) {
    try {
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
    catch (const std::exception& e) {
        std::cerr << "Error al guardar citas: " << e.what() << "\n";
    }
}

void Archivo::guardarEspecialidades(const std::vector<Especialidad>& especialidades, const std::string& archivo) {
    std::ofstream outFile(archivo);
    if (!outFile.is_open()) {
        std::cerr << "Error al guardar el archivo de especialidades: " << archivo << "\n";
        return;
    }

    for (const auto& esp : especialidades) {
        outFile << esp.getID() << "," << esp.getNombre() << "," << esp.getDescripcion() << "\n";
    }

    outFile.close();
}

void Archivo::guardarHistorialMedico(const HistorialMedico& historial) {
    std::string rutaDirectorio = "data";
    std::string rutaArchivo = rutaDirectorio + "/historial_" + historial.getPacienteID() + ".csv";

    // Verificar si el directorio existe; si no, crearlo
    if (!std::filesystem::exists(rutaDirectorio)) {
        try {
            std::filesystem::create_directory(rutaDirectorio);
        }
        catch (const std::exception& e) {
            std::cerr << "Error al crear el directorio 'data': " << e.what() << "\n";
            return;
        }
    }

    // Abrir el archivo para guardar
    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar historial médico: " << rutaArchivo << "\n";
        return;
    }

    // Escribir contenido en el archivo
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
        archivo << enfermedad.getFechaDiagnostico() << "," << enfermedad.getNombre() << ","
            << enfermedad.getSeveridad() << "," << enfermedad.getTratamiento() << "\n";
    }

    archivo << "Notas\n" << historial.getNotas();

    archivo.close();
    std::cout << "Historial médico guardado correctamente en: " << rutaArchivo << "\n";
}

// Cargar datos de pacientes, medicos, citas, especialidades o historial médico
std::vector<Paciente> Archivo::cargarPacientes(const std::string& archivo) {
    std::ifstream in(archivo);
    if (!in) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    std::vector<Paciente> pacientes;

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        int edad;
        std::string id, nombre, apellido, direccion;

        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');
        std::getline(ss, direccion, ',');

        std::getline(ss, token, ',');
        edad = std::stoi(token);

        pacientes.emplace_back(id, nombre, apellido, direccion, edad);
    }

    return pacientes;
}

std::vector<Medico> Archivo::cargarMedicos(const std::string& archivo) {
    std::ifstream in(archivo);
    if (!in) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    std::vector<Medico> medicos;

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        std::string id, nombre, apellido, especialidad;
        bool disponibilidad;

        std::getline(ss, id, ',');
        
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');

        std::getline(ss, especialidad, ',');

        std::getline(ss, token, ',');
        disponibilidad = (token == "1");

        medicos.emplace_back(id, nombre, apellido, especialidad, disponibilidad);
    }

    return medicos;
}

std::vector<Cita> Archivo::cargarCitas(const std::string& archivo) {
    std::ifstream in(archivo);
    if (!in) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    std::vector<Cita> citas;

    std::string linea;
    while (std::getline(in, linea)) {
        std::istringstream ss(linea);
        std::string token;

        std::string citaIDHashStr, citaID, pacienteID, medicoID, fecha;
        int prioridad;

        std::getline(ss, citaIDHashStr, ',');
        std::getline(ss, citaID, ',');
        std::getline(ss, pacienteID, ',');
        std::getline(ss, medicoID, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, token, ',');

        try {
            unsigned long citaIDHash = std::stoul(citaIDHashStr);
            prioridad = std::stoi(token);                        

            citas.emplace_back(citaIDHash, citaID, pacienteID, medicoID, fecha, prioridad, false);
        }
        catch (const std::exception& e) {
            std::cerr << "Error al procesar la línea: " << linea << "\n";
            std::cerr << "Detalle del error: " << e.what() << "\n";
            continue;
        }
    }

    return citas;
}

std::vector<Especialidad> Archivo::cargarEspecialidades(const std::string& archivo) {
    std::vector<Especialidad> especialidades;
    std::ifstream inFile(archivo);

    if (!inFile.is_open()) {
        std::cerr << "Error al abrir el archivo de especialidades: " << archivo << "\n";
        return especialidades;
    }

    std::string linea;
    while (std::getline(inFile, linea)) {
        std::istringstream ss(linea);
        std::string idStr, nombre, descripcion;

        // Lee el ID como una cadena y conviértelo a entero
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, descripcion);

        int id = std::stoi(idStr); // Convierte el ID a entero

        if (!nombre.empty() && !descripcion.empty()) {
            especialidades.emplace_back(id, nombre, descripcion);
        }
    }

    inFile.close();
    return especialidades;
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
            ss.ignore();
            std::getline(ss, tratamiento);

            historial.agregarEnfermedadCronica(EnfermedadCronica(nombre, severidad, tratamiento, fecha));
        }
    }
}