#include "Archivo.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>


// Guardar datos de pacientes, medicos, citas, especialidades o historial médico
void Archivo::guardarPacientes(const std::vector<Paciente>& pacientes, const std::string& nombreArchivo) {
    try {
        // Obtener la ruta completa del archivo
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        // Abrir el archivo para escritura
        std::ofstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        // Escribir los datos de los pacientes
        for (const auto& paciente : pacientes) {
            archivo << paciente.getID() << ',' << paciente.getNombre() << ',' << paciente.getApellido() << ','
                << paciente.getDireccion() << ',' << paciente.getEdad() << '\n';
        }

        archivo.close();
        std::cout << "Pacientes guardados correctamente en: " << rutaArchivo << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al guardar pacientes: " << e.what() << "\n";
    }
}

void Archivo::guardarMedicos(const std::vector<Medico>& medicos, const std::string& nombreArchivo) {
    try {
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        std::ofstream outFile(rutaArchivo.string()); // Cambiamos "archivo" por "outFile"
        if (!outFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        for (const auto& medico : medicos) {
            outFile << medico.getID() << ',' << medico.getNombre() << ',' << medico.getApellido() << ','
                << medico.getEspecialidad() << ',' << medico.obtenerDisponibilidad() << '\n';
        }

        outFile.close();
        std::cout << "Médicos guardados correctamente en: " << rutaArchivo << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al guardar médicos: " << e.what() << "\n";
    }
}

void Archivo::guardarCitas(const std::vector<Cita>& citas, const std::string& nombreArchivo) {
    try {
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        std::ofstream outFile(rutaArchivo.string()); // Cambiamos "archivo" por "outFile"
        if (!outFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        for (const auto& cita : citas) {
            outFile << cita.getCitaIDHash() << ',' << cita.getCitaID() << ',' << cita.getPacienteID() << ','
                << cita.getMedicoID() << ',' << cita.getFecha() << ',' << cita.getPrioridad() << '\n';
        }

        outFile.close();
        std::cout << "Citas guardadas correctamente en: " << rutaArchivo << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al guardar citas: " << e.what() << "\n";
    }
}

void Archivo::guardarEspecialidades(const std::vector<Especialidad>& especialidades, const std::string& archivo) {
    try {
        std::filesystem::path rutaArchivo = obtenerRutaBase(archivo);

        std::ofstream outFile(rutaArchivo.string());
        if (!outFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        for (const auto& esp : especialidades) {
            outFile << esp.getID() << "," << esp.getNombre() << "," << esp.getDescripcion() << "\n";
        }

        outFile.close();
        std::cout << "Especialidades guardadas correctamente en: " << rutaArchivo << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error al guardar especialidades: " << e.what() << "\n";
    }
}

void Archivo::guardarHistorialMedico(const HistorialMedico& historial) {
    try {
        std::filesystem::path rutaArchivo = obtenerRutaBase("historial_" + historial.getPacienteID() + ".csv");

        std::ofstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
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
            archivo << enfermedad.getFechaDiagnostico() << "," << enfermedad.getNombre() << ","
                << enfermedad.getSeveridad() << "," << enfermedad.getTratamiento() << "\n";
        }

        archivo << "Notas\n" << historial.getNotas();

        archivo.close();
        std::cout << "Historial médico guardado correctamente en: " << rutaArchivo << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error en guardarHistorialMedico: " << e.what() << "\n";
    }
}

// Cargar datos de pacientes, medicos, citas, especialidades o historial médico
std::vector<Paciente> Archivo::cargarPacientes(const std::string& nombreArchivo) {
    try {
        // Obtener la ruta completa del archivo
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        std::ifstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        std::vector<Paciente> pacientes;
        std::string linea;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string id, nombre, apellido, direccion, edadStr;
            int edad;

            std::getline(ss, id, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, apellido, ',');
            std::getline(ss, direccion, ',');
            std::getline(ss, edadStr, ',');

            edad = std::stoi(edadStr);
            pacientes.emplace_back(id, nombre, apellido, direccion, edad);
        }

        return pacientes;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar pacientes: " << e.what() << "\n";
        return {};
    }
}

std::vector<Medico> Archivo::cargarMedicos(const std::string& nombreArchivo) {
    try {
        // Obtener la ruta completa del archivo
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        std::ifstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        std::vector<Medico> medicos;
        std::string linea;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string id, nombre, apellido, especialidad, disponibilidadStr;
            bool disponibilidad;

            std::getline(ss, id, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, apellido, ',');
            std::getline(ss, especialidad, ',');
            std::getline(ss, disponibilidadStr, ',');

            disponibilidad = (disponibilidadStr == "1");
            medicos.emplace_back(id, nombre, apellido, especialidad, disponibilidad);
        }

        return medicos;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar médicos: " << e.what() << "\n";
        return {};
    }
}

