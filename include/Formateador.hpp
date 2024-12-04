#ifndef FORMATEADOR_HPP
#define FORMATEADOR_HPP

#include "Paciente.hpp"
#include "Medico.hpp"
#include "Cita.hpp"
#include <vector>

class Formateador {
public:
    // Métodos para imprimir encabezados
    static void imprimirEncabezadoPacientes();
    static void imprimirEncabezadoMedicos();
    static void imprimirEncabezadoCitas();

    // Métodos para imprimir registros individuales
    static void imprimirRegistro(const Paciente& paciente);
    static void imprimirRegistro(const Medico& medico);
    static void imprimirRegistro(const Cita& cita);

    // Métodos para imprimir tablas completas
    static void imprimirTablaPacientes(const std::vector<Paciente>& pacientes);
    static void imprimirTablaMedicos(const std::vector<Medico>& medicos);
    static void imprimirTablaCitas(const std::vector<Cita>& citas);

    // Limpieza de pantalla
    static void limpiarPantalla();
};

#endif
