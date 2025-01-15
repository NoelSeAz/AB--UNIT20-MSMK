#ifndef ENFERMEDADCRONICA_HPP
#define ENFERMEDADCRONICA_HPP

#include <string>

class EnfermedadCronica {
private:
    std::string nombre;           // Nombre de la enfermedad
    int severidad;                // Nivel de severidad
    std::string tratamiento;      // Tratamiento actual
    std::string fechaDiagnostico; // Fecha del diagnóstico

public:
    // Constructor
    EnfermedadCronica(const std::string& nombre, int severidad, const std::string& tratamiento, const std::string& fechaDiagnostico);

    // Métodos
    std::string getNombre() const;
    int getSeveridad() const;
    std::string getTratamiento() const;
    std::string getFechaDiagnostico() const;

    void setTratamiento(const std::string& nuevoTratamiento);
};

#endif
