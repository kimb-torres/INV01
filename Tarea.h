#ifndef TAREA_H
#define TAREA_H
#include <string>

struct Tarea {
    int id;
    int idPadre;
    std::string nombre;
    int esfuerzo;
    bool completada;
};

struct ResumenTrabajo {
    int esfuerzoTotal;
    int esfuerzoPendiente;
    int tareas;

    ResumenTrabajo() {
        esfuerzoTotal = 0;
        esfuerzoPendiente = 0;
        tareas = 0;
    }
};

inline void SumarTrabajo(const Tarea &nTarea, ResumenTrabajo &rResumen) {
    rResumen.esfuerzoTotal += nTarea.esfuerzo;
    if (!nTarea.completada) rResumen.esfuerzoPendiente += nTarea.esfuerzo;
    rResumen.tareas++;
}

#endif
