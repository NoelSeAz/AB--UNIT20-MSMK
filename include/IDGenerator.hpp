#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

#include <string>
#include <vector>

/// Clase encargada de generar IDs únicos para médicos, pacientes y citas.
class IDGenerator {
public:
    /**
     * @brief Genera un ID único basado en el tipo (M para médico, P para paciente),
     * las iniciales del nombre y apellido, y un sufijo numérico si es necesario.
     *
     * @param tipo Tipo de entidad ('M' para médico, 'P' para paciente).
     * @param nombre Nombre del individuo.
     * @param apellido Apellido del individuo.
     * @param idsExistentes Vector con los IDs ya existentes para verificar unicidad.
     * @return std::string ID único generado.
     */
    static std::string generarID(const std::string& tipo, const std::string& nombre, const std::string& apellido,
        const std::vector<std::string>& idsExistentes);

    /**
     * @brief Genera un ID único para una cita en formato C-PacienteID-MedicoID-FechaHash.
     *
     * @param pacienteID ID del paciente asociado.
     * @param medicoID ID del médico asociado.
     * @param fecha Fecha de la cita (en formato dd/mm/yyyy).
     * @return std::string ID único de la cita.
     */
    static std::string generarIDCita(const std::string& pacienteID, const std::string& medicoID, const std::string& fecha);

    /**
     * @brief Genera un hash único para una cita basado en sus datos.
     *
     * @param pacienteID ID del paciente asociado.
     * @param medicoID ID del médico asociado.
     * @param fecha Fecha de la cita (en formato dd/mm/yyyy).
     * @return unsigned long Hash único de la cita.
     */
    static unsigned long generarHashCita(const std::string& pacienteID, const std::string& medicoID, const std::string& fecha);

private:
    /**
     * @brief Extrae las iniciales del nombre y apellido.
     *
     * @param nombre Nombre del individuo.
     * @param apellido Apellido del individuo.
     * @return std::string Iniciales concatenadas (en mayúsculas).
     */
    static std::string extraerIniciales(const std::string& nombre, const std::string& apellido);
};

#endif
