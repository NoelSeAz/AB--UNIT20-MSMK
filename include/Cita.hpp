#ifndef CITA_HPP
#define CITA_HPP

#include <string>
#include <vector>
#include <algorithm> // Para std::sort

class Cita {
private:
    int citaID;                    // Identificador único de la cita
    std::string pacienteID;        // ID del paciente asociado
    std::string medicoID;          // ID del médico asociado
    std::string fecha;             // Fecha de la cita (formato: "YYYY-MM-DD")
    int prioridad;                 // Prioridad de la cita (0: normal, 1: urgente)

    // Funciones privadas para comparar citas
    static bool compararPorFecha(const Cita& a, const Cita& b);
    static bool compararPorPrioridad(const Cita& a, const Cita& b);

public:
    // Constructor
    Cita(int citaID, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad);

    // Métodos para gestionar la cita
    void modificarCita(const std::string& nuevaFecha, int nuevaPrioridad);

    // Métodos estáticos para ordenar citas
    static void ordenarCitasPorFecha(std::vector<Cita>& citas);
    static void ordenarCitasPorPrioridad(std::vector<Cita>& citas);

    // Métodos de depuración
    void imprimirCita() const;

    // Getters
    int getCitaID() const;
    std::string getPacienteID() const;
    std::string getMedicoID() const;
    int getPrioridad() const;
    std::string getFecha() const;
};

#endif
