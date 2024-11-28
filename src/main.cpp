#include <iostream>
#include <windows.h>
#include <Medico.hpp>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    // Crear un m�dico
    Medico medico1(1, "Ana", "G�mez", "Cardiolog�a", true);

    // Imprimir datos del m�dico
    medico1.imprimirDatos();

    // Cambiar disponibilidad
    medico1.cambiarDisponibilidad(false);
    std::cout << "\nNueva disponibilidad: " << (medico1.obtenerDisponibilidad() ? "Disponible" : "No disponible") << "\n";

    // Asignar una nueva especialidad
    medico1.asignarEspecialidad("Neurolog�a");
    medico1.imprimirDatos();

    // Agregar y mostrar citas
    medico1.agregarCita(101);
    medico1.agregarCita(102);
    medico1.mostrarCitas();

    return 0;
}