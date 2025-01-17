#ifndef CITA_HPP
#define CITA_HPP

#include <string>
#include <vector>

class Cita {
private:
    unsigned long citaIDHash;      // Identificador único de la cita (Hash)
    std::string citaID;            // Identificador único de la cita
    std::string pacienteID;        // ID del paciente asociado
    std::string medicoID;          // ID del médico asociado
    std::string fecha;             // Fecha de la cita (formato: "DD/MM/YYYY")
    int prioridad;                 // Prioridad de la cita (1: Urgente, 2: Normal)

    

public:
    // Constructor
    Cita(unsigned long citaIDHash, const std::string& citaID, const std::string& pacienteID,
        const std::string& medicoID, const std::string& fecha, int prioridad, bool validar = true);

    // Métodos para gestionar la cita
    void modificarCita(const std::string& nuevaFecha, int nuevaPrioridad);

    // Métodos para comparar citas
    static bool compararPorFecha(const Cita& a, const Cita& b);
    static bool compararPorPrioridad(const Cita& a, const Cita& b);

    // Getters
    unsigned long getCitaIDHash() const;
    std::string getCitaID() const;
    std::string getPacienteID() const;
    std::string getMedicoID() const;
    std::string getFecha() const;
    int getPrioridad() const;

    // Setters
    void setCitaIDHash(unsigned long nuevoHash);
};

#endif