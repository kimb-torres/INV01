#include <iostream>
#include <string>
#include "Tarea.h"
#include "Lista.h"
#include "Arbol.h"

int fallos = 0;

void Verificar(const std::string &descripcion, int obtenido, int esperado) {
    bool ok = (obtenido == esperado);
    if (!ok) fallos++;
    std::cout << (ok ? "[OK]    " : "[FALLO] ") << descripcion
              << " -> obtenido " << obtenido << ", esperado " << esperado << "\n";
}

template <typename Estructura>
int IdEncontrado(Estructura &e, int id) {
    Tarea *t = e.BuscarPorId(id);
    return t == nullptr ? -1 : t->id;
}

template <typename Estructura>
void Probar(const std::string &nombre, Estructura &e) {
    std::cout << "\n--- " << nombre << " ---\n";
    Verificar("buscar 1 (inicio)", IdEncontrado(e, 1), 1);
    Verificar("buscar 4 (dos niveles abajo)", IdEncontrado(e, 4), 4);
    Verificar("buscar 6 (final)", IdEncontrado(e, 6), 6);
    Verificar("buscar 99 (inexistente)", IdEncontrado(e, 99), -1);
    Verificar("pendiente de 1 (4 + 3)", e.EsfuerzoPendiente(1), 7);
    Verificar("pendiente de 2 (solo 4, el 5 esta completado)", e.EsfuerzoPendiente(2), 4);
    Verificar("pendiente de 5 (hoja)", e.EsfuerzoPendiente(5), 0);
    Verificar("pendiente de 6 (independiente)", e.EsfuerzoPendiente(6), 0);
    Verificar("pendiente de 99 (inexistente)", e.EsfuerzoPendiente(99), -1);

    e.ReiniciarContadores();
    e.BuscarPorId(1);
    std::cout << "contadores al buscar 1: visitados " << e.ObtenerVisitados()
              << ", comparaciones " << e.ObtenerComparaciones() << "\n";
    e.ReiniciarContadores();
    e.EsfuerzoPendiente(1);
    std::cout << "contadores en pendiente de 1: visitados " << e.ObtenerVisitados()
              << ", comparaciones " << e.ObtenerComparaciones() << "\n";
}

int main() {
    Tarea tareas[] = {
        {1, 0, "Proyecto 1", 0, false},
        {2, 1, "Entregable informe", 0, false},
        {3, 1, "Entregable video", 3, false},
        {4, 2, "Redactar metodologia", 4, false},
        {5, 2, "Redactar resumen", 2, true},
        {6, 0, "Quiz 1", 1, false}
    };

    Lista<Tarea> lista;
    Arbol<Tarea> arbol;
    for (int i = 0; i < 6; i++) {
        lista.AgregarFinal(tareas[i]);
        arbol.Insertar(tareas[i]);
    }

    Tarea huerfana = {9, 50, "Padre inexistente", 1, false};
    std::cout << "--- Construccion ---\n";
    Verificar("arbol: insertar con padre inexistente (0 = rechazada)", arbol.Insertar(huerfana), 0);

    Probar("Lista", lista);
    Probar("Arbol", arbol);

    std::cout << "\nFallos: " << fallos << "\n";
    return fallos == 0 ? 0 : 1;
}
