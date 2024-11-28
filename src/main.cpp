#include <iostream>
#include <windows.h>
#include <Paciente.hpp>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    Paciente paciente1(1, "Juan", "Pérez", "Calle Falsa 123", 35);

    // Registrar historial clínico
    paciente1.registrarHistorial("Consulta inicial - 2024-11-26");
    paciente1.registrarHistorial("Examen de laboratorio - 2024-11-27");

    // Mostrar datos del paciente
    paciente1.imprimirDatos();

    // Mostrar historial clínico
    paciente1.mostrarHistorial();

    // Modificar datos personales
    paciente1.modificarDatos("Avenida Real 456", 36);

    // Mostrar datos actualizados
    paciente1.imprimirDatos();

    return 0;
}