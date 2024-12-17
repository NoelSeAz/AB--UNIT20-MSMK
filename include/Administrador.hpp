#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include "ICreadorDeCitas.hpp"
#include <vector>
#include <string>

// Clase estática para la gestión de pacientes y médicos
class GestorAdministrativo {
public:
    static void altaMedico(std::vector<Medico>& medicos, const std::string& nombre, const std::string& apellido,
        const std::string& especialidad, bool disponibilidad);

    static void bajaMedico(std::vector<Medico>& medicos, const std::string& id);

    static void altaPaciente(std::vector<Paciente>& pacientes, const std::string& nombre, const std::string& apellido,
        const std::string& direccion, int edad);

    static void bajaPaciente(std::vector<Paciente>& pacientes, const std::string& id);

    static Paciente* buscarPacientePorID(const std::vector<Paciente>& pacientes, const std::string& id);
    static Medico* buscarMedicoPorID(const std::vector<Medico>& medicos, const std::string& id);

    static void cargarPacientes(std::vector<Paciente>& pacientes, const std::string& archivo);
    static void cargarMedicos(std::vector<Medico>& medicos, const std::string& archivo);
    static void cargarCitas(std::vector<Cita>& citas, const std::string& archivo);
};

// Clase concreta para la gestión de citas
class AdministradorCitas : public ICreadorDeCitas {
public:
    void crearCita(std::vector<Cita>& citas, const std::string& pacienteID, const std::string& medicoID, const std::string& fecha, int prioridad) override;
    void cancelarCita(std::vector<Cita>& citas, const std::string& citaID);
    void modificarCita(std::vector<Cita>& citas, const std::string& citaID, const std::string& nuevaFecha, int nuevaPrioridad);
};

#endif
