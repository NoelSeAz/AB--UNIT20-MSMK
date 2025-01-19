#ifndef FORMATEADOR_HPP
#define FORMATEADOR_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include "Cita.hpp"
#include "HistorialMedico.hpp"
#include "EnfermedadCronica.hpp"
#include "GestorEspecialidades.hpp"
#include <vector>

class Formateador {
public:
    //Encabezados Menús
    static void imprimirEncabezadoMenuMedico(const Paciente& paciente);

    // Métodos para imprimir encabezados
    static void imprimirEncabezadoPacientes();
    static void imprimirEncabezadoMedicos();
    static void imprimirEncabezadoCitas();
    static void imprimirEncabezadoEspecialidades();

    // Métodos para imprimir registros individuales
    static void imprimirRegistro(const Paciente& paciente);
    static void imprimirRegistro(const Medico& medico);
    static void imprimirRegistro(const Cita& cita);
    static void imprimirRegistro(const Especialidad& especialidad);

    // Métodos para imprimir tablas completas
    static void imprimirTablaPacientes(const std::vector<Paciente>& pacientes);
    static void imprimirTablaMedicos(const std::vector<Medico>& medicos);
    static void imprimirTablaCitas(const std::vector<Cita>& citas);
    static void imprimirTablaEspecialidades(const std::vector<Especialidad>& especialidades);

    // Imprimir Historial Médico
    static void imprimirHistorialMedico(const HistorialMedico& historial);
    static void imprimirEnfermedadCronica(const EnfermedadCronica& enfermedad);

    // Limpieza de pantalla
    static void limpiarPantalla();

    //Métodos para ajustar y ordenar el texto
    static std::vector<std::string> dividirTexto(const std::string& texto, size_t ancho);

};

#endif