std::vector<Cita> Archivo::cargarCitas(const std::string& nombreArchivo) {
    try {
        // Obtener la ruta completa del archivo
        std::filesystem::path rutaArchivo = obtenerRutaBase(nombreArchivo);

        std::ifstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        std::vector<Cita> citas;
        std::string linea;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string citaIDHashStr, citaID, pacienteID, medicoID, fecha, prioridadStr;
            unsigned long citaIDHash;
            int prioridad;

            std::getline(ss, citaIDHashStr, ',');
            std::getline(ss, citaID, ',');
            std::getline(ss, pacienteID, ',');
            std::getline(ss, medicoID, ',');
            std::getline(ss, fecha, ',');
            std::getline(ss, prioridadStr, ',');

            citaIDHash = std::stoul(citaIDHashStr);
            prioridad = std::stoi(prioridadStr);

            citas.emplace_back(citaIDHash, citaID, pacienteID, medicoID, fecha, prioridad, false);
        }

        return citas;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar citas: " << e.what() << "\n";
        return {};
    }
}

std::vector<Especialidad> Archivo::cargarEspecialidades(const std::string& archivo) {
    try {
        // Obtener la ruta completa del archivo
        std::filesystem::path rutaArchivo = obtenerRutaBase(archivo);

        std::ifstream outFile(rutaArchivo.string());
        if (!outFile.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo.string());
        }

        std::vector<Especialidad> especialidades;
        std::string linea;

        while (std::getline(outFile, linea)) {
            std::istringstream ss(linea);
            std::string idStr, nombre, descripcion;
            int id;

            std::getline(ss, idStr, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, descripcion);

            id = std::stoi(idStr);
            especialidades.emplace_back(id, nombre, descripcion);
        }

        return especialidades;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al cargar especialidades: " << e.what() << "\n";
        return {};
    }
}

void Archivo::cargarHistorialMedico(HistorialMedico& historial) {
    try {
        std::filesystem::path rutaArchivo = obtenerRutaBase("historial_" + historial.getPacienteID() + ".csv");

        std::ifstream archivo(rutaArchivo.string());
        if (!archivo.is_open()) return;

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
    catch (const std::exception& e) {
        std::cerr << "Error al cargar historial médico: " << e.what() << "\n";
    }
}

//
std::filesystem::path Archivo::obtenerRutaBase(const std::string& nombreArchivo) {
    try {
        // Obtener el directorio actual
        std::filesystem::path rutaBase = std::filesystem::current_path();

        // Verificar si estamos en un subdirectorio como x64-debug, Release o Debug
        if (rutaBase.filename() == "x64-debug" || rutaBase.filename() == "Release" || rutaBase.filename() == "Debug") {
            rutaBase = rutaBase.parent_path().parent_path(); // Subir dos niveles
        }
        else {
            rutaBase = rutaBase.parent_path(); // Subir un nivel
        }

        rutaBase /= "data"; // Añadir la carpeta data

        // Crear el directorio si no existe
        if (!std::filesystem::exists(rutaBase)) {
            std::filesystem::create_directories(rutaBase);
        }

        rutaBase /= nombreArchivo; // Añadir el nombre del archivo
        return rutaBase;

    }
    catch (const std::exception& e) {
        std::cerr << "Error al obtener la ruta base: " << e.what() << "\n";
        throw; // Rethrow para permitir que el programa maneje el error si es necesario
    }
}
